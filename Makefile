CC =c99
CFLAGS=-Wall -O2 -D_POSIX_C_SOURCE=200809L
LIBS	=-lglib-2.0
INCLUDE =`pkg-config --cflags glib-2.0`

-include makerules.mk

rules: makerules.pl
	perl makerules.pl
	@printf "Rules generated - run make again to build\n"
