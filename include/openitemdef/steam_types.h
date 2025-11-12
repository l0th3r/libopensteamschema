#ifndef OID_STEAM_TYPES_H
#define OID_STEAM_TYPES_H

#include <stddef.h>  /* size_t */
#include <stdint.h>  /* uint32_t */

#ifdef __cplusplus
extern "C" {
#endif

/**
 *
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
 * @brief Represents a string key–value pair (for arbitrary properties).
 */
typedef struct oid_kv_t
{
    char* key;
    char* value;
} oid_kv_t;

/**
 * @brief Represents an item identifier with an associated quantity.
 *
 * Used in bundles, exchange recipes, and other contexts where a fixed
 * number of a given itemdefid is required.
 */
typedef struct oid_amount_t
{
    int itemdefid;
    int quantity;
} oid_amount_t;

/**
 * @brief Represents an item identifier with a probability weight.
 *
 * Used in generators and playtimegenerators to express drop chances.
 */
typedef struct oid_weight_t
{
    int itemdefid;
    double weight;
} oid_weight_t;

/**
 * @brief Represents a simple dynamic list of strings.
 *
 * Useful for fields like tags, store_tags, or language-specific names.
 */
typedef struct oid_strlist_t
{
    char** data;
    size_t count;
} oid_strlist_t;


/* ITEMDEF */
typedef struct oid_itemdef_t
{
    int itemdefid;          /* unique Steam ID */
    char* type;             /* "item", "bundle", "generator", etc. */
    char* name;             /* base name (unlocalized) */
    char* description;      /* optional description */

    int tradable;
    int marketable;
    int hidden;

    char* icon_url;
    char* icon_url_large;
    char* background_color;
    char* name_color;

    oid_strlist_t tags;         /* item tags */
    oid_strlist_t store_tags;   /* store categories */

    /* optional Steam fields */
    char* bundle;           /* raw bundle string if present */
    char* exchange;         /* raw exchange string if present */
    char* promo;            /* raw promo rule */
    char* price;            /* explicit price list */
    char* price_category;

    /* free-form metadata */
    oid_kv_t* attributes;
    size_t attribute_count;
} oid_itemdef_t;

/* BUNDLE */
typedef struct oid_bundle_t
{
    int itemdefid;            /* bundle’s own id */
    oid_amount_t* entries;    /* contained items */
    size_t entry_count;
} oid_bundle_t;

/* GENERATOR */
typedef struct oid_generator_t
{
    int itemdefid;            /* generator id */
    oid_weight_t* entries;    /* possible drops */
    size_t entry_count;
} oid_generator_t;

/* PLAYTIME GENERATOR */
typedef struct oid_playtime_generator_t {
    int itemdefid;
    int generator_id;         /* linked generator */
    int drop_interval;        /* minutes between grants */
    int drop_window;          /* cooldown window in minutes */
    int drop_max_per_window;  /* max per window */
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

#ifdef __cplusplus
}
#endif
#endif