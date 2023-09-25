#include <stdio.h>

int GetFebruaryDayCount(int year){
    if(year % 100 == 0) return year % 400 == 0 ? 29 : 28;
    else return year % 4 == 0 ? 29 : 28;
}
const int daysInMonth[] = {31, -1, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
void MakeDateLegal(int* _year, int* _month, int* _day){
    int day = (*_day);
    int month = (*_month);
    int year = (*_year);
    while(day > (month == 2 ? GetFebruaryDayCount(year) : daysInMonth[month - 1])){
        day -= month == 2 ? GetFebruaryDayCount(year) : daysInMonth[month - 1];
        month++;
        if(month > 12){
            year++;
            month = 1;
        }
    }
    (*_year) = year;
    (*_month) = month;
    (*_day) = day;
    return;
}
void GetDateInDays(int* year, int* month, int* day, int dayPassed){
    (*day) += dayPassed;
    MakeDateLegal(year, month, day);
}

//向GetDateInDays传入year，month，day和步进天数（必须大于0）
//注意year和month和day需要加取地址符&
//函数退出后会自动将year，month，day设置成步进天数之后的日期

//示例，计算1976年5月16日开始13085天之后的日期
int main(){
    int year = 1976;
    int month = 5;
    int day = 16;
    GetDateInDays(&year, &month, &day, 13085);
    printf("%d|%d|%d\n", year, month, day);
}
