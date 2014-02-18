#--------------------------------------------------------------------------------
# Copyright(c) 2013-2014. 
# Dependable Networking and Computing (DNC) Lab in Wayne State University. 
# All rights reserved.
#---------------------------------------------------------------------------------
# Redistribution and use in source and binary forms, with or without modification,
# are permitted provided that the following conditions are met:
# 
# 1. Redistributions of source code must retain the above copyright notice, this
# list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice, 
# this list of conditions and the following disclaimer in the documentation and/or
# other materials provided with the distribution.
#
# 3. Neither the name of the DNC lab nor the names of its contributors may be used 
# to endorse or promote products derived from this software without specific prior 
# written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
# SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
# TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
# BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#--------------------------------------------------------------------------------
# Dependable Networking and Computing Lab
# Wayne State University
# Email: vinsight.dnc@gmail.com
#--------------------------------------------------------------------------------
# Name: makefile
# Function: facilitate the compleing the VInsight 
# Author: Yuehua Wang 
# Email: yuehua.research@gmail.com


CC=gcc
<<<<<<< HEAD
LDFLAGS=-loml2 -lpthread	-lexpat	-lXext	-lsqlite3	-lrt	-lgps	-lncurses	-ltinfo -lm	 
CFLAGS=-std=gnu99  -g 
OBJECTS=main.o
TARGET=vinsight
SERVER=viserver
OMLTRANS=vioml
WIMAXMEAS=viwimaxtool
INCLUDES=
LFLAGS=
PREFIX=/usr
DEPS_V=$(SOURCE_DIR)/config.h
DEPS_S=$(SOURCE_DIR)/serverside.h
DEPS_O=$(SOURCE_DIR)/omltransmission.h
FILES=$(SOURCE_DIR)/datacollection.c	$(SOURCE_DIR)/datatransmission.c	$(SOURCE_DIR)/experimentcontroller.c	$(SOURCE_DIR)/experimentengine.c	$(SOURCE_DIR)/healthmonitoring.c	$(SOURCE_DIR)/listentoserver.c	$(SOURCE_DIR)/resourcemanager.c
INSIGHT=$(SOURCE_DIR)/main.c
WIMAXTOOLS=$(SOURCE_DIR)/wimaxmeasurementtools.c
SOURCE_DIR=./


all:$(TARGET) $(SERVER) $(OMLTRANS) $(WIMAXMEAS)
$(TARGET):$(FILES) $(INSIGHT) $(DEPS_V)
	$(CC)	  $(FILES) $(INSIGHT)  $(DEPS_V) -o	$(TARGET)	$(LDFLAGS)	$(CFLAGS)

$(SERVER):$(SOURCE_DIR)/serverside.c	$(DEPS_S)
	$(CC)	$(SOURCE_DIR)/serverside.c	$(DEPS_S)	-o	$(SERVER)	$(LDFLAGS)	$(CFLAGS)

$(OMLTRANS):$(SOURCE_DIR)/omltransmission.c	$(DEPS_S)
	$(CC)	$(SOURCE_DIR)/omltransmission.c	$(DEPS_O)	-o	$(OMLTRANS)	$(LDFLAGS)	$(CFLAGS)


$(WIMAXMEAS):$(FILES) $(WIMAXTOOLS)	$(DEPS_V)
	$(CC) $(FILES) $(WIMAXTOOLS) $(DEPS_V)	-o	$(WIMAXMEAS)	$(LDFLAGS)	$(CFLAGS)
clean	:
	rm	-f	*.o	$(TARGET) $(SERVER) $(OMLTRANS) $(WIMAXMEAS)
install	: 
	@echo  "\n***** Installing *****"
	cp -f $(TARGET) $(PREFIX)/bin/$(TARGET)
	cp -f $(SERVER) $(PREFIX)/bin/$(SERVER)
	cp -f $(VIOML) $(PREFIX)/bin/$(VIOML)
	cp -f $(VIOML) $(PREFIX)/bin/$(WIMAXMEAS)
=======
LDFLAGS=-lpthread -l sqlite3 -lrt -lgps -lm -lncurses -ltinfo
CFLAGS= -std=gnu99  -g
OBJECTS=main.o
TARGET=vinsight
INCLUDES=
LFLAGS=
PREFIX=/usr
DEPS=$(SOURCE_DIR)/*.h

SOURCE_DIR=./


all	:	$(TARGET)
$(TARGET)	:	$(SOURCE_DIR)/*.c $(DEPS)
		$(CC)	$(SOURCE_DIR)/*.c $(DEPS)	-o	$(TARGET)	$(LDFLAGS) $(CFLAGS)

clean	:
	rm	-f	*.o	$(TARGET)

install	: 
	@echo  "\n***** Installing *****"
	cp -f $(TARGET) $(PREFIX)/bin/$(TARGET)
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
