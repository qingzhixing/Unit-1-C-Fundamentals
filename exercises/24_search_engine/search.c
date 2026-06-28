/*
 * Lesson 24c: 简单搜索引擎 — HTML 链接提取器
 *
 * 知识点：字符串匹配，指针操作，引号解析，动态内存
 * 参考原课 search.c — 从 HTML 中提取所有 <a href="..."> 链接
 *
 * 任务：read_all 已实现 (读取全部 stdin)，学生实现:
 *       1. find_istr(text, pattern): tolower 大小写不敏感匹配
 *       2. extract_links(html): 循环 find_istr("href=") → 解析引号 → 提取 URL
 *       3. main(): 调用 read_all + extract_links + 打印总计
 *
 * 验证：HTML 含 2 个 href → "[1] url1\n[2] url2\n\nTotal: 2 links found.\n"
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL 1024

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

static int extract_links(const char *html) {
    const char *p = html;
    int count = 0;
    // 循环查找
    while ((p = find_istr(p, "href="))) {
        p += 5;
        while (isspace(*p) || *p == '"' || *p == '\'') p++;
        char url[MAX_URL];
        int len = 0;
        while (p[len] && !isspace(p[len]) && p[len] != '\n' && p[len] != '"' && p[len] != '\'') {
            url[len++] = p[len];
        }
        url[len] = '\0';
        printf("[%d] %s\n", ++count, url);
    }
    return count;
}
/* 读取全部 stdin 到动态 buffer (给出，不需要实现) */
static char *read_all(FILE *fp) {
    size_t cap = 4096, len = 0;
    char *buf = malloc(cap);
    if (!buf) return NULL;

    size_t n;
    while ((n = fread(buf + len, 1, cap - len - 1, fp)) > 0) {
        len += n;
        if (len + 1 >= cap) {
            cap *= 2;
            buf = realloc(buf, cap);
            if (!buf) return NULL;
        }
    }
    buf[len] = '\0';
    return buf;
}

int main(void) {
    // TODO: Read all input, extract links, print total, free memory.
    char *html = read_all(stdin);

    // error handler
    if (!html) return 1;

    int total = extract_links(html);

    printf("\nTotal: %d links found.\n", total);

    free(html);
    return 0;
}
