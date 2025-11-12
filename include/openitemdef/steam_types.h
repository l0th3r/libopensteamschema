#ifndef OID_STEAM_TYPES_H
#define OID_STEAM_TYPES_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h> /* size_t */
#include <stdint.h> /* uint32_t */
#include <ctype.h> /* isxdigit */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * These types provide a C representation of the structures described in the
 * official Steamworks Inventory Schema documentation.
 *
 * Reference:
 *   https://partner.steamgames.com/doc/features/inventory/schema
 *
 * The goal of these definitions is to provide a direct yet flexible mapping
 * between the JSON schema used by Steam (item_schema.json) and internal
 * C structures. All fields are optional and may be extended with custom
 * attributes or tags to support game-specific logic.
*/

/**
 * @brief Represents a string key–value pair.
 * 
 * @note Used for dynamic properties:
 *  https://partner.steamgames.com/doc/features/inventory/dynamicproperties
 */
typedef struct oid_kv_t
{
    char* key;
    char* value;
} oid_kv_t;

/**
 * @brief Represents an item identifier with an associated quantity.
 *
 * @note Used in bundles, exchange recipes, and other contexts where a fixed
 * number of a given itemdefid is required.
 */
typedef struct oid_amount_t
{
    int itemdefid;
    int quantity;
} oid_amount_t;

/**
 * @brief Represents a list of (itemdefid × quantity) pairs.
 */
typedef struct oid_amount_list_t
{
    oid_amount_t* entries;
    size_t count;
} oid_amount_list_t;

/**
 * @brief Represents an item identifier with a probability weight.
 *
 * @note Used in generators and playtimegenerators to express drop chances.
 */
typedef struct oid_weight_t
{
    int itemdefid;
    double weight;
} oid_weight_t;

/**
 * @brief Represents a simple dynamic list of strings.
 *
 * @note Useful for fields like tags, store_tags, or language-specific names.
 */
typedef struct oid_strlist_t
{
    char** data;
    size_t count;
} oid_strlist_t;

/**
 * @brief Unique identifier for an item definition in the Steam Inventory Schema.
 *
 * @note For non-Workshop items, the value must be lower than 1,000,000.
 * Workshop items may use higher values.
 */
typedef struct oid_itemdefid_t
{
    int32_t value;
} oid_itemdefid_t;

/**
 * @enum oid_item_type_t
 * @brief Enumerates all valid item types recognized by Steam.
 */
typedef enum oid_item_type_t
{
    OID_ITEM_TYPE_ITEM,
    OID_ITEM_TYPE_BUNDLE,
    OID_ITEM_TYPE_GENERATOR,
    OID_ITEM_TYPE_PLAYTIME_GENERATOR,
    OID_ITEM_TYPE_TAG_GENERATOR,
    OID_ITEM_TYPE_UNKNOWN
} oid_item_type_t;

/**
 * @brief Represents 24-bit RGB colors used by the Steam Inventory Schema.
 *
 * @note Steam expects color strings like "FFA500" (hexadecimal RRGGBB).
 */
typedef struct oid_color_t
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    int valid; /* 0 = invalid, 1 = valid */
} oid_color_t;

/* ITEMDEF */
typedef struct oid_itemdef_t
{
    oid_itemdefid_t itemdefid;
    oid_item_type_t type;
    char* name;
    char* description;

    int tradable;
    int marketable;
    int hidden;

    char* icon_url;
    char* icon_url_large;
    oid_color_t background_color;
    oid_color_t name_color;

    oid_strlist_t tags;
    oid_strlist_t store_tags;

    oid_amount_list_t bundle;
    oid_amount_list_t exchange;

    char* promo;
    char* price;
    char* price_category;

    oid_kv_t* attributes;
    size_t attribute_count;
} oid_itemdef_t;

/* BUNDLE */
typedef struct oid_bundle_t
{
    int itemdefid;
    oid_amount_t* entries;
    size_t entry_count;
} oid_bundle_t;

/* GENERATOR */
typedef struct oid_generator_t
{
    int itemdefid;
    oid_weight_t* entries;
    size_t entry_count;
} oid_generator_t;

/* PLAYTIME GENERATOR */
typedef struct oid_playtime_generator_t {
    int itemdefid;
    int generator_id;
    int drop_interval;
    int drop_window;
    int drop_max_per_window;
    int use_drop_window;
    int use_drop_limit;
    int drop_limit;
} oid_playtime_generator_t;

/* EXCHANGE */
typedef struct oid_exchange_t {
    int itemdefid;
    oid_amount_t* inputs;
    size_t input_count;

    oid_amount_t* outputs;
    size_t output_count;
} oid_exchange_t;

/* Steam Localization
 *  https://partner.steamgames.com/doc/store/localization/languages */
static const char* OID_LANG_API_ARABIC      = "arabic";
static const char* OID_LANG_API_BULGARIAN   = "bulgarian";
static const char* OID_LANG_API_SCHINESE    = "schinese";
static const char* OID_LANG_API_TCHINESE    = "tchinese";
static const char* OID_LANG_API_CZECH       = "czech";
static const char* OID_LANG_API_DANISH      = "danish";
static const char* OID_LANG_API_DUTCH       = "dutch";
static const char* OID_LANG_API_ENGLISH     = "english";
static const char* OID_LANG_API_FINNISH     = "finnish";
static const char* OID_LANG_API_FRENCH      = "french";
static const char* OID_LANG_API_GERMAN      = "german";
static const char* OID_LANG_API_GREEK       = "greek";
static const char* OID_LANG_API_HUNGARIAN   = "hungarian";
static const char* OID_LANG_API_INDONESIAN  = "indonesian";
static const char* OID_LANG_API_ITALIAN     = "italian";
static const char* OID_LANG_API_JAPANESE    = "japanese";
static const char* OID_LANG_API_KOREAN      = "koreana";
static const char* OID_LANG_API_NORWEGIAN   = "norwegian";
static const char* OID_LANG_API_POLISH      = "polish";
static const char* OID_LANG_API_PORTUGUESE  = "portuguese";
static const char* OID_LANG_API_BRAZILIAN   = "brazilian";
static const char* OID_LANG_API_ROMANIAN    = "romanian";
static const char* OID_LANG_API_RUSSIAN     = "russian";
static const char* OID_LANG_API_SPANISH     = "spanish";
static const char* OID_LANG_API_LATAM       = "latam";
static const char* OID_LANG_API_SWEDISH     = "swedish";
static const char* OID_LANG_API_THAI        = "thai";
static const char* OID_LANG_API_TURKISH     = "turkish";
static const char* OID_LANG_API_UKRAINIAN   = "ukrainian";
static const char* OID_LANG_API_VIETNAMESE  = "vietnamese";

/**
 * @brief Parses a semicolon-separated list of "itemdefidxquantity" pairs.
 *
 * Examples:
 *   "100x5;200x2;300"  ->  [{100,5},{200,2},{300,1}]
 *   "101;102;103x10"   ->  [{101,1},{102,1},{103,10}]
 *
 * @param text Steam style bundle string (e.g., "101x2;102x5").
 * @return oid_amount_list_t containing parsed entries (caller frees).
 */
oid_amount_list_t oid_amount_list_from_string(const char* text);

/**
 * @brief Converts the list back to a Steam-style string.
 *
 * Caller frees the returned string.
 */
char* oid_amount_list_to_string(const oid_amount_list_t* list);

/**
 * @brief Frees all memory associated with an oid_amount_list_t.
 *
 * @param list Pointer to the list to release.
 */
void oid_amount_list_free(oid_amount_list_t* list);

/**
 * @brief Validates a Steam itemdefid according to Steamworks rules.
 *
 * Checks whether the given identifier is within the valid range for
 * Steam Inventory definitions. For non-Workshop items, the ID must
 * be strictly positive and below 1,000,000. Workshop items may use
 * higher values when workshop_allowed is non-zero.
 *
 * @param id               Item definition identifier to validate.
 * @param workshop_allowed 1 if Workshop IDs above 1,000,000 are permitted.
 * @return 1 if valid, 0 if invalid.
 */
int oid_itemdefid_valid(const oid_itemdefid_t id, int workshop_allowed);

/**
 * @brief Creates an oid_itemdefid_t from a raw integer value.
 *
 * @ref oid_itemdefid_valid to verify the resulting ID.
 *
 * @param val Integer value to convert.
 * @return oid_itemdefid_t containing the given value.
 */
oid_itemdefid_t oid_itemdefid_from_int(const int32_t val);

/**
 * @brief Extracts the integer value from an oid_itemdefid_t.
 *
 * @param id Item definition identifier structure.
 * @return The 32-bit integer value contained in id.
 */
int32_t oid_itemdefid_to_int(const oid_itemdefid_t id);

/**
 * @brief Converts a string from JSON into the corresponding item type.
 */
oid_item_type_t oid_item_type_from_string(const char* str);

/**
 * @brief Converts an item type enum into its canonical string form.
 */
const char* oid_item_type_to_string(const oid_item_type_t type);

/**
 * @brief Parses a 6-digit hexadecimal RGB string into an oid_color_t.
 * @param hex Null-terminated string like "FF0000".
 * @return Parsed color. If invalid, valid = 0.
 */
const oid_color_t oid_color_from_hex(const char* hex);

/**
 * @brief Converts an oid_color_t to its hexadecimal string form.
 * @param color Input color.
 * @param buffer Output buffer (must hold at least 7 bytes).
 */
void oid_color_to_hex(const oid_color_t color, char* buffer);

#ifdef __cplusplus
}
#endif
#endif