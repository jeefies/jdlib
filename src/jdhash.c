#ifndef _JDLIST_HASH_C
#define _JDLIST_HASH_C
#include <stdio.h>
#include <stdlib.h>

#include <jdlib.h>

extern jht_node * jht_node_new(jstr key, jany val);
extern jht_node * jht_node_free(jht_node * node);
extern jht_node * jht_exists(jht * map, unsigned key);

// Use time33
unsigned int hash(jstr str) {
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

	// Find in group
	// FIXED: Must be do while loop instead of normal while loop!
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

jbt * jbt_new() {
	return NULL;
}

jbt * jbt_new_node(jany val, jstr skey) {
	rnull(skey);

	unsigned key = hash(skey);
	jbt * nbt = (jbt *)jmalloc(S_BT);
	nbt->val = val;
	nbt->key = key;
	nbt->left = nbt->right = NULL;
	nbt->leftc = nbt->rightc = 0;
	
	return nbt;
}

jbt * jbt__exist(jbt * bt, unsigned key) {
	rnull(bt);

	if (bt->key == key)
		return bt;

	if (bt->key < key) {
		rnull(bt->right);
		return jbt__exist(bt->right, key);
	} else {
		rnull(bt->left);
		return jbt__exist(bt->left, key);
	}

	NOT_REACHED();
	return NULL;
}

#endif // _JDLIST_HASH_C
