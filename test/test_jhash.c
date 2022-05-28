#include <stdio.h>
#include <jdlib.h>
#include <assert.h>

// J HashTable
void test_jht() {
	jht * ht = jht_new();

	jht_set(ht, "Fuckyou", (jany)25);
	jht_set(ht, "HEI", (jany)7);
	jht_set(ht, "Hei", (jany)6);
	jht_set(ht, "Shi", (jany)66);

	// Only test can do this!
	long i;
	i = (long)jht_get(ht, "Fuckyou");
	assert(i == 25);
	printf("Fuckyou should be 25: %ld\n", i);
	i = (long)jht_get(ht, "HEI");
	assert(i == 7);
	printf("HEI should be 7: %ld\n", i);
	i = (long)jht_get(ht, "Hei");
	assert(i == 6);
	printf("Hei should be 6: %ld\n", i);
	i = (long)jht_get(ht, "Shi");
	assert(i == 66);
	printf("Shi should be 66: %ld\n", i);
}

int main() {
	test_jht();
	return 0;
}
