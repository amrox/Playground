#include "library.h"

#include <stdlib.h>
#include <stddef.h>
#include <string.h>


int compare_ints(void const* a, void const* b)
{
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;

    // return (arg1 > arg2) - (arg1 < arg2); // possible shortcut
    // return arg1 - arg2; // erroneous shortcut (fails if INT_MIN is present)
}


int kth(int const v[static 1], size_t const v_len, int const k) {

    int v2[v_len];
    memcpy(v2, v, v_len * sizeof(int));
    qsort(v2, v_len, sizeof(int), compare_ints);

    return v2[k-1];
}
