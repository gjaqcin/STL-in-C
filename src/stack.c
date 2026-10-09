#include "vector.h"

typedef struct
{
    vector storage;
} stack;

bool stack_push(stack *s, int value)
{
    return vector_push(&s->storage, value);
}

bool stack_pop (stack *s)
{
     return vector_pop(&s->storage);
}

bool stack_top(const stack *s, int *out)
{
    if (s->storage.size == 0) return false;
    return vector_get(&s->storage, s->storage.size - 1, out);
}

void stack_init(stack *s)
{
    vector_init(&s->storage);
}

void stack_destroy(stack *s)
{
    vector_destroy(&s->storage);
}
