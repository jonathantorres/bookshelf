#include <stdlib.h>
#include <stdio.h>
#include "hash_table.h"

size_t fnv1a_hash(const char* cp)
{
    size_t hash = 0x811c9dc5;
    while (*cp) {
        hash ^= (unsigned char) *cp++;
        hash *= 0x01000193;
    }

    return hash;
}

hash_table *hash_table_create(hash_table_compare cmp)
{
    hash_table *_hash_table = malloc(sizeof(hash_table));

    if (!_hash_table) {
        fputs("[hash_table_create] Not enough memory.", stderr);
        return NULL;
    }

    _hash_table->cmp = cmp;
    _hash_table->buckets = array_create(NUM_OF_BUCKETS, sizeof(array*));
    _hash_table->buckets->length = _hash_table->buckets->capacity;

    return _hash_table;
}

void hash_table_destroy(hash_table *_hash_table)
{
    if (!_hash_table) {
        fputs("[hash_table_destroy] Must provide a hash_table.", stderr);
        return;
    }

    if (_hash_table->buckets) {
        for (unsigned int i = 0; i < _hash_table->buckets->length; i++) {
            array *bucket = array_get(_hash_table->buckets, i);
            if (bucket) {
                for (unsigned int j = 0; j < bucket->length; j++) {
                    hash_table_node *elem = array_get(bucket, j);
                    if (elem) {
                        if (elem->key) {
                            free(elem->key);
                        }
                        free(elem);
                    }
                }
                if (bucket->contents) {
                    free(bucket->contents);
                }
                free(bucket);
            }
        }
        if (_hash_table->buckets->contents) {
            free(_hash_table->buckets->contents);
        }
        free(_hash_table->buckets);
    }
    free(_hash_table);
}

bool bucket_index_is_valid(unsigned int bucket_index)
{
    if (bucket_index >= NUM_OF_BUCKETS) {
        return false;
    }

    return true;
}

array *find_bucket(hash_table *_hash_table, void *key, size_t *bucket_hash, bool create_new)
{
    *bucket_hash = fnv1a_hash(key);
    unsigned int bucket_index = *bucket_hash % NUM_OF_BUCKETS;

    if (!bucket_index_is_valid(bucket_index)) {
        return NULL;
    }

    array *bucket = array_get(_hash_table->buckets, bucket_index);
    if (!bucket && create_new) {
        bucket = array_create(NUM_OF_BUCKETS, sizeof(hash_table_node*));
        array_set(_hash_table->buckets, bucket, bucket_index);
    }

    return bucket;
}

bool hash_table_set(hash_table *_hash_table, void *key, void *value)
{
    if (!_hash_table) {
        fputs("[hash_table_set] Must provide a hash_table.", stderr);
        return false;
    }

    size_t bucket_hash = 0;
    array *bucket = find_bucket(_hash_table, key, &bucket_hash, true);

    if (!bucket) {
        return false;
    }

    // create the node
    hash_table_node *node = malloc(sizeof(hash_table_node));
    if (!node) {
        return false;
    }

    node->key = strdup(key);
    node->value = value;
    node->hash = bucket_hash;
    array_push(bucket, node);

    return true;
}

void *hash_table_get(hash_table *_hash_table, void *key)
{
    if (!_hash_table) {
        fputs("[hash_table_get] Must provide a hash_table.", stderr);
        return NULL;
    }

    size_t bucket_hash = 0;
    array *bucket = find_bucket(_hash_table, key, &bucket_hash, false);
    if (!bucket) {
        return NULL;
    }

    for (unsigned int i = 0; i < bucket->length; i++) {
        hash_table_node *node = array_get(bucket, i);
        if (node && node->hash == bucket_hash && _hash_table->cmp(node->key, key) == 0) {
            return node->value;
        }
    }

    return NULL;
}

void *hash_table_remove(hash_table *_hash_table, void *key)
{
    if (!_hash_table) {
        fputs("[hash_table_remove] Must provide a hash_table.", stderr);
        return NULL;
    }

    void *value = NULL;
    size_t bucket_hash = 0;
    array *bucket = find_bucket(_hash_table, key, &bucket_hash, false);
    if (!bucket) {
        return value;
    }

    for (unsigned int i = 0; i < bucket->length; i++) {
        hash_table_node *node = array_get(bucket, i);
        if (node && node->hash == bucket_hash && _hash_table->cmp(node->key, key) == 0) {
            value = node->value;
            void *last = array_pop(bucket);
            if (last != node) {
                array_set(bucket, last, i);
            }
            free(node->key);
            free(node);
            break;
        }
    }

    return value;
}

bool hash_table_traverse(hash_table *_hash_table, hash_table_node_cb cb)
{
    if (!_hash_table) {
        fputs("[hash_table_traverse] Must provide a hash_table.", stderr);
        return false;
    }
    unsigned int traverse_ok = false;

    for (unsigned int i = 0; i < _hash_table->buckets->length; i++) {
        array *bucket = array_get(_hash_table->buckets, i);
        if (bucket) {
            for (unsigned int j = 0; j < bucket->length; j++) {
                hash_table_node *node = array_get(bucket, j);
                if (node) {
                    if (cb(node)) {
                        traverse_ok = true;
                        break;
                    }
                }
            }
        }
    }

    return traverse_ok;
}
