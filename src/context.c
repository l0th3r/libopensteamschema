#include "opensteamschema/context.h"
#include <stdlib.h>

struct oss_context_t
{
    int* data;
};

oss_context_t* oss_create_context(void)
{
    oss_context_t* ctx = (oss_context_t*) malloc(sizeof(oss_context_t));

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

void oss_free_context(oss_context_t* ctx)
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
