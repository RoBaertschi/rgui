#include <rgui.h>
#include <stdlib.h>
#include <string.h>

#include "rgui_internal.h"

// This is private, so we don't need to prefix it
typedef struct window {
    rgui_id      id;
    rgui_vector2 pos;
    rgui_vector2 size;
    char        *name;
} window;

typedef struct windows {
    rgui_id id;
    usz     count;
    usz     capacity;
    window *windows;
} windows;

struct rgui_ctx {
    /** The allocator that gets used to allocate permanent and temporary data.
     */
    rgui_allocator allocator;
    windows        windows;
    rgui_id        current_window;
};

RGUI_PUBLIC rgui_ctx *rgui_create_ctx(rgui_allocator allocator) {
    rgui_ctx *ctx = allocator.alloc(allocator.user_data, sizeof(rgui_ctx));
    if (ctx == NULL) {
        return NULL;
    }

    *ctx = (rgui_ctx){
        .allocator = allocator,
        .windows   = {0},
    };

    char const *name_literal = "null";
    usz         name_len     = strlen(name_literal) + 1;
    char       *name         = allocator.alloc(allocator.user_data, name_len);
    memcpy(name, name_literal, name_len);

    window null_window = {
        .name = name,
        .id   = RGUI_INVALID_WINDOW_ID,
        .pos  = {0},
        .size = {0},
    };

    RGUI_APPEND(&ctx->windows, windows, null_window);

    return ctx;
}

RGUI_PUBLIC void rgui_destroy_ctx(rgui_ctx *ctx) {
    ctx->allocator.free(ctx->allocator.user_data, ctx);
}

RGUI_PUBLIC rgui_vertices rgui_ctx_vertex_data(rgui_ctx *ctx) {
    return (rgui_vertices){0};
}

RGUI_PUBLIC rgui_id rgui_begin_window(rgui_ctx *ctx, char *name) {
    rgui_id new_id     = ctx->windows.id++;

    window  new_window = {0};

    usz     name_len   = strlen(name) + 1;
    new_window.name = ctx->allocator.alloc(ctx->allocator.user_data, name_len);
    if (new_window.name == NULL) {
        RGUI_MEMORY_ALLOCATION_HANDLER();
    }
    memcpy(new_window.name, name, name_len);

    RGUI_APPEND(&ctx->windows, windows, new_window);

    if (ctx->windows.windows == NULL) {
        return 0;
    }

    ctx->current_window = new_id;

    return new_id;
}

RGUI_PUBLIC void rgui_end_window(rgui_ctx *ctx) { ctx->current_window = 0; }
