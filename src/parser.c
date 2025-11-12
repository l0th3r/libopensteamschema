#include "parser.h"

#include <jansson.h>

int oid_load_schema(oid_context_t* ctx, const char* file_path)
{
    if (ctx == NULL || file_path == NULL)
    {
        return 1;
    }

    json_error_t json_err;
    json_t* root = json_load_file(file_path, 0, &json_err);
    if(root == NULL)
    {
        oid_set_json_error(ctx, &json_err);
        return 2;
    }

    // TODO register local schema

    json_decref(root);
    return 0;
}