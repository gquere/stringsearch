/*
** Warning: for big pattern length, libgmp will be required to handle >64bits integers
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REHASH(a,b,h) ((((h) - (a)*d) << 1) + b)

int rabin_karp(char *text, char *pattern)
{
	unsigned int tsize, psize;
	int ht, hp;
	int i, d;

	tsize = strlen(text);
	psize = strlen(pattern);

	for (d = i = 1; i < psize; i++)
		d <<= 1;

	for (ht = hp = i = 0; i < psize; i++) {
		hp = (hp << 1) + pattern[i];
		ht = (ht << 1) + text[i];
	}

	for (i = 0; i <= tsize - psize; i++) {
		if (ht == hp)
			if (!memcmp(pattern, text + i, psize))
				return i;
		ht = REHASH(text[i], text[i + psize], ht);
	}

	return -1;
}

int main(int argc, char *argv[])
{
	int res;
	res = rabin_karp("stupid_spring_string", "string");
	printf("Res=%d\n", res);

	return 0;
}

