#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bf(char *text, char *pattern)
{
	int i, j;
	unsigned int psize;
	int match;

	psize = strlen(pattern);

	i = 0;
	while (text[i]) {
		match = 1;
		for (j = 0; j < psize; j++) {
			if (text[i + j] != pattern[j]) {
				match = 0;
				break;
			}
		}
		if (match)
			return i;

		i++;
	}

	return -1;
}

int main(int argc, char *argv[])
{
	bf("stupid_spring_string", "string");

	return 0;
}

