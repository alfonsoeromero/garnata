# Makefile - The Garnata Retrieval System
# Copyright (C) 2005, 2026 Alfonso E. Romero
# SPDX-License-Identifier: GPL-3.0-or-later
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <https://www.gnu.org/licenses/>.

#####################################################
# Makefile for the Garnata Retrieval System
# Alfonso E. Romero 
# <aromero@correo.ugr.es>
# July, 2005
#####################################################

#####################################################################
# Predefined vars
#####################################################################

CXX=g++
CPPFLAGS=-c -g -O3 -pipe -W -Wall -std=c++11 -pedantic
CCFLAGS=-c -g -O3 -pipe -std=c++11
COMPRESSION=./compression
INCLUDE=./include
OBJ=./obj
SRC=./src
BIN=./bin
LIB=./lib

#####################################################################
# Command to make an object file:

COMPILE = $(CXX) -I $(INCLUDE) $(CCFLAGS) -c

#####################################################################

ALL_PROGRAMS=addItem delItem getInfo insertWeightFile makeWeightFile queryIndex queryINEX makeIndex

ALL_LIBS=libcompress

makeIndex_OBJS=$(OBJ)/Collection.o $(OBJ)/NodeTree.o  $(OBJ)/porter_stemmer.o $(OBJ)/PorterStemmer.o \
$(OBJ)/QuadExtractor.o $(OBJ)/Quad.o $(OBJ)/QuadPool.o $(OBJ)/UnitWriter.o \
$(OBJ)/Index.o $(OBJ)/Unit.o $(OBJ)/Term.o $(OBJ)/Lexicon.o $(OBJ)/Occurrence.o \
$(OBJ)/OccurrenceFile.o $(OBJ)/IndexBuilder.o $(OBJ)/DTD.o \
$(OBJ)/DTDList.o $(OBJ)/Globals.o $(OBJ)/PositionFile.o $(OBJ)/GarnataMakeIndex.o\
$(OBJ)/makeIndex.o $(OBJ)/XMLAdditional.o $(OBJ)/XMLIndexer.o  $(OBJ)/Garnata.o

makeWeightFile_OBJS=$(OBJ)/Collection.o $(OBJ)/Index.o $(OBJ)/IndexReader.o \
$(OBJ)/Term.o $(OBJ)/Lexicon.o $(OBJ)/Globals.o $(OBJ)/Unit.o $(OBJ)/Occurrence.o\
$(OBJ)/Weight.o $(OBJ)/WeightBNRSD.o $(OBJ)/WeightBNRSD_norm.o $(OBJ)/makeWeightFile.o\
$(OBJ)/Garnata.o $(OBJ)/GarnataWeight.o $(OBJ)/DTDList.o\
$(OBJ)/DTD.o $(OBJ)/Triad.o $(OBJ)/TriadPool.o $(OBJ)/UnitReader.o $(OBJ)/UnitWriter.o $(OBJ)/WeightInserter.o

insertWeightFile_OBJS=$(OBJ)/Collection.o $(OBJ)/Index.o $(OBJ)/IndexReader.o $(OBJ)/Term.o\
$(OBJ)/Lexicon.o $(OBJ)/Occurrence.o $(OBJ)/Globals.o $(OBJ)/Unit.o\
$(OBJ)/Weight.o $(OBJ)/WeightBNRSD.o $(OBJ)/WeightBNRSD_norm.o $(OBJ)/insertWeightFile.o\
$(OBJ)/WeightInserter.o $(OBJ)/Garnata.o $(OBJ)/GarnataWeight.o $(OBJ)/Triad.o\
$(OBJ)/TriadPool.o $(OBJ)/DTDList.o $(OBJ)/DTD.o $(OBJ)/UnitWriter.o $(OBJ)/UnitReader.o

queryIndex_OBJS=$(OBJ)/queryIndex.o $(OBJ)/Query.o $(OBJ)/ProcessedQuery.o\
$(OBJ)/RetrievalModel.o $(OBJ)/_BNR-SD.o $(OBJ)/BNR-SD.o $(OBJ)/NodeResult.o $(OBJ)/Lexicon.o $(OBJ)/Term.o\
$(OBJ)/Occurrence.o $(OBJ)/Index.o $(OBJ)/IndexReader.o $(OBJ)/UnitReader.o\
$(OBJ)/Globals.o $(OBJ)/Garnata.o $(OBJ)/GarnataQuery.o $(OBJ)/Collection.o $(OBJ)/DTD.o\
$(OBJ)/DTDList.o $(OBJ)/Unit.o $(OBJ)/porter_stemmer.o $(OBJ)/PorterStemmer.o $(OBJ)/UnitCache.o\
$(OBJ)/NodeGroup.o $(OBJ)/NodeResult_SID.o $(OBJ)/SID.o $(OBJ)/NodeResult_CID.o $(OBJ)/CID.o\
$(OBJ)/NodeResult_ID.o $(OBJ)/ID.o 

queryINEX_OBJS=$(OBJ)/queryINEX.o $(OBJ)/Query.o $(OBJ)/ProcessedQuery.o\
$(OBJ)/RetrievalModel.o $(OBJ)/_BNR-SD.o $(OBJ)/BNR-SD.o $(OBJ)/NodeResult.o $(OBJ)/Lexicon.o $(OBJ)/Term.o\
$(OBJ)/Occurrence.o $(OBJ)/Index.o $(OBJ)/IndexReader.o $(OBJ)/UnitReader.o\
$(OBJ)/Globals.o $(OBJ)/Garnata.o $(OBJ)/GarnataQueryXML.o $(OBJ)/Collection.o $(OBJ)/DTD.o\
$(OBJ)/DTDList.o $(OBJ)/Unit.o $(OBJ)/porter_stemmer.o $(OBJ)/PorterStemmer.o $(OBJ)/UnitCache.o\
$(OBJ)/NodeGroup.o $(OBJ)/NodeResult_SID.o $(OBJ)/SID.o $(OBJ)/NodeResult_CID.o $(OBJ)/CID.o\
$(OBJ)/NodeResult_ID.o $(OBJ)/ID.o 

getInfo_OBJS=$(OBJ)/getInfo.o $(OBJ)/Collection.o $(OBJ)/Index.o $(OBJ)/Globals.o $(OBJ)/Garnata.o

delItem_OBJS=$(OBJ)/delItem.o $(OBJ)/Collection.o $(OBJ)/Index.o $(OBJ)/Globals.o $(OBJ)/Garnata.o

addItem_OBJS=$(OBJ)/addItem.o $(OBJ)/Collection.o $(OBJ)/Index.o $(OBJ)/Globals.o $(OBJ)/Garnata.o

#####################################################################

all: $(ALL_LIBS) $(ALL_PROGRAMS)

libcompress : $(COMPRESSION)/*.cpp
	make -f Makefile.compression

#####################################################################

# default rules

$(OBJ)/%.o : $(SRC)/%.cpp
	@echo 		Building file $@...
	@$(COMPILE) $< -o $@
	
##################################
# ======> main executables <======
##################################

makeIndex : $(makeIndex_OBJS)
	@echo - Executable $@
	@$(CXX) -o $(BIN)/makeIndex $(makeIndex_OBJS) -lxerces-c $(LIB)/libcompress.a

makeWeightFile : $(makeWeightFile_OBJS)
	@echo - Executable $@
	@$(CXX) -o $(BIN)/makeWeightFile $(makeWeightFile_OBJS) $(LIB)/libcompress.a

insertWeightFile : $(insertWeightFile_OBJS)
	@echo - Executable $@
	@$(CXX) -o $(BIN)/insertWeightFile $(insertWeightFile_OBJS) $(LIB)/libcompress.a

queryIndex : $(queryIndex_OBJS)
	@echo - Executable $@
	@$(CXX) -o $(BIN)/queryIndex $(queryIndex_OBJS) $(LIB)/libcompress.a
	
queryINEX : $(queryINEX_OBJS)
	@echo - Executable $@
	@$(CXX) -o $(BIN)/queryINEX $(queryINEX_OBJS) $(LIB)/libcompress.a

getInfo : $(getInfo_OBJS)
	@echo - Executable $@
	@$(CXX) -o $(BIN)/getInfo $(getInfo_OBJS)

delItem : $(delItem_OBJS)
	@echo - Executable $@
	@$(CXX) -o $(BIN)/delItem $(delItem_OBJS)

addItem :  $(addItem_OBJS)
	@echo - Executable $@
	@$(CXX) -o $(BIN)/addItem $^

#####################################################################

clean :
	@echo Deleting object files...
	@\rm $(OBJ)/*
	
#####################################################################


