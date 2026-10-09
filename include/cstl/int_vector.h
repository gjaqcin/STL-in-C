#ifndef CSTL_INT_VECTOR_H
#define CSTL_INT_VECTOR_H

#include <stdbool.h>
#include <stddef.h>

/*
 * Dynamic array of int values.
 *
 * Invariants after initialization:
 *   0 <= size <= capacity
 *   capacity == 0  => data == NULL
 *   capacity > 0   => data points to an allocated block of capacity ints
 *
 * This type owns its allocated memory. Do not copy it by assignment:
 * two copies would then own the same block (double free).
 */
typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} cstl_int_vector;

/* All functions require a valid pointer to an initialized vector,
 * except init(), which receives a valid, uninitialized vector.
 */

/** Initialize an empty vector. Call before any other operation. */
void cstl_int_vector_init(cstl_int_vector *v);

/** Free the allocated storage and reset the vector to its empty state.
 *  May be called again on the same initialized/destroyed vector.
 */
void cstl_int_vector_destroy(cstl_int_vector *v);

/** Append value, growing storage as necessary.
 *  Returns false on allocation/size overflow failure; in this case
 *  the vector and its elements remain unchanged.
 */
bool cstl_int_vector_push_back(cstl_int_vector *v, int value);

/** Remove the last logical element without shrinking capacity.
 *  Returns false if the vector is empty.
 */
bool cstl_int_vector_pop_back(cstl_int_vector *v);

/** Copy an element into *out.
 *  Returns false if index is invalid or out is NULL.
 *  On failure *out is not modified.
 */
bool cstl_int_vector_get(
    const cstl_int_vector *v, size_t index, int *out);

/** Overwrite an existing element.
 *  Returns false if index is invalid.
 */
bool cstl_int_vector_set(
    cstl_int_vector *v, size_t index, int value);

#endif /* CSTL_INT_VECTOR_H */
