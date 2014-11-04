#include "stdio.h"
#include "stdlib.h"
#include "string.h"


#define max(a, b)	(((a) > (b)) ? (a) : (b))

char *text = "stupid_spring_string_bla";
char *pattern = "string";


/* the first skip table is used to skip to the next nearest match */
static int * build_first_skip_table(char *pattern)
{
	unsigned int *skip_table;
	unsigned int i;

	skip_table = malloc(256 * sizeof(unsigned int));
	if (!skip_table) {
		printf("Error: no memory for build_first_skip_table\n");
		exit(-1);
	}

	/* fill table with max jump */
	for (i = 0; i < 256; i++) {
		skip_table[i] = strlen(pattern);
	}

	/* then compute jump for characters in pattern */
	for (i = 0; i < strlen(pattern) - 1; i++) {
		skip_table[pattern[i]] = strlen(pattern) - i - 1;
	}

	return skip_table;
}


/**
 * Build second skip table
 *
 * Note: this could be hugely optimized but this way it was simple
 * to write and hopefully to read. Anyways, this is constant time at init so
 * it hardly matters */
static int * build_second_skip_table(char *string)
{
	unsigned int *skip_table;
	unsigned int i, j, decal, k;
	unsigned int ssize, psize;
	char *pattern, *invstring;
	char offender;
	int match;

	ssize = strlen(string);

	skip_table = malloc(ssize * sizeof(unsigned int));
	invstring = calloc(ssize * 2, sizeof(char));
	pattern = calloc(ssize * 2, sizeof(char));
	if (!skip_table || !invstring || !pattern) {
		printf("Error: no memory for build_second_skip_table\n");
		exit(-1);
	}

	/* fill table with max size because it's hard to detect it */
	for (i = 0; i < ssize; i++) {
		skip_table[i] = ssize;
	}

	/* invert string for less brainfuck algorithm */
	for (i = 0; i < ssize; i++) {
		invstring[i] = string[ssize - 1 - i];
	}

	/* first occurence is rather special */
	i = 0;
	while (invstring[i] == invstring[i + 1]) {
		i++;
	}
	skip_table[0] = i + 1;

	/* for each subpattern of the string */
	for (i = 0; i < ssize - 1; i++) {
		strncpy(pattern, invstring, i + 1);
		psize = strlen(pattern);
		offender = invstring[i + 1];
		/* for each shift of the subpattern */
		for (decal = 0; decal < ssize - 1; decal++) {
			match = 1;
			/* compare shifted subpattern with string */
			for (k = 0; k < psize; k++) {
				if (pattern[k] != invstring[decal + k]) {
					/* abuse the calloc trick */
					if (invstring[decal + k] == 0) {
						break;
					}
					match = 0;
					break;
				}
			}
			/* pattern matches, but check offender */
			if (match) {
				if (invstring[decal + k] != offender) {
					skip_table[i + 1] = decal;
					break;
				}
			}
		}
	}

	free(invstring);
	free(pattern);

	return skip_table;
}

#if 0
/* second skip table */
static int * build_second_skip_table(char *pattern)
{
	unsigned int *skip_table;
	unsigned int i;
	unsigned int psize;
	char *position;
	char offender;

	psize = strlen(pattern);

	skip_table = malloc(psize * sizeof(int));
	if (!skip_table) {
		printf("Error: no memory for build_second_skip_table\n");
		exit(-1);
	}

	/* first occurence is rather special */
	i = psize - 1;
	while (pattern[i] == pattern[i - 1]) {
		i--;
	}
	skip_table[0] = psize - i - 1;

	/* now find lowest shift */
	for (i = psize - 1; i > 0; i--) {
		position = pattern;
		offender = pattern[i - 1];
		printf("pattern = %s, offender = %c\n", pattern + i, offender);
		while (position = strstr(position, pattern + i)) {
			printf("3 %d\n", position - pattern);
			if (position - pattern >= 2) {
				if (*(position - 1) != offender) {
					skip_table[psize - i] = position - pattern;
					printf("Value = %d\n", position - pattern);
				} else {
					printf("Offender\n");
				}
			}
			position += 1; // += i ?
		}
	}
	printf("Done");
}
#endif

int bm(char *text, char *pattern)
{
	unsigned int *first_skipt, *second_skipt;
	unsigned int tsize, psize;
	int i, j;
	char curchar; //FIXME: remove, for tests
	unsigned int fskip, sskip;

	first_skipt = build_first_skip_table(pattern);
	second_skipt = build_second_skip_table(pattern);

	tsize = strlen(text);
	psize = strlen(pattern);

	i = psize - 1;
	while (i < tsize) {
		j = psize - 1;
		while (j >= 0 && text[i] == pattern[j]) {
			--i;
			--j;
		}

		if (j < 0) {
			free(first_skipt);
			free(second_skipt);
			return i + 1;
		}

		fskip = first_skipt[text[i]]; //0->255
		sskip = second_skipt[psize - 1 - j]; //0->psize-1
		i += max(fskip, sskip);
		//i += max(first_skipt[text[i]], second_skipt[j]);
	}

	free(first_skipt);
	free(second_skipt);
	return -1;
}

int main(int argc, char *argv[])
{
	bm(text, pattern);

	return 0;
}

