#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int   *data;
    size_t len;
    size_t cap;
} IntList;

static void list_init(IntList *l) {
    l->cap  = 8;
    l->len  = 0;
    l->data = malloc(l->cap * sizeof(int));
    if (!l->data) { perror("malloc"); exit(1); }
}

static void list_ensure(IntList *l, size_t need) {
    if (need <= l->cap) return;

    size_t newcap = l->cap ? l->cap * 2 : 8;
    while (newcap < need) newcap *= 2;

    int *p = realloc(l->data, l->cap * sizeof(int));
    if (!p) { perror("realloc"); free(l->data); exit(1); }

    l->data = p;
    l->cap  = newcap;
}

static void list_push(IntList *l, int x) {
    if (l->len == l->cap) list_ensure(l, l->cap + 1);
    l->data[l->len++] = x;
}

static long long list_sum(const IntList *l) {
    long long s = 0;
    for (size_t i = 0; i < l->len; i++) s += l->data[i];
    return s;
}

static void list_free(IntList *l) {
    free(l->data);
    l->data = NULL;
    l->len = l->cap = 0;
}

int main(void) {
    IntList l;
    list_init(&l);

    const int N = 2000000;
    for (int i = 0; i < N; i++) {
        list_push(&l, i % 100);
    }

    printf("len=%zu cap=%zu sum=%lld\n", l.len, l.cap, list_sum(&l));
    list_free(&l);
    return 0;
}
