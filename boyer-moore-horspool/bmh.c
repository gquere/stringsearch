#include "stdio.h"
#include "stdlib.h"
#include "string.h"


char *text = "stupide_strinp_string";	//tsize = 20
char *pattern = "string";		//psize = 6


#define ALPHABET_SIZE	256	// taille de l'alphabet ASCII

/**
 * Implémentation de Boyer-Moore-Horspool
 *
 * Note : retourne directement la position du pattern trouvé, sinon -1
 */
int bmh(char *text, char *pattern)
{
	unsigned int skip_table[ALPHABET_SIZE];
	ssize_t tsize, psize;
	int i;

	tsize = strlen(text);
	psize = strlen(pattern);

	/* pré-traitement */
	/** remplir la table avec la valeur de saut maximum */
	for (i = 0; i < ALPHABET_SIZE; i++)
		skip_table[i] = psize;

	/** puis calculer pour chaque caractère de pattern le saut */
	for (i = 0; i < psize - 1; i++)
		skip_table[(int) pattern[i]] = psize - i - 1;

	/* recherche */
	i = 0;
	while (i <= tsize - psize) {
		if (text[i + psize - 1] == pattern[psize - 1])
			if (memcmp(text + i, pattern, psize - 2) == 0)
				return i;

		i += skip_table[(int) text[i + psize - 1]];
	}

	return -1;
}


int main(int argc, char *argv[])
{
	int res;

	res = bmh(text, pattern);
	printf("%d\n", res);

	return 0;
}

