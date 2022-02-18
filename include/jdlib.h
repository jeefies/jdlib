#ifndef _JDLIB_C_H_
#define _JDLIB_C_H_

typedef char* jstr;
typedef struct jstrs {
	jstr * strs;
	int length;
} jstrs;

// Return a copy create by malloc
jstr jstr_copy(jstr sth);
jstr jstr_free(jstr str);

// Create a jstrs instance
jstrs * jstrs_new(int size);
jstrs * jstrs_new_empty();
jstrs * jstrs_new_from(const jstrs * strs);

// Cleanup
void jstrs_free(jstrs * strs);

// Read ops
// Return NULL if index is out of range
jstr jstrs_index(const jstrs * strs, int index);
// Print all content to stdout
void jstrs_print(const jstrs * strs, const jstr sep);
// Return the index match the src, return -1 if nothing find
int jstrs_find (const jstrs * strs, const jstr dst);

// Write ops
// It just spare a NULL space if src is NULL.
void jstrs_append(jstrs * strs, const jstr src);
void jstrs_delete(jstrs * strs, int index);
// It works like jstrs_delete if src is NULL
void jstrs_set(jstrs * strs, int index, const jstr src);


#endif // _JDLIB_C_H_
