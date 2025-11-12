#include "unity.h"
#include "context.h"
#include "parser.h"

#include <stdio.h>

static oid_context_t* context = NULL;

void setUp(void)
{
    context = oid_create_context();
    TEST_ASSERT_NOT_NULL(context);
}

void tearDown(void)
{
    oid_free_context(context);
    context = NULL;
}

void test_oid_load_schema_null_args(void)
{
    TEST_ASSERT_EQUAL_INT(1, oid_load_schema(NULL, "file.json"));
    TEST_ASSERT_EQUAL_INT(1, oid_load_schema(context, NULL));
}

void test_oid_load_schema_invalid_file(void)
{
    TEST_ASSERT_EQUAL_INT(2, oid_load_schema(context, "does_not_exist.json"));
}

void test_oid_load_schema_valid_file(void)
{
    oid_context_t* ctx = oid_create_context();
    FILE* f = fopen("valid.json", "w");
    fputs("{\"key\":\"value\"}", f);
    fclose(f);

    TEST_ASSERT_EQUAL_INT(0, oid_load_schema(ctx, "valid.json"));

    remove("valid.json");
    oid_free_context(ctx);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_oid_load_schema_null_args);
    RUN_TEST(test_oid_load_schema_invalid_file);
    RUN_TEST(test_oid_load_schema_valid_file);
    return UNITY_END();
}
