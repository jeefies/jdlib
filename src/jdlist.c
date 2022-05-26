#ifndef _JDLIB_LIST_C_
#define _JDLIB_LIST_C_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <jdlib.h>

extern jlist_node * _jlist_node_new(jany val);
extern jdlist_node * _jdlist_node_new(jany val);
extern jlist_node * _jlist_node_free(jlist_node * node);
extern jdlist_node * _jdlist_node_free(jdlist_node * node);

jllist * jllist_new_empty() {
	return jllist_new(0);
}

jllist * jllist_new(int cap_size) {
	jllist * l = (jllist *)jmalloc(S_LL);

	int memsize = S_ANY * cap_size;
	l->elems = (jany *)jmalloc(memsize);
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
		if (isnull(l->elems[i])) {
			l->elems[i] = elem;
			l->len++;
			return JOK;
		}
	}

	return jllist_append(l, elem);
}

// Append the element at end of the List (alloc a new place)
jcode jllist_append(jllist * l, jany elem) {
	l->elems = (jany *)jrealloc(l->elems, S_ANY * (++l->cap));
	l->len = l->cap;
	return JOK;
}

jcode jllist_set(jllist * l, int index, jany elem) {
	INDEXC(l, JERR);

	if (l->elems[index] == NULL) l->len++;
	l->elems[index] = elem;
	return JOK;
}

jany jllist_index(jllist * l, int index) {
	INDEXC(l,NULL);
	return l->elems[index];
}

jcode jllist_remove(jllist * l, int index) {
	INDEXC(l,JERR);
	l->elems[index] = NULL;
	l->len--;
}

jllist * jllist_free(jllist * l) {
	free(l->elems);
	free(l);
	return NULL;
}

jlist * jlist_new() {
	jlist * l = (jlist *)jmalloc(S_L);
	l->len = 0;
	// Why it is must needed?
	l->node = NULL;
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

jcode jlist_remove(jlist * l, int index) {
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
	rnull(l);
	jlist_node * node = l->node;
	rnull(node);

	for (int i = 0; i < index; i++) {
		if (node->next == NULL)
			return NULL;
		node = node->next;
	}

	return node->val;
}

jany jlist_pop(jlist * l) {
	rnull(l);
	jlist_node * node = l->node;
	rnull(node);

	if (l->len == 1) {
		jany val = node->val;
		l->node = _jlist_node_free(node);
		l->len--;
		return val;
	}

	for (int i = 0; i < l->len - 2; i++) {
		node = node->next;
	}

	jany val = node->next->val;
	node->next = _jlist_node_free(node->next);

	l->len--;
	return val;
}

jany jlist_popl(jlist * l) {
	rnull(l);
	jlist_node * node = l->node;
	rnull(node);

	jany val = node->val;
	l->node = _jlist_node_free(node);
	l->len--;
	return val;
}

jlist * jlist_free(jlist * l) {
	jlist_node * node = l->node;
	while (node) {
		node = _jlist_node_free(node);
	}
	free(l);
	return NULL;
}

jlist_classic * jlist_classic_new() {
	return (jlist_classic *)malloc(sizeof(jlist_classic));
}

jlist_classic * jlist_classic_free(jlist_classic * li) {
	rnull(li);
	jlist_classic * next = li->next;
	free(li);
	return next;
}

jcode jlist_classic_check(jlist_classic ** l, jany elem) {
	if (*l == NULL) {
		*l = jlist_classic_new();
		(*l)->val = elem;
		return JOK;
	}
	return JERR;
}

jcode jlist_classic_depthappend(jlist_classic *  li, jany elem, int len, int aim) {
	li->remain_length = len;

	if (len == aim) {
		jlist_classic * newNode = jlist_classic_new();

		newNode->val = li->val;
		li->val = elem;

		if (li->next != NULL)
			newNode->next = li->next->next;

		li->next = newNode;
	}

	if (len > 0 && li->next == NULL) {
		li->next = jlist_classic_new();
	}

	if (li->next != NULL)
		return jlist_classic_depthappend(li->next, elem, len - 1, aim);
	return JOK;
}

jcode jlist_classic_append(jlist_classic ** l, jany elem) {
	if (jlist_classic_check(l, elem))
		jlist_classic_depthappend(*l, elem, (*l)->remain_length + 1, 0);
}

jcode jlist_classic_append_left(jlist_classic ** l, jany elem) {
	if (jlist_classic_check(l, elem))
		jlist_classic_depthappend(*l, elem, (*l)->remain_length + 1, (*l)->remain_length + 1);
}

jcode jlist_classic_insert(jlist_classic ** l, int index, jany elem) {
	if (jlist_classic_check(l, elem))
		jlist_classic_depthappend(*l, elem, (*l)->remain_length + 1, (*l)->remain_length + 1 - index);
}

jany jlist_classic_depthremove(jlist_classic * li, int len, int aim) {
	rnull(li);

	li->remain_length = len;
	if (len == aim) {
		// move next node's val to this and remove next node structure
		jany val = li->val;
		li->val = li->next->val;
		li->next = jlist_classic_free(li->next);

		jlist_classic_depthremove(li->next, len - 1, aim);
		return val;
	}

	if (li->next != NULL)
		return jlist_classic_depthremove(li->next, len - 1, aim);
	return NULL;
}

jany jlist_classic_remove(jlist_classic ** l, int index) {
	rnull(l);
	return jlist_classic_depthremove(*l, (*l)->remain_length - 1, (*l)->remain_length - 1 - index);
}

jany jlist_classic_pop(jlist_classic ** l) {
	rnull(l);
	return jlist_classic_depthremove(*l, (*l)->remain_length - 1, 0);
}

jany jlist_classic_pop_left(jlist_classic ** l) {
	rnull(l);
	return jlist_classic_depthremove(*l, (*l)->remain_length - 1, (*l)->remain_length - 1);
}

jlist_classic * jlist_classic_depthindex(jlist_classic * l, int aim) {
	if (l->remain_length == aim) {
		return l;
	}

	if (l->next) return jlist_classic_depthindex(l->next, aim);
	return NULL;
}

jany jlist_classic_index(jlist_classic ** l, int index) {
	rnull(l);

	jlist_classic * result =  jlist_classic_depthindex(*l, (*l)->remain_length - index);
	if (result) return result->val;
	return NULL;
}

int jlist_classic_len(jlist_classic ** l) {
	if (!l) return 0;
	return (*l)->remain_length + 1;
}

#define JDLIST_PRECHECK if (start == NULL) {\
		l->len = 1;\
		l->start = new;\
		l->end = new;\
		new->prev = NULL;\
		new->next = NULL;\
		return JOK;\
	}


jdlist * jdlist_new() {
	jdlist * l = (jdlist *)jmalloc(S_DL);
	l->len = 0;
	//  Why it must set to NULL?
	l->start = NULL;
	l->end = NULL;
	return l;
}

jdlist * jdlist_free(jdlist * l) {
	jdlist_node * node = l->start;
	while (node != NULL)
		node = _jdlist_node_free(node);
	return NULL;
}

jcode jdlist_append(jdlist * l, jany val) {
	jdlist_node * new = _jdlist_node_new(val);
	jdlist_node * start = l->start;

	// DEFINE
	JDLIST_PRECHECK;

	jdlist_node * end = l->end;
	end->next = new;
	new->prev = end;
	l->end = new;

	l->len++;
	return JOK;
}

jcode jdlist_append_front(jdlist * l, jany val) {
	jdlist_node * new = _jdlist_node_new(val);
	jdlist_node * start = l->start;

	// DEFINE
	JDLIST_PRECHECK;

	start->prev = new;
	new->next = start;
	l->start = new;

	l->len++;

	return JOK;
}

jcode jdlist_remove(jdlist * l, int index) {
	jdlist_node * start = l->start;
	INDEX(l,JERR);

	if (index == 0) {
		l->start = _jdlist_node_free(start);
		l->start->prev = NULL;
		goto END;
	}
	
	if (index < 0 && (index+=l->len) < 0)
		return JERR;

	for (int i = 0; i < index - 1; i++) {
		start = start->next;
	}

	start->next = _jdlist_node_free(start->next);
	start->next->prev = start;

END:
	l->len--;
	return JOK;
}

jcode jdlist_foreach(jdlist * l, jany(*operation)(jany,int)) {
	jdlist_node * start = l->start;
	for (int i = 0;;i++) {
		if (isnull(start)) return JOK;
		jany val = operation(start->val,i);
		if (val != NULL) start->val = val;
		start=start->next;
	}
	return JERR;
}

jcode jdlist_foreach_reverse(jdlist * l, jany(*operation)(jany,int)) {
	jdlist_node * end = l->end;
	for (int i = l->len-1;;i--) {
		if (isnull(end)) return JOK;
		jany val = operation(end->val,i);
		if (val != NULL) end->val = val;
		end = end->prev;
	}
	return JERR;
}

jcode jdlist_insert(jdlist * l, int index, jany val) {
	if (index == 0)
		return jdlist_append_front(l, val);
	else if (index >= l->len) 
		return jdlist_append(l, val);
	else if (index < 0 && (index+=l->len) < 0)
		return JERR;

	jdlist_node * new = _jdlist_node_new(val);
	jdlist_node * start = l->start;

	for (int i = 0; i < index - 1; i++)
		start = start->next;

	new->next = start->next;
	new->next->prev = new;
	start->next = new;
	new->prev = start;

	l->len++;
	return JOK;
}

jcode jdlist_set(jdlist * l, int index, jany val) {
	if (index == 0) {
		l->start->val = val;
		return JOK;
	} else if (index >= l->len) 
		return JERR;
	else if (index < 0 && (index+=l->len) < 0)
		return JERR;

	jdlist_node * node = l->start;
	for (int i = 0; i < index; i++)
		node = node->next;

	node->val = val;
	return JOK;
}

jany jdlist_index(jdlist * l, int index) {
	jdlist_node * start = l->start;

	if (index > l->len)
		return NULL;
	else if (index < 0 && (index+=l->len) < 0)
		return NULL;

	for (int i = 0; i < index - 1; i++) 
		start = start->next;

	return start->val;
}

int _jdlist_find(jdlist * l, jany val, int from, int end) {
	jdlist_node * node = l->start;
	for (int i = 0; i < l->len; i++) {
		if (i < from) {
			node = node->next;
			continue;
		};
		if (i >= end) break;
		if (node->val == val) return i;
		node = node->next;
	}
	return -1;
}

int _jdlist_rfind(jdlist * l, jany val, int from, int end) {
	jdlist_node * node = l->end;
	for (int i = l->len - 1; i >= 0; i--) {
		if (i >= end) {
			node = node->prev;
			continue;
		}
		if (i < from) break;
		if (node->val == val) return i;
		node = node->prev;
	}
	return -1;
}

int jdlist_find(jdlist * l, jany val) {
	return _jdlist_find(l, val, 0, l->len);
}

int jdlist_rfind(jdlist * l, jany val) {
	return _jdlist_rfind(l, val, 0, l->len);
}

int jdlist_find_from(jdlist * l, jany val, int from) {
	return _jdlist_find(l, val, from, l->len);
}

int jdlist_rfind_from(jdlist * l, jany val, int from) {
	return _jdlist_rfind(l, val, 0, from);
}

jcode jdlist_reverse(jdlist * l) {
	jdlist_node * node = l->start;

	jdlist_node * start = l->start;
	jdlist_node * end = l->end;

	rerr(start);

	// FIXED: could not real reverse the double linked list
	// It's caused by insertion operations.
	// I missed changing ->next->prev to inserted one.
	jdlist_node * tmp;
	for (int i = 0; i < l->len; i++) {
		tmp = node->next;
		node->next = node->prev;
		node->prev = tmp;
		node = tmp;
	}
	// At last, tmp also node is NULL

	l->end = start;
	l->start = end;
	return JOK;
}

jlist_node * _jlist_node_new(jany val) {
	jlist_node * node = (jlist_node *)jmalloc(S_LN);
	node->val = val;
	node->next = NULL;
	return node;
}

jlist_node * _jlist_node_free(jlist_node * node) {
	rnull(node);
	jlist_node * next = node->next;
	free(node);
	return next;
}

jdlist_node * _jdlist_node_new(jany val) {
	jdlist_node * node = (jdlist_node *)jmalloc(S_DLN);
	node->val = val;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

jdlist_node * _jdlist_node_free(jdlist_node * node) {
	rnull(node);
	jdlist_node * next = node->next;
	jfree(node);
	return next;
}

#endif // _JDLIB_LIST_C_
