#include "unity.h"
#include "schema.h"

#include <stdio.h>

static oid_schema_t* schema = NULL;

void setUp(void)
{
    schema = oid_init_schema();
    TEST_ASSERT_NOT_NULL(schema);
}

void tearDown(void)
{
    oid_free_schema(schema);
    schema = NULL;
}

void test_set_and_get_json_error(void)
{
    json_error_t jerr;
    jerr.line = 42;
    jerr.column = 7;
    snprintf(jerr.text, sizeof(jerr.text), "Unexpected token");

    oid_set_json_error(schema, &jerr);

    const json_error_t* last = oid_get_last_json_err(schema);
    TEST_ASSERT_NOT_NULL(last);
    TEST_ASSERT_EQUAL_INT(42, last->line);
    TEST_ASSERT_EQUAL_INT(7, last->column);
    TEST_ASSERT_EQUAL_STRING("Unexpected token", last->text);
}

void test_get_json_error_null_context(void)
{
    const json_error_t* last = oid_get_last_json_err(NULL);
    TEST_ASSERT_NULL(last);
}

void test_oid_load_itemdef_schema_null_args(void)
{
    TEST_ASSERT_EQUAL_INT(1, oid_load_itemdef_schema(NULL, "file.json"));
    TEST_ASSERT_EQUAL_INT(1, oid_load_itemdef_schema(schema, NULL));
}

void test_oid_load_itemdef_schema_invalid_file(void)
{
    TEST_ASSERT_EQUAL_INT(2, oid_load_itemdef_schema(schema, "does_not_exist.json"));
}

void test_oid_load_itemdef_schema_valid_file(void)
{
    FILE* f = fopen("valid.json", "w");
    fputs("{\"key\":\"value\"}", f);
    fclose(f);

    TEST_ASSERT_EQUAL_INT(0, oid_load_itemdef_schema(schema, "valid.json"));

    remove("valid.json");
}

void test_oid_load_itemdef_schema_valid_file_invalid_JSON(void)
{
    FILE* f = fopen("invalid_syntax.json", "w");
    fputs("{\n\"key\":\"value\n}", f);
    fclose(f);

    int result = oid_load_itemdef_schema(schema, "invalid_syntax.json");
    const json_error_t* err = oid_get_last_json_err(schema);

    TEST_ASSERT_NOT_EQUAL_INT(0, result);
    TEST_ASSERT_NOT_EQUAL_INT(0, json_error_code(err));
    
    remove("invalid_syntax.json");
}

void test_oid_allocated_item_data(void)
{
    // First allocation
    int res = oid_alloc_item_defs(schema, 3);
    TEST_ASSERT_EQUAL_INT(0, res); /* Check no err code */
    TEST_ASSERT_EQUAL_INT(3, oid_get_schema_capacity(schema)); /* Check updated capacity */
    TEST_ASSERT_EQUAL_INT(0, oid_get_schema_size(schema)); /* Check non-updated size */

    // Second allocation (allocated 2 items)
    int res2 = oid_alloc_item_defs(schema, 2);
    TEST_ASSERT_EQUAL_INT(0, res2); /* Check no err code */
    TEST_ASSERT_EQUAL_INT(5, oid_get_schema_capacity(schema)); /* Check updated capacity */
    TEST_ASSERT_EQUAL_INT(0, oid_get_schema_size(schema)); /* Check non-updated size */
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_set_and_get_json_error);
    RUN_TEST(test_get_json_error_null_context);
    RUN_TEST(test_oid_load_itemdef_schema_null_args);
    RUN_TEST(test_oid_load_itemdef_schema_invalid_file);
    RUN_TEST(test_oid_load_itemdef_schema_valid_file);
    RUN_TEST(test_oid_load_itemdef_schema_valid_file_invalid_JSON);
    RUN_TEST(test_oid_allocated_item_data);
    return UNITY_END();
}
