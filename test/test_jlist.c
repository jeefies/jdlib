#include <stdio.h>
#include <assert.h>
#include <string.h>

#include <jdlib.h>


void test_linear_list() {
	jllist * list = jllist_new(5);
	assert(list->len == 0);
	assert(list->cap == 5);

	jllist_append(list, (jany)2);
	assert((long)list->elems[0] == 2);

	jllist_append_empty(list, (jany)3);
	assert((long)jllist_index(list, 1) == 3);

	jllist_append_empty(list, "Hello World");
	assert(strcmp(jllist_index(list, 2), "Hello World") == 0);
	// Test NULL 
	assert(jllist_index(list, -2) == NULL);
	assert(strcmp(jllist_index(list, -3), "Hello World") == 0);
	assert(jllist_free(list) == NULL);
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
	assert(strcmp(jlist_index(li, 1), "Mid Insert") == 0);

	jlist_remove(li, 0);
	assert(li->len == 3);
	assert(strcmp(jlist_index(li, 0), "Mid Insert") == 0);

	jlist_insert(li, 0, "SHOULD BE FIRST");
	assert(li->len == 4);
	assert(strcmp(jlist_index(li, 0), "SHOULD BE FIRST") == 0);
	
	// Test pop and popl
	assert(strcmp(jlist_popl(li), "SHOULD BE FIRST") == 0);
	assert(li->len == 3);
	assert((long)jlist_pop(li) == 10);
	// Test free
	jlist_free(li);
}

#define jcl jlist_classic
void print_jcl(jcl * l) {
	int len = jlist_classic_len(&l);
	printf("Length : %d\n", len);
	for (int i = 0; i < len; i++) {
		printf("Index[%d] = %s\n", i, l->val);
		l = l->next;
	}
}


void test_classic_linked_list() {
	jcl * li = NULL;

	jlist_classic_append(&li, "three");
	print_jcl(li); printf("\n");
	jlist_classic_append_left(&li, "one");
	print_jcl(li); printf("\n");
	jlist_classic_insert(&li, 1, "two");
	print_jcl(li); printf("\n");
	jlist_classic_append_left(&li, "zero");
	print_jcl(li); printf("\n");

	printf("Remove index[2] = %s, should be \"two\".\n", jlist_classic_remove(&li, 2));
	print_jcl(li); printf("\n");
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
	i = jdlist_find(li, "One");
	assert(i == 0);
	i = jdlist_find_from(li, "One", 1);
	assert(i == 5);
	i = jdlist_rfind(li, "Two");
	assert(i == 4);
	i = jdlist_rfind_from(li, "Two", 4);
	assert(i == 1);
}

int main() {
	test_linear_list();
	printf("- - - - - - - - - - - - -\n");
	test_linked_list();
	printf("- - - - - - - - - - - - -\n");
	test_double_linked_list();
	printf("- - - - - - - - - - - - -\n");
	test_classic_linked_list();

	printf("jllist, jlist, jdlist test ok!\n");

	return 0;
}
