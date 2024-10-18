ALL = cube_conundrum cube_conundrum_part2

CFLAGS+= -std=c99 -Wall -g

all: $(ALL)

cube_conundrum: cube_conundrum.c ../day1/utils.c ../day1/utils.h
	$(CC) $(CFLAGS) -o $@ $@.c ../day1/utils.c

cube_conundrum_part2: cube_conundrum_part2.c ../day1/utils.c ../day1/utils.h
	$(CC) $(CFLAGS) -o $@ $@.c ../day1/utils.c

.PHONY: clean
clean:
	rm -f $(ALL)
