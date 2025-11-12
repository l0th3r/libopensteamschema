#include "context.h"

#include <stdlib.h>
#include <string.h>

struct oid_context_t
{
    json_error_t last_json_err;
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
        free(ctx);
    }
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
