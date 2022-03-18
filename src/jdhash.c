#ifndef _JDLIST_HASH_C
#define _JDLIST_HASH_C
#include <stdio.h>
#include <stdlib.h>

#include <jdlib.h>

extern jmap_node * jmap_node_new(jstr key, jany val);
extern jmap_node * jmap_node_free(jmap_node * node);
extern jmap_node * jmap_exists(jmap * map, unsigned key);

// Use time33
unsigned int hash(jstr str) {
	unsigned int hash = 5381;
	while (*str)
		hash += (hash << 5) + (*str++);

	return (hash & 0x7FFFFFFF);
}

jmap * jmap_new() {
	return jmap_new_sized(JMAP_DEFAULT);
}

jmap * jmap_new_sized(int max_length) {
	jmap * map = (jmap *)jmalloc(S_MAP);
	map->item_len = max_length;
	map->len = 0;
	map->nodes = jllist_new(max_length);
}

jcode jmap_set(jmap * map, jstr key, jany val) {
	rerr(map);
	jllist * nodes = map->nodes;

	jmap_node * node = jmap_node_new(key, val);
	rerr(node);
	// Short Key
	int skey = node->key % map->item_len;
	// printf("key %s with hash %u, short for %d\n", key, node->key, skey);
	// get the front pointer of the key group
	jmap_node * to_node = jllist_index(nodes, skey);
	// If nothing exists in this key group
	if (to_node == NULL) {
		jllist_set(nodes, skey, node);
		// printf("nodes[%d] = %p, should be %p\n", skey, nodes->elems[skey], node);
		map->len++;
		return JOK;
	} else {
		// Check if the key is already exists
		jmap_node * exist_node = jmap_exists(map, node->key);
		if (exist_node) { // YES
			exist_node->val = val;
			jmap_node_free(node);
		} else { // NO
			node->next = to_node->next;
			to_node->next = node;
		}
		map->len++;
		return JOK;
	}
}

jbool jmap_isexists(jmap * map, jstr skey) {
	rerr(map); rerr(skey);

	unsigned key = hash(skey);
	jmap_node * node = jmap_exists(map, key);
	if (node)
		return JTRUE;
	return JFALSE;
}

jany * jmap_get(jmap * map, jstr skey) {
	rnull(map); rnull(skey);

	unsigned key = hash(skey);
	jmap_node * node = jmap_exists(map, key);
	if (node)
		return node->val;
	return NULL;
}

jmap_node * jmap_exists(jmap * map, unsigned key) {
	rnull(map);
	int group = key % map->item_len;
	// printf("Check full key: %d, short key: %d\n", key, group);

	jmap_node * node = jllist_index(map->nodes, group);
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

jmap_node * jmap_node_new(jstr key, jany val) {
	rnull(key);

	jmap_node * node = (jmap_node *)jmalloc(S_MN);
	node->val = val;
	node->key = hash(key);
	node->next = NULL;
	return node;
}

jmap_node * jmap_node_free(jmap_node * node) {
	return jfree(node);
}


#endif // _JDLIST_HASH_C
