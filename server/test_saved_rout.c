#include"jogging.h"

int  saved_route_select_test();

int main() {
    FILE *result1 = saved_route_select_test();
    FILE *result2 = saved_route_select_test();
    FILE *result3 = saved_route_select_test();
    FILE *result4 = saved_route_select_test();

    int result = result1 + result2 + result3 + result4;
    printf("select test result : %d\n", result);
}

int saved_route_select_test() {
    int error_sum = 0;

    // saved_route_table access test
    saved_route_TABLE ct = saved_route_select();
    error_sum += ct.error;
    printf("id: %d\n", ct.food);
    printf("    food_name    : %s\n", ct.food_name);
    printf("    food_saved_route : %d\n", ct.food_saved_route);

    return error_sum;
}
