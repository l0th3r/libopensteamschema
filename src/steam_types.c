#include "steam_types.h"

oid_amount_list_t oid_amount_list_from_string(const char* text)
{
    oid_amount_list_t list = { 0 };

    if (!text || *text == '\0')
    {
        return list;
    }

    char* buffer = strdup(text);
    if (!buffer)
    {
        return list;
    }

    size_t capacity = 8;
    list.entries = (oid_amount_t*)calloc(capacity, sizeof(oid_amount_t));

    if (!list.entries)
    {
        free(buffer);
        return list;
    }

    char* saveptr = NULL;
    char* token = strtok_r(buffer, ";", &saveptr);

    while (token != NULL)
    {
        /* trim leading spaces */
        while (isspace((unsigned char)*token))
        {
            token++;
        }

        /* trim trailing spaces */
        char* end = token + strlen(token) - 1;
        while (end > token && isspace((unsigned char)*end))
        {
            *end = '\0';
            end--;
        }

        if (*token != '\0')
        {
            int id = 0;
            int qty = 1;

            char* x = strchr(token, 'x');
            if (x != NULL)
            {
                *x = '\0';
                id = atoi(token);
                qty = atoi(x + 1);
            }
            else
            {
                id = atoi(token);
            }

            if (id > 0 && qty > 0)
            {
                if (list.count >= capacity)
                {
                    capacity *= 2;
                    oid_amount_t* resized = (oid_amount_t*)realloc(list.entries, capacity * sizeof(oid_amount_t));

                    if (!resized)
                    {
                        break;
                    }

                    list.entries = resized;
                }

                list.entries[list.count].itemdefid = id;
                list.entries[list.count].quantity = qty;
                list.count++;
            }
        }

        token = strtok_r(NULL, ";", &saveptr);
    }

    free(buffer);
    return list;
}

char* oid_amount_list_to_string(const oid_amount_list_t* list)
{
    if (!list || list->count == 0)
    {
        return strdup("");
    }

    size_t bufsize = list->count * 16;
    char* out = (char*)malloc(bufsize);

    if (!out)
    {
        return NULL;
    }

    out[0] = '\0';

    for (size_t i = 0; i < list->count; ++i)
    {
        char part[32];

        if (list->entries[i].quantity != 1)
        {
            snprintf(part, sizeof(part), "%d x %d", list->entries[i].itemdefid, list->entries[i].quantity);
        }
        else
        {
            snprintf(part, sizeof(part), "%d", list->entries[i].itemdefid);
        }

        if (i > 0)
        {
            strncat(out, ";", bufsize - strlen(out) - 1);
        }

        strncat(out, part, bufsize - strlen(out) - 1);
    }

    return out;
}

void oid_amount_list_free(oid_amount_list_t* list)
{
    if (!list)
    {
        return;
    }

    if (list->entries != NULL)
    {
        free(list->entries);
        list->entries = NULL;
    }

    list->count = 0;
}

int oid_itemdefid_valid(const oid_itemdefid_t id, int workshop_allowed)
{
    if (id.value <= 0 || (!workshop_allowed && id.value >= 1000000))
    {
        return 0;
    }

    return 1;
}

oid_itemdefid_t oid_itemdefid_from_int(const int32_t val)
{
    oid_itemdefid_t id = { val };
    return id;
}

int32_t oid_itemdefid_to_int(const oid_itemdefid_t id)
{
    return id.value;
}

oid_item_type_t oid_item_type_from_string(const char* str)
{
    if (!str) return OID_ITEM_TYPE_UNKNOWN;
    if (!strcmp(str, "item")) return OID_ITEM_TYPE_ITEM;
    if (!strcmp(str, "bundle")) return OID_ITEM_TYPE_BUNDLE;
    if (!strcmp(str, "generator")) return OID_ITEM_TYPE_GENERATOR;
    if (!strcmp(str, "playtimegenerator")) return OID_ITEM_TYPE_PLAYTIME_GENERATOR;
    if (!strcmp(str, "tag_generator")) return OID_ITEM_TYPE_TAG_GENERATOR;
    return OID_ITEM_TYPE_UNKNOWN;
}

const char* oid_item_type_to_string(const oid_item_type_t type)
{
    switch (type)
    {
        case OID_ITEM_TYPE_ITEM: return "item";
        case OID_ITEM_TYPE_BUNDLE: return "bundle";
        case OID_ITEM_TYPE_GENERATOR: return "generator";
        case OID_ITEM_TYPE_PLAYTIME_GENERATOR: return "playtimegenerator";
        case OID_ITEM_TYPE_TAG_GENERATOR: return "tag_generator";
        default: return "unknown";
    }
}

const oid_color_t oid_color_from_hex(const char* hex)
{
    oid_color_t color = {0, 0, 0, 0};
    
    if (!hex || strlen(hex) != 6)
    {
        return color;
    }

    for (size_t i = 0; i < 6; ++i)
    {
        if (!isxdigit((unsigned char)hex[i]))
        {
            return color;
        }
    }

    unsigned int rgb;
    if (sscanf(hex, "%06x", &rgb) == 1)
    {
        color.r = (rgb >> 16) & 0xFF;
        color.g = (rgb >> 8) & 0xFF;
        color.b = rgb & 0xFF;
        color.valid = 1;
    }

    return color;
}

void oid_color_to_hex(const oid_color_t color, char* buffer)
{
    if (!buffer)
    {
        return;
    }

    snprintf(buffer, 7, "%02X%02X%02X", color.r, color.g, color.b);
}
