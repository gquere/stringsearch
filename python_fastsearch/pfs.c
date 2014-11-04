#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define BLOOM(mask, c)		((mask |= (1UL << ((c) & (32 - 1)))))
#define BLOOM_ADD(mask, c)	((mask &  (1UL << ((c) & (32 - 1)))))

char *text = "stupide_strinp_string";	//tsize = 20
char *pattern = "string";		//psize = 6


/**
 * Simplified python faststring
 * Uses a mix of Boyer-Moore, Horspool, Sunday and bloom filters
 */
int pfs(char *text, char *pattern)
{
	unsigned int tsize, psize;
	int i, j;
	unsigned int skip;
	char c;
	unsigned long int mask;

	tsize = strlen(text);
	psize = strlen(pattern);
	mask = 0;
	skip = psize - 2;

	/* construct bloom mask, could be optimized in another loop */
	for (i = 0; i < psize - 1; i++) {
		BLOOM_ADD(mask, pattern[i]);
		if (pattern[i] == pattern[psize - 1])
			skip = psize - i - 2;
	}
	BLOOM_ADD(mask, pattern[psize - 1]);

	for (i = 0; i <= tsize - psize; i++) {
		if (text[i + psize - 1] == pattern[psize - 1]) {
			for (j = 0; j < psize; j++) {
				if (text[i + j] != pattern[j])
					break;
			}
			if (j == psize) {
				return i;
			}

			if (!BLOOM(mask, text[i + psize]))
				i += psize;
			else
				i += skip;
		} else {
			if (!BLOOM(mask, text[i + psize]))
				i += psize;
		}
	}

	return -1;
}


int main(int argc, char *argv[])
{
	int res;

	res = pfs(text, pattern);
	printf("Res = %d\n", res);

	return 0;
}

