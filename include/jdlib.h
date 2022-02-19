#ifndef _JDLIB_C_H_
#define _JDLIB_C_H_

#define JOK 0
#define JERR 1
typedef char jcode;

#ifndef _LDLIB_STRS_
#define _LDLIB_STRS_
typedef char* jstr;
typedef struct jstrs {
	jstr * strs;
	int len;
} jstrs;

// Return a copy create by malloc
jstr jstr_copy(jstr sth);
jstr jstr_free(jstr str);

// Create a jstrs instance
jstrs * jstrs_new(int size);
jstrs * jstrs_new_empty();
jstrs * jstrs_new_from(const jstrs * strs);

// Cleanup
jcode jstrs_free(jstrs * strs);

// Read ops
// Return NULL if index is out of range
jstr jstrs_index(const jstrs * strs, int index);
// Print all content to stdout
jcode jstrs_print(const jstrs * strs, const jstr sep);
// Return the index match the src, return -1 if nothing find
int jstrs_find (const jstrs * strs, const jstr dst);

// Write ops
// It just spare a NULL space if src is NULL.
jcode jstrs_append(jstrs * strs, const jstr src);
jcode jstrs_delete(jstrs * strs, int index);
// It works like jstrs_delete if src is NULL
jcode jstrs_set(jstrs * strs, int index, const jstr src);
#endif // _LDLIB_STRS_

#ifndef _LDLIB_LIST_
#define _LDLIB_LIST_

typedef void* jany;
// Linear List
typedef struct jllist { 
	jany * elems;
	int len;
	int cap; // capacity
} jllist;

jllist * jllist_new(int size);
jllist * jllist_new_empty();
jcode jllist_append(jllist * l, jany elem);
jcode jllist_append_empty(jllist * l, jany elem);
jcode jllist_set(jllist * l, int index, jany elem);
jany jllist_index(jllist * l, int index);
jcode jllist_delete(jllist * l, int index);


// Linked List (Default List)
typedef struct jlist_node {
	jany val;
	struct jlist_node * next;
} jlist_node;

typedef struct jlist {
	jlist_node * node;
	int len;
} jlist;

// Double Linked List
typedef struct jdlist_node {
	jany val;
	struct jdlist_node * prev;
	struct jdlist_node * next;
} jdlist_node;

typedef struct jdlist {
	jdlist_node * node;
	int len;
} jdlist;

#endif // _LDLIB_LIST_

#define INDEX(x,r) if(index >= x->len)\
		return r;\
	if (index < 0 && ((index += x->len) < 0))\
		return r;
#endif // _JDLIB_C_H_
