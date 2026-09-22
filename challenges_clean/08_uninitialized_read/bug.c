#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 32 // 열
#define COLS 4 // 행

static void dirty_heap(void) {
    void *scratch = malloc(ROWS * sizeof(int *));
    if (scratch) {
        memset(scratch, 0xAB, ROWS * sizeof(int *));
        free(scratch);
    }
}
// 매트릭스 만들기
static int **make_matrix(void) {

    int **rows = calloc(ROWS, sizeof(int *)); // 빈 행 = NULL
    if (!rows) { perror("calloc"); exit(1); } // 실패

    for (int i = 0; i < ROWS; i += 2) { // 한 칸씩 넣어도 되긴함
        int *r = malloc(COLS * sizeof(int));
        for (int j = 0; j < COLS; j++) r[j] = i * COLS + j;
        rows[i] = r;
    }
    return rows;
}

static long row_sum(int **rows, int nrows) {
    long total = 0;
    for (int i = 0; i < nrows; i++) { // 사실 두칸씩 읽어도 됨
        if (!rows[i]) continue; // 빈 행 건너뛰기
        for (int j = 0; j < COLS; j++) {
            total += rows[i][j];
        }
    }
    return total;
}

int main(void) {
    dirty_heap();

    int **rows = make_matrix();
    printf("summing %dx%d matrix...\n", ROWS, COLS);

    long s = row_sum(rows, ROWS);

    printf("sum = %ld\n", s);

    for (int i = 0; i < ROWS; i++) free(rows[i]);
    free(rows);
    return 0;
}
