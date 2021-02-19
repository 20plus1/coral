#ifndef _GLUME_HASHTB_H
#define _GLUME_HASHTB_H

#include <stdbool.h>
#include <stddef.h>

struct hashelm
{
    struct hashelm *collision;
    void *data;
    int datalen;
};

struct hashtb
{
    bool (*isequal)(void *data1, int data1len, void *data2, int data2len);
    int (*hashfun)(void *data, int len);
    struct hashelm **table;
    int size;
    int num;
};

int hashtb_init(bool (*isequal)(void *data1, int data1len, void *data2, int data2len), int (*hashfun)(void *data, int datalen), int size, struct hashtb **res);

int hashtb_insert(struct hashtb *ht, void *data, int datalen);

void *hashtb_search(struct hashtb *ht, void *data, int datalen);

void hashtb_delete(struct hashtb *ht, void *data, int datalen);

void hashtb_destory(struct hashtb *ht);

#endif
