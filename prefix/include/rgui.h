/** \file
 * rgui is a simple, intermediat gui library
 */
#ifndef RGUI_H_
#define RGUI_H_

#if defined(_WIN32) || defined(__CYGWIN__)
#ifdef RGUI_BUILD_SHARED
#define RGUI_PUBLIC __declspec(dllexport)
#else
#define RGUI_PUBLIC __declspec(dllimport)
#endif
#else
#if defined (RGUI_BUILD_SHARED ) && (defined (__GNUC__) || defined (__clang__))
#define RGUI_PUBLIC __attribute__((visibility("default")))
#else
#define RGUI_PUBLIC
#endif
#endif

#include <stddef.h>

/** \typedef usz
 * usz is a shorthand for size_t
 */
typedef size_t       usz;

/** \typedef uint
 * A short hand for an unsigned int. This is mostly used to make it
 * easier to interface with opengl and vulkan, as they don't support size_t.
 */
typedef unsigned int uint;

/**
 * Allocates a memory block that is size big. Returns NULL on error.
 */
typedef void *(*rgui_alloc)(void *user_data, usz size);
/**
 * The reallocation function used. The returned pointer has to contain the
 * same data from old_data.
 *
 * Returns NULL on error.
 */
typedef void *(*rgui_realloc)(void *user_data, void *old_data, usz new_size);
/**
 * The free function to free the memory of the memory block at old_data.
 */
typedef void *(*rgui_free)(void *user_data, void *old_data);

typedef struct rgui_allocator {
    rgui_alloc   alloc;
    rgui_realloc realloc;
    rgui_free    free;
    void        *user_data;
} rgui_allocator;

/**
 * rgui_ctx contains all the information required to use the rgui library.
 * Almost all functions take an ctx.
 */
typedef struct rgui_ctx rgui_ctx;
typedef int             rgui_id;

typedef struct rgui_vector2 {
    float x;
    float y;
} rgui_vector2;

/**
 * A rgui_vertex contains all the information for a singular vertex.
 * This is used to draw everything on the screen.
 */
typedef struct rgui_vertex {
    /** The x position of the vertex. */
    float x;
    /** The y position of the vertex. */
    float y;
    /** The z position of the vertex. */
    float z;
} rgui_vertex;

typedef struct rgui_vertices {
    uint         count;
    rgui_vertex *vertices;
} rgui_vertices;

/**
 * \param allocator The allocator required. Use rgui_basic_allocator for a
 * malloc/free based one.
 * \return NULL on failiure, else a valid rgui_ctx pointer.
 */
RGUI_PUBLIC rgui_ctx     *rgui_create_ctx(rgui_allocator allocator);

/**
 * Creates a
 */
RGUI_PUBLIC void          rgui_destroy_ctx(rgui_ctx *ctx);

/**
 * \param[in]   ctx
 *
 * To render the vertices correctly, user will also the indices from
 * rgui_ctx_index_data()
 *
 * \return A list of vertices to draw.
 */
RGUI_PUBLIC rgui_vertices rgui_ctx_vertex_data(rgui_ctx *ctx);

#endif // RGUI_H_
