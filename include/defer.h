#ifndef DEFER_H
#define DEFER_H

/* Go-style defer implementation */
#define __STRMERGE(a, b) a##b
#define _STRMERGE(a, b) __STRMERGE(a, b)
#ifdef __clang__

static void __attribute__ ((unused)) _clang_cleanup_func(void (^*dfunc) (void))
{
    (*dfunc) ();
}
#define defer(a) void (^_STRMERGE(__df_, __COUNTER__))(void) __attribute__((cleanup(_clang_cleanup_func))) __attribute__((unused)) = ^{ a; }

#else

#define __block
#define defer(a) void _STRMERGE(_cleanup_func_, __LINE__)(void *_STRMERGE(_cleanup_unused_, __LINE__) __attribute__((unused))) { a; } ; int _STRMERGE(_cleanup_var_, __LINE__) __attribute__((cleanup(_STRMERGE(_cleanup_func_, __LINE__)))) __attribute__((unused))

#endif

#endif // END DEBUG_H
