#include "vector.h"

#include <assert.h>
#include <stdio.h>

/* Run tests without defining NDEBUG: assert() is our test mechanism. */
static void test_empty_and_invalid_operations(void)
{
    vector v;
    vector_init(&v);

    assert(v.data == NULL);
    assert(v.size == 0);
    assert(v.capacity == 0);
    assert(!vector_pop(&v));

    int value = 123;
    assert(!vector_get(&v, 0, &value));
    assert(value == 123);
    assert(!vector_get(&v, 0, NULL));
    assert(!vector_set(&v, 0, 42));

    vector_destroy(&v);
    vector_destroy(&v); /* free(NULL) is safe */
}

static void test_growth_and_access(void)
{
    vector v;
    vector_init(&v);

    for (int i = 0; i < 100; i++)
    {
        assert(vector_push(&v, i * 10));
        assert(v.size == (size_t)(i + 1));
        assert(v.capacity >= v.size);
    }

    assert(v.capacity == 128); /* 4, 8, 16, 32, 64, 128 */
    for (size_t i = 0; i < v.size; i++)
    {
        int value = -1;
        assert(vector_get(&v, i, &value));
        assert(value == (int)i * 10);
    }

    assert(vector_set(&v, 2, 99));
    int value = -1;
    assert(vector_get(&v, 2, &value));
    assert(value == 99);

    value = 777;
    assert(!vector_get(&v, v.size, &value));
    assert(value == 777);
    assert(!vector_get(&v, 1, NULL));
    assert(!vector_set(&v, v.size, 1000));

    vector_destroy(&v);
    assert(v.data == NULL);
    assert(v.size == 0);
    assert(v.capacity == 0);
}

static void test_pop_and_reuse(void)
{
    vector v;
    vector_init(&v);

    assert(vector_push(&v, 10));
    assert(vector_push(&v, 20));
    assert(vector_push(&v, 30));

    size_t reserved = v.capacity;

    assert(vector_pop(&v));
    assert(vector_pop(&v));
    assert(vector_pop(&v));
    assert(!vector_pop(&v));
    assert(v.size == 0);
    assert(v.capacity == reserved);

    assert(vector_push(&v, 99));
    int value = 0;
    assert(vector_get(&v, 0, &value));
    assert(value == 99);
    assert(v.size == 1);
    assert(v.capacity == reserved);

    vector_destroy(&v);

    /* Destroyed objects can be initialized and reused. */
    vector_init(&v);
    assert(vector_push(&v, -10));
    assert(vector_get(&v, 0, &value));
    assert(value == -10);
    vector_destroy(&v);
}

int main(void)
{
    test_empty_and_invalid_operations();
    test_growth_and_access();
    test_pop_and_reuse();

    puts("All vector tests passed!");
    return 0;
}
