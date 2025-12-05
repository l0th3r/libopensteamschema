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
    FILE* f = fopen("valid.json", "w");
    fputs("{\"key\":\"value\"}", f);
    fclose(f);

    TEST_ASSERT_EQUAL_INT(0, oid_load_schema(context, "valid.json"));

    remove("valid.json");
}

void test_oid_load_schema_valid_file_invalid_JSON(void)
{
    FILE* f = fopen("invalid_content.json", "w");
    fputs("{\n\"key\":\"value\n}", f);
    fclose(f);

    int result = oid_load_schema(context, "invalid_content.json");
    const json_error_t* err = oid_get_last_json_err(context);

    TEST_ASSERT_NOT_EQUAL_INT(0, result);
    TEST_ASSERT_NOT_EQUAL_INT(0, json_error_code(err));
    
    remove("invalid_content.json");
}

void test_oid_allocated_item_data(void)
{
    // First allocation
    int res = oid_alloc_item_def(context, 3);
    TEST_ASSERT_EQUAL_INT(0, res); /* Check no err code */
    TEST_ASSERT_EQUAL_INT(3, oid_get_item_def_capacity(context)); /* Check updated capacity */
    TEST_ASSERT_EQUAL_INT(0, oid_get_item_def_size(context)); /* Check non-updated size */

    // Second allocation (allocated 2 items)
    int res2 = oid_alloc_item_def(context, 2);
    TEST_ASSERT_EQUAL_INT(0, res2); /* Check no err code */
    TEST_ASSERT_EQUAL_INT(5, oid_get_item_def_capacity(context)); /* Check updated capacity */
    TEST_ASSERT_EQUAL_INT(0, oid_get_item_def_size(context)); /* Check non-updated size */
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_oid_load_schema_null_args);
    RUN_TEST(test_oid_load_schema_invalid_file);
    RUN_TEST(test_oid_load_schema_valid_file);
    RUN_TEST(test_oid_load_schema_valid_file_invalid_JSON);
    RUN_TEST(test_oid_allocated_item_data);
    return UNITY_END();
}
