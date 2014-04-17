all: obj/input.o obj/utf8.o obj/main.o obj/output.o obj/options.o obj/multus.o obj/string_utilities.o
	$(CC) $(CFLAGS) -o bin/multus obj/input.o obj/utf8.o obj/main.o obj/output.o obj/options.o obj/multus.o obj/string_utilities.o $(LIBS)

obj/input.o: src/input.c src/input.h src/output.h prepare
	$(CC) $(CFLAGS) $(INCLUDE) -c -o obj/input.o src/input.c

obj/utf8.o: src/utf8.c src/utf8.h src/utf_data.h src/output.h prepare
	$(CC) $(CFLAGS) $(INCLUDE) -c -o obj/utf8.o src/utf8.c

obj/main.o: src/main.c src/options.h src/input.h src/output.h src/string_utilities.h src/multus.h prepare
	$(CC) $(CFLAGS) $(INCLUDE) -c -o obj/main.o src/main.c

obj/output.o: src/output.c src/output.h src/options.h prepare
	$(CC) $(CFLAGS) $(INCLUDE) -c -o obj/output.o src/output.c

obj/options.o: src/options.c src/input.h src/options.h src/output.h prepare
	$(CC) $(CFLAGS) $(INCLUDE) -c -o obj/options.o src/options.c

obj/multus.o: src/multus.c src/string_utilities.h src/options.h src/output.h src/multus.h src/utf8.h prepare
	$(CC) $(CFLAGS) $(INCLUDE) -c -o obj/multus.o src/multus.c

obj/string_utilities.o: src/string_utilities.c src/string_utilities.h prepare
	$(CC) $(CFLAGS) $(INCLUDE) -c -o obj/string_utilities.o src/string_utilities.c

prepare:
	mkdir -p obj/ bin/

clean:
	rm -rf makerules.mk obj/ bin/

new: clean all

