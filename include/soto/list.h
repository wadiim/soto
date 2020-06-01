#ifndef SOTO_LIST_H
#define SOTO_LIST_H

#include "soto/soto.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef SOTO_TYPE
#undef SOTO_TYPE
#endif
#define SOTO_TYPE int
#include "list_template.h"

#ifdef SOTO_TYPE
#undef SOTO_TYPE
#endif
#define SOTO_TYPE float
#include "list_template.h"

#ifdef SOTO_TYPE
#undef SOTO_TYPE
#endif
#define SOTO_TYPE double
#include "list_template.h"

#ifdef SOTO_TYPE
#undef SOTO_TYPE
#endif
#define SOTO_TYPE char_ptr
#include "list_template.h"

#ifdef __cplusplus
}
#endif

#endif // SOTO_LIST_H
