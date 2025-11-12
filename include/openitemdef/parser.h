#ifndef OID_PARSER_H
#define OID_PARSER_H

#include "context.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Loads and parses an item schema JSON file.
 *
 * @param context  Pointer to a valid context.
 * @param file_path Path to the JSON file to load.
 * @return 0 on success, non-zero value if the file cannot be read or parsed.
 * 
 * @note The file is released once parsed.
 * 
 */
int oid_load_schema(oid_context_t* context, const char* file_path);

#ifdef __cplusplus
}
#endif
#endif