#include "unity.h"
#include "context.h"

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

void test_context_creation(void)
{
    oid_context_t* ctx = oid_create_context();
    TEST_ASSERT_NOT_NULL(ctx);
    oid_free_context(ctx);
}

void test_set_and_get_json_error(void)
{
    json_error_t jerr;
    jerr.line = 42;
    jerr.column = 7;
    snprintf(jerr.text, sizeof(jerr.text), "Unexpected token");

    oid_set_json_error(context, &jerr);

    const json_error_t* last = oid_get_last_json_err(context);
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

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_context_creation);
    RUN_TEST(test_set_and_get_json_error);
    RUN_TEST(test_get_json_error_null_context);
    return UNITY_END();
}
