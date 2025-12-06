#include "schema.h"
#include "steam_types.h"

#include <jansson.h>

struct oid_schema_t
{
    oid_itemdef_t* item_defs;    /* parsed item definitions */
    size_t item_defs_capacity;   /* allocated item definitions */
    size_t item_defs_size;       /* amount of item definitions */

    json_error_t last_json_err; /* latest jansson parsing error */
};

oid_schema_t* oid_init_schema(void)
{
    return calloc(1, sizeof(oid_schema_t));
}

void oid_free_schema(oid_schema_t* schema)
{
    if (schema)
    {
        oid_free_item_defs(schema);
        free(schema);
    }
}

int oid_parse_json_to_struct(oid_schema_t* sch, json_t* jroot)
{
    if (!sch || !jroot || !json_is_object(jroot))
    {
        return 1;
    }

    oid_free_item_defs(sch);

    return 0;
}

int oid_load_itemdef_schema(oid_schema_t* sch, const char* file_path)
{
    if (!sch || !file_path)
    {
        return 1;
    }

    json_error_t json_err;
    json_t* root = json_load_file(file_path, 0, &json_err);
    if(!root)
    {
        oid_set_json_error(sch, &json_err);
        return 2;
    }

    int pres = oid_parse_json_to_struct(sch, root);

    json_decref(root);
    return pres;
}

int oid_alloc_item_defs(oid_schema_t* sch, size_t size)
{
    if (!sch)
    {
        return 1;
    }

    size_t newsz = sch->item_defs_capacity + size;
    oid_itemdef_t* tmp = realloc(sch->item_defs, newsz * sizeof(oid_itemdef_t));
    if (!tmp)
    {
        return 2;
    }
    
    sch->item_defs = tmp;
    sch->item_defs_capacity = newsz;
    return 0;
}

void oid_free_item_defs(oid_schema_t* sch)
{
    if (!sch)
    {
        return;
    }

    free(sch->item_defs);
    sch->item_defs_capacity = 0;
    sch->item_defs_size = 0;
}

size_t oid_get_schema_capacity(const oid_schema_t* sch)
{
    if (!sch)
    {
        return 0;
    }

    return sch->item_defs_capacity;
}

size_t oid_get_schema_size(const oid_schema_t* sch)
{
    if (!sch)
    {
        return 0;
    }

    return sch->item_defs_size;
}

/* ERROR HANDLING */

const json_error_t* oid_get_last_json_err(const oid_schema_t* sch)
{
    if (!sch)
    {
        return NULL;
    }

    return &sch->last_json_err;
}

void oid_set_json_error(oid_schema_t* sch, const json_error_t* err)
{
    if (!sch || !err)
    {
        return;
    }

    sch->last_json_err = *err;
}