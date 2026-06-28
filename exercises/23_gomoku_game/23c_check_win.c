/*
 * Lesson 23b: 五子棋判定 — check_dir + check_win
 *
 * 知识点：二维数组，方向扫描 (dr,dc), 函数封装
 * 参考原课 gomoku.c 的判赢逻辑
 *
 * 任务:
 *       1. check_dir(r, c, dr, dc, player):
 *          从 (r,c) 沿 (dr,dc) 方向检查连续 5 个同色棋子
 *          - for k=0..4: nr = r+k*dr, nc = c+k*dc
 *          - 越界返回 0, 不同色 break, count>=5 返回 1
 *       2. check_win(player):
 *          遍历棋盘每个位置，4 方向 (0,1)(1,0)(1,1)(1,-1) 调用 check_dir
 *
 * 验证：第一行 BBBBB... → "black\n"
 */

#include <stdio.h>
#include <string.h>

#define SIZE 15

char board[SIZE][SIZE + 1];

int check_dir(int r, int c, int dr, int dc, char player) {
    for (int i = 0; i < 5; i++) {
        int nr = r + i * dr;
        int nc = c + i * dc;
        if (nr >= SIZE || nr < 0 || nc >= SIZE || nc < 0) {
            return 0;
        }
        if (board[nr][nc] != player) {
            return 0;
        }
    }
    return 1;
}

static const int DR[4] = {-1, 1, 0, 0};
static const int DC[4] = {0, 0, -1, 1};
int check_win(char player) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            for (int dir = 0; dir < 4; dir++) {
                if (check_dir(row, col, DR[dir], DC[dir], player)) {
                    return 1;
                }
            }
        }
    }
}

int main(void) {
    for (int i = 0; i < SIZE; i++) scanf("%s", board[i]);

    if (check_win('B'))
        printf("black\n");
    else if (check_win('W'))
        printf("white\n");
    else
        printf("none\n");

    return 0;
}
