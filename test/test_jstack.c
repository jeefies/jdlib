#include <stdio.h>
#include <jdlib.h>
#include <assert.h>

jany change(jany js) {
	jstr s = jstr_from(js);
	s[0] += s[0] - 'A';
	return s;
}

void test_jstack() {
	jstack * stk = jstack_new();

	jstack_push(stk, "A");
	jstack_push(stk, "C");

	jstack_foreach(stk, change);

	printf("%s\n", jstack_pop(stk));
	printf("%s\n", jstack_pop(stk));
}

int main() {
	test_jstack();
	return 0;
}
