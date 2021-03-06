#include<stdio.h>
#include<stdlib.h>
#include"jogging.h"

int select_test2();
    
int main() {
    int result = select_test2();
    printf("select test result : %d\n", result);
}

int select_test2() {
    int error_sum = 0;
    
    // user_table access test
    USER_TABLE ut = user_select(1);
    error_sum += ut.error;
    printf("ユーザID：%d\n",ut.id);
    printf("体重：%lf\n", ut.weight);
    printf("身長：%lf\n", ut.height);
    printf("年齢：%d\n", ut.age);
    printf("性別：%d\n", ut.sex);
    printf("生年月日：%s\n", ut.birth);
    printf("目標体重：%lf\n", ut.goal_weight);
    printf("目標期間：%s\n", ut.goal_term);
    
    //usedlog_table access test
    //該当データ数
    int n = 0;
    
    USEDLOG_TABLE *ult = usedlog_select(1, &n);
    error_sum += ult[0].error;
    printf("走行日時：%s\n", ult[1].jog_datetime);
    printf("走行距離：%lf\n", ult[2].jog_distance);
    printf("走行時間：%s\n", ult[3].jog_time);
    printf("運動燃焼量：%d\n", ult[4].burned_calorie);
    print_ult(ult, n);
    free(ult);
    
    return error_sum;
}
