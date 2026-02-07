#include "table.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static void *ecalloc(size_t num, size_t size);
static void *erealloc(void *ptr, size_t new_size);
extern const struct Replacement *table(register const char *str, register size_t len);

#define die(...)                                                                                                       \
	do {                                                                                                           \
		fprintf(stderr, "fatal: ");                                                                            \
		fprintf(stderr, __VA_ARGS__);                                                                          \
		fprintf(stderr, "\n");                                                                                 \
		exit(EXIT_FAILURE);                                                                                    \
	} while (0)

void *ecalloc(size_t num, size_t size)
{
	void *p = calloc(num, size);
	if (!p) die("failed to allocate buffer");
	return p;
}

void *erealloc(void *ptr, size_t new_size)
{
	void *p = realloc(ptr, new_size);
	if (!p) die("failed to reallocate buffer");
	return p;
}

int main(void)
{
	size_t num = 64;
	size_t len = 0;
	char *buf = ecalloc(num, sizeof *buf);

	for (int c = 0; c = getchar(), c != EOF;) {
		if (len + 1 >= num) buf = erealloc(buf, num *= 2);
		buf[len++] = (char)c;
	}

	buf[len] = '\0';

	/* Trim input. */

	char *start = buf;
	while (*start && isspace((unsigned char)*start)) start += 1;

	len -= start - buf;
	while (len > 0 && isspace((unsigned char)start[len - 1])) len -= 1;
	start[len] = '\0';

	/* Print codepoint. */

	const struct Replacement *r = table(start, len);
	free(buf);

	if (!r) die("failed to find input macro's codepoint");
	printf("%s", r->codepoint);

	return EXIT_SUCCESS;
}
