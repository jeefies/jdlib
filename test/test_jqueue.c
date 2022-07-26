#include <stdio.h>
#include <jdlib.h>
#include <assert.h>
#include <string.h>

void test_jqueue() {
	jqueue * jq = jqueue_new();
	jqueue_push(jq, "One");
	jqueue_push(jq, "Two");

	assert(strcmp("One", jqueue_pop(jq)) == 0);
	jqueue_push(jq, "Three");
	assert(strcmp("Two", jqueue_pop(jq)) == 0);
	assert(strcmp("Three", jqueue_pop(jq)) == 0);

	printf("Test Jqueue OK\n");
}

int main() {
	test_jqueue();
	return 0;
}
