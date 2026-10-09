#include "cstl/int_vector.h"

#include <stdio.h>

int main(void)
{
    cstl_int_vector numbers;
    cstl_int_vector_init(&numbers);

    for (int i = 1; i <= 10; i++)
    {
        if (!cstl_int_vector_push_back(&numbers, i * 10))
        {
            fputs("Could not append an element.\n", stderr);
            cstl_int_vector_destroy(&numbers);
            return 1;
        }
    }

    printf("size=%zu, capacity=%zu\n", numbers.size, numbers.capacity);

    for (size_t i = 0; i < numbers.size; i++)
    {
        int value = 0;
        if (cstl_int_vector_get(&numbers, i, &value))
            printf("%d ", value);
    }
    putchar('\n');

    cstl_int_vector_destroy(&numbers);
    return 0;
}
