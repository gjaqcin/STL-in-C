#include "cstl/int_vector.h"

#include <stdint.h> /* SIZE_MAX */
#include <stdlib.h> /* free, realloc */

void cstl_int_vector_init(cstl_int_vector *v)
{
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

void cstl_int_vector_destroy(cstl_int_vector *v)
{
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

bool cstl_int_vector_push_back(cstl_int_vector *v, int value)
{
    if (v->size == v->capacity)
    {
        /*
         * Grow geometrically: 4, 8, 16, ...
         * This makes push_back O(1) amortized (O(n) on a resize).
         *
         * Check overflow BEFORE multiplying sizes, since size_t
         * arithmetic wraps around on overflow.
         */
        const size_t max_elements = SIZE_MAX / sizeof(*v->data);
        size_t new_capacity = 4;

        if (v->capacity != 0)
        {
            if (v->capacity > max_elements / 2)
                return false;

            new_capacity = v->capacity * 2;
        }

        if (new_capacity > max_elements)
            return false;

        /*
         * realloc(NULL, bytes) acts like malloc(bytes).
         * On failure the old allocation stays valid, so only update
         * v->data after checking the temporary pointer.
         */
        int *temp = realloc(v->data, new_capacity * sizeof(*v->data));
        if (temp == NULL)
            return false;

        v->data = temp;
        v->capacity = new_capacity;
    }

    /* size is the index of the first unused slot. */
    v->data[v->size] = value;
    v->size++;
    return true;
}

bool cstl_int_vector_pop_back(cstl_int_vector *v)
{
    if (v->size == 0)
        return false;

    /* No need to erase an int: only [0, size) is logically valid. */
    v->size--;
    return true;
}

bool cstl_int_vector_get(const cstl_int_vector *v, size_t index, int *out)
{
    if (index >= v->size || out == NULL)
        return false;

    *out = v->data[index];
    return true;
}

bool cstl_int_vector_set(cstl_int_vector *v, size_t index, int value)
{
    if (index >= v->size)
        return false;

    v->data[index] = value;
    return true;
}
