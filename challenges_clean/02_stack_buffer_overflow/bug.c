#include <stdio.h>
#include <stdlib.h>

#define ROWS 14
// 14 * (15) / 2  = 105
enum { SIZE = ROWS * (ROWS + 1) / 2 };

static int tri_index(int i, int j) {
    return i * (i + 1) / 2 + j;
}
// tri 105 / rows 14
// 파스칼 삼각형 만들기 
// idx가 119임 초과
static void build_pascal(int *tri, int rows) {
    for (int i = 0; i <= rows; i++) { // ?????
        for (int j = 0; j <= i; j++) {
            int idx = tri_index(i, j);
            if (j == 0 || j == i) { // j = 0 / j
                tri[idx] = 1;
            } else {
                int up_left  = tri_index(i - 1, j - 1);
                int up_right = tri_index(i - 1, j);
                tri[idx] = tri[up_left] + tri[up_right];
            }
            // printf("%d\n",idx);
        }
    }
}

// row의 수 계산해서 sum값 리턴 
static long row_sum(const int *tri, int i) {
    long sum = 0;
    for (int j = 0; j <= i; j++) sum += tri[tri_index(i, j)]; // 4. tri_index로 가서 계산
    return sum; // 아마 길이 계산 후 뱉기
}
// 1
// 말그래도 row 프린트
static void print_row(const int *tri, int i) {
    printf("row %2d:", i);
    for (int j = 0; j <= i; j++) printf(" %d", tri[tri_index(i, j)]); // 2. tri_index로 가서 계산
    printf("   (sum=%ld)\n", row_sum(tri, i)); // 3. row_sum(총합) 계산 
}

int main(void) {
    int tri[SIZE]; //size = 105

    build_pascal(tri, ROWS);

    for (int i = 0; i < ROWS; i++) print_row(tri, i); // 시작점

    printf("SIZE = %d\n", SIZE);

    return 0;
}
