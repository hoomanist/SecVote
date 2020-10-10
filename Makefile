CC=cc
CFLAGS=-lreadline -lcrypto -std=c99
all:
	$(CC) $(CFLAGS) main.c -o secureVote
clean:
	rm secureVote
