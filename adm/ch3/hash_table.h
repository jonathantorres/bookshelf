#ifndef _hash_table_h
#define _hash_table_h

#include "array.h"
#include <stdbool.h>
#include <string.h>

#define NUM_OF_BUCKETS 100

typedef int (*hash_table_compare)(void *a, void *b);

typedef struct hash_table {
    array *buckets;
    hash_table_compare cmp;
} hash_table;

typedef struct hash_table_node {
    void *key;
    void *value;
    size_t hash;
} hash_table_node;

typedef bool (*hash_table_node_cb)(hash_table_node *node);

hash_table *hash_table_create(hash_table_compare cmp);
void hash_table_destroy(hash_table *_hash_table);
void *hash_table_get(hash_table *_hash_table, void *key);
bool hash_table_set(hash_table *_hash_table, void *key, void *value);
void *hash_table_remove(hash_table *_hash_table, void *key);
bool hash_table_traverse(hash_table *_hash_table, hash_table_node_cb cb);

// Macro Usage:
// HASH_TABLE_FOREACH(hash_table) {
    // use elem
    // elem is the current hash_table_node
// } HASH_TABLE_FOREACH_END
#define HASH_TABLE_FOREACH(hash_table) \
    if ((hash_table)->buckets) { \
        for (unsigned int i = 0; i < (hash_table)->buckets->length; i++) { \
            array *bucket = array_get((hash_table)->buckets, i); \
            if (bucket) { \
                for (unsigned int j = 0; j < bucket->length; j++) { \
                    hash_table_node *elem = array_get(bucket, j); \
                    if (elem)

#define HASH_TABLE_FOREACH_END } } } }

#endif
