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
static unsigned int hashTime33(jstr str) {
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

jany jht_delete(jht * map, jstr key) {
	rnull(map);
	jllist * nodes = map->nodes;
	unsigned ikey = hash(key);

	int skey = ikey % map->item_len;
	jht_node * front, * origin = jllist_index(nodes, skey);
	front = origin;
	while (front != NULL && front->next != NULL && front->key != ikey && front->next->key != ikey) {
		front = front->next;
	}

	if (front == NULL || front == origin) {
		jany val = front ? front->val : NULL;
		jllist_set(nodes, 0, jht_node_free(front));
		return val;
	}

	jany val = front->next->val;
	front->next = jht_node_free(front->next);
	return val;
}

jcode jht_set(jht * map, jstr key, jany val) {
	rerr(map);
	jllist * nodes = map->nodes;

	jht_node * node = jht_node_new(key, val);
	rerr(node);
	// Short Key
	int skey = node->key % map->item_len;
	// get the front pointer of the key group
	jht_node * to_node = jllist_index(nodes, skey);
	// If nothing exists in this key group
	if (to_node == NULL) {
		jllist_set(nodes, skey, node);
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
	// Return node->next after free if node is not NULL else NULL
	return node ? (jht_node *)((uintptr_t)node->next | (uintptr_t)jfree(node)) : NULL;
}

#endif // _JDLIST_HASH_C
