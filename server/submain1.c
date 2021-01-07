#include"jogging.h"

void print_srt(SAVED_ROUTE_TABLE srt);
int  select_test();

int main() {
    int result = select_test();
    printf("select test result : %d\n", result);
}

int select_test() {
    int error_sum = 0;

    // calorie_table access test
    CALORIE_TABLE ct = calorie_select();
    error_sum += ct.error;
    printf("id: %d\n", ct.food);
    printf("    food_name    : %s\n", ct.food_name);
    printf("    food_calorie : %d\n", ct.food_calorie);

    error_sum += srt0.error + srt1.error + srt2.error + srt3.error;

    print_srt(srt0);
    print_srt(srt1);
    print_srt(srt2);
    print_srt(srt3);

    return error_sum;
}
