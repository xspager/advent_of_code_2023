#include <sys/types.h>
#include <pcre2posix.h>
#include <stdio.h>

/*
 *
 *  gcc -o posix_regex_with_pcre2_posix posix_regex_with_pcre2_posix.c -lpcre2-posix
 *  ./posix_regex_with_pcre2_posix '([0-9]|one|two|three|four|five|six|seven|eight|nine|zero){1}.*(\g<1>)'
 *
 */

#define MAX_MATCHES 5 //The maximum number of matches allowed in a single string

void match(regex_t *pexp, char *sz) {
	regmatch_t matches[MAX_MATCHES]; //A list of the matches in the string (a list of 1)
	//Compare the string to the expression
	//regexec() returns 0 on match, otherwise REG_NOMATCH
	if (regexec(pexp, sz, MAX_MATCHES, matches, 0) == 0) {
		printf("\"%s\" matches characters %d - %d\n", sz, matches[0].rm_so, matches[0].rm_eo);
	} else {
		printf("\"%s\" does not match\n", sz);
	}
}

int main(int argc, char *argv[]) {
	int rv;
	regex_t exp; //Our compiled expression
	//1. Compile our expression.
	//rv = regcomp(&exp, "(one|two|three|four|five|six|seven|eight|nine|zero){1}.*(\g<1>)", REG_EXTENDED);
	//rv = regcomp(&exp, "([0-9]|one|two|three|four|five|six|seven|eight|nine|zero){1}.*(\g<1>)", REG_EXTENDED);
	rv = regcomp(&exp, argv[1], REG_EXTENDED);
	if (rv != 0) {
		printf("regcomp failed with %d\n", rv);
		char errbuf[512];
		regerror(rv, NULL, errbuf, 512);
		printf("%s\n", errbuf);
		return -1;
	}
	//2. Now run some tests on it
	match(&exp, "0zero4444two");
	match(&exp, "0.");
	match(&exp, "hello");
	//3. Free it
	regfree(&exp);
	return 0;
}
