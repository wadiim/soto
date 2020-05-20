#include "soto/soto.h"
#include "soto/sort.h"

#ifdef SOTO_TYPE
#undef SOTO_TYPE
#endif
#define SOTO_TYPE int
#include "sort_template.c"

#ifdef SOTO_TYPE
#undef SOTO_TYPE
#endif
#define SOTO_TYPE float
#include "sort_template.c"

#ifdef SOTO_TYPE
#undef SOTO_TYPE
#endif
#define SOTO_TYPE double
#include "sort_template.c"
