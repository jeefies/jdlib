#ifndef _JDLIB_LIST_C_
#define _JDLIB_LIST_C_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <jdlib.h>

extern jlist_node * _jlist_node_new(jany val);
extern jdlist_node * _jdlist_node_new(jany val);
extern jlist_node * _jlist_node_free(jlist_node * node);
extern jdlist_node * _jdlist_node_free(jlist_node * node);

jllist * jllist_new_empty() {
	return jllist_new(0);
}

jllist * jllist_new(int cap_size) {
	jllist * l = (jllist *)malloc(sizeof(jllist));

	int memsize = sizeof(jany) * cap_size;
	l->elems = (jany *)malloc(memsize);
	l->len = 0;
	l->cap = cap_size;

	// Clear the elems to NULL or '\0'
	memset(l->elems, '\0', memsize);

	return l;
}

// Maybe This method is totally useless
// Append the element to first empty node
jcode jllist_append_empty(jllist * l, jany elem) {
	for (int i = 0; i < l->cap; i++) {
		if (l->elems[i] == NULL) {
			l->elems[i] = elem;
			l->len++;
			return JOK;
		}
	}

	return jllist_append(l, elem);
}

// Append the element at end of the List (alloc a new place)
jcode jllist_append(jllist * l, jany elem) {
	l->elems = (jany *)realloc(l->elems, sizeof(jany) * (++l->cap));
	l->len = l->cap;
	return JOK;
}

jcode jllist_set(jllist * l, int index, jany elem) {
	INDEX(l,JERR)

	if (l->elems[index] != NULL) l->len++;
	l->elems[index] = elem;
	return JOK;
}

jany jllist_index(jllist * l, int index) {
	INDEX(l,NULL)
	return l->elems[index];
}

jcode jllist_delete(jllist * l, int index) {
	INDEX(l,JERR)
	l->elems[index] = NULL;
	l->len--;
}

jllist * jllist_free(jllist * l) {
	free(l->elems);
	free(l);
	return NULL;
}

jlist * jlist_new() {
	jlist * l = (jlist *)malloc(sizeof(jlist));
	l->len = 0;
	return l;
}

jcode jlist_append(jlist * l, jany elem) {
	jlist_node * new = _jlist_node_new(elem);
	jlist_node * node = l->node;

	if (node == NULL) {
		l->node = new;
		l->len = 1;
		return JOK;
	}

	while (node->next != NULL) {
		node = node->next;
	}
	node->next = new;

	l->len++;
	return JOK;
}

jcode jlist_insert(jlist * l, int index, jany elem) {
	jlist_node * new = _jlist_node_new(elem);
	jlist_node * node = l->node;

	if (node == NULL) {
		l->node = new;
		goto END;
	}

	if (index == 0) {
		l->node = new;
		new->next = node;
		goto END;
	}

	for (int i = 0; i < index - 1; i++) {
		if (node->next == NULL) {
			node->next = new;
			goto END;
		}
		node = node->next;
	}

	new->next = node->next;
	node->next = new;

END:
	l->len++;
	return JOK;
}

jcode jlist_delete(jlist * l, int index) {
	jlist_node * node = l->node;
	if (node == NULL)
		return JERR;

	if (index == 0) {
		l->node = _jlist_node_free(node);
		goto __END;
	}

	for (int i = 0; i < index - 1; i++) {
		if (node->next == NULL)
			return JERR;
		node = node->next;
	}
	jlist_node * next = node->next;
	node->next = _jlist_node_free(next);

__END:
	l->len--;
	return JOK;
}

jany jlist_index(jlist * l, int index) {
	jlist_node * node = l->node;
	if (node == NULL) 
		return NULL;

	for (int i = 0; i < index; i++) {
		if (node->next == NULL)
			return NULL;
		node = node->next;
	}

	return node->val;
}

jlist * jlist_free(jlist * l) {
	jlist_node * node = l->node;
	while (node) {
		node = _jlist_node_free(node);
	}
	free(l);
	return NULL;
}

jdlist * jdlist_new() {
	jdlist * l = (jdlist *)malloc(sizeof(jdlist));
	l->len = 0;
	return l;
}

jdlist * jdlist_append(jdlist * l, jany val) {
	jdlist_node * new = _jlist_node_new(val);
	jdlist_node * node = l->node;
	jdlist_node * back = node->prev;
}


jlist_node * _jlist_node_new(jany val) {
	jlist_node * node = (jlist_node *)malloc(sizeof(jlist_node));
	node->val = val;
	return node;
}

jlist_node * _jlist_node_free(jlist_node * node) {
	if (node == NULL) return NULL;
	jlist_node * next = node->next;
	free(node);
	return next;
}

jdlist_node * _jdlist_node_new(jany val) {
	jdlist_node * node = (jdlist_node *)malloc(sizeof(jdlist_node));
	node->val = val;
	return node;
}

jdlist_node * _jdlist_node_free(jdlist_node * node) {
	if (node == NULL) return NULL;
	jdlist_node * next = node->next;
	free(node);
	return next;
}

#endif // _JDLIB_LIST_C_
