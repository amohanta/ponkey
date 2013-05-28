#include <stdio.h>

int main(int argc, char *argv[])
{
	unsigned long count=0; int c;
	char name[25];
	FILE *f=fopen(argv[1], "r");

	if(!f) return 1;

	while (fscanf(f, "%d %s\n", &c, name) != EOF) {
		count+=c;
		printf("lines=%-6d in file=%-18s total now=%lu\n",
			c, name, count);
	}
	fclose(f);
	return 0;
}
