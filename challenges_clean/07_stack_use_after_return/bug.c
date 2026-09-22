#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 8
// 그만 정신을 잃고 말았습니다.
typedef struct {
    char *lines[MAX_LINES];
    int   count;
} LineView;
/*
라인 별로 분리
\n로 구분
*/
static void split_lines(LineView *out, char *text) {
    out->count = 0;
    for (char *ln = strtok(text, "\n"); ln && out->count < MAX_LINES; ln = strtok(NULL, "\n")) {
        // fprintf(stderr, "split_lines: parts  주소 = %p\n", out->lines[out->count++]);
        fprintf(stderr, "\tlines[%d] = %p (%s)\n", out->count, (void*)ln, ln);
        out->lines[out->count++] = ln;
    }
}
// 이상한 값으로 변경 / 왜 하지?
static void warm_stack(void) {
    char *scratch[MAX_LINES];
    fprintf(stderr, "warm_stack : scratch주소 = %p\n", (void*)scratch);
    for (int i = 0; i < MAX_LINES; i++) {
        fprintf(stderr, "\twarm_stack : scratch[%d]주소 = %p\n", i,(void*)scratch[i]);
        scratch[i] = (char *)0x4141414141414141ULL;
    }
    __asm__ volatile("" :: "r"(scratch) : "memory");
}

int main(void) {
    char text[] = "alpha\nbeta\ngamma";

    LineView v;
    split_lines(&v, text);
    fprintf(stderr, "리턴 직후  : v.lines[0] = %p\n", (void*)v.lines[0]);
    warm_stack();
    fprintf(stderr, "warm 이후  : v.lines[0] = %p\n", (void*)v.lines[0]);

    long checksum = 0;
    for (int i = 0; i < v.count; i++)
        checksum += (unsigned char)v.lines[i][0];

    printf("lines = %d, checksum = %ld\n", v.count, checksum);
    return 0;
}
