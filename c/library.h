#ifndef C_LIBRARY_H
#define C_LIBRARY_H

#include <stddef.h>

// NOTE: no error handling, bad inputs will crash
extern int kth(int const v[static 1], size_t const v_len, int const k);

#endif //C_LIBRARY_H
