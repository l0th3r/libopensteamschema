#include "parser.h"
#include "steam_types.h"

#include <jansson.h>

int oid_parse_json_to_struct(oid_context_t* ctx, json_t* jroot)
{
    if (ctx == NULL || jroot == NULL || !json_is_object(jroot))
    {
        return 1;
    }

    oid_free_item_defs(ctx);

    return 0;
}

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

    int pres = oid_parse_json_to_struct(ctx, root);

    json_decref(root);
    return pres;
}