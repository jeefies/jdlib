#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <jdlib.h>

void test_strs() {
	// jstr is another name of "char *"
	jstr str = "Here's a simple string";
	
	// jstrs include a list of strs and a length number
	jstrs * str_l = jstrs_new_empty();
	assert(str_l->len == 0);
	assert(str_l->cap == 0);

	// This operations would copy the string and you can free origin anytime you want.
	jstrs_append(str_l, str);
	assert(str_l->len == 1);
	assert(str_l->cap == 1);
	
	// Second argument is the `sep` between each str
	jstrs_print(str_l, "\n");
	printf("\n...\n");

	jstrs * strs2 = jstrs_new(2);
	assert(strs2->len == 0);
	assert(strs2->cap == 2);
	// test set and index method
	jstrs_set(strs2, 1, "Fuck you!");
	jstrs_set(strs2, 0, jstrs_index(str_l, 0));
	
	assert(strs2->len == 2);
	assert(strs2->cap == 2);

	jstrs_print(strs2, "\n");
	printf("\n...\n");

	// test remove method
	jstrs_remove(strs2, 2);
	assert(strs2->len == 2);
	jstrs_append(strs2, "Hello bitch");
	assert(strs2->len == 3);
	assert(strs2->cap == 3);
	jstrs_remove(strs2, 1);
	assert(strs2->len == 2);
	jstrs_print(strs2, "\n");
	printf("\n....\n");

	// test new_from method
	printf(".....\n");
	jstrs * str2_2 = jstrs_deepcopy_from(strs2);
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

	jstr trimed = jstr_trim(str);
	assert(strcmp(trimed, "J str here") == 0);

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
