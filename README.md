# Garnata

**An XML (structured document) information retrieval system based on probabilistic graphical models.**

Garnata is a C++ indexing and retrieval engine for collections of XML documents. Instead of returning whole documents, it retrieves the *structural units* (XML elements) that best answer a query, ranking them with retrieval models built on Bayesian networks (BNR-SD) and influence diagrams (SID, CID).

It was designed and written from scratch in 2005 by Alfonso E. Romero as his final-year project (*Proyecto Fin de Carrera*) in Computer Science at the University of Granada, under the supervision of Luis M. de Campos, with the collaboration of Juan M. Fernández-Luna and Juan F. Huete (research group *Uncertainty Treatment in Intelligent Systems*, TIC-103). It was later used as the experimental platform for the group's participations in the INEX evaluation campaigns (2006–2008) and as the basis of a search prototype for the session diaries of the Parliament of Andalusia.

> **Status:** research code from 2005–2008, ported to modern C++ (C++11, Xerces-C 3) in 2026. It builds without warnings on a current GCC and passes an end-to-end smoke test (`make test`). The original, untouched code is available as release [`v0.1`](https://github.com/alfonsoeromero/garnata/releases/tag/v0.1).

---

## Table of contents

- [Background](#background)
- [Features](#features)
- [Retrieval models](#retrieval-models)
- [Architecture](#architecture)
- [Repository layout](#repository-layout)
- [Building](#building)
- [Usage](#usage)
- [Known issues](#known-issues)
- [Publications](#publications)
- [Author and acknowledgements](#author-and-acknowledgements)
- [Third-party code](#third-party-code)
- [License](#license)

---

## Background

Classic information retrieval treats a document as an atomic unit. In structured (XML) collections, documents are trees of nested elements. Think of a book: it is divided into chapters, chapters into sections, sections into subsections, and those into paragraphs. For a given query, the most useful answer is often not the whole book but a particular section or paragraph. Structured retrieval therefore has to index both the text and the tree structure, and score every element at every level.

When the project started there was no freely licensed toolkit for this kind of work, so Garnata was designed from the ground up to:

- store arbitrarily large XML collections, possibly heterogeneous (several DTDs under one collection name), using compact on-disk structures;
- support content-only (CO) queries, with the storage model designed with content-and-structure (CAS) queries in mind;
- keep the retrieval model pluggable, so new models could be added on top of the same index;
- precompute and store several term-weighting schemes, and swap between them to run batteries of experiments without re-indexing.

The low-level design owes a great deal to Witten, Moffat and Bell's *Managing Gigabytes* ([see below](#further-reading)): the sort-based inversion algorithm, the compressed inverted files with variable-byte coding, and the general philosophy of keeping the lexicon in memory and the postings on disk all come from there, adapted to the structured case.

The code in this repository is a snapshot from around the end of 2006: it corresponds to the version used in the group's first INEX participation (2006). The extensions described in the later INEX papers (tag-type importance in 2007, non-linear utility models in 2008) are not included.

The full design (requirements, logical and physical levels, indexing and retrieval algorithms) is documented in the project report: [*Sistema de Recuperación de Información Estructurada para el Parlamento de Andalucía*](https://github.com/alfonsoeromero/website/blob/master/pdf/pfc.pdf) (A. E. Romero, University of Granada, 2005; in Spanish).

## Features

- **Structured indexing** of XML collections with a SAX parser (Xerces-C), keeping the full element tree and XPath-like routes for every unit.
- **Heterogeneous collections**: tag types are tracked per DTD, so documents following different DTDs can live in the same collection.
- **Inverted index over structural units**: postings map terms to the leaf units (elements that directly contain text) where they occur, with frequencies and positions stored in a separate file to enable proximity-based extensions.
- **Structural index**: for every unit, its path to the root and its contained units, so relevance can be propagated up the tree efficiently.
- **Compression** of index files with variable-byte coding (`compression/`).
- **Text processing**: stopword removal (with named, installable stopword lists) and optional Porter stemming (using Martin Porter's reference implementation), configurable per index.
- **Precomputed, swappable weight sets**: several weighting schemes can be stored for the same index and activated on demand.
- **Three retrieval models**: BNR-SD (Bayesian network), SID and CID (influence diagrams).
- **Interactive query shell** and an **INEX batch mode** that writes runs in the INEX submission XML format.
- **Collection management tools** to add, inspect and delete collections, indexes, stopword lists and weight files.

## Retrieval models

### BNR-SD (Bayesian Network Retrieval model for Structured Documents)

BNR-SD (Crestani, de Campos, Fernández-Luna and Huete, ECSQARU 2003; see [Models implemented](#models-implemented)) extends the BNR model of de Campos, Fernández-Luna and Huete to structured documents. The XML tree is turned upside down and used as the graph of a Bayesian network:

- **term nodes** `T` at the top;
- **basic units** `B` (elements that only contain text), whose parents are the terms they contain;
- **complex units** `S` (elements that contain other elements), whose parents are the units they contain.

Every node is a binary variable (relevant / not relevant). Conditional probabilities use a canonical additive model, so the posterior probability of relevance given a query `Q` can be computed exactly and cheaply:

```
p(b+ | Q) = Σ_{T ∈ Pa(B) \ Q} w(T,B)·p(t+)  +  Σ_{T ∈ Pa(B) ∩ Q} w(T,B)
p(s+ | Q) = Σ_{U ∈ Pa(S)} w(U,S)·p(u+ | Q)
```

Term-in-unit weights are normalised tf·idf values, and unit-in-unit weights are proportional to the share of the parent's "mass" that each child carries. The prior probability of a term is `p0 = 1/|T|`.

In the implementation, relevance is propagated from the leaf units containing query terms up to the root, accumulating `prod = w(T,U) · Π w(U_i, U_{i+1})` along each path, and every accumulator is finally mapped to `p0 + (1 − p0)·acc`. Units are then ranked by that posterior probability. Only the sub-forest of units reachable from the query terms is ever visited.

### SID and CID (influence-diagram models)

SID (*Simple Influence Diagram*) and CID (*Context-based Influence Diagram*), proposed by de Campos, Fernández-Luna and Huete (IPM 2004; see [Models implemented](#models-implemented)), add decision and utility nodes on top of the BNR-SD network, so that the system ranks units by the **expected utility of retrieving them** rather than by relevance probability alone. This lets the ranking take into account the overlap between nested elements (retrieving a section and also its paragraphs). SID uses four utility values (retrieve / not retrieve × relevant / not relevant); CID additionally conditions on the relevance of the containing unit and uses eight. The utility values are set in `src/GarnataQueryXML.cpp`.

As in the INEX papers, the expected utility of each unit is multiplied by a query-coverage factor, **nIdf**: the sum of the idfs of the query terms the unit contains (directly or through its contained units), divided by the sum of the idfs of all the query terms. It lies in [0, 1] and acts as a soft, idf-weighted AND, favouring units that cover more of the query. An unfinished variant that gives every unit the nIdf of its whole article is kept in `src/ID.cpp`, disabled unless `GARNATA_GLOBAL_NIDF` is defined.

### Weighting schemes

`makeWeightFile` can compute two schemes for an index:

- `classic`: normalised `tf(i,j) · idf(i)`;
- `norm_max`: normalised `(tf(i,j) / max_j tf(i,j)) · idf(i)`.

A `WeightBM25` class is also present in the source tree but is not wired into the build.

## Architecture

The design separates three levels: a **conceptual** level (collections, queries, results), a **data-structure** level (lexicon, inverted index, units, retrieval model) and a **physical** level (the files and caches that make it fast). The main physical structures are:

| Structure | Description | Location |
|---|---|---|
| Lexicon | Sorted array of terms with ids and pointers to postings, plus a meta-index for lookup by id | Memory |
| Occurrence file | Postings: for each term, `(unit, frequency, position pointer, weight)` | Disk |
| Position file | Positions of each term within each unit | Disk |
| Occurrence / descendant caches | In-memory caches of the most requested postings and root paths | Memory |
| Descendant and parent files | Path to the root of each leaf unit, and contained units of each inner unit | Disk |
| Unit file | Per-unit information (tag type, parent, position, size) | Disk |
| Direct index | Terms contained in each unit | Disk |
| Tag / DTD files | Tag-type identifiers and their DTD | Disk |
| Weight files | One file per precomputed weighting scheme | Disk |

Indexing follows a sort-based inversion adapted to structured documents: each file is parsed, units are given identifiers and tag types, leaf units emit `(term, unit, frequency, position pointer)` records to a temporary file, and that file is sorted in memory-sized runs, merged, and dumped as the compressed inverted file.

Key classes: `Garnata` (system and configuration), `Collection`, `Index`, `IndexBuilder` / `XMLIndexer` (indexing), `Lexicon`, `Term`, `Occurrence`, `Unit` / `UnitReader` / `UnitWriter` / `UnitCache`, `Weight` and its subclasses, `RetrievalModel` with `BNR_SD`, `SID` and `CID`, and the front-ends `GarnataQuery` / `GarnataQueryXML`.

## Repository layout

```
.
├── compression/          Variable-byte coder and compressed binary file I/O (built as lib/libcompress.a)
├── include/              Header files
├── src/                  Library sources and the command-line programs (addItem.cpp, makeIndex.cpp, ...)
├── scripts/postInstall   Creates the ~/.garnata working directory
├── test/                 Smoke test (smoke_test.sh), its data, and old test utilities
├── Makefile              Main build (programs)
├── Makefile.compression  Compression library
└── Makefile.test         Test programs
```

## Building

### Requirements

- GNU/Linux (or another Unix-like system), `make` and a C++11 compiler (tested with GCC 13 and 15)
- [Xerces-C++](https://xerces.apache.org/xerces-c/) 3.x, with its development headers:

```bash
sudo apt install libxerces-c-dev     # Debian / Ubuntu
sudo dnf install xerces-c-devel      # Fedora
```

### Build and test

```bash
make          # builds lib/libcompress.a and the programs into bin/
make test     # end-to-end smoke test (see below)
make clean    # removes the object files
```

`make test` runs `test/smoke_test.sh`: it indexes a two-document collection (`test/data/`), computes and activates a weight set, and checks the results of a few queries. It works in a temporary `HOME`, so your own `~/.garnata` is never touched.

### Original toolchain

Release `v0.1` contains the code exactly as it was in 2006, which targets a pre-C++11 compiler and Xerces-C 2.x. The changes needed to build it today (missing standard headers, two-phase template lookup, `inline` functions defined in `.cpp` files, the Xerces-C 3 API, deprecated function adaptors and so on) are described one by one in the commit history.

## Usage

All data lives under `~/.garnata/` (collections, indexes, weight files and stopword lists, plus a small configuration file).

### 1. Initialise the working directory

```bash
scripts/postInstall
```

Choose option 1 to create `~/.garnata`. (Option 2 is currently broken, see [Known issues](#known-issues); to keep the data elsewhere, create a symbolic link `~/.garnata` to your directory and run option 1's steps manually.)

### 2. Install a stopword list

```bash
bin/addItem stopword /path/to/stopwords.txt english
```

This copies the file into `~/.garnata/stopwords/english`. Indexes refer to stopword lists by this name.

### 3. Register a collection

Write a text file listing the XML files of the collection (whitespace-separated), then:

```bash
bin/addItem collection mycollection files.txt /path/to/xml/files
```

The program asks for a short description of the collection.

### 4. Build an index

```bash
bin/makeIndex mycollection myindex english stem=yes
```

Arguments: collection name, new index name, stopword list name (not its path), and whether to apply Porter stemming.

### 5. Compute and activate weights

```bash
bin/makeWeightFile   mycollection myindex w_classic classic    # or norm_max
bin/insertWeightFile mycollection myindex w_classic
```

`makeWeightFile` computes a weight set and registers it with the index; `insertWeightFile` makes it the active set used at query time. Several weight files can coexist for the same index, and you can switch between them without re-indexing.

### 6. Query interactively (BNR-SD)

```bash
bin/queryIndex mycollection myindex stem=yes
```

Any line not starting with `#` is treated as a query (a conjunction of the listed terms). Results are printed as `file name`, `XPath route` and `P(relevance)`. Lines starting with `#` are commands:

| Command | Effect |
|---|---|
| `# help` | Show help |
| `# set docs N` | Maximum number of units to return |
| `# set minimum X` | Minimum relevance value for a unit to be returned |
| `# set output FILE` | Also write results to `FILE` |
| `# set output none` | Stop writing to file |
| `# set console output on\|off` | Toggle console output |
| `# quit` | End the session |

Use the same `stem=` setting as when the index was built.

### 7. INEX batch runs

```bash
bin/queryINEX mycollection myindex stem=yes model=SID < topics.txt
```

`model` can be `BNR-SD`, `SID` or `CID`. The program reads one topic per line from standard input (`topic_id term term ...`) and writes a run in the INEX submission XML format to `salida_<MODEL>.xml`. The number of topics (111), the task (`Thorough`) and the model utilities are hard-coded for the INEX 2006 setup; adjust them in `src/queryINEX.cpp` and `src/GarnataQueryXML.cpp` for other campaigns.

### 8. Inspect and clean up

```bash
bin/getInfo collections                     # list collections
bin/getInfo collection mycollection         # details of a collection
bin/getInfo index mycollection myindex      # details of an index

bin/delItem collection mycollection         # deletes the collection and all its indexes
bin/delItem index mycollection myindex
bin/delItem stopword english
```

## Known issues

- **`delItem weight` is dangerous:** the argument parser maps the `weight` command to the *index* deletion branch, so `delItem weight COL INDEX FILE` removes the index named `INDEX` instead of the weight file. Do not use it until fixed (`src/delItem.cpp`, `processArgs`).
- **`scripts/postInstall`, option 2**, creates a link to the literal string `direct` instead of the directory entered (`$direct` is missing).
- `queryINEX` is hard-wired to the INEX 2006 setup (111 topics, *Thorough* task); see [INEX batch runs](#7-inex-batch-runs).
- `queryIndexXML.cpp`, `WeightBM25.cpp` and some test programs referenced by `Makefile.test` are not part of the main build, and some of them refer to headers or files that are not in the repository.
- Collection paths cannot contain spaces (they are read with `>>`).
- The positional information is stored but not used by the current retrieval models (no phrase or proximity queries), and CAS queries are not implemented in the query front-ends.
- Tuning parameters (cache sizes, lexicon size, buffer sizes) are compile-time constants in `src/Globals.cpp`.

### Fixed since v0.1

- **Ranking bug (top-k).** `partial_sort` was called with `vec.begin()` as the end of the range, so only the first `NUMDOCS` candidates, in processing order, were sorted and returned. With the INEX limit of 1500 results, any query matching more units than that (the usual case on the INEX Wikipedia collection) returned an essentially arbitrary subset of them. This is the bug that affected our INEX 2006 runs; it was fixed in later internal versions, but not in the snapshot published as `v0.1`.
- **Silent indexing bug with Xerces-C 3.** The SAX `characters()` handler no longer matched the Xerces-C 3 signature, so it would have compiled but never been called, producing indexes without text. All handler methods are now marked `override`.
- The unfinished global nIdf variant prevented the influence-diagram models from compiling; it is now disabled by default (see [SID and CID](#sid-and-cid-influence-diagram-models)).

## Publications

### Models implemented

The retrieval models in Garnata were proposed in the following papers:

- F. Crestani, L. M. de Campos, J. M. Fernández-Luna, J. F. Huete. *A Multi-layered Bayesian Network Model for Structured Document Retrieval.* ECSQARU 2003, LNCS 2711, pp. 74–86. **(BNR-SD)**
- L. M. de Campos, J. M. Fernández-Luna, J. F. Huete. *Using context information in structured document retrieval: an approach based on influence diagrams.* Information Processing & Management, 40(5), pp. 829–847, 2004. [doi:10.1016/j.ipm.2004.04.014](https://doi.org/10.1016/j.ipm.2004.04.014) **(SID and CID)**
- L. M. de Campos, J. M. Fernández-Luna, J. F. Huete. *Improving the Context-Based Influence Diagram Model for Structured Document Retrieval: Removing Topological Restrictions and Adding New Evaluation Methods.* ECIR 2005, LNCS 3408, pp. 215–229. [doi:10.1007/978-3-540-31865-1_16](https://doi.org/10.1007/978-3-540-31865-1_16) **(CID extension)**

### Publications about Garnata

Garnata is described in, or was used for, the following publications:

- L. M. de Campos, J. M. Fernández-Luna, J. F. Huete, A. E. Romero. *Un prototipo de motor de búsqueda para los Diarios de Sesiones del Parlamento de Andalucía basado en modelos gráficos probabilísticos.* TTIA 2005, pp. 37–44.
- L. M. de Campos, J. M. Fernández-Luna, J. F. Huete, A. E. Romero. *Garnata: An Information Retrieval System for Structured Documents based on Probabilistic Graphical Models.* IPMU 2006, Paris.
- L. M. de Campos, J. M. Fernández-Luna, J. F. Huete, A. E. Romero. *Influence Diagrams and Structured Retrieval: Garnata Implementing the SID and CID Models at INEX'06.* INEX 2006, LNCS 4518, pp. 165–177, 2007.
- L. M. de Campos, J. M. Fernández-Luna, J. F. Huete, A. E. Romero. *A flexible object-oriented system for teaching and learning structured IR.* TLIR'07 workshop, London, 2007.
- L. M. de Campos, J. M. Fernández-Luna, J. F. Huete, C. J. Martín-Dancausa, A. E. Romero. *The Garnata Information Retrieval System at INEX'07.* INEX 2007, LNCS 4862, pp. 57–69, 2008.
- L. M. de Campos, J. M. Fernández-Luna, J. F. Huete, A. E. Romero. *An Information Retrieval System for Parliamentary XML Documents based on Probabilistic Graphical Models.* In *Bayesian Belief Networks: A Practical Guide to Applications*, Wiley, 2008.
- L. M. de Campos, J. M. Fernández-Luna, J. F. Huete, C. J. Martín-Dancausa, A. E. Romero. *New Utility Models for the Garnata Information Retrieval System at INEX'08.* INEX 2008, LNCS 5631, pp. 39–45, 2009.

If you use Garnata in academic work, please cite the IPMU 2006 paper, together with the paper that introduced the model you use.

### Further reading

- I. H. Witten, A. Moffat, T. C. Bell. *Managing Gigabytes: Compressing and Indexing Documents and Images*, 2nd ed. Morgan Kaufmann, 1999. The main reference for Garnata's indexing and compression machinery, and highly recommended for anyone interested in how search engines work under the hood.

## Author and acknowledgements

Written by **Alfonso E. Romero** ([github.com/alfonsoeromero](https://github.com/alfonsoeromero)) at the Department of Computer Science and Artificial Intelligence, University of Granada.

Thanks to Luis M. de Campos (project supervisor), Juan M. Fernández-Luna (who defined the system requirements and advised on the implementation) and Juan F. Huete, and to the University of Granada, whose research initiation grant funded the original work.

## Third-party code

`src/porter_stemmer.cpp` contains Martin Porter's ANSI C reference implementation of the Porter stemming algorithm (Porter, 1980, *An algorithm for suffix stripping*, Program 14(3), pp. 130–137), compiled as C++ and with its entry point renamed to `porter_stem()`. According to its author, this code is free for any purpose, with terms never more restrictive than the BSD License; see [tartarus.org/martin/PorterStemmer](https://tartarus.org/martin/PorterStemmer/). It is not covered by Garnata's GPL notice. The C++ interface to it (`PorterStemmer.hpp` / `PorterStemmer.cpp`) is part of Garnata.

## License

Copyright (C) 2005, 2026 Alfonso E. Romero.

Garnata is free software: you can redistribute it and/or modify it under the terms of the [GNU General Public License](LICENSE) as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. This applies to all the code in the repository except for `src/porter_stemmer.cpp` (see [Third-party code](#third-party-code)).
