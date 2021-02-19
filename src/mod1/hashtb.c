#include <stdlib.h>
#include <string.h>
#include "hashtb.h"
#include "errcode.h"

int hashtb_init(bool (*isequal)(void *data1, int data1len, void *data2, int data2len), int (*hashfun)(void *data, int datalen), int size, struct hashtb **res)
{
    if (!res || size < 1) return WRONG_PARAMETER;
    *res = malloc(sizeof(struct hashtb));
    if (!*res) return ALLOC_FAIL;
    (*res)->table = calloc(size, sizeof(struct hashelm *));
    if (!(*res)->table) return ALLOC_FAIL;
    (*res)->isequal = isequal;
    (*res)->hashfun = hashfun;
    (*res)->size = size;
    return 0;
}

int hashtb_insert(struct hashtb *ht, void *data, int datalen)
{
    if (!ht) return WRONG_PARAMETER;
    int hashcode = ht->hashfun(data, datalen) % ht->size;
    struct hashelm *bucket = ht->table[hashcode];
    while (bucket)
    {
        if (ht->isequal(data, datalen, bucket->data, bucket->datalen)) return 0;
        bucket = bucket->collision;
    }
    struct hashelm *elm = malloc(sizeof(struct hashelm));
    if (!elm) return ALLOC_FAIL;
    elm->data = malloc(datalen);
    if (!elm->data) return ALLOC_FAIL;
    memcpy(elm->data, data, datalen);
    elm->collision = ht->table[hashcode];
    ht->table[hashcode] = elm;
    ht->num++;
    return 0;
}

void *hashtb_search(struct hashtb *ht, void *data, int datalen)
{
    if (!ht) return NULL;
    int hashcode = ht->hashfun(data, datalen) % ht->size;
    struct hashelm *bucket = ht->table[hashcode];
    while (bucket)
    {
        if (ht->isequal(data, datalen, bucket->data, bucket->datalen)) return data;
        bucket = bucket->collision;
    }
    return NULL;
}

void hashtb_delete(struct hashtb *ht, void *data, int datalen)
{
    if (!ht) return;
    int hashcode = ht->hashfun(data, datalen) % ht->size;
    struct hashelm **bucket_p = &(ht->table[hashcode]);
    while (*bucket_p)
    {
        if (ht->isequal(data, datalen, (*bucket_p)->data, (*bucket_p)->datalen))
        {
            free((*bucket_p)->data);
            struct hashelm *tmp = (*bucket_p)->collision;
            free(*bucket_p);
            *bucket_p = tmp;
            return;
        }
        bucket_p = &((*bucket_p)->collision);
    }
}

void hashtb_destory(struct hashtb *ht)
{
    if (!ht) return;
    int i;
    for (i = 0; i < ht->size; i++)
    {
        struct hashelm *bucket = ht->table[i], *tmp;
        while (bucket)
        {
            free(bucket->data);
            tmp = bucket->collision;
            free(bucket);
            bucket = tmp;
        }
    }
    free(ht->table);
    free(ht);
    ht = NULL;
}
