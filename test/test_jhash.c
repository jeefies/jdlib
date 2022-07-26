#include <stdio.h>
#include <jdlib.h>
#include <assert.h>
#include <string.h>

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
	i = (long)jht_get(ht, "HEI");
	assert(i == 7);
	i = (long)jht_get(ht, "Hei");
	assert(i == 6);
	i = (long)jht_get(ht, "Shi");
	assert(i == 66);

	jht_delete(ht, "Fuckyou");
	assert(jht_get(ht, "Fuckyou") == NULL);

	printf("Test JHT ok\n");
}

// J Binary Search Tree
void test_jbst() {
	jbst * bt = jbst_new();

	jbst_set(bt, "Ha", "Ha");
	jbst_set(bt, "Hu", "Hu");
	jbst_set(bt, "Xi", "Xi");

	assert(strcmp(jbst_get(bt, "Ha"), "Ha") == 0);
	assert(strcmp(jbst_get(bt, "Hu"), "Hu") == 0);
	assert(strcmp(jbst_get(bt, "Xi"), "Xi") == 0);

	jbst_delete(bt, "Hu");
	assert(jbst_get(bt, "Hu") == NULL);

	printf("Test JBST 1 OK");
}

void printbt(jbst_node * node) {
	printf("%s\n", node->val);
}

void test_jbst2() {
	jbst * bt= jbst_new();

	jbst_keyset(bt, 10, "ten");
	jbst_keyset(bt, 5, "five");
	jbst_keyset(bt, 3, "three");
	jbst_keyset(bt, 7, "seven");
	jbst_keyset(bt, 1, "one");
	jbst_keyset(bt, 15, "ten-five");
	jbst_keyset(bt, 12, "ten-two");
	jbst_keyset(bt, 17, "ten-seven");
	jbst_keyset(bt, 19, "ten-nine");
	jbst_keyset(bt, 14, "ten-four");
	jbst_keyset(bt, 13, "ten-three");
	jbst_preorder(bt, printbt);
	printf("... Preorder\n\n");
	//       10
	//      /  \
	//     5   15
	//    / \  / \
	//   3  7 12 17
	//  /      \   \
	// 1        14  19
	//          /
	//         13

	jbst_keydelete(bt, 15);
	//       10
	//      /  \
	//     5   14
	//    / \  / \
	//   3  7 12 17
	//  /      \   \
	// 1        13  19
	jbst_node * root = bt->node;
	assert(root->right->key == 14);
	assert(root->right->right->key == 17);
	assert(root->right->left->key == 12);
	assert(root->right->left->right->key == 13);
	jbst_inorder(bt, printbt);
	printf("... Inorder\n\n");

	//       10
	//      /  \
	//     5   14
	//    /    / \
	//   3    12 17
	//  /      \   \
	// 1        13  19
	jbst_keydelete(bt, 7);
	assert(root->left->right == NULL);
	jbst_postorder(bt, printbt);
	printf("... Postorder\n\n");

	printf("Test JBST 2 OK\n");
}

int main() {
	test_jht();
	test_jbst();
	test_jbst2();
	return 0;
}
