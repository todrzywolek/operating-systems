CFLAGS = -Wall -c -I include
CC = gcc

OBJECT=$(CC) $< $(CFLAGS) -o $@

all: main
	sh start.sh

main: bin/main.o \
		bin/utils.o \
		bin/readdir_search.o \
		bin/nftw_search.o \
		bin/common.o
	$(CC) $^ -o $@

bin/main.o: src/main.c \
			include/utils.h \
			include/readdir_search.h \
			include/nftw_search.h | bin
	$(OBJECT)

bin/utils.o: src/utils.c \
				include/utils.h | bin
	$(OBJECT)

bin/readdir_search.o: src/readdir_search.c \
				include/readdir_search.h \
				include/utils.h \
				include/common.h | bin
	$(OBJECT)

bin/nftw_search.o: src/nftw_search.c \
				include/nftw_search.h \
				include/common.h | bin
	$(OBJECT)

bin/common.o: src/common.c \
				include/common.h \
				include/utils.h | bin
	$(OBJECT)


bin:
	mkdir bin

.PHONY: clean
clean:
	rm -rf bin/ main