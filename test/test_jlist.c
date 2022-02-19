#include <stdio.h>

#include <jdlib.h>

void test_linear_list() {
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
}

void test_linked_list() {
	// Test linked list
	jlist * li = jlist_new();
	// Test Append Method
	// Append string
	jlist_append(li, "Static string");
	// Append int
	jlist_append(li, (jany)5);
	// Test insert method
	jlist_insert(li, 1, "Mid Insert");
	jlist_insert(li, 20, (jany)10);
	// ["Static string", "Mid Insert", 5, 10]
	// and Test index
	printf("insert 1 to :%s\n", jlist_index(li, 1)); // Mid Insert
	// Test delete
	jlist_delete(li, 0);
	printf("delete 0 and li[0]: %s\n", jlist_index(li, 0));
	// Test insert 0
	jlist_insert(li, 0, "SHOULD BE FRIST");
	printf("insert 0 and li[0]: %s\n", jlist_index(li, 0));
	// Test free
	jlist_free(li);
}

int main() {
	test_linear_list();
	printf("- - - - - - - - - - - - -\n");
	test_linked_list();

	return 0;
}