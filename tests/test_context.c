#include "unity.h"
#include "openitemdef.h"

void setUp(void) {}
void tearDown(void) {}

void test_context_creation(void)
{
    oid_context_t* ctx = oid_create_context();
    TEST_ASSERT_NOT_NULL(ctx);

    oid_free_context(ctx);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_context_creation);
    return UNITY_END();
}
