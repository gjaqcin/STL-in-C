#include "vector.h"

#include <stdint.h> /* SIZE_MAX */
#include <stdlib.h> /* free, realloc */

void vector_init(vector *v)
{
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

void vector_destroy(vector *v)
{
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

bool vector_push(vector *v, int value)
{
    if (v->size == v->capacity)
    {
        const size_t max_elements = SIZE_MAX / sizeof(*v->data);
        size_t new_capacity = 4;
        if (v->capacity != 0)
        {
            if (v->capacity > max_elements / 2) return false;
            new_capacity = v->capacity * 2;
        }
        if (new_capacity > max_elements) return false;
        int *temp = realloc(v->data, new_capacity * sizeof(*v->data));
        if (temp == NULL) return false;

        v->data = temp;
        v->capacity = new_capacity;
    }
    v->data[v->size] = value;
    v->size++;
    return true;
}

bool vector_pop(vector *v)
{
    if (v->size == 0) return false;
    v->size--;
    return true;
}

bool vector_get(const vector *v, size_t index, int *out)
{
    if (index >= v->size || out == NULL) return false;

    *out = v->data[index];
    return true;
}

bool vector_set(vector *v, size_t index, int value)
{
    if (index >= v->size) return false;

    v->data[index] = value;
    return true;
}
