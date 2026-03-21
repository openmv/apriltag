/* AprilTag platform abstraction layer.
 *
 * When APRILTAG_HAVE_CONFIG is defined, includes a user-provided
 * apriltag_config.h that can override allocators, assert, and feature macros.
 * Without it, the library compiles identically to upstream.
 */
#ifndef __APRILTAG_PLATFORM_H__
#define __APRILTAG_PLATFORM_H__

#ifdef APRILTAG_HAVE_CONFIG
#include "apriltag_config.h"
#endif

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// === Memory allocation ===
#ifndef apriltag_malloc
#define apriltag_malloc(s)      malloc(s)
#endif
#ifndef apriltag_calloc
#define apriltag_calloc(n, s)   calloc(n, s)
#endif
#ifndef apriltag_realloc
#define apriltag_realloc(p, s)  realloc(p, s)
#endif
#ifndef apriltag_free
#define apriltag_free(p)        free(p)
#endif

// strdup uses malloc internally — default impl uses apriltag_malloc.
#ifndef apriltag_strdup
static inline char *apriltag_strdup(const char *s) {
    size_t len = strlen(s) + 1;
    char *d = (char *) apriltag_malloc(len);
    if (d) memcpy(d, s, len);
    return d;
}
#endif

// === Assert ===
#ifndef apriltag_assert
  #ifdef APRILTAG_NO_ASSERT
    #define apriltag_assert(x) ((void)0)
  #else
    #include <assert.h>
    #define apriltag_assert(x) assert(x)
  #endif
#endif

#endif // __APRILTAG_PLATFORM_H__
