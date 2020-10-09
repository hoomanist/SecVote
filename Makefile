CC=cc
CFLAGS=-Wall -Wextra -std=c99

all:
	$(CC) $(CFLAGS) main.c -o secureVote

clean:
	rm secureVote

