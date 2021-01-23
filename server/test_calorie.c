#include"jogging.h"

int  calorie_select_test();

int main() {
    int result1 = calorie_select_test();
    int result2 = calorie_select_test();
    int result3 = calorie_select_test();
    int result4 = calorie_select_test();

    int result = result1 + result2 + result3 + result4;
    printf("select test result : %d\n", result);
}

int calorie_select_test() {
    int error_sum = 0;

    // calorie_table access test
    CALORIE_TABLE ct = calorie_select();
    error_sum += ct.error;
    printf("id: %d\n", ct.food);
    printf("    food_name    : %s\n", ct.food_name);
    printf("    food_calorie : %d\n", ct.food_calorie);

    char sendBuffer[1024];
    ct_tab2str_select(sendBuffer, ct);
    printf("sendBuffer : \n%s\n(finish)\n\n", sendBuffer);

    return error_sum;
}
