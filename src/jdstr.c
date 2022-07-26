#ifndef _JDLIB_STR_
#define _JDLIB_STR_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <jdlib.h>

jstr jstr_free(jstr str) {
	jfree(str);
	return NULL;
}

jstr jstr_copy(jstr sth) {
	rnull(sth);
	return jstr_lcopy(sth, strlen(sth));
}

jstr jstr_lcopy(jstr sth, int len) {
	rnull(sth);

	jstr r = jstr_new(len + 1);
	memcpy(r, sth, len);
	r[len] = '\0';
	return r;

}

jstr jstr_from(jstr sth) {
	return jstr_copy(sth);
}

jstr jstr_new(int size) {
	jstr r = (jstr)jmalloc(S_CH * size);
	r[size - 1] = '\0';
	return r;
}

jstr jstr_ltrim(jstr str) {
	// Trim left white space
	while (isspace(*str)) {
		if (*str == '\0') return "";
		str++;
	}
	return jstr_copy(str);
}

jstr jstr_rtrim(jstr str) {
	// rseek not only means the seek of the string but also means 
	// the length of the result string
	int rseek = strlen(str);
	// search for end
	// rseek -1 for ignore the last and make sure the length ok
	while (isspace(str[rseek - 1]))
		rseek--;

	jstr rstr = jstr_lcopy(str, rseek);
	return rstr;

}

jstr jstr_trim(jstr str) {
	jstr rstr;
	jstr lcleared_str;

	// Trim left
	lcleared_str = jstr_ltrim(str);
	// Trim right
	rstr = jstr_rtrim(lcleared_str);
	// Free left string
	jstr_free(lcleared_str);

	return rstr;
}

jstrs * jstrs_new_empty() {
	return jstrs_new(0);
}

jstrs * jstrs_new(int size) {
	jstrs * strs = (jstrs *)malloc(S_STR);

	strs->strs = (jstr *)malloc(S_STR * size);
	strs->len = size;

	return strs;
}

jstrs * jstrs_new_from(const jstrs * strs) {
	jstrs * r = jstrs_new(strs->len);
	for (int i = 0; i < strs->len; i++) {
		jstrs_set(r, i , jstrs_index(strs, i));
	}
	return r;
}

jstrs * jstrs_free(jstrs * strs) {
	rnull(strs);
	for (int i = 0; i < strs->len; i++) {
		jstr str = strs->strs[i];
		// Free not NULL ones
		jfree(str);
	}
	free(strs);

	return NULL;
}


// Read ops
jcode jstrs_print(const jstrs * strs, const jstr sep) {
	int i = 0;
	for (; i < strs->len - 1; i++) {
		jstr str = strs->strs[i];
		if (str == NULL)
			continue;
		printf("%s%s", strs->strs[i], sep);
	}
	printf(strs->strs[i]);

	return JOK;
}

jstr jstrs_index(const jstrs * strs, int index) {
	CHECK_INDEX(strs,NULL);
	return strs->strs[index];
}

int jstrs_find(const jstrs * strs, const jstr dst) {
	for (int i = 0; i < strs->len; i++) {
		jstr src = strs->strs[i];
		if (src != NULL && (strcmp(src, dst) == 0)) {
			return i;
		}
	}
	return -1;
}

// Write ops
jcode jstrs_append(jstrs * strs, const jstr src) {
	strs->strs = (jstr *)realloc(strs->strs, sizeof(jstr) * (strs->len + 1));
	strs->strs[strs->len++] = jstr_copy(src);

	return JOK;
}

jcode jstrs_set(jstrs * strs, int index, const jstr src) {
	CHECK_INDEX(strs,JERR);

	jstrs_remove(strs, index);
	strs->strs[index] = jstr_copy(src);

	return JOK;
}

jstr jstrs_remove(jstrs * strs, int index) {
	CHECK_INDEX(strs,NULL);

	jstr str = strs->strs[index];
	strs->strs[index] = NULL;

	return str;
}

#endif // _JDLIB_STR_
