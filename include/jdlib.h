#ifndef _JDLIB_C_H_
#define _JDLIB_C_H_

#define JOK 0
#define JERR 1
typedef char jcode;

#ifndef _LDLIB_STRS_
#define _LDLIB_STRS_
typedef char jchar;
typedef jchar* jstr;
typedef struct jstrs {
	jstr * strs;
	int len;
} jstrs;

#define S_CHAR sizeof(jchar)
#define S_STR sizeof(jstr)
#define S_STRS sizeof(jstrs)

// Return a copy create by malloc
jstr jstr_copy(jstr sth);
// Return a new jstr instance (last space is set to '\0')
jstr jstr_new(int size);
jstr jstr_free(jstr str);

// str operations
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
jcode jstrs_delete(jstrs * strs, int index);
// It works like jstrs_delete if src is NULL
jcode jstrs_set(jstrs * strs, int index, const jstr src);
#endif // _LDLIB_STRS_

#ifndef _LDLIB_LIST_
#define _LDLIB_LIST_

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
jcode jllist_delete(jllist * l, int index);
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
jcode jlist_delete(jlist * l, int index);
jcode jlist_insert(jlist * l, int index, jany elem);
// Read Method
jany jlist_index(jlist * l, int index);


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
jcode jdlist_append(jdlist * l, jany val);
jcode jdlist_append_front(jdlist * l, jany val);
jcode jdlist_remove(jdlist * l, int index);
jcode jdlist_foreach(jdlist * l, jany(*)(jany, int));
jcode jdlist_foreach_reverse(jdlist * l, jany(*)(jany,int));

// For check the index if it's out of range
#define INDEX(x,r) if(index >= x->len)\
		return r;\
	if (index < 0 && ((index += x->len) < 0))\
		return r

#endif // _LDLIB_LIST_

// Generic Definations
#define ABS(x) x<0?-x:x
#define MAX(x,y) x<y?y:x
#define MIN(x,y) x<y?x:y
#define isnull(x) x==NULL
#define rnull(x) if(x==NULL)return NULL
jany jfree(jany p);
jany jmalloc(int size);
jany jrealloc(jany p, int size);

#endif // _JDLIB_C_H_
