#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strstr2(char *text, char *pattern)
{
	char *pos;

	pos = strstr(text, pattern);
	if (pos != NULL) {
		return (pos - text);
	} else {
		return -1;
	}
}

int main(int argc, char *argv[])
{
	strstr2("stupid_spring_string", "string");

	return 0;
}

