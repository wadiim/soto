#ifndef SOTO_STACK_H
#define SOTO_STACK_H

#include "soto/soto.h"

#define SOTO_STACK_ALLOC_SIZE 64

#ifdef __cplusplus
extern "C" {
#endif

#ifdef SOTO_TYPE
#undef SOTO_TYPE
#endif
#define SOTO_TYPE int
#include "stack_template.h"

#ifdef SOTO_TYPE
#undef SOTO_TYPE
#endif
#define SOTO_TYPE float
#include "stack_template.h"

#ifdef SOTO_TYPE
#undef SOTO_TYPE
#endif
#define SOTO_TYPE double
#include "stack_template.h"

#ifdef SOTO_TYPE
#undef SOTO_TYPE
#endif
#define SOTO_TYPE char_ptr
#include "stack_template.h"

#ifdef __cplusplus
}
#endif

#endif // SOTO_STACK_H
