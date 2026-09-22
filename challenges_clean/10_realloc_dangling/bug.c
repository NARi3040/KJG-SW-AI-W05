#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_UNDO 8
typedef struct {
    int   *data; // 
    size_t len, cap; // 현재 길이와 최대 길이
    int   *clipboard; // 복사?
    int   *undo[MAX_UNDO]; // 최대 되돌리기?
    int    undo_n; // 되돌리기 횟수?
} EditBuffer;

// 초기 세팅
static void eb_init(EditBuffer *e) {
    e->cap = 4;
    e->len = 0;
    e->undo_n = 0;
    e->data = malloc(e->cap * sizeof(int)); // data에 빈공간 할당
    if (!e->data) { perror("malloc"); exit(1); } 
    e->clipboard = malloc(e->cap * sizeof(int)); // cap의 크기만큼 공간 할당
    if (!e->clipboard) { perror("malloc"); exit(1); }
}

/*
e->undo_n기 MAX_UNDO보다 작으면
 undo에 넣기? 
실행 취소 역할
여기서 [0] = 0
*/
static void eb_snapshot(EditBuffer *e) {
    if (e->undo_n < MAX_UNDO) {
        int *t = malloc(e->len * sizeof *t);
        if (!t) return;
        memcpy(t, e->data, e->len * sizeof *t);
        e->undo[e->undo_n++] = t;
    }
}

// cap 길이 늘리기
static void eb_grow(EditBuffer *e, size_t need) {
    size_t nc = e->cap; // 현재 최대값을 받고 
    while (nc < need) nc *= 2; // need가 크면 nc * 2
    int *p = realloc(e->data, nc * sizeof(int)); // e->data 공간을 기준으로 확장 - 얘가 건든다 4, 4 /  1431655769 / 1431655769
    if (!p) { perror("realloc"); free(e->data); exit(1); }
    e->data = p; // 실제로 넣기
    e->cap = nc; // 반영
}

// 넣는 얘
static void eb_push(EditBuffer *e, int v) { // 받은 값이 v
    if (e->len == e->cap) eb_grow(e, e->len + 1); // 현과 최가 동일할때 최대 길이 +1
    e->data[e->len++] = v; // len ++ 하고 v 넣기
}

static void eb_free(EditBuffer *e) {
    free(e->data);
    free(e->clipboard);
    for (int i = 0; i < e->undo_n; i++) {
        free(e->undo[i]); // 여기서 죽음
    }
    e->undo_n = 0;
    e->data = NULL;
}

int main(void) {
    EditBuffer e;
    eb_init(&e);

    for (int i = 0; i < 3; i++) eb_push(&e, i); // 0 ~ 2까지 값을 e로 넣음

    eb_snapshot(&e);

    for (int i = 0; i < 4000; i++) eb_push(&e, i); // 0 ~ 3999까지 값을 e로 넣음 - 여기 거치면서 undo값이 이상해졌는데

    printf("len=%zu cap=%zu head=%d tail=%d\n",
           e.len, e.cap, e.data[0], e.data[e.len - 1]);

    eb_free(&e); // 여기서 죽음
    printf("done\n");
    return 0;
}
