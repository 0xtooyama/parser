#include "pack.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void add_pack(Pack **head, int key, int value) {
    Pack *iterator = *head;
    while (iterator) {
        if (!iterator->used) {
            iterator->used = 1;
            iterator->key = key;
            iterator->value = value;
            return;
        }
        iterator = iterator->next;
    }

    Pack *pack = (Pack *)calloc(1, sizeof (Pack));
    pack->used = 1;
    pack->key = key;
    pack->value = value;
    pack->next = NULL;

    if (*head == NULL) {
        *head = pack;
    } else {
        iterator = *head;
        while (iterator->next) {
            iterator = iterator->next;
        }
        iterator->next = pack;
    }
}

// if found key then return value of key else return -1
int get_value(Pack *head, int key) {
    Pack *iterator = head;
    while(iterator) {
        if (iterator->key == key) {
            return iterator->value;
        }
        iterator = iterator->next;
    }

    return -1;
}

void clear_pack(Pack *head) {
    Pack *iterator = head;
    while (iterator) {
        iterator->used = 0;
        iterator->key = 0;
        iterator->value = 0;
        iterator = iterator->next;
    };
}

