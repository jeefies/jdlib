#ifndef _JDLIB_QUEUE_C_
#define _JDLIB_QUEUE_C_

#include <jdlib.h>

jqueue_node * jqueue_node_new(jany val) {
	jqueue_node * node = (jqueue_node *)jmalloc(sizeof(jqueue_node));
	node->val = val;
	return node;
}

jqueue * jqueue_new() {
	jqueue * jq = (jqueue *)jmalloc(sizeof(jqueue));
	jq->front = NULL;
	jq->back = NULL;
	return jq;
}

jcode jqueue_push(jqueue * jq, jany val) {
	rerr(jq);
	jqueue_node * new = jqueue_node_new(val);
	if (jq->back == NULL) {
		jq->front = jq->back = new;
		return JOK;
	}

	jq->back->next = new;
	jq->back = new;
}

jany jqueue_pop(jqueue * jq) {
	rnull(jq);
	if (jq->front == NULL) {
		return NULL;
	}

	if (jq->front == jq->back) jq->back == NULL;
	jqueue_node * cur = jq->front;
	jq->front = cur->next;
	return cur->val;
}

#endif // _JDLIB_QUEUE_C_
