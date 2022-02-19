#include <stdio.h>

#include <jdlib.h>

int main() {
	// Test Linear List
	jllist * list = jllist_new(5);
	// Test Append method
	jllist_append(list, (jany)2);
	// Test Length
	printf("Length: %d\n", list->len);
	// Test Append Empty
	jllist_append_empty(list, (jany)3);
	// Test Index method
	printf("list[0] %d\n", jllist_index(list, 0));
	// Test String ADD
	jllist_append_empty(list, "Hello World");
	printf("List[1] %s\n", (char *)jllist_index(list, 1));

	// Test NULL 
	printf("Empty Elem: %s\n", jllist_index(list, -2));
	//  Test negative index
	printf("list[-6]: %d\n", jllist_index(list, -6));
	// Test free
	list = jllist_free(list);

	return 0;
}
