#ifndef SOTO_UTILS_H
#define SOTO_UTILS_H

#include "soto/soto.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef SOTO_TYPE
#undef SOTO_TYPE
#endif
#define SOTO_TYPE int
#include "utils_template.h"

#ifdef SOTO_TYPE
#undef SOTO_TYPE
#endif
#define SOTO_TYPE float
#include "utils_template.h"

#ifdef SOTO_TYPE
#undef SOTO_TYPE
#endif
#define SOTO_TYPE double
#include "utils_template.h"

#ifdef SOTO_TYPE
#undef SOTO_TYPE
#endif
#define SOTO_TYPE char_ptr
#include "utils_template.h"

#ifdef __cplusplus
}
#endif

#endif // SOTO_UTILS_H
