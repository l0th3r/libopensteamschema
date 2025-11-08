#ifndef OSS_CONTEXT_H
#define OSS_CONTEXT_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief type representing the OpenSteamSchema context.
 *
 * The internal structure is defined only in the implementation.
 * Users should only handle this pointer through the API functions.
 */
typedef struct oss_context_t oss_context_t;

/**
 * @brief Creates and initializes a new context.
 *
 * @return A pointer to the newly created context, or NULL if memory allocation fails.
 *
 * @note This function does not load or parse any file. It only prepares the internal structures required by the library.
 */
oss_context_t* oss_create_context(void);

/**
 * @brief Frees all resources associated with a context.
 *
 * @param context Pointer to the context to destroy. If NULL, the function performs no action.
 *
 * @note After this call, the pointer becomes invalid and must not be used in any further API calls.
 */
void oss_free_context(oss_context_t* context);

#ifdef __cplusplus
}
#endif
#endif
