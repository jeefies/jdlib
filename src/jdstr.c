#ifndef _JDLIB_STR_
#define _JDLIB_STR_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <jdlib.h>

/**
 * @brief 释放jstr占用的空间
 * @param str 需要释放的对象(如果为NULL不会出现段错误)
 */
jstr jstr_free(jstr str) {
	jfree(str);
	return NULL;
}

/**
 * @brief 将字符串复制到新的空间
 * @warning 函数调用了strlen，如果不是合格的字符串，则可能产生段错误
 * @param str 需要复制的对象
 * @retval 新的对象
 * @see jstr_lcopy
 */
jstr jstr_copy(jstr str) {
	rnull(str);
	return jstr_lcopy(str, strlen(str));
}

/**
 * @brief 给定长度复制字符串
 * @param str 需要复制的对象
 * @param len 需要复制的长度
 * @warning 这个函数会多申请一个字节的长度来放'\0'
 * @retval 新的对象
 * @see jstr_new
 */
jstr jstr_lcopy(jstr str, int len) {
	rnull(str);

	jstr r = jstr_new(len + 1);
	memcpy(r, str, len);
	r[len] = '\0';
	return r;

}

/**
 * @brief jstr_copy的另一个声明
 * @see jstr_copy
 */
jstr jstr_from(jstr sth) {
	return jstr_copy(sth);
}

/**
 * 创建一个新的jstr对象
 * @warning 会将最后一个字节设为'\0'，不会申请更多的内存
 * @param size 需要申请的字节数
 */
jstr jstr_new(int size) {
	jstr r = (jstr)jmalloc(S_CH * size);
	r[size - 1] = '\0';
	return r;
}

/**
 * 将左侧的空字符去除
 * @warning 空字符用内置函数`isspace`判定
 * @see jstr_rtrim, jstr_trim
 */
jstr jstr_ltrim(jstr str) {
	// Trim left white space
	while (isspace(*str)) {
		if (*str == '\0') return "";
		str++;
	}
	return jstr_copy(str);
}

/**
 * 移除右侧的空字符
 * @warning 空字符用内置函数`isspace`判定
 * @see jstr_ltrim, jstr_trim
 */
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

/**
 * 移除两段的空字符
 * @warning 空字符用内置函数`isspace`判定
 * @see jstr_ltrim, jstr_rtrim
 */
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

/**
 * 新建一个空字符串集
 * @warning 调用了jstrs_new
 * @see jstrs_new
 */
jstrs * jstrs_new_empty() {
	return jstrs_new(0);
}

/**
 * 新建一个有size个元素的字符串集，其中每一个元素都没有被初始化
 * @warning 请勿直接使用其内的元素，一般来说全部都是NULL
 * @see jstrs_index, jstrs_set, jstrs_append, jstrs_find, jstrs_free, jstrs_print, jstrs_remove
 */
jstrs * jstrs_new(int size) {
	jstrs * strs = (jstrs *)malloc(S_STR);

	strs->strs = (jstr *)malloc(S_STR * size);
	strs->len = 0;
	strs->cap = size;

	return strs;
}

/**
 * 依据给定的字符串集创建一个新的集
 * @warning 其中每一个元素都是原始集的直接应用（相同的指针）
 * @see jstrs_deepcopy_from
 */
jstrs * jstrs_copy_from(const jstrs * strs) {
	jstrs * r = jstrs_new(strs->cap);
	for (int i = 0; i < strs->cap; i++) {
		r->strs[i] = jstrs_index(strs, i);
	}
	return r;
}

/**
 * 依据给定的字符串集创建一个新的集
 * @warning 其中每一个元素都进行了内存拷贝
 * @see jstrs_copy_from
 */
jstrs * jstrs_deepcopy_from(const jstrs * strs) {
	jstrs * r = jstrs_new(strs->cap);

	for (int i = 0; i < strs->cap; i++) {
		jstrs_set(r, i, jstrs_index(strs, i));
	}

	return r;
}

/**
 * 释放集所占用的所有空间
 * @warning 会同时释放其中每一个元素所占用的空间
 * @see jstrs_free_only
 */
jstrs * jstrs_free(jstrs * strs) {
	rnull(strs);
	for (int i = 0; i < strs->cap; i++) {
		jstr str = strs->strs[i];
		// Free not NULL ones
		jfree(str);
	}
	free(strs);

	return NULL;
}

/**
 * 只释放jstrs本身占用的内存，不释放每个元素的内存
 */
jstrs * jstrs_free_only(jstrs * strs) {
	rnull(strs);
	return jfree(strs);
}


// Read ops
jcode jstrs_print(const jstrs * strs, const jstr sep) {
	int i = 0, pc = 0;
	while (pc < strs->len - 1) {
		jstr str = strs->strs[i++];
		if (str == NULL)
			continue;
		printf("%s%s", strs->strs[i - 1], sep);
		++pc;
	}
	while (strs->strs[i++] != NULL) printf(strs->strs[i - 1]);

	return JOK;
}

jstr jstrs_index(const jstrs * strs, int index) {
	if (index < 0 || strs->cap <= index) return NULL;
	return strs->strs[index];
}

int jstrs_find(const jstrs * strs, const jstr dst) {
	for (int i = 0; i < strs->cap; i++) {
		jstr src = strs->strs[i];
		if (src != NULL && (strcmp(src, dst) == 0)) {
			return i;
		}
	}
	return -1;
}

// Write ops
int jstrs_append(jstrs * strs, const jstr src) {
	for (int i = 0; i < strs->cap; i++) {
		if (strs->strs[i] == NULL) {
			strs->strs[i] = jstr_copy(src), ++strs->len;
			return i;
		}
	}
	strs->strs = (jstr *)realloc(strs->strs, sizeof(jstr) * (strs->cap + 1));
	strs->strs[strs->cap++] = jstr_copy(src);

	return strs->len++;
}

jcode jstrs_set(jstrs * strs, int index, const jstr src) {
	if (index < 0 || strs->cap <= index) return JERR;

	jstrs_remove(strs, index);
	strs->strs[index] = jstr_copy(src), ++strs->len;

	return JOK;
}

/**
 * 删除其中的某一个元素（只是会简单的哦标记为NULL, 参见jstrs_append)
 * @retval 原来的字符串
 * @see jstrs_append
 */
jstr jstrs_remove(jstrs * strs, int index) {
	if (index < 0 || strs->cap <= index) return NULL;

	jstr str = strs->strs[index];
	strs->strs[index] = NULL;

	if (str != NULL) --strs->len;

	return str;
}

#endif // _JDLIB_STR_
