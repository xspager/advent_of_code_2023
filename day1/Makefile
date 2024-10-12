ALL = posix_regex_with_pcre2_posix trebuchet

CFLAGS+= -ansi -Wall

all: $(ALL)

posix_regex_with_pcre2_posix: posix_regex_with_pcre2_posix.c
	$(CC) $(CFLAGS) -std=c99 -o $@ $@.c -lpcre2-posix

trebuchet: trebuchet.c
	$(CC) $(CFLAGS) -o $@ $@.c

.PHONY: clean
clean:
	rm -f $(ALL)
