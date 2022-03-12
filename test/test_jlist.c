#include <stdio.h>
#include <assert.h>

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
	assert(list->len == 8);

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
	assert(li->len == 0);
	// Test Append Method
	// Append string
	jlist_append(li, "Static string");
	assert(li->len == 1);
	// Append int
	jlist_append(li, (jany)5);
	assert(li->len == 2);
	// Test insert method
	jlist_insert(li, 1, "Mid Insert");
	assert(li->len == 3);
	jlist_insert(li, 20, (jany)10);
	assert(li->len == 4);
	// ["Static string", "Mid Insert", 5, 10]
	// and Test index
	printf("insert 1 to: %s\n", jlist_index(li, 1)); // Mid Insert
	// Test delete
	jlist_delete(li, 0);
	assert(li->len == 3);

	printf("delete 0 and li[0]: %s\n", jlist_index(li, 0));
	// Test insert 0
	jlist_insert(li, 0, "SHOULD BE FRIST");
	assert(li->len == 4);
	printf("insert 0 and li[0]: %s\n", jlist_index(li, 0));
	// Test free
	jlist_free(li);
}

jany pr(jany s, int index) {
	printf("%d: %s\n", index, (char*)s);
	return NULL;
}

void test_double_linked_list() {
	jdlist * li = jdlist_new();
	jdlist_append(li, "2");
	jdlist_append_front(li, "Front Append");
	jdlist_append(li, "Last Append");
	assert(li->len == 3);

	jdlist_foreach(li, pr);
	printf("- - -\n");
	jdlist_remove(li, 1);
	assert(li->len == 2);
	jdlist_foreach_reverse(li, pr);
	printf("- - -\n");

	jdlist_insert(li, 1, "Middle insertion");
	jdlist_foreach(li, pr);
	assert(li->len == 3);
	printf("- - -\n");

	jdlist_reverse(li);
	printf("Reversed and set 1 to MDI:\n");
	jdlist_set(li, 1, "MDI");
	jdlist_foreach(li, pr);
	printf("- - -\n");

	jdlist_free(li);

	// Again, test find
	li = jdlist_new();
	jdlist_append(li, "One");
	jdlist_append(li, "Two");
	jdlist_append(li, "Three");
	jdlist_append(li, "Four");
	jdlist_append(li, "Two");
	jdlist_append(li, "One");

	int i;
	printf("%d\n", (i = jdlist_find(li, "One")));
	assert(i == 0);
	printf("%d\n", (i = jdlist_find_from(li, "One", 1)));
	assert(i == 5);
	printf("%d\n", (i = jdlist_rfind(li, "Two")));
	assert(i == 4);
	printf("%d\n", i = jdlist_rfind_from(li, "Two", 4));
}

int main() {
	test_linear_list();
	printf("- - - - - - - - - - - - -\n");
	test_linked_list();
	printf("- - - - - - - - - - - - -\n");
	test_double_linked_list();

	printf("jllist, jlist, jdlist test ok!\n");

	return 0;
}
