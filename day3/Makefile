ALL = gear_ratios

CFLAGS+= -ansi -Wall -g -O0

all: $(ALL)

gear_ratios: gear_ratios.c ../day1/utils.c ../day1/utils.h
	$(CC) $(CFLAGS) -o $@ $@.c ../day1/utils.c

.PHONY: clean
clean:
	rm -f $(ALL)
