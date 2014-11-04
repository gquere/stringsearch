#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *text = "stupide_strinp_string2";	//tsize = 20
char *pattern = "string";		//psize = 6

int za(const char *text, const char *pattern)
{
	int *z;
	unsigned int tsize, psize;
	int i, k;
	char *s;
	int len;
	int R, L, n, p;

	psize = strlen(pattern);
	tsize = strlen(text);
	s = calloc(psize + tsize + 1, sizeof(char));
	if (!s) {
		printf("Error: Failed alloc\n");
		exit(-1);
	}

	s = strcat(s, pattern);
	s = strcat(s, text);
	len = psize + tsize + 1;

	z = calloc(len, sizeof(int));
	if (!z) {
		printf("Error: Failed alloc\n");
		exit(-1);
	}

	for (k = 1; k < len; k++) {
		if (k > R) {
			n = 0;
			while (n + k < len && s[n] == s[n + k])
				n++;
			z[k] = n;
			if (n > 0) {
				L = k;
				R = k + n - 1;
			}
		} else {
			p = k - L;
			if (z[p] < R - k + 1) {
				z[k] = z[p];
			} else {
				i = R + 1;
				while (i < len && s[i] == s[i - k])
					i++;
				z[k] = i - k;
				L = k;
				R = i - 1;
			}
		}
		z[k] = psize < z[k] ? psize : z[k];
		if (z[k] == psize) {
			free(s);
			free(z);
			return k - psize;
		}
	}

	free(s);
	free(z);
	return -1;
}


int main(int argc, char *argv[])
{
	int res;

	res = za(text, pattern);
	printf("Res = %d\n", res);

	return 0;
}

