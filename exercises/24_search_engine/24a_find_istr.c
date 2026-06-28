/*
 * Lesson 24a: 大小写不敏感子串查找
 *
 * 知识点：指针操作，tolower, 字符串匹配
 * 参考原课 search.c 中的 find_istr() 函数
 *
 * 任务：实现 find_istr(text, pattern):
 *       1. 计算 plen = strlen(pattern)
 *       2. while (*text) 逐位置尝试匹配
 *       3. 内层 for 循环比较 tolower(text[i]) vs tolower(pattern[i])
 *       4. 全部匹配返回 text 指针，否则 text++ 继续
 *
 * 验证：text="Hello World" pattern="world" → "found\n"
 *       text="abc" pattern="xyz" → "not found\n"
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

const char *find_istr(const char *text, const char *pattern) {
    int plen = strlen(pattern);
    while (*text) {
        int i;
        for (i = 0; i < plen; i++) {
            if (tolower(text[i]) != tolower(pattern[i])) {
                break;
            }
        }
        if (i == plen) {
            return text;
        }
        text++;
    }
    return NULL;
}

int main(void) {
    char text[1024];
    char pattern[256];

    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = '\0';

    if (find_istr(text, pattern))
        printf("found\n");
    else
        printf("not found\n");

    return 0;
}
