#include "marker.h"

#include <stdlib.h>

Marker * init_marker() {
    Marker *marker = (Marker *)calloc(1, sizeof (Marker));
    marker->p = 0;
    return marker;
}

void push(Marker *marker, int n) {
    (marker->mark)[marker->p] = n;
    (marker->p)++;
}

int pop(Marker *marker) {
    (marker->p)--;
    return (marker->mark)[marker->p];
}

void clear_marker(Marker *marker) {
    for (int i = 0; i < MAX_MARK_SIZE; i++) {
        (marker->mark)[i] = 0;
    }
    marker->p = 0;
}
