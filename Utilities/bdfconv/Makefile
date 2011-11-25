#
# Usage 
#
#	0. be sure to install otf2bdf utility
#	1. create the executable: make bdfconv
#	2. put otf fonts in the OTF directory
#	3. generate font data: make POINT=14 data
#	4. clean bdf data  before going another round: make cleanbdf
#	5. gather your data from the DAT directory
#
.PHONY:	bdfconv clean cleandata cleanbdf bdf data

CFLAGS += -g
CFLAGS += -Os

SRC_DIR = ./SRC
OTF_DIR = ./OTF
BDF_DIR = ./BDF
DAT_DIR = ./DAT

INCLUDEPATHS += -I $(SRC_DIR)

POINT = 12
RANGE = '32_126'

OTF_FILES := $(wildcard $(OTF_DIR)/*.ttf)
BDF_FILES := $(addprefix $(BDF_DIR)/, $(notdir $(subst .ttf,.bdf,$(OTF_FILES))))
DAT_FILES := $(addprefix $(DAT_DIR)/, $(notdir $(subst .ttf,.c,$(OTF_FILES))))


bdfconv: $(SRC_DIR)/bdfconv.o
	$(CC) $(LDFLAGS) $(SRC_DIR)/bdfconv.o -o bdfconv

$(SRC_DIR)/bdfconv.o: $(SRC_DIR)/bdfconv.c
	$(CC) $(CFLAGS) $(INCLUDEPATHS) $(SRC_DIR)/bdfconv.c -c -o $(SRC_DIR)/bdfconv.o
	
clean:
	-rm bdfconv $(SRC_DIR)/bdfconv.o

cleanbdf:
	-rm $(BDF_DIR)/*

cleandata:
	-rm $(DAT_DIR)/*

bdf: $(BDF_FILES)

$(BDF_DIR)/%.bdf: $(OTF_DIR)/%.ttf
	-otf2bdf -p $(POINT) -l $(RANGE) $< -o $@

data: $(DAT_FILES)
	-mv *.c $(DAT_DIR)

$(DAT_DIR)/%.c: $(BDF_DIR)/%.bdf
	./bdfconv $<
