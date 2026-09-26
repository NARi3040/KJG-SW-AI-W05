#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARENA_SIZE 4096
static unsigned char arena[ARENA_SIZE];
static size_t arena_off = 0;

/*
여기서 일어나는데 어떻게 발생하는지 모르겠음


*/
static void* arena_alloc(size_t n) {
    if (n > ARENA_SIZE - arena_off) return NULL;
    void *p = &arena[arena_off];
    arena_off += n;
    return p;
}
/*
dst 0x7a69c1b6bec7e5b3 <error: Cannot access memory at address 0x7a69c1b6bec7e5b3>
349
*/
static char* intern(const char *s) {
    size_t n = strlen(s) + 1;
    char *dst = arena_alloc(n);
    if (!dst) return NULL;
    memcpy(dst, s, n); // 문제
    return dst;
}

int main(void) {

    const char *words[] = {
        "insert", "delete", "search", "traverse", "balance",
        "rotate", "rehash", "compact", "serialize", "checkpoint",
    };
    int nwords = (int)(sizeof(words) / sizeof(words[0]));

    char *last = NULL;
    long total = 0;
    for (int i = 0; i < 100000; i++) {
        char buf[32];
        snprintf(buf, sizeof buf, "%s-%d", words[i % nwords], i); // 버퍼에 넣기 
        char *p = intern(buf);
        if (!p) break;
        last = p;
        total += (long)strlen(last);
    }

    printf("interned, last=%s total_len=%ld\n", last, total);
    return 0;
}
