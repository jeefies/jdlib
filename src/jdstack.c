#ifndef _JD_STACK_C_
#define _JD_STACK_C_

#include <jdlib.h>

jstack_node * jstack_node_new(jany val) {
	jstack_node * node = (jstack_node *)jmalloc(sizeof(jstack_node));
	node->val = val;
	return node;
}

jstack_node * jstack_node_free(jstack_node * node) {
	rnull(node);
	jstack_node * next = node->next;
	jfree(node);
	return next;
}

jstack * jstack_new() {
	jstack * stk = (jstack *)jmalloc(sizeof(jstack));
	stk->front = NULL;
	return stk;
}

jcode jstack_push(jstack * stk, jany val) {
	rerr(stk);
	jstack_node * front = stk->front;
	stk->front = jstack_node_new(val);
	stk->front->next = front;
	return JOK;
}

jany jstack_pop(jstack * stk) {
	jany val = stk->front->val;
	stk->front = jstack_node_free(stk->front);
	return val;
}

void jstack_node_foreach(jstack_node * node, jany(*op)(jany)) {
	if (node == NULL) return;
	jstack_node_foreach(node->next, op);

	jany val = op(node->val);
	if (val != NULL) node->val = val;
}

jcode jstack_foreach(jstack * stk, jany(*op)(jany)) {
	rerr(stk); rerr(op);
	jstack_node_foreach(stk->front, op);
	return JOK;
}

#endif // _JD_STACK_C_
