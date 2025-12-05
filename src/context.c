#include "context.h"
#include "steam_types.h"

#include <stdlib.h>
#include <string.h>

struct oid_context_t
{
    oid_itemdef_t* item_defs;    /* parsed item definitions */
    size_t item_defs_capacity;   /* allocated item definitions */
    size_t item_defs_size;       /* amount of item definitions */

    json_error_t last_json_err; /* latest jansson parsing error */
};

oid_context_t* oid_create_context(void)
{
    oid_context_t* ctx = (oid_context_t*) malloc(sizeof(oid_context_t));

    if(ctx == NULL)
    {
        return NULL;
    }
    else
    {
        memset(ctx, 0, sizeof(*ctx));
        
        ctx->item_defs = NULL;
        ctx->item_defs_capacity = 0;
        ctx->item_defs_size = 0;
        
        return ctx;
    }
}

void oid_free_context(oid_context_t* ctx)
{
    if (ctx == NULL)
    {
        return;
    }
    else
    {
        oid_free_item_defs(ctx);
        free(ctx);
    }
}


int oid_alloc_item_def(oid_context_t* ctx, size_t size)
{
    if (ctx == NULL)
    {
        return 1;
    }

    size_t newsz = ctx->item_defs_capacity + size;
    oid_itemdef_t* tmp = realloc(ctx->item_defs, newsz * sizeof(oid_itemdef_t));
    if (tmp == NULL)
    {
        return 2;
    }
    
    ctx->item_defs = tmp;
    ctx->item_defs_capacity = newsz;
    return 0;
}

void oid_free_item_defs(oid_context_t* ctx)
{
    if (ctx == NULL)
    {
        return;
    }

    free(ctx->item_defs);
    ctx->item_defs_size = 0;
    ctx->item_defs_capacity = 0;
}

size_t oid_get_item_def_capacity(oid_context_t* ctx)
{
    if (ctx == NULL)
    {
        return 0;
    }

    return ctx->item_defs_capacity;
}

size_t oid_get_item_def_size(oid_context_t* ctx)
{
    if (ctx == NULL)
    {
        return 0;
    }

    return ctx->item_defs_size;
}


const json_error_t* oid_get_last_json_err(const oid_context_t* ctx)
{
    if (ctx == NULL)
    {
        return NULL;
    }

    return &ctx->last_json_err;
}

void oid_set_json_error(oid_context_t* ctx, const json_error_t* err)
{
    if (ctx == NULL || err == NULL)
    {
        return;
    }

    ctx->last_json_err = *err;
}
