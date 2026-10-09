#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include "vector.h"

/* LIFO stack of integers implemented using our vector.
 * Like vector, this structure owns its storage and must not be copied
 * by assignment.
 */
typedef struct
{
    vector storage;
} stack;

/* Initialize before use, and destroy when finished. */
void stack_init(stack *s);
void stack_destroy(stack *s);

/* Push onto the top. Returns false if allocation fails. */
bool stack_push(stack *s, int value);

/* Remove the top. Returns false if the stack is empty. */
bool stack_pop(stack *s);

/* Read the top without removing it.
 * Returns false if the stack is empty or out is NULL.
 * On failure, *out is not modified.
 */
bool stack_top(const stack *s, int *out);

#endif /* STACK_H */
