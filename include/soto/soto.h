#ifndef SOTO_H
#define SOTO_H

#ifdef __cplusplus
extern "C" {
#endif

#define SOTO_CAT(X,Y) X##_##Y
#define SOTO_TEMPLATE(X,Y) SOTO_CAT(X,Y)

typedef char* char_ptr;

#ifdef __cplusplus
}
#endif

#endif // SOTO_H
