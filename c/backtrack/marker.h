#ifndef MARKER_H
#define MARKER_H

#define MAX_MARK_SIZE 50

typedef struct {
    int mark[MARK_SIZE];
    int p;
} Marker;

Marker * init_marker();
void mark(Marker *, int);
int pop(Marker *);
void clear_marker(Marker *);

#endif
