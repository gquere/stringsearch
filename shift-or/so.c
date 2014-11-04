#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE	256

int shiftor(const char *text, const char *pattern)
{
	unsigned int psize;
	unsigned long int R;
	unsigned long int mask[ALPHABET_SIZE];
	unsigned int i;

	psize = strlen(pattern);
	if (psize > 31) {
		printf("Pattern trop long !\n");
		exit(-1);
	}

	/* pré-traitement */
	R = ~1;

	for (i = 0; i < ALPHABET_SIZE; i++)
		mask[i] = ~0;

	for (i = 0; i < psize; i++)
		mask[pattern[i]] &= ~(1UL << i);

	/* recherche */
	i = 0;
	while (text[i]) {
		R |= mask[text[i]];
		R <<= 1;

		if (!(R & (1UL << psize)))
			return i - psize + 1;

		i++;
	}

	return -1;
}

int main(int argc, char *argv[])
{
	shiftor("stupid_strina_string", "string");

	return 0;
}

