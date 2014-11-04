#include "stdio.h"
#include "stdlib.h"
#include "string.h"


char *text = "stupide_strinp_string";	//tsize = 20
char *pattern = "string";		//psize = 6


/* the first skip table is used to skip to the next nearest match */
int * build_skip_table(char *pattern, unsigned int psize)
{
	unsigned int *skip_table;
	unsigned int i;

	skip_table = malloc(256 * sizeof(unsigned int));
	if (!skip_table) {
		printf("Error: no memory for build_skip_table\n");
		exit(-1);
	}

	/* fill table with max jump */
	for (i = 0; i < 256; i++) {
		skip_table[i] = psize + 1;
	}

	/* then compute jump for characters in pattern */
	for (i = 0; i < psize; i++) {
		skip_table[pattern[i]] = psize - i;
	}

	return skip_table;
}


int qs(char *text, char *pattern)
{
	unsigned int *skipt;
	unsigned int tsize, psize;
	int i;

	tsize = strlen(text);
	psize = strlen(pattern);
	skipt = build_skip_table(pattern, psize);

	i = 0;
	while (i <= tsize - psize) {
		if (!memcmp(text + i, pattern, psize)) {
			free(skipt);
			return i;
		}
		i += skipt[text[i + psize]];
	}

	free(skipt);
	return -1;
}


int main(int argc, char *argv[])
{
	int res;

	res = qs(text, pattern);
	printf("Res = %d\n", res);

	return 0;
}

