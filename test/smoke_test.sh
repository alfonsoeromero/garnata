#!/usr/bin/env bash
#
# smoke_test.sh - The Garnata Retrieval System
# Copyright (C) 2005, 2026 Alfonso E. Romero
# SPDX-License-Identifier: GPL-3.0-or-later
#
# End-to-end smoke test: builds a tiny two-document collection, indexes
# it, computes and activates a weight set, and runs a few queries.
# Everything happens in a temporary HOME, so ~/.garnata is never touched.
#
# The last section also exercises delItem (weight sets and indexes).
#
# Usage: test/smoke_test.sh [path/to/bin]   (or simply: make test)

set -u

HERE="$(cd "$(dirname "$0")" && pwd)"
BIN="$(cd "${1:-$HERE/../bin}" && pwd)"
DATA="$HERE/data"

WORK="$(mktemp -d "${TMPDIR:-/tmp}/garnata-test.XXXXXX")"
trap 'rm -rf "$WORK"' EXIT

export HOME="$WORK/home"
GARNATA="$HOME/.garnata"
for d in collections indexes weight stopwords; do mkdir -p "$GARNATA/$d"; done
printf '0\n1\n' > "$GARNATA/conf_file"     # same as scripts/postInstall

COL="$WORK/collection/"
mkdir -p "$COL"
cp "$DATA"/book1.xml "$DATA"/book2.xml "$COL"
printf 'book1.xml\nbook2.xml\n' > "$WORK/files.txt"

failures=0
pass() { printf '  ok    %s\n' "$1"; }
fail() { printf '  FAIL  %s\n' "$1"; failures=$((failures + 1)); }

# run DESCRIPTION COMMAND... : checks the exit status, keeps the output in $OUT
run() {
  local desc="$1"; shift
  if OUT="$("$@" 2>&1)"; then pass "$desc"; else fail "$desc"; printf '%s\n' "$OUT" | sed 's/^/        /'; fi
}

# expect DESCRIPTION PATTERN : checks that $OUT matches PATTERN
expect() {
  if printf '%s\n' "$OUT" | grep -qE "$2"; then pass "$1"; else fail "$1"; printf '%s\n' "$OUT" | sed 's/^/        /'; fi
}

query() {  # query TERMS... : runs one query through queryIndex
  OUT="$(printf '%s\n# quit\n' "$*" | "$BIN/queryIndex" test idx stem=yes 2>&1)"
}

echo "Garnata smoke test (binaries in $BIN)"

echo "Setup"
run "install stopword list"   "$BIN/addItem" stopword "$DATA/stopwords.txt" english
run "register collection"     sh -c "echo 'Smoke test collection' | '$BIN/addItem' collection test '$WORK/files.txt' '$COL'"
run "list collections"        "$BIN/getInfo" collections
expect "collection is listed" '\+ test'

echo "Indexing"
run "build index (stemming)"  "$BIN/makeIndex" test idx english stem=yes
run "index information"       "$BIN/getInfo" index test idx
expect "21 units in total"    'Number of units \(total\): 21'
expect "12 final units"       'Number of final units: 12'

echo "Weights"
run "compute weight set"      "$BIN/makeWeightFile" test idx w_classic classic
run "activate weight set"     "$BIN/insertWeightFile" test idx w_classic

echo "Retrieval (BNR-SD)"
query trains
first="$(printf '%s\n' "$OUT" | grep -m1 '\.xml' | cut -f1,2)"
if [ "$first" = "$(printf 'book2.xml\t/book[1]/title[1]')" ]; then
  pass "'trains': best unit is the title of book2"
else
  fail "'trains': best unit is the title of book2 (got: $first)"
fi
if printf '%s\n' "$OUT" | grep -q '^book1\.xml'; then
  fail "'trains': must not match book1"
else
  pass "'trains': does not match book1"
fi
query networks
expect "'networks': matches book1 (stemmed)" '^book1\.xml'
expect "'networks': matches book2 (stemmed)" '^book2\.xml'
query structured retrieval
expect "'structured retrieval': retrieves the Retrieval chapter" '^book1\.xml[[:space:]]+/book\[1\]/chapter\[2\]'
query xylophone
expect "unknown term: no results" 'No documents matching'

echo "Maintenance"
run "compute a second weight set" "$BIN/makeWeightFile" test idx w_norm norm_max
run "delete the second weight set" sh -c "echo y | '$BIN/delItem' weight test idx w_norm"
if [ -e "$GARNATA/weight/test_idx_w_norm" ]; then fail "weight file is gone"; else pass "weight file is gone"; fi
run "index survives deleting a weight set" "$BIN/getInfo" index test idx
query trains
expect "index still answers queries" '^book2\.xml'
if echo y | "$BIN/delItem" weight test idx no_such_weight >/dev/null 2>&1; then
  fail "deleting a missing weight set fails"
else
  pass "deleting a missing weight set fails"
fi
run "declining confirmation keeps the index" sh -c "echo n | '$BIN/delItem' index test idx"
run "index still listed"      "$BIN/getInfo" index test idx
run "delete the index"        sh -c "echo y | '$BIN/delItem' index test idx"
if ls "$GARNATA/indexes/" | grep -q '^test_idx'; then fail "index files are gone"; else pass "index files are gone"; fi

echo
if [ "$failures" -eq 0 ]; then
  echo "All checks passed."
else
  echo "$failures check(s) failed."
  exit 1
fi
