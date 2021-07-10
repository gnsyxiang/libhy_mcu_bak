/**
 *
 * Release under GPLv-3.0.
 * 
 * @file    hy_module.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    07/07 2021 17:11
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        07/07 2021      create the file
 * 
 *     last modified: 07/07 2021 17:11
 */
#ifndef __LIBHY_XXX_INCLUDE_HY_MODULE_H_
#define __LIBHY_XXX_INCLUDE_HY_MODULE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef void *(*create_t)(void *config);
typedef void (*destroy_t)(void *handle);
typedef struct {
    char        *name;
    void        **handle;
    void        *config;
    create_t    create;
    destroy_t   destroy;
} module_create_t;

typedef struct {
    char        *name;
    void        *handle;
    destroy_t   destroy;
} module_destroy_t;

#define HyUtilsArrayCnt(array) (int)(sizeof((array)) / sizeof((array)[0]))

#define RUN_CREATE(module)                                      \
    do {                                                        \
        int i = 0;                                              \
        int len = HyUtilsArrayCnt(module);                      \
        for (i = 0; i < len; ++i) {                             \
            module_create_t *create = &module[i];               \
            *create->handle = create->create(create->config);   \
            if (!*create->handle) {                             \
                LOGE("%s create error \n", create->name);       \
                break;                                          \
            }                                                   \
        }                                                       \
                                                                \
        if (i < len) {                                          \
            for (int j = i - 1; j >= 0; j--) {                  \
                module_create_t *create = &module[j];           \
                create->destroy(create->handle);                \
            }                                                   \
            return NULL;                                        \
        }                                                       \
    } while(0)

#define RUN_DESTROY(module)                                     \
    do {                                                        \
        for (int i = 0; i < HyUtilsArrayCnt(module); ++i) {     \
            module_destroy_t *destroy = &module[i];             \
            destroy->destroy(destroy->handle);                  \
        }                                                       \
    } while(0)

#ifdef __cplusplus
}
#endif

#endif

