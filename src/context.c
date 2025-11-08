#include "context.h"
#include <stdlib.h>

struct oid_context_t
{
    int* data;
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
        ctx->data = (int*)malloc(sizeof(int));
        *ctx->data = 10;
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
        free(ctx->data);
        free(ctx);
    }
}
