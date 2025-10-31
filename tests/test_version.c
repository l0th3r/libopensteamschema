#include "unity.h"
#include "opensteamschema/version.h"

void setUp(void) {}
void tearDown(void) {}

void test_oss_version_string(void) {
    const char* version = oss_version_string();
    TEST_ASSERT_NOT_NULL(version);
    TEST_ASSERT_EQUAL_STRING("0.0.1", version);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_oss_version_string);
    return UNITY_END();
}