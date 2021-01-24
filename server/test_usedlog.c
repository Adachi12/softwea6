#include"jogging.h"

int usedlog_select_test_start();
int usedlog_insert_test_start();

int main(int argc, char *argv[]) {
    if ( argc != 2 ) {
        perror("Invalid command line argument\n");
        return 1;
    }

    if ( strcmp(argv[1], "insert") == 0 ) {
        usedlog_insert_test_start();
    } else if ( strcmp(argv[1], "select") == 0 ) {
        usedlog_select_test_start();
    } else {
        perror("Invalid command line argument\n");
    }

    return 0;
}

int usedlog_select_test_start() {
    USEDLOG_TABLE *resp_data0;
    USEDLOG_TABLE *resp_data1;
    USEDLOG_TABLE *resp_data2;
    USEDLOG_TABLE *resp_data3;
    USEDLOG_TABLE *resp_data4;
    int n0 = 0, n1 = 0, n2 = 0, n3 = 0, n4 = 0;

    resp_data0 = usedlog_select(0, &n0);
    print_ult(resp_data0, n0); 
    free(resp_data0);

    resp_data1 = usedlog_select(1571225, &n1);
    print_ult(resp_data1, n1); 
    free(resp_data1);

    resp_data2 = usedlog_select(83614101, &n2);
    print_ult(resp_data2, n2); 
    free(resp_data2);

    resp_data3 = usedlog_select(88567915, &n3);
    print_ult(resp_data3, n3); 
    free(resp_data3);

    resp_data4 = usedlog_select(92065983, &n4);
    print_ult(resp_data4, n4); 
    free(resp_data4);

}

int usedlog_insert_test_start() {
    int result_sum = 0;
    USEDLOG_TABLE test_data1  = {0, 0, "2020-01-03 13:00:00",  4.5, "01:00:00", 400};
    USEDLOG_TABLE test_data2  = {0, 88567915, "2020-01-03 13:00:00",  5.0, "01:00:00", 400};
    USEDLOG_TABLE test_data3  = {0, 83614101, "2020-01-04 14:30:00",  2.0, "00:40:00", 400};
    USEDLOG_TABLE test_data4  = {0, 1571225, "2020-01-04 14:45:00", 10.0, "03:00:00", 400};
    USEDLOG_TABLE test_data5  = {0, 0, "2020-01-04 15:00:00",  4.5, "01:00:00", 400};
    USEDLOG_TABLE test_data6  = {0, 1571225, "2020-01-04 16:00:00", 15.5, "04:00:00", 400};
    USEDLOG_TABLE test_data7  = {0, 1571225, "2020-01-05 08:00:00", 13.0, "03:30:00", 400};
    USEDLOG_TABLE test_data8  = {0, 83614101, "2020-01-05 09:00:00",  2.5, "00:40:00", 400};
    USEDLOG_TABLE test_data9  = {0, 0, "2020-01-05 12:45:00",  4.5, "01:00:00", 400};
    USEDLOG_TABLE test_data10 = {0, 88567915, "2020-01-06 15:00:00",  4.5, "01:00:00", 400};
    USEDLOG_TABLE test_data11 = {0, 0, "2021-01-03 13:00:00",  4.5, "01:00:00", 400};
    USEDLOG_TABLE test_data12 = {0, 88567915, "2021-01-03 13:00:00",  5.0, "01:00:00", 400};
    USEDLOG_TABLE test_data13 = {0, 83614101, "2021-01-04 14:30:00",  2.0, "00:40:00", 400};
    USEDLOG_TABLE test_data14 = {0, 1571225, "2021-01-04 14:45:00", 10.0, "03:00:00", 400};
    USEDLOG_TABLE test_data15 = {0, 0, "2021-01-04 15:00:00",  4.5, "01:00:00", 400};
    USEDLOG_TABLE test_data16 = {0, 1571225, "2021-01-04 16:00:00", 15.5, "04:00:00", 400};
    USEDLOG_TABLE test_data17 = {0, 1571225, "2021-01-05 08:00:00", 13.0, "03:30:00", 400};
    USEDLOG_TABLE test_data18 = {0, 83614101, "2021-01-05 09:00:00",  2.5, "00:40:00", 400};
    USEDLOG_TABLE test_data19 = {0, 0, "2021-01-05 12:45:00",  4.5, "01:00:00", 400};
    USEDLOG_TABLE test_data20 = {0, 92065983, "2021-01-06 15:00:00",  4.5, "01:00:00", 400};
    USEDLOG_TABLE test_data21 = {0, 92065983, "2021-01-06 16:00:00",  4.5, "01:00:00", 400};
    USEDLOG_TABLE test_data22 = {0, 92065983, "2021-01-06 17:00:00",  4.5, "01:00:00", 400};
    USEDLOG_TABLE test_data23 = {0, 92065983, "2021-01-06 18:00:00",  4.5, "01:00:00", 400};
    USEDLOG_TABLE test_data24 = {0, 92065983, "2021-01-06 19:00:00",  4.5, "01:00:00", 400};
    USEDLOG_TABLE test_data25 = {0, 92065983, "2021-01-06 20:00:00",  4.5, "01:00:00", 400};
    USEDLOG_TABLE test_data26 = {0, 92065983, "2021-01-06 21:00:00",  4.5, "01:00:00", 400};

    result_sum += usedlog_insert(test_data1);
    result_sum += usedlog_insert(test_data2);
    result_sum += usedlog_insert(test_data3);
    result_sum += usedlog_insert(test_data4);
    result_sum += usedlog_insert(test_data5);
    result_sum += usedlog_insert(test_data6);
    result_sum += usedlog_insert(test_data7);
    result_sum += usedlog_insert(test_data8);
    result_sum += usedlog_insert(test_data9);
    result_sum += usedlog_insert(test_data10);
    result_sum += usedlog_insert(test_data11);
    result_sum += usedlog_insert(test_data12);
    result_sum += usedlog_insert(test_data13);
    result_sum += usedlog_insert(test_data14);
    result_sum += usedlog_insert(test_data15);
    result_sum += usedlog_insert(test_data16);
    result_sum += usedlog_insert(test_data17);
    result_sum += usedlog_insert(test_data18);
    result_sum += usedlog_insert(test_data19);
    result_sum += usedlog_insert(test_data20);
    result_sum += usedlog_insert(test_data21);
    result_sum += usedlog_insert(test_data22);
    result_sum += usedlog_insert(test_data23);
    result_sum += usedlog_insert(test_data24);
    result_sum += usedlog_insert(test_data25);
    result_sum += usedlog_insert(test_data26);

    printf("USEDLOG_TABLE select test result : %d\n", result_sum);

    return result_sum;
}

void print_ult(USEDLOG_TABLE *ult, int n) {
    printf("id : %d\n", ult[0].id);

    int i = 0;
    for(i = 0; i < n; i++) {
        printf("    datetime : %s\n", ult[i].jog_datetime);
        printf("    distance : %1.2f\n", ult[i].jog_distance);
        printf("    jogtime  : %8s\n", ult[i].jog_time);
        printf("    calorie  : %d\n", ult[i].burned_calorie);
        printf("\n");
    }
}