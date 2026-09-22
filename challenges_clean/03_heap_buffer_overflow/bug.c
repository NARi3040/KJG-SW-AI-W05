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

/*
newcap 32

len 16
cap 16
len == cap일떄 여기 온다 
그럼 newcap 2배 시키고 새로 공간을 할당해주는 것 같음
*/
static void list_ensure(IntList *l, size_t need) {
    if (need <= l->cap) return;

    size_t newcap = l->cap ? l->cap * 2 : 8; // l->cap가 없으면 기본 8 / 있으면 l->cap * 2
    while (newcap < need) newcap *= 2; // 

    int *p = realloc(l->data, l->cap * sizeof(int)); // len == cap == 16일 때 여기서 죽음 / l->data 공간에  l->cap * sizeof(int)
    if (!p) { perror("realloc"); free(l->data); exit(1); }

    l->data = p;
    l->cap  = newcap;
}

// 초반에 잘되다가 list_ensure넘기는 도중에 list_ensure에서 오류
static void list_push(IntList *l, int x) {
    if (l->len == l->cap) list_ensure(l, l->cap + 1); // IntList랑 cap(need)를 +1까지 해주고 넘김
    l->data[l->len++] = x; // 아니면 그냥 len ++
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
