ALL = trebuchet posix_regex_with_pcre2_posix trebuchet_part2

CFLAGS+= -ansi -Wall -g

all: $(ALL)

trebuchet: trebuchet.c
	$(CC) $(CFLAGS) -o $@ $@.c

posix_regex_with_pcre2_posix: posix_regex_with_pcre2_posix.c
	$(CC) $(CFLAGS) -std=c99 -o $@ $@.c -lpcre2-posix

trebuchet_part2: trebuchet_part2.c utils.c
	$(CC) $(CFLAGS) -o $@ trebuchet_part2.c utils.c -lpcre2-8

.PHONY: clean
clean:
	rm -f $(ALL)
