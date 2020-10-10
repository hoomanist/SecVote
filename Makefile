CC=cc
CFLAGS= -g -lreadline -lcrypto -std=c99
all:
	$(CC) $(CFLAGS) main.c -o secureVote
clean:
	rm secureVote
