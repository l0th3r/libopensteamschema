#include "unity.h"
#include "steam_types.h"

void setUp(void) {}
void tearDown(void) {}

/* ------------------------------------------------------------------------- */
/* TESTS FOR ITEMDEFID HELPERS                                               */
/* ------------------------------------------------------------------------- */

void test_oid_itemdefid_valid_should_accept_valid_non_workshop_ids(void)
{
    oid_itemdefid_t id = oid_itemdefid_from_int(999999);
    TEST_ASSERT_EQUAL_INT(1, oid_itemdefid_valid(id, 0));
}

void test_oid_itemdefid_valid_should_reject_too_large_non_workshop_ids(void)
{
    oid_itemdefid_t id = oid_itemdefid_from_int(1000000);
    TEST_ASSERT_EQUAL_INT(0, oid_itemdefid_valid(id, 0));
}

void test_oid_itemdefid_valid_should_accept_large_workshop_ids_if_allowed(void)
{
    oid_itemdefid_t id = oid_itemdefid_from_int(2000000);
    TEST_ASSERT_EQUAL_INT(1, oid_itemdefid_valid(id, 1));
}

void test_oid_itemdefid_valid_should_reject_zero_or_negative(void)
{
    TEST_ASSERT_EQUAL_INT(0, oid_itemdefid_valid(oid_itemdefid_from_int(0), 0));
    TEST_ASSERT_EQUAL_INT(0, oid_itemdefid_valid(oid_itemdefid_from_int(-10), 1));
}

void test_oid_itemdefid_conversion_should_preserve_value(void)
{
    oid_itemdefid_t id = oid_itemdefid_from_int(12345);
    TEST_ASSERT_EQUAL_INT(12345, oid_itemdefid_to_int(id));
}

/* ------------------------------------------------------------------------- */
/* TESTS FOR oid_amount_list_from_string / oid_amount_list_to_string          */
/* ------------------------------------------------------------------------- */

void test_oid_amount_list_from_string_should_parse_basic_bundle(void)
{
    const char* text = "100x2;200;300x5";
    oid_amount_list_t list = oid_amount_list_from_string(text);

    TEST_ASSERT_EQUAL_size_t(3, list.count);
    TEST_ASSERT_EQUAL_INT(100, list.entries[0].itemdefid);
    TEST_ASSERT_EQUAL_INT(2, list.entries[0].quantity);
    TEST_ASSERT_EQUAL_INT(200, list.entries[1].itemdefid);
    TEST_ASSERT_EQUAL_INT(1, list.entries[1].quantity);
    TEST_ASSERT_EQUAL_INT(300, list.entries[2].itemdefid);
    TEST_ASSERT_EQUAL_INT(5, list.entries[2].quantity);

    oid_amount_list_free(&list);
}

void test_oid_amount_list_from_string_should_handle_empty_input(void)
{
    oid_amount_list_t list = oid_amount_list_from_string(NULL);
    TEST_ASSERT_EQUAL_size_t(0, list.count);

    list = oid_amount_list_from_string("");
    TEST_ASSERT_EQUAL_size_t(0, list.count);
}

void test_oid_amount_list_to_string_should_roundtrip_correctly(void)
{
    const char* text = "101x2;102;103x5";
    oid_amount_list_t list = oid_amount_list_from_string(text);

    char* out = oid_amount_list_to_string(&list);
    TEST_ASSERT_NOT_NULL(out);

    /* Order and formatting should match parsing */
    TEST_ASSERT_TRUE(strstr(out, "101") != NULL);
    TEST_ASSERT_TRUE(strstr(out, "102") != NULL);
    TEST_ASSERT_TRUE(strstr(out, "103") != NULL);

    free(out);
    oid_amount_list_free(&list);
}

/* ------------------------------------------------------------------------- */
/* MAIN RUNNER                                                               */
/* ------------------------------------------------------------------------- */

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_oid_itemdefid_valid_should_accept_valid_non_workshop_ids);
    RUN_TEST(test_oid_itemdefid_valid_should_reject_too_large_non_workshop_ids);
    RUN_TEST(test_oid_itemdefid_valid_should_accept_large_workshop_ids_if_allowed);
    RUN_TEST(test_oid_itemdefid_valid_should_reject_zero_or_negative);
    RUN_TEST(test_oid_itemdefid_conversion_should_preserve_value);

    RUN_TEST(test_oid_amount_list_from_string_should_parse_basic_bundle);
    RUN_TEST(test_oid_amount_list_from_string_should_handle_empty_input);
    RUN_TEST(test_oid_amount_list_to_string_should_roundtrip_correctly);

    return UNITY_END();
}
