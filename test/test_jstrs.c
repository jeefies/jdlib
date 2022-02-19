#include <stdio.h>

#include <jdlib.h>

int main(int argc, const char *argv[])
{
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

	// test delete method
	jstrs_delete(strs2, 2);
	jstrs_append(strs2, "Hello bitch");
	jstrs_delete(strs2, 1);
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

	printf("Test jstrs OK\n");

	return 0;
}
