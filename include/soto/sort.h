#ifndef SOTO_SORT_H
#define SOTO_SORT_H

#include "soto/soto.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef SOTO_TYPE
#undef SOTO_TYPE
#endif
#define SOTO_TYPE int
#include "sort_template.h"

#ifdef SOTO_TYPE
#undef SOTO_TYPE
#endif
#define SOTO_TYPE float
#include "sort_template.h"

#ifdef SOTO_TYPE
#undef SOTO_TYPE
#endif
#define SOTO_TYPE double
#include "sort_template.h"

#ifdef SOTO_TYPE
#undef SOTO_TYPE
#endif
#define SOTO_TYPE char_ptr
#include "sort_template.h"

#ifdef __cplusplus
}
#endif

#endif // SOTO_SORT_H
