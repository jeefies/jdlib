#ifndef _JDLIST_HASH_C
#define _JDLIST_HASH_C
#include <stdio.h>
#include <stdlib.h>

#include <jdlib.h>

#define hash hashTime33

extern jht_node * jht_node_new(jstr key, jany val);
extern jht_node * jht_node_free(jht_node * node);
extern jht_node * jht_exists(jht * map, unsigned key);

// Use time33
unsigned int hashTime33(jstr str) {
	unsigned int hash = 5381;
	while (*str)
		hash += (hash << 5) + (*str++);

	return (hash & 0x7FFFFFFF);
}

jht * jht_new() {
	return jht_new_sized(JHT_DEFAULT);
}

jht * jht_new_sized(int max_length) {
	jht * map = (jht *)jmalloc(S_HT);
	map->item_len = max_length;
	map->len = 0;
	map->nodes = jllist_new(max_length);

	return map;
}

jcode jht_set(jht * map, jstr key, jany val) {
	rerr(map);
	jllist * nodes = map->nodes;

	jht_node * node = jht_node_new(key, val);
	rerr(node);
	// Short Key
	int skey = node->key % map->item_len;
	// printf("key %s with hash %u, short for %d\n", key, node->key, skey);
	// get the front pointer of the key group
	jht_node * to_node = jllist_index(nodes, skey);
	// If nothing exists in this key group
	if (to_node == NULL) {
		jllist_set(nodes, skey, node);
		// printf("nodes[%d] = %p, should be %p\n", skey, nodes->elems[skey], node);
		map->len++;
		return JOK;
	} else {
		// Check if the key is already exists
		jht_node * exist_node = jht_exists(map, node->key);
		if (exist_node) { // YES
			exist_node->val = val;
			jht_node_free(node);
		} else { // NO
			node->next = to_node->next;
			to_node->next = node;
		}
		map->len++;
		return JOK;
	}

	NOT_REACHED();
	return JERR;
}

jbool jht_isexists(jht * map, jstr skey) {
	rerr(map); rerr(skey);

	unsigned key = hash(skey);
	jht_node * node = jht_exists(map, key);
	if (node)
		return JTRUE;
	return JFALSE;
}

jht_node * jht_get_origin(jht * map, jstr skey) {
	rnull(map); rnull(skey);

	unsigned key = hash(skey);
	jht_node * node = jht_exists(map, key);
	if (node)
		return node;
	return NULL;
}

jany * jht_get(jht * map, jstr skey) {
	jht_node * node = jht_get_origin(map, skey);
	if (node)
		return node->val;
	return NULL;
}

jht_node * jht_exists(jht * map, unsigned key) {
	rnull(map);
	int group = key % map->item_len;
	// printf("Check full key: %d, short key: %d\n", key, group);

	jht_node * node = jllist_index(map->nodes, group);
	// Key does not exist
	rnull(node);

	// compare the key and return the node
	do {
		if (node->key == key)
			return node;
		node = node->next;
	} while (node != NULL);

	return NULL;
}

jht_node * jht_node_new(jstr key, jany val) {
	rnull(key);

	jht_node * node = (jht_node *)jmalloc(S_MN);
	node->val = val;
	node->key = hash(key);
	node->next = NULL;
	return node;
}

jht_node * jht_node_free(jht_node * node) {
	return jfree(node);
}

// Returns the node has the key.
// Returns NULL if the key doesn't exist
jbst_node * jbst_node_exist(jbst_node * bt, unsigned key) {
	rnull(bt);

	if (bt->key == key)
		return bt;

	if (bt->key < key) {
		// Current key is smaller than wanted key
		// Find in right nodes unless there's no right node anymore
		if (bt->right == NULL) return NULL;
		return jbst_node_exist(bt->right, key);
	} else {
		if (bt->left == NULL) return NULL;
		return jbst_node_exist(bt->left, key);
	}

	NOT_REACHED();
	return NULL;
}

jbst * jbst_new() {
	jbst * bt = (jbst *)jmalloc(S_BST);
	bt->node = NULL;
	return bt;
}

jbst_node * jbst_new_node(jany val, unsigned key) {
	jbst_node * nbt = (jbst_node *)jmalloc(S_BSTN);
	nbt->val = val;
	nbt->key = key;
	nbt->left = nbt->right = NULL;
	
	return nbt;
}

jbst_node * jbst_get_origin(jbst * bt, Cjstr skey) {
	rnull(bt);
	unsigned key = hash(skey);
	return jbst_node_exist(bt->node, key);
}

jbst_node * jbst_keyget_origin(jbst * bt, unsigned key) {
	rnull(bt);
	return jbst_node_exist(bt->node, key);
}

jany jbst_get(jbst * bt, Cjstr skey) {
	jbst_node * node = jbst_get_origin(bt, skey);
	if (!node) return NULL;
	return node->val;
}

jany jbst_keyget(jbst * bt, unsigned key) {
	jbst_node * node = jbst_keyget_origin(bt, key);
	if (!node) return NULL;
	return node->val;
}

jbool jbst_isexists(jbst * bt, Cjstr skey) {
	if (!jbst_get_origin(bt, skey)) return JFALSE;
	return JTRUE;
}

jbool jbst_keyisexists(jbst * bt, unsigned key) {
	if (!jbst_keyget_origin(bt, key)) return JFALSE;
	return JTRUE;
}

jcode jbst_set(jbst * bt, Cjstr skey, jany val) {
	unsigned key = hash(skey);
	return jbst_keyset(bt, key, val);
}

jcode jbst_keyset(jbst * bt, unsigned key, jany val) {
	rerr(bt);
	jbst_node * btn = bt->node;
	while (1) {
		if (btn->key == key) {
			btn->val = val;
			return JOK;
		}

		if (btn->key < key) {
			// Current Key is smaller than wanted key
			// Search In left Nodes
			if (btn->left == NULL) {
				jbst_node * nbtn = jbst_new_node(val, key);
				btn->left = nbtn;
			}

			btn = btn->left;
		} else {
			if (btn->right == NULL) {
				jbst_node * nbtn = jbst_new_node(val, key);
				btn->right = nbtn;
			}

			btn = btn->right;
		}
	}
	NOT_REACHED();
}

#endif // _JDLIST_HASH_C
