#include "cstl/int_vector.h"

#include <assert.h>
#include <stdio.h>

/* Run tests without defining NDEBUG: assert() is our test mechanism. */
static void test_empty_and_invalid_operations(void)
{
    cstl_int_vector v;
    cstl_int_vector_init(&v);

    assert(v.data == NULL);
    assert(v.size == 0);
    assert(v.capacity == 0);
    assert(!cstl_int_vector_pop_back(&v));

    int value = 123;
    assert(!cstl_int_vector_get(&v, 0, &value));
    assert(value == 123);
    assert(!cstl_int_vector_get(&v, 0, NULL));
    assert(!cstl_int_vector_set(&v, 0, 42));

    cstl_int_vector_destroy(&v);
    cstl_int_vector_destroy(&v); /* free(NULL) is safe */
}

static void test_growth_and_access(void)
{
    cstl_int_vector v;
    cstl_int_vector_init(&v);

    for (int i = 0; i < 100; i++)
    {
        assert(cstl_int_vector_push_back(&v, i * 10));
        assert(v.size == (size_t)(i + 1));
        assert(v.capacity >= v.size);
    }

    assert(v.capacity == 128); /* 4, 8, 16, 32, 64, 128 */
    for (size_t i = 0; i < v.size; i++)
    {
        int value = -1;
        assert(cstl_int_vector_get(&v, i, &value));
        assert(value == (int)i * 10);
    }

    assert(cstl_int_vector_set(&v, 2, 99));
    int value = -1;
    assert(cstl_int_vector_get(&v, 2, &value));
    assert(value == 99);

    value = 777;
    assert(!cstl_int_vector_get(&v, v.size, &value));
    assert(value == 777);
    assert(!cstl_int_vector_get(&v, 1, NULL));
    assert(!cstl_int_vector_set(&v, v.size, 1000));

    cstl_int_vector_destroy(&v);
    assert(v.data == NULL);
    assert(v.size == 0);
    assert(v.capacity == 0);
}

static void test_pop_and_reuse(void)
{
    cstl_int_vector v;
    cstl_int_vector_init(&v);

    assert(cstl_int_vector_push_back(&v, 10));
    assert(cstl_int_vector_push_back(&v, 20));
    assert(cstl_int_vector_push_back(&v, 30));

    size_t reserved = v.capacity;

    assert(cstl_int_vector_pop_back(&v));
    assert(cstl_int_vector_pop_back(&v));
    assert(cstl_int_vector_pop_back(&v));
    assert(!cstl_int_vector_pop_back(&v));
    assert(v.size == 0);
    assert(v.capacity == reserved);

    assert(cstl_int_vector_push_back(&v, 99));
    int value = 0;
    assert(cstl_int_vector_get(&v, 0, &value));
    assert(value == 99);
    assert(v.size == 1);
    assert(v.capacity == reserved);

    cstl_int_vector_destroy(&v);

    /* Destroyed objects can be initialized and reused. */
    cstl_int_vector_init(&v);
    assert(cstl_int_vector_push_back(&v, -10));
    assert(cstl_int_vector_get(&v, 0, &value));
    assert(value == -10);
    cstl_int_vector_destroy(&v);
}

int main(void)
{
    test_empty_and_invalid_operations();
    test_growth_and_access();
    test_pop_and_reuse();

    puts("All CSTL int_vector tests passed!");
    return 0;
}
