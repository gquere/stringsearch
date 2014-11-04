#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE	256

static int * build_skip_table(char *pattern, unsigned int psize)
{
	unsigned int *skip_table;
	unsigned int i;

	skip_table = malloc(ALPHABET_SIZE * sizeof(unsigned int));
	if (!skip_table) {
		printf("Error: no memory for build_skip_table\n");
		exit(-1);
	}

	/* fill table with max jump */
	for (i = 0; i < ALPHABET_SIZE; i++)
		skip_table[i] = psize;

	/* then compute min jump for each char pos in pattern */
	for (i = 0; i < psize - 1; i++)
		skip_table[pattern[i]] = psize - i - 1;

	return skip_table;
}

int raita(char *text, char *pattern)
{
	unsigned int skipt[ALPHABET_SIZE];
	unsigned int psize, tsize;
	int i;
	char first, mid, last;

	tsize = strlen(text);
	psize = strlen(pattern);
//	skipt = build_skip_table(pattern, psize);
	/* fill table with max jump */
	for (i = 0; i < ALPHABET_SIZE; i++)
		skipt[i] = psize;

	/* then compute min jump for each char pos in pattern */
	for (i = 0; i < psize - 1; i++)
		skipt[pattern[i]] = psize - i - 1;

	first = pattern[0];
	mid = pattern[psize/2];
	last = pattern[psize - 1];

	i = 0;
	while (i <= tsize - psize) {
		if (text[i + psize - 1] == last && text[i] == first && text[i + psize/2] == mid) {
			if (memcmp(pattern + 1, text + i + 1, psize - 2) == 0) {
				return i;
			}
		}
		i += skipt[text[i + psize - 1]];
	}

	return -1;

}

int main(int argc, char *argv[])
{
	int res;

	res = raita("stupid_spring_string", "string");
	res = raita("stupid_int_spring_string", "int");
	//res = raita("abbaabaabddbabadbb", "abddb");
	printf("Found at %d\n", res);

	return 0;
}

