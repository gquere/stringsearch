#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int * build_partial_match_table(char *pattern, unsigned int psize)
{
	int *pmt;
	int i, count;

	pmt = calloc(psize, sizeof(int));

	pmt[0] = -1;

	count = 0;
	for(i = 1; i < psize; i++) {
		pmt[i] = count;
		if (pattern[i] == pattern[0 + count]) {
			count++;
		} else {
			count = 0;
		}
	}

	return pmt;
}

int kmp(char *text, char *pattern)
{
	unsigned int psize;
	int m, i;
	int *pmt;

	psize = strlen(pattern);

	pmt = build_partial_match_table(pattern, psize);

	i = 0;
	m = 0;
	while (text[m + i] != 0) {
		if (pattern[i] == text[m + i]) {
			i++;
			if (i == psize) {
				return m;
			}
		} else {
			if (pmt[i] >= 0) {
				m += i - pmt[i];
				i = pmt[i];
			} else {
				i = 0;
				m++;
			}
		}
	}

	free(pmt);
	return -1;
}

int main(int argc, char *argv[])
{
	int res;

	res = kmp("stupid_spring_string", "string");
	printf("Result at %d\n", res);

	return 0;
}

