CC =c99
CFLAGS=-Wall -O2
LIBS	=-lglib-2.0
INCLUDE =`pkg-config --cflags glib-2.0`
PATH_SRC=src
PATH_OBJ=obj
PATH_BIN=bin
HEADERS:=$(PATH_SRC)/string_utilities.h $(PATH_SRC)/options.h\
	 $(PATH_SRC)/output.h $(PATH_SRC)/wordcount.h
SOURCES:=$(PATH_SRC)/main.c $(PATH_SRC)/string_utilities.c \
         $(PATH_SRC)/wordcount.c $(PATH_SRC)/output.c
OBJECTS:=$(patsubst $(PATH_SRC)/%.c, $(PATH_OBJ)/%.o, $(SOURCES))
FILENAME=wordcount

all: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $(PATH_BIN)/$(FILENAME)

$(OBJECTS): $(PATH_OBJ)/%.o: $(PATH_SRC)/%.c $(HEADERS) prepare
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

prepare:
	mkdir -p obj
	mkdir -p bin

clean:
	rm -rf $(PATH_OBJ)/*

new: clean all

tarball: $(HEADERS) $(SOURCES) Makefile LICENSE README.md
	tar -cJf wordcount.tar.xz $(HEADERS) $(SOURCES) Makefile LICENSE README.md
