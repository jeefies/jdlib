#ifndef _JDLIB_STR_
#define _JDLIB_STR_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <jdlib.h>

jstr jstr_free(jstr str) {
	free(str);
	return NULL;
}

jstr jstr_copy(jstr sth) {
	if (sth == NULL)
		return NULL;
	int l = strlen(sth);

	jstr r = jstr_new(l + 1);
	memcpy(r, sth, l);
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

jstr jstr_trim(jstr str) {
	jstr rstr;

	// search for start
	while (isspace(*str)) {
		if (*str == '\0')
			return "";
		str++;
	}

	int rseek = strlen(str);
	// search for end
	// rseek -1 for ignore the last and make sure the length ok
	while (isspace(str[rseek - 1]))
		rseek--;


	rstr = jstr_new(rseek + 1);
	memcpy(rstr, str, rseek);

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
	for (int i = 0; i < strs->len; i++) {
		jstr str = strs->strs[i];
		// Free not NULL ones
		if (str != NULL) free(str);
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
}

jstr jstrs_index(const jstrs * strs, int index) {
	INDEX(strs,NULL);
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
}

jcode jstrs_set(jstrs * strs, int index, const jstr src) {
	INDEX(strs,JERR);

	jstrs_delete(strs, index);
	strs->strs[index] = jstr_copy(src);
}

jcode jstrs_delete(jstrs * strs, int index) {
	INDEX(strs,JERR);

	strs->strs[index] = jstr_free(strs->strs[index]);
}

#endif // _JDLIB_STR_
