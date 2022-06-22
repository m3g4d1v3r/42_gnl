#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <stdio.h>
#include <fcntl.h>
#include "../get_next_line.h"

Test(gnl, simple0) {
	FILE *ptrSimple;
	int fd;
	ptrSimple = fopen("simple0.txt", "w+");
	fd = fileno(ptrSimple);
	fputs("42\n", ptrSimple);
	fputs("24\n", ptrSimple);
	fputs("A", ptrSimple);
	fclose(ptrSimple);
	fd = open("simple0.txt", O_RDWR);
	printf("file descriptor: %d\n", fd);
	
	char *res;
	res = get_next_line(fd);
	cr_assert(eq(str, res, "42\n"));
	free(res);
	res = get_next_line(fd);
	cr_assert(eq(str, res, "24\n"));
	free(res);
	res = get_next_line(fd);
	cr_assert(eq(str, res, "A"));
	free(res);
	res = get_next_line(fd);
	cr_assert(ne(str, res, "B"));
	free(res);
}
