#include "stack.h"

#include <assert.h>
#include <stdio.h>

static void test_empty_stack(void)
{
    stack s;
    stack_init(&s);

    assert(s.storage.size == 0);
    assert(!stack_pop(&s));

    int result = 123;
    assert(!stack_top(&s, &result));
    assert(result == 123);

    stack_destroy(&s);
    stack_destroy(&s); /* free(NULL) is safe */
}

static void test_lifo_and_reuse(void)
{
    stack s;
    stack_init(&s);

    assert(stack_push(&s, 10));
    assert(stack_push(&s, 20));
    assert(stack_push(&s, 30));

    int top = 0;
    assert(stack_top(&s, &top));
    assert(top == 30);
    assert(s.storage.size == 3); /* top doesn't remove */
    assert(!stack_top(&s, NULL));

    const size_t reserved = s.storage.capacity;

    assert(stack_pop(&s));
    assert(stack_top(&s, &top) && top == 20);
    assert(stack_pop(&s));
    assert(stack_top(&s, &top) && top == 10);
    assert(stack_pop(&s));
    assert(!stack_pop(&s));
    assert(s.storage.size == 0);
    assert(s.storage.capacity == reserved);

    assert(stack_push(&s, 99));
    assert(stack_top(&s, &top) && top == 99);
    assert(s.storage.capacity == reserved);

    stack_destroy(&s);
}

static void test_growth(void)
{
    stack s;
    stack_init(&s);

    for (int i = 0; i < 100; i++)
        assert(stack_push(&s, i));

    assert(s.storage.size == 100);
    assert(s.storage.capacity == 128);

    for (int i = 99; i >= 0; i--)
    {
        int top = -1;
        assert(stack_top(&s, &top));
        assert(top == i);
        assert(stack_pop(&s));
    }

    assert(!stack_pop(&s));
    stack_destroy(&s);
}

int main(void)
{
    test_empty_stack();
    test_lifo_and_reuse();
    test_growth();

    puts("All stack tests passed!");
    return 0;
}
