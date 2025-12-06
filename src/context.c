#include "context.h"
#include "schema.h"

#include <stdlib.h>
#include <string.h>

struct oid_context_t
{
    oid_schema_t* schema;
};

oid_context_t* oid_init_context(void)
{
    oid_context_t* ctx = calloc(1, sizeof(oid_context_t));

    if(!ctx)
    {
        return NULL;
    }

    ctx->schema = oid_init_schema();
    if (!ctx->schema)
    {
        free(ctx);
        return NULL;
    }

    return ctx;
}

void oid_free_context(oid_context_t* ctx)
{
    if (ctx)
    {
        oid_free_schema(ctx->schema);
        free(ctx);
    }
}
