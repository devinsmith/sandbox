#include <stdio.h>

struct string {
	char *bytes;
	size_t len;
};

int main(int argc, char *argv[])
{
	struct string source = { "Hello", 5};
	struct string dest;

	dest = source;
	printf("%s %zu\n", dest.bytes, dest.len);

	return 0;
}
