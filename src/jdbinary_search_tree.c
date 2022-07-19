#include <stdlib.h>

#ifndef _JDLIB_BINARY_SEARCH_TREE_C_
#define _JDLIB_BINARY_SEARCH_TREE_C_

#include <jdlib.h>

#define hash hashTime33

// Use time33
unsigned int hashTime33(jstr str) {
	unsigned int hash = 5381;
	while (*str)
		hash += (hash << 5) + (*str++);

	return (hash & 0x7FFFFFFF);
}

jbst_node * jbst_node_new(int key, jany val) {
	jbst_node * node = (jbst_node *)malloc(S_BSTN);

	node->key = key;
	node->val = val;

	return node;
}

jbst_node * jbst_node_free(jbst_node * node) {
	jfree(node);
	return NULL;
}

jbst * jbst_new() {
	jbst * bst = (jbst *)malloc(sizeof(jbst));
	bst->node = NULL;
	return bst;
}

jbst * jbst_free(jbst * bt) {
	// TODO
}

jbst_node * jbst_keyget_origin(jbst * bt, unsigned key) {
	rnull(bt);

	jbst_node * node = bt->node;

	while (node != NULL && node->key != key) {
		if (node->key > key) {
			node = node->left;
		}

		if (node->key < key) {
			node = node->right;
		}
	}
	return node;
}

jbst_node * jbst_get_origin(jbst *bt, Cjstr skey) {
	return bt && skey ? jbst_keyget_origin(bt, hash(skey)) : NULL;
}

jbool jbst_keyisexists(jbst * bt, unsigned key) {
	return (bt && jbst_keyget_origin(bt, key)) ? JTRUE : JFALSE;
}

jbool jbst_isexists(jbst * bt, Cjstr key) {
	return key ? jbst_keyisexists(bt, hash(key)) : JFALSE;
}

jany jbst_keyget(jbst * bt, unsigned key) {
	rnull(bt);
	jbst_node * node = jbst_keyget_origin(bt, key);
	return node ? node->val : NULL;
}

jany jbst_get(jbst * bt, Cjstr key) {
	return key ? jbst_keyget(bt, hash(key)) : NULL;
}

jcode jbst_keyset(jbst * bt, unsigned key, jany val) {
	rerr(bt);

	jbst_node * node = bt->node;
	if (node == NULL) {
		bt->node = jbst_node_new(key, val);
		return JOK;
	}

	while (1) {
		if (node->key == key) {
			node->val = val;
			return JOK;
		}

		if (node->key < key) {
			if (node->right == NULL) {
				node->right = jbst_node_new(key, val);
				return JOK;
			}
			node = node->right;
		} else {
			if (node->left == NULL) {
				node->left = jbst_node_new(key, val);
				return JOK;
			}
			node = node->left;
		}
	}

	NOT_REACHED();
	return JFALSE;
}

jcode jbst_set(jbst * bt, Cjstr skey, jany val) {
	return skey ? jbst_keyset(bt, hash(skey), val) : JERR;
}

// FIXME:
// Can not handle situation like this:
//    20
//   /
// 17
//   \
//    18
// This would remove and return the min key node of the rigth tree
jbst_node * jbst_rightminkey(jbst_node * parent) {
	rnull(parent);

	jbst_node * child = parent->rigth;
	if (child == NULL) return parent;
	while (child != NULL && child->left != NULL) {
		parent = child;
		child = child->left;
	}

	parent->left = NULL;
	return child;
}

jbst_node * jbst_leftmaxkey(jbst_node * parent) {
	rnull(parent);

	jbst_node * child = parent->left;
	if (child == NULL) return parent;
	while (child->right != NULL) {
		parent = child;
		child = child->right;
	}

	parent->right = NULL;
	return child;
}

jany jbst_keydelete_replace(jbst_node * parent) {
	jbst_node * aim_node = parent->right ? jbst_rightminkey(parent) : jbst_leftmaxkey(parent);
	jany val = parent->val;
	if (aim_node == NULL) return NULL;
	parent->key = aim_node->key;
	parent->val = aim_node->val;
	jbst_node_free(aim_node);
	return val;
}

jany * jbst_keydelete(jbst * bt, unsigned key) {
	rnull(bt);

	jbst_node * child, * parent = bt->node;
	rnull(parent);
	if (parent->key == key) {
		jany val = jbst_keydelete_replace(parent);
		if (val == NULL && parent->key == key) {
			return bt->node = jbst_node_free(parent);
		}
	}

	child = (parent->key > key) ? parent->left : parent->right;
	rnull(child);

	while (1) {
		if (child->key == key) {
			jany val = jbst_keydelete_replace(child);
			if (val == NULL && child->key == key) {
				if (parent->key > key) {
					return parent->left = jbst_node_free(child);
				} else {
					return parent->right = jbst_node_free(child);
				}
			}
		}

		parent = child;
		child = (child->key > key) ? child->left : child->right;
		rnull(child);
	}
			
}

#endif // _JDLIB_BINARY_SEARCH_TREE_C_
