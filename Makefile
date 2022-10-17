CC=clang
CFLAGS=-g -Wall
BIN=CNIT315_Final

all: $(BIN)

%: %.c
	$(CC) $(CFLAGS) $< -o $@ -lcurl

clean:
	$(RM) -rf $(BIN) *.dSYM