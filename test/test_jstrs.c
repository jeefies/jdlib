#include <stdio.h>

#include <jdlib.h>

void test_strs() {
	// jstr is another name of "char *"
	jstr str = "Here's a simple string";
	// jstrs include a list of strs and a length number
	jstrs * str_l = jstrs_new_empty();

	// it should be equal to jstrs_len(str_l);
	printf("empty length %d\n", str_l->len);

	// This operations would copy the string and you can free origin anytime you want.
	jstrs_append(str_l, str);

	printf("one added length %d\n", str_l->len);

	// Second argument is the `sep` between each str
	jstrs_print(str_l, "\n");

	printf("\nCreate one with 2 place\n");
	jstrs * strs2 = jstrs_new(2);

	// test set and index method
	jstrs_set(strs2, 1, "Fuck you!");
	jstrs_set(strs2, 0, jstrs_index(str_l, 0));
	jstrs_print(strs2, "\n");
	printf("\n...\n");

	// test remove method
	jstrs_remove(strs2, 2);
	jstrs_append(strs2, "Hello bitch");
	jstrs_remove(strs2, 1);
	jstrs_print(strs2, "\n");
	printf("\n....\n");

	// test negative index method
	int i = 0;
	for (i = -1; i >= -4; i--)
		printf("%d %s\n", i, jstrs_index(strs2, i));

	// test new_from method
	printf(".....\n");
	jstrs * str2_2 = jstrs_new_from(strs2);
	jstrs_print(str2_2, ", ");
	printf("\n......\n");

	// test cleanup method
	jstrs_free(str_l);
	jstrs_free(strs2);
	jstrs_free(str2_2);
}

void test_str() {
	// jstr str = jstr_copy("\tJ str here    ");
	jstr str = jstr_from("\tJ str here    ");

	printf("old str: \"%s\"\n", str);

	jstr trimed = jstr_trim(str);
	printf("trimed: \"%s\"\n", trimed);

	jstr_free(str);
	jstr_free(trimed);
}

int main(int argc, const char *argv[]) {
	test_strs();
	printf("- - - - - - - - - - - \n");
	test_str();
	printf("jstrs jstr test ok!\n");
	return 0;
}
