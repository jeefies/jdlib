#include <stdlib.h>

#ifndef _JDLIB_BINARY_SEARCH_TREE_C_
#define _JDLIB_BINARY_SEARCH_TREE_C_

#include <jdlib.h>

#define hash hashTime33

// Use time33
unsigned int hashTime33(jstr str) {
	if (str == NULL) return 0;

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
		} else if (node->key < key) {
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



jbst_node * jbst_leftmaxkey(jbst_node * parent) {
	rnull(parent);

	jbst_node * child = parent->left;
	if (child == NULL) return parent;

	while (child->right != NULL) {
		parent = child;
		child = child->right;
	}

	parent->right = child->left;
	return child;
}

jbst_node * jbst_keydelete_origin(jbst * bt, unsigned key) {
	jbst_node * root = bt ? bt->node : NULL;
	rnull(root);

	// 处理删除root节点
	if (root->key == key) {
		// 如果没有子节点
		if (root->left == NULL && root->right == NULL) {
			bt->node = NULL;
			return root;
		}

		// 如果只有一个节点
		if (root->left == NULL && root->right != NULL) {
			bt->node = root->right;
			return root;
		} else if (root->right == NULL && root->left != NULL) {
			bt->node = root->left;
			return root;
		}
		
		// 寻找左树最大或右树最小(前者)
		jbst_node * lmax = jbst_leftmaxkey(root);
		bt->node = lmax;
		lmax->left = root->left;
		lmax->right = root->right;
		return root;
	}

	jbst_node * parent = root;
	jbst_node * child;
#define LEFT_NODE -1
#define RIGHT_NODE 1
	int status = 0;

	do {
		if (parent->key > key) {
			child = parent->left;
			status = LEFT_NODE;
		} else {
			child = parent->right;
			status = RIGHT_NODE;
		}

		if (child == NULL) {
			return NULL;
		}

		if (child->key == key) {
			// 如果没有子节点
			jbst_node ** parent_child;
			if (status == RIGHT_NODE) parent_child = &(parent->right);
			else parent_child = &(parent->left);

			if (child->left == NULL && child->right == NULL) {
				*parent_child = NULL;
				return child;
			}

			// 如果只有一个节点
			if (child->left == NULL && child->right != NULL) {
				*parent_child = child->right;
				return child;
			} else if (child->right == NULL && child->left != NULL) {
				*parent_child = child->left;
				return child;
			}
			
			// 寻找左树最大或右树最小(前者)
			jbst_node * lmax = jbst_leftmaxkey(child);
			*parent_child = lmax;
			lmax->left = child->left;
			lmax->right = child->right;

			return child;
		}

		parent = child;
	} while (1);

	NOT_REACHED();
	return NULL;
}

jany jbst_keydelete(jbst * bt, unsigned key) {
	jbst_node * r;
	return bt ? ((r = jbst_keydelete_origin(bt, key)) ? r->val : NULL) : NULL;
}

jany jbst_delete(jbst * bt, Cjstr skey) {
	return skey ? jbst_keydelete(bt, hash(skey)) : skey;
}

void jbst_node_preorder(jbst_node * node, JBT_CALL call) {
	if (node == NULL) return;
	call(node);
	jbst_node_preorder(node->left, call);
	jbst_node_preorder(node->right, call);
}

jcode jbst_preorder(jbst * bt, JBT_CALL call) {
	// 前序遍历，根，左，右
	rerr(bt);
	rerr(call);
	jbst_node_preorder(bt->node, call);
	return JOK;
}

void jbst_node_inorder(jbst_node * node, JBT_CALL call) {
	if (node == NULL) return;
	jbst_node_inorder(node->left, call);
	call(node);
	jbst_node_inorder(node->right, call);
}

jcode jbst_inorder(jbst * bt, JBT_CALL call) {
	// 中序遍历，左，根，右
	// 中序是按照key的大小顺序输出，可以用于排序
	rerr(bt);
	rerr(call);
	jbst_node_inorder(bt->node, call);
	return JOK;
}

void jbst_node_postorder(jbst_node * node, JBT_CALL call) {
	if (node == NULL) return;
	jbst_node_postorder(node->left, call);
	jbst_node_postorder(node->right, call);
	call(node);
}

jcode jbst_postorder(jbst * bt, JBT_CALL call) {
	// 后序遍历，左，右，根
	rerr(bt);
	rerr(call);
	jbst_node_postorder(bt->node, call);
	return JOK;
}
#endif // _JDLIB_BINARY_SEARCH_TREE_C_
