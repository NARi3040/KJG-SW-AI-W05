#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int   id;
    char *name;
} Rec;

#define MAXN 16
typedef struct {
    Rec *by_id[MAXN];
    Rec *by_name[MAXN];
    int  count;
} Directory;

/*
여기서 진짜로 동적할당하기
*/
static Rec *rec_new(int id, const char *name) {
    Rec *r = malloc(sizeof *r);
    if (!r) { perror("malloc"); exit(1); }
    r->id = id;
    r->name = malloc(strlen(name) + 1);
    if (!r->name) { perror("malloc"); exit(1); }
    strcpy(r->name, name);
    return r;
}

/*
데이터 넣기 오더 내리기 및 넣기
by_id : 삽입 순서 그대로 (정렬 안 함)
by_name : 사전순 정렬
*/
static void directory_add(Directory *d, int id, const char *name) {
    Rec *r = rec_new(id, name);
    d->by_id[d->count] = r;
    d->by_name[d->count] = r;
    d->count++;
}

/*
데이터 정렬
*/
static void directory_sort_by_name(Directory *d) {
    for (int i = 0; i < d->count; i++) {
        for (int j = i + 1; j < d->count; j++) {
            if (strcmp(d->by_name[i]->name, d->by_name[j]->name) > 0) {
                Rec *t = d->by_name[i];
                d->by_name[i] = d->by_name[j];
                d->by_name[j] = t;
            }
        }
    }
}

/*
id 기반으로 찾기
d->by_id[i]
없으면 NULL
*/
static Rec *find_by_id(Directory *d, int id) {
    for (int i = 0; i < d->count; i++)
        if (d->by_id[i]->id == id) return d->by_id[i];
    return NULL;
}

/*
있는 내용물 전부 출력
*/
static void directory_dump(Directory *d) {
    printf("by id:  ");
    for (int i = 0; i < d->count; i++) printf("%d:%s ", d->by_id[i]->id, d->by_id[i]->name);
    printf("\nby name:");
    for (int i = 0; i < d->count; i++) printf(" %s(%d)", d->by_name[i]->name, d->by_name[i]->id);
    printf("\n");
}

/*
free
동일한 이름이 by_id가 반복문에서 해제되면 by_name도 해제가 됨
*/
static void directory_free(Directory *d) {
    for (int i = 0; i < d->count; i++) {
        free(d->by_id[i]->name);
        free(d->by_id[i]);
    }
    d->count = 0;
}

int main(void) {
    Directory dir = { .count = 0 };

    directory_add(&dir, 3, "carol");
    directory_add(&dir, 1, "alice");
    directory_add(&dir, 4, "dave");
    directory_add(&dir, 2, "bob");

    directory_sort_by_name(&dir);
    directory_dump(&dir);

    Rec *r = find_by_id(&dir, 2);
    if (r) printf("lookup id=2 -> %s\n", r->name);

    directory_free(&dir);
    printf("done\n");
    return 0;
}
