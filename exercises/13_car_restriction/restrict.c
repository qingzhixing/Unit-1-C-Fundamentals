/*
 * Lesson 13c: 车辆限行完整程序
 *
 * 知识点：enum, switch, 三元表达式，日期计算，函数组合调用
 * 参考原课 restrict.c — 综合使用 get_last_char + is_restricted + get_week_day
 *
 * 任务：实现 get_week_day() + main():
 *       1. get_week_day(year, month, day):
 *          - origin_day = 2 (2013-1-1 为星期二)
 *          - 用 m[12]={31,28,31,30,...} 累加前 month-1 个月天数
 *          - alldays += day - 1
 *          - switch ((alldays + origin_day) % 7) 返回对应 enum day
 *       2. main(): 读入车牌号和日期 → 组合调用三个函数 → 输出结果
 *
 * 验证："A23456\n2013 1 1\n" → "restricted!\n" (周二限 1/6，尾号 6)
 */

#include <stdio.h>

enum day { MONDAY = 1, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY };

char get_last_char(char str[]) {
    char c = 0;
    int i = 0;

    while (str[i]) {
        c = str[i];
        i++;
    }
    return c;
}

int is_restricted(int tail_num, enum day today) {
    int ret = 0;

    switch (tail_num) {
        case 0:
        case 5:
            ret = (today == MONDAY) ? 1 : 0;
            break;
        case 1:
        case 6:
            ret = (today == TUESDAY) ? 1 : 0;
            break;
        case 2:
        case 7:
            ret = (today == WEDNESDAY) ? 1 : 0;
            break;
        case 3:
        case 8:
            ret = (today == THURSDAY) ? 1 : 0;
            break;
        case 4:
        case 9:
            ret = (today == FRIDAY) ? 1 : 0;
            break;
        default:
            ret = 0;
            break;
    }
    return ret;
}

const static int DAYS[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const static int ORIGIN_DAY = 2;  // 2013-1-1 为星期二
enum day get_week_day(int year, int month, int day) {
    int d_year = year - 2013;
    int d_month = month - 1;
    int d_day = day - 1;

    int all_days = 0;

    // year
    all_days += 365 * d_year;
    // month
    for (int i = 1; i <= 1 + d_month - 1; i++) {
        all_days += DAYS[i];
    }
    // day
    all_days += d_day;

    return (enum day)((all_days + ORIGIN_DAY) % 7);
}

int main(void) {
    char number[10] = "\0";
    int year = 0, month = 0, day = 0;

    scanf("%s", number);
    scanf("%d %d %d", &year, &month, &day);

    int last_number = get_last_char(number) - '0';
    enum day weekday = get_week_day(year, month, day);

    printf("%s\n", is_restricted(last_number, weekday) ? "restricted!" : "NOT restricted!");
    return 0;
}
