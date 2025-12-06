#include "unity.h"
#include "context.h"

static oid_context_t* context = NULL;

void setUp(void)
{
    context = oid_init_context();
    TEST_ASSERT_NOT_NULL(context);
}

void tearDown(void)
{
    oid_free_context(context);
    context = NULL;
    TEST_ASSERT_NULL(context);
}

void test_context_creation(void)
{
    oid_context_t* ctx = oid_init_context();
    TEST_ASSERT_NOT_NULL(ctx);
    oid_free_context(ctx);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_context_creation);
    return UNITY_END();
}
