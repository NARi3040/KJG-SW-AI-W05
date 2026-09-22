#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* 크기 세준다. */
static size_t joined_size(const char *const *parts, int n) {
    size_t total = 1;
    for (int i = 0; i < n; i++) { // 너는 널문자를 중요시 하지 않았지
        total += strlen(parts[i]);
    }
    return total;
}
/*
0x5555555892a0 "GET /index.html HTTP/1.1\r\n\r\n", 'x' <repeats 172 times>...
71 'G'
off 28
*/
static char *join(const char *const *parts, int n) {
    size_t need = joined_size(parts, n); // 크기 계산
    char *out = malloc(need);
    if (!out) { perror("malloc"); exit(1); }

    size_t off = 0;
    for (int i = 0; i < n; i++) {
        strcpy(out + off, parts[i]); // 여기서 오류 
        off += strlen(parts[i]);
    }
    out[off] = '\0';
    return out;
}

int main(void) {

    static char body[200000];
    memset(body, 'x', sizeof body - 1);
    body[sizeof body - 1] = '\0';

    const char *parts[] = { "GET ", "/index.html", " HTTP/1.1\r\n\r\n", body };
    int n = (int)(sizeof(parts) / sizeof(parts[0]));

    char *msg = join(parts, n);

    printf("joined length = %zu\n", strlen(msg));
    free(msg);
    return 0;
}
