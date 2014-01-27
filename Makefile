CC	=gcc
CFLAGS=-Wall -O2 -std=c99
LIBS	=-lglib-2.0
INCLUDE =`pkg-config --cflags glib-2.0`
PATH_SRC=src
PATH_OBJ=obj
PATH_BIN=bin
SOURCES:=$(PATH_SRC)/main.c $(PATH_SRC)/string_utilities.c \
         $(PATH_SRC)/wordcount.c
OBJECTS:=$(patsubst $(PATH_SRC)/%.c, $(PATH_OBJ)/%.o, $(SOURCES))
FILENAME=wordcount

all: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $(PATH_BIN)/$(FILENAME)

$(OBJECTS): $(PATH_OBJ)/%.o: $(PATH_SRC)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(PATH_OBJ)/*

new: clean all
