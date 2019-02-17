#ifndef PACK_H
#define PACK_H

typedef struct Pack {
    char used; // 0 not used. 1 used.
    int key;
    int value;
    struct Pack *next;
} Pack;

void add_pack(Pack **, int, int);
int get_value(Pack *, int);
void clear_pack(Pack *);

#endif
