CC=gcc
prog_ang: progressive_anagram.c
	$(CC) progressive_anagram.c -o prog_ang
install:
	cp -f prog_ang /usr/local/bin
clean:
	$(CC) progressive_anagram.c -g -std=gnu11 -o prog_ang -lm && rm vg*
