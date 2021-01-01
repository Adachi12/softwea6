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

    // saved_route access test
    SAVED_ROUTE_TABLE srt0 = saved_route_select(0);
    SAVED_ROUTE_TABLE srt1 = saved_route_select(1);
    SAVED_ROUTE_TABLE srt2 = saved_route_select(2);
    SAVED_ROUTE_TABLE srt3 = saved_route_select(3);

    error_sum += srt0.error + srt1.error + srt2.error + srt3.error;

    print_srt(srt0);
    print_srt(srt1);
    print_srt(srt2);
    print_srt(srt3);

    return error_sum;
}

void print_srt(SAVED_ROUTE_TABLE srt) {
    printf("id : %d\n", srt.id);
    printf("    saved_route1 : %s\n", srt.saved_route1);
    printf("    saved_route2 : %s\n", srt.saved_route2);
    printf("    saved_route3 : %s\n", srt.saved_route3);
    printf("    saved_route4 : %s\n", srt.saved_route4);
    printf("    saved_route5 : %s\n", srt.saved_route5);
    printf("\n");
}