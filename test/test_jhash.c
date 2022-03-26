#include <stdio.h>
#include <jdlib.h>
#include <assert.h>

void test_jht() {
	jht * map = jht_new();

	jht_set(map, "Fuckyou", (jany)25);
	jht_set(map, "HEI", (jany)7);
	jht_set(map, "Hei", (jany)6);
	jht_set(map, "Shi", (jany)66);

	// Only test can do this!
	long i;
	i = (long)jht_get(map, "Fuckyou");
	assert(i == 25);
	printf("Fuckyou should be 25: %ld\n", i);
	i = (long)jht_get(map, "HEI");
	assert(i == 7);
	printf("HEI should be 7: %ld\n", i);
	i = (long)jht_get(map, "Hei");
	assert(i == 6);
	printf("Hei should be 6: %ld\n", i);
	i = (long)jht_get(map, "Shi");
	assert(i == 66);
	printf("Shi should be 66: %ld\n", i);
}

int main() {
	test_jht();
	return 0;
}
