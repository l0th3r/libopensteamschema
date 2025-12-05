#ifndef OID_CONTEXT_H
#define OID_CONTEXT_H

#include "steam_types.h"

#include <jansson.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Type representing an openitemdef context.
 * 
 */
typedef struct oid_context_t oid_context_t;

/**
 * @brief Creates and initializes a new context.
 *
 * @return A pointer to the newly created context, or NULL if memory allocation fails.
 */
oid_context_t* oid_create_context(void);

/**
 * @brief Frees all resources associated with a context.
 *
 * @param context Pointer to the context to destroy. If NULL, the function performs no action.
 *
 * @note After this call, the pointer becomes invalid and must not be used in any further API calls.
 */
void oid_free_context(oid_context_t* context);

/* PARSING */

/**
 * @brief Pre-allocate data for parsing.
 * 
 * @param context Pointer to the context. If NULL, the function return 1.
 * @param allocate_size Amout of elements to allocate (not the size).
 * 
 * @note Allocation is dynamic this function will not overwrite or free any data.
 * @note Item counter will not be updated.
 * 
 * @return 0 if the allocation is successful, non-zero value if the allocation failed.
 */
int oid_alloc_item_def(oid_context_t* context, size_t allocate_size);

/**
 * @brief Free all parsed data from json.
 * 
 * @param context Pointer to the context. If NULL, the function performs no action.
 * 
 * @note Item counter will be set to 0.
 */
void oid_free_item_defs(oid_context_t* context);

/**
 * @brief Get the item definitions capacity.
 * 
 * @param context Pointer to the context.
 */
size_t oid_get_item_def_capacity(oid_context_t* context);

/**
 * @brief Get the item definitions size.
 * 
 * @param context Pointer to the context.
 */
size_t oid_get_item_def_size(oid_context_t* context);

/* Errors and info */

/**
 * @brief Retrieves the last JSON parsing error stored in the given context.
 *
 * Provides read-only access to the most recent JSON parsing or serialization
 * error encountered by the library. The returned pointer remains valid for the
 * lifetime of the context and must not be modified or freed by the caller.
 *
 * @param context Pointer to a valid context. Must not be NULL.
 * @return A pointer to the last stored JSON error, or NULL if context is NULL.
 */
const json_error_t* oid_get_last_json_err(const oid_context_t* context);

/**
 * @brief Stores a JSON parsing error into the given context.
 *
 * This function is intended to be used internally whenever a
 * Jansson parsing or loading operation fails.
 *
 * @param context Pointer to the context in which to store the error. If NULL, the function performs no action.
 * @param json_error Pointer to a @ref json_error_t structure provided by Jansson.
 */
void oid_set_json_error(oid_context_t* context, const json_error_t* json_error);

#ifdef __cplusplus
}
#endif
#endif
