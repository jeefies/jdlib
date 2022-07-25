#ifndef _JDLIB_C_H_
#define _JDLIB_C_H_

#include <stdio.h>
#include <stdint.h>

#define JOK 0
#define JERR 1
#define JFALSE 0
#define JTRUE 1
typedef char jbool;
typedef char jcode;
#define Cjstr const jstr

#ifndef _JDLIB_STRS_
#define _JDLIB_STRS_
typedef char jchar;
typedef jchar* jstr;
typedef struct jstrs {
	jstr * strs;
	int len;
} jstrs;

#define S_CH sizeof(jchar)
#define S_STR sizeof(jstr)
#define S_STRS sizeof(jstrs)

// Return a copy create by malloc
jstr jstr_copy(jstr sth);
jstr jstr_lcopy(jstr sth, int len);
jstr jstr_from(jstr sth);
// Return a new jstr instance (last space is set to '\0')
jstr jstr_new(int size);
jstr jstr_free(jstr str);

// str operations
jstr jstr_ltrim(jstr str);
jstr jstr_rtrim(jstr str);
jstr jstr_trim(jstr str);
jstrs * jstr_sep(jstr str, const jchar chr);
jstrs * jstr_split(jstr str, const jstr sep);

// Create a jstrs instance
jstrs * jstrs_new(int size);
jstrs * jstrs_new_empty();
jstrs * jstrs_new_from(const jstrs * strs);

// Cleanup
jstrs * jstrs_free(jstrs * strs);

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
jcode jstrs_remove(jstrs * strs, int index);
// It works like jstrs_remove if src is NULL
jcode jstrs_set(jstrs * strs, int index, const jstr src);
#endif // _JDLIB_STRS_

#ifndef _JDLIB_LIST_
#define _JDLIB_LIST_

typedef void* jany;
#define S_ANY sizeof(jany)
// Linear List
typedef struct jllist { 
	jany * elems;
	int len;
	int cap; // capacity
} jllist;
#define S_LL sizeof(jllist)

jllist * jllist_new(int size);
jllist * jllist_new_empty();

jllist * jllist_free(jllist * l);

// Write Method
jcode jllist_append(jllist * l, jany elem);
jcode jllist_append_empty(jllist * l, jany elem);
jcode jllist_set(jllist * l, int index, jany elem);
jcode jllist_remove(jllist * l, int index);
// Read Method
jany jllist_index(jllist * l, int index);


// Linked List (Default List)
typedef struct jlist_node {
	jany val;
	struct jlist_node * next;
} jlist_node;
#define S_LN sizeof(jlist_node)

typedef struct jlist {
	jlist_node * node;
	int len;
} jlist;
#define S_L sizeof(jlist)

jlist * jlist_new();
jlist * jlist_free();
// Write Method
jcode jlist_append(jlist * l, jany elem);
jcode jlist_remove(jlist * l, int index);
jcode jlist_insert(jlist * l, int index, jany elem);

jany jlist_pop(jlist * l);
jany jlist_popl(jlist * l);
// Read Method
jany jlist_index(jlist * l, int index);

// Classic Linked List
struct jlist_classic {
	int remain_length;
	jany val;
	struct jlist_classic * next;
};
typedef struct jlist_classic jlist_classic;

jcode jlist_classic_append_left(jlist_classic ** l, jany elem);
jcode jlist_classic_append(jlist_classic ** l, jany elem);
jcode jlist_classic_insert(jlist_classic ** l, int index, jany elem);
jany jlist_classic_index(jlist_classic **  l, int index);
jany jlist_classic_remove(jlist_classic ** l, int index);
jany jlist_classic_pop(jlist_classic ** l);
jany jlist_classic_pop_left(jlist_classic ** l);

int jlist_classic_len(jlist_classic ** l);

// Double Linked List
typedef struct jdlist_node {
	jany val;
	struct jdlist_node * prev;
	struct jdlist_node * next;
} jdlist_node;
#define S_DLN sizeof(jdlist_node)

typedef struct jdlist {
	jdlist_node * start;
	jdlist_node * end;
	int len;
} jdlist;
#define S_DL sizeof(jdlist)
jdlist * jdlist_new();
jdlist * jdlist_free(jdlist * l);

jcode jdlist_append(jdlist * l, jany val);
jcode jdlist_append_front(jdlist * l, jany val);
jcode jdlist_insert(jdlist * l, int index, jany val);
jcode jdlist_remove(jdlist * l, int index);
jcode jdlist_set(jdlist * l, int index, jany val);
jcode jdlist_reverse(jdlist * l);

jany jdlist_index(jdlist * l, int index);
int jdlist_find(jdlist * l, jany val);
int jdlist_rfind(jdlist * l, jany val);
int jdlist_find_from(jdlist * l, jany val, int from);
int jdlist_rfind_from(jdlist * l, jany val, int from);
jcode jdlist_foreach(jdlist * l, jany(*)(jany, int));
jcode jdlist_foreach_reverse(jdlist * l, jany(*)(jany,int));

// For check the index if it's out of range
#define CHECK_INDEX(x,r) if(index >= x->len)\
		return r;\
	if (index < 0 && ((index += x->len) < 0))\
		return r
#define CHECK_INDEXC(x,r) if(index >= x->cap)\
		return r;\
	if (index < 0 && ((index += x->cap) < 0))\
		return r

#endif // _JDLIB_LIST_

#ifndef _JDLIB_HASHTABLE_
#define _JDLIB_HASHTABLE_

#define JHT_DEFAULT 33
typedef struct jht_node {
	unsigned int key;
	jany val;
	struct jht_node * next;
} jht_node;
#define S_MN sizeof(jht_node)
typedef struct jht {
	jllist * nodes;
	int len;
	int item_len; // The length of the nodes, default 33
} jht;
#define S_HT sizeof(jht)

jht * jht_new();
jht * jht_new_sized(int max_length);
jht * jht_free(jht * map);

jcode jht_set(jht * map, Cjstr key, jany val);
jany * jht_get(jht * map, Cjstr skey);
jht_node * jht_get_origin(jht * map, Cjstr skey);
jbool jht_isexists(jht * map, Cjstr skey);

jany jht_delete(jht * map, Cjstr key);

#endif // _JDLIB_HASHTABLE_

#ifndef _JDLIB_BINARY_SEARCH_TREE_
#define _JDLIB_BINARY_SEARCH_TREE_

typedef struct jbst_node {
	jany val;
	int key;
	struct jbst_node *left, *right;
} jbst_node;

typedef struct jbst {
	jbst_node * node;
} jbst;
#define S_BSTN sizeof(jbst_node)
#define S_BST sizeof(jbst)

jbst * jbst_new();
jbst * jbst_free(jbst * bt);

jcode jbst_set(jbst * bt, Cjstr skey, jany val);
jcode jbst_keyset(jbst * bt, unsigned key, jany val);
jany jbst_get(jbst * bt, Cjstr skey);
jany jbst_keyget(jbst * bt, unsigned key);
jbst_node * jbst_get_origin(jbst * bt, Cjstr skey);
jbst_node * jbst_keyget_origin(jbst * bt, unsigned key);
jbool jbst_isexists(jbst * bt, Cjstr skey);
jbool jbst_keyisexists(jbst * bt, unsigned key);

jany jbst_keydelete(jbst * bt, unsigned key);
jany jbst_delete(jbst * bt, Cjstr skey);

typedef void(*JBT_CALL)(jbst_node * node);
jcode jbst_preorder(jbst * bt, JBT_CALL call);
jcode jbst_postorder(jbst * bt, JBT_CALL call);
jcode jbst_inorder(jbst * bt, JBT_CALL call);

#endif // _JDLIB_BINARY_SEARCH_TREE_

#ifndef _JDLIB_STACK_
#define _JDLIB_STACK_
typedef struct jstack_node {
	jany val;
	struct jstack_node * next;
} jstack_node;

typedef struct jstack {
	jstack_node * front;
} jstack;

jstack * jstack_new();
jcode jstack_push(jstack * stk, jany val);
jany jstack_pop(jstack * stk);
jcode jstack_foreach(jstack * stk, jany(*)(jany val));


#endif // _JDLIB_STACK_

// Generic Definations
#define ABS(x) x<0?-x:x
#define MAX(x,y) x<y?y:x
#define MIN(x,y) x<y?x:y
#define isnull(x) x==NULL
#define rnull(x) if (x == NULL) return NULL
#define rerr(x) if (x == NULL) return JERR

#define NOT_REACHED() \
	do {\
		fprintf(stderr, "NOT_REACHED: %s:%d In function %s.\n", \
				__FILE__, __LINE__, __func__);\
		while (1);\
	} while (0);

jany jfree(jany p);
jany jmalloc(int size);
jany jrealloc(jany p, int size);

#endif // _JDLIB_C_H_
