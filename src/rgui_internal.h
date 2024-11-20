#ifndef RGUI_INTERNAL_H_
#define RGUI_INTERNAL_H_

#include <rgui.h>

#define RGUI_APPEND_ADVANCED(arr, items, capacity, count, item)   \
    do {                                                          \
        if ((arr)->capacity < (arr)->count + 1) {                 \
            RGUI_EXPAND_ADVANCED(arr, items, capacity, count,     \
                                 (arr)->count + 1, sizeof(item)); \
        }                                                         \
        (arr)->items[(arr)->count++] = item;                      \
    } while (0);

#define RGUI_EXPAND_ADVANCED(arr, items, capacity, count, new_size, item_size) \
    do {                                                                       \
        while ((arr)->capacity < new_size) {                                   \
            if ((arr)->items == NULL) {                                        \
                (arr)->items =                                                 \
                    ctx->allocator.alloc(ctx->allocator.user_data, new_size);  \
                (arr)->capacity = new_size;                                    \
                break;                                                         \
            }                                                                  \
            (arr)->items =                                                     \
                ctx->allocator.realloc(ctx->allocator.user_data, (arr)->items, \
                                       item_size * (arr)->capacity * 2);       \
            (arr)->capacity *= 2;                                              \
        }                                                                      \
        if ((arr)->items == NULL) {                                            \
            RGUI_MEMORY_ALLOCATION_HANDLER();                                  \
        }                                                                      \
    } while (0)

#define RGUI_APPEND(arr, items, item) \
    RGUI_APPEND_ADVANCED(arr, items, capacity, count, item)

#endif // RGUI_INTERNAL_H_
