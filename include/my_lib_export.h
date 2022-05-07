
#ifndef MY_LIB_EXPORT_H
#define MY_LIB_EXPORT_H

#ifdef MY_LIB_STATIC_DEFINE
#  define MY_LIB_EXPORT
#  define MY_LIB_NO_EXPORT
#else
#  ifndef MY_LIB_EXPORT
#    ifdef my_lib_EXPORTS
        /* We are building this library */
#      define MY_LIB_EXPORT 
#    else
        /* We are using this library */
#      define MY_LIB_EXPORT 
#    endif
#  endif

#  ifndef MY_LIB_NO_EXPORT
#    define MY_LIB_NO_EXPORT 
#  endif
#endif

#ifndef MY_LIB_DEPRECATED
#  define MY_LIB_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef MY_LIB_DEPRECATED_EXPORT
#  define MY_LIB_DEPRECATED_EXPORT MY_LIB_EXPORT MY_LIB_DEPRECATED
#endif

#ifndef MY_LIB_DEPRECATED_NO_EXPORT
#  define MY_LIB_DEPRECATED_NO_EXPORT MY_LIB_NO_EXPORT MY_LIB_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef MY_LIB_NO_DEPRECATED
#    define MY_LIB_NO_DEPRECATED
#  endif
#endif

#endif /* MY_LIB_EXPORT_H */
