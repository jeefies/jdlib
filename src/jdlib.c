/*
 * Generic methods like malloc and sizeof definations
 */

#include <jdlib.h>
#include <stdio.h>
#include <stdlib.h>

jany jmalloc(int size) {
	jany p = malloc(abs(size));
	if (isnull(p))
		exit(1);
	return p;
}

jany jfree(jany p) {
	rnull(p);
	free(p);
	return NULL;
}

jany jrealloc(jany p, int size) {
	rnull(p);
	return realloc(p, size);
}
