#ifndef OID_PARSER_H
#define OID_PARSER_H

#include "openitemdef/context.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Loads and parses an item schema JSON file.
 *
 * This function opens the specified file, reads its full contents,
 * and stores them inside the given context. Future versions will
 * extend this function to perform full JSON parsing and validation.
 *
 * @param context  Pointer to a valid context.
 * @param file_path Path to the JSON file to load.
 * @return 0 on success, non-zero value if the file cannot be read or parsed.
 */
int oid_load_schema(oid_context_t* context, const char* file_path);

#ifdef __cplusplus
}
#endif
#endif