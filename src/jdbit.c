/**
 * @file jbst.c
 * @author  Jeefy Fu
 * @email jeefy163@163.com
 * @brief
 * 		树状数组的实现
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <limits.h>

#ifndef _JDLIB_BIT_INDEX_TREE_C_
#define _JDLIB_BIT_INDEX_TREE_C_

#include <jdlib.h>

static int sg_error_return = INT_MIN;

static int lowbit(int x) {
	return x & -x;
}

/**
 * 返回一个jbit对象
 */
jbit * jbit_new(int maxint) {
	// +1 for maxint
	jbit * r = (jbit *)malloc(sizeof(int) * (maxint + 1));
	r->maxint = maxint;
	return r;
}

/**
 * 在下标为i的位置加上v
 * @warning 这不是设置位置的值，下表超过最大值或者为负数都会直接返回
 * @see jbit_set
 */
void jbit_add(jbit * bit, int i, int v) {
	/*
	 * This judgement may cause some confusion, but better than cause segmentation fault
	 * The same for other functions judgement.
	 */
	if (i >= bit->maxint || i < 0) return;

	while (i < bit->maxint) {
		bit->storage[i] += v;
		i += lowbit(i);
	}
}

/**
 * 获取整个数组在下表及之前的所有数的和
 * @warning
 *  如果下表不合法，默认则会返回INT_MIN，虽然可能造成一些小小的迷惑
 *  可以通过jbit_global_set_error_return(int err_code)来改变默认值
 * @see jbit_global_set_error_return
 */
int jbit_sum(jbit * bit, int i) {
	if (i >= bit->maxint || i < 0) return sg_error_return;

	int r;
	while (i) {
		r += bit->storage[i];
		i -= lowbit(i);
	}

	return r;
}

/**
 * 获取下表为i的数的值
 * @warning
 *  如果下表不合法，默认则会返回INT_MIN，虽然可能造成一些小小的迷惑
 *  可以通过jbit_global_set_error_return(int err_code)来改变默认值
 * @see jbit_global_set_error_return, jbit_set
 */
int jbit_index(jbit * bit, int i) {
	if (i >= bit->maxint || i < 0) return sg_error_return;

	int r = bit->storage[i];
	while (i -= lowbit(i)) {
		r -= bit->storage[i];
	}
	return r;
}

/**
 * 将下表为i的数设置为val
 * @warning
 *  如果下表不合法，默认则会返回INT_MIN，虽然可能造成一些小小的迷惑
 *  可以通过jbit_global_set_error_return(int err_code)来改变默认值
 * @see jbit_global_set_error_return, jbit_index
 */
void jbit_set(jbit * bit, int i, int val) {
	if (i >= bit->maxint || i < 0) return;

	int origin = jbit_index(bit, i);
	jbit_add(bit, i, val - origin);
}

/**
 * 改变jbit遇到下表错误之后的默认返回值
 * @see jbit_index, jbit_set, jbit_sum
 */
void jbit_global_set_error_return(int err_code) {
	sg_error_return = err_code;
}

#endif // _JDLIB_BIT_INDEX_TREE_C_
