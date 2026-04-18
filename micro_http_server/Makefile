CC=gcc
CFLAGS=-Wall -Wextra -Iinclude
LDFLAGS=-lws2_32

all: micro_http

micro_http: src/main.o src/http.o src/file.o
	$(CC) $(CFLAGS) -o micro_http src/main.o src/http.o src/file.o $(LDFLAGS)

src/main.o: src/main.c include/http.h
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

src/http.o: src/http.c include/http.h include/file.h
	$(CC) $(CFLAGS) -c src/http.c -o src/http.o

src/file.o: src/file.c include/file.h
	$(CC) $(CFLAGS) -c src/file.c -o src/file.o

clean:
	rm -f src/*.o micro_http
