/*
 * Lesson 23a: 画棋盘
 *
 * 知识点：二维数组，二重 for 循环，printf, memset
 * 参考原课 gomoku.c 中的 init_board() + print_board()
 * 参考 README Step 1: "画棋盘 15*15, =0"
 *
 * 任务:
 *       1. 实现 init_board(): 用 memset 将 board 初始化为 '.'
 *       2. 实现 print_board(): 打印列号 + 每行带行号
 *
 * 验证：输出 15x15 棋盘 (首行列号，每行 "%2d " + " %c")
 */

#include <stdio.h>
#include <string.h>

#define SIZE 15

static char board[SIZE][SIZE];

void init_board(void) { memset(board, '.', sizeof(board)); }

void print_board(void) {
    // 打印列号（首行）
    printf("  ");  // 两个空格，与行号对齐（行号占2位）
    for (int j = 0; j < SIZE; j++) {
        printf(" %2d", j);  // 每个列号占2位，前面加一个空格
    }
    printf("\n");

    // 打印每一行
    for (int i = 0; i < SIZE; i++) {
        printf("%2d ", i);  // 行号占2位，后面一个空格
        for (int j = 0; j < SIZE; j++) {
            printf(" %c", board[i][j]);  // 每个字符前一个空格
        }
        printf("\n");
    }
}

int main(void) {
    init_board();
    print_board();

    return 0;
}
