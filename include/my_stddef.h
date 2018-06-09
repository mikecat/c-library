#ifndef MY_STDDEF_H_GUARD_5298F448_3D90_4E76_9BFB_881008E4780B
#define MY_STDDEF_H_GUARD_5298F448_3D90_4E76_9BFB_881008E4780B

#ifdef __cplusplus
#define MY_C_LIBRARY_EXTERN_C extern "C" {
#define MY_C_LIBRARY_EXTERN_C_END }
#else
#define MY_C_LIBRARY_EXTERN_C
#define MY_C_LIBRARY_EXTERN_C_END
#endif

typedef int my_pttrdiff_t;
typedef unsigned int my_size_t;

#define my_NULL ((void*)0)

#endif
