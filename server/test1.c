#include"jogging.h"

int user_insert_test_start();
int user_update_test_start();
int user_select_test_start();

int user_insert_test(USER_TABLE test_data);
int user_update_test(USER_TABLE test_data);
int user_select_test(int user_id);

void print_ut(USER_TABLE ut);


int main(int argc, char *argv[]) {
    if ( argc == 1 ) {
        printf("Please enter a command line argument : \
            'insert' or 'update' or 'select'\n");
        return 1;
    }

    if ( strcmp(argv[1], "insert") == 0 ) {
        user_insert_test_start();
    } else if ( strcmp(argv[1], "update") == 0 ) {
        user_insert_test_start();
        user_update_test_start();
    } else if ( strcmp(argv[1], "select") == 0 ) {
        user_select_test_start();
    } else {
        perror("Invalid command line argument\n");
    }

    return 0;
}

int user_update_test_start() {
    USER_TABLE test_data1 = 
        {0, 0, "pass1", "name1", 68.0, 166.0, 
        30, 1, "1990-01-01", 60.0, "2021-3-1", "mail-address1@yahoo.co.jp"};
    int result1 = user_update_test(test_data1);

    USER_TABLE test_data2 = 
        {0, 1, "pass2", "name2", 72.0, 156.0, 
        27, 0, "1990-02-01", 58.0, "2021-2-1", "mail-address2@yahoo.co.jp"};
    int result2 = user_update_test(test_data2);

    USER_TABLE test_data3 = 
        {0, 2, "pass3", "name3", 85.0, 171.0, 
        24, 1, "1990-03-01", 70.0, "2021-2-1", "mail-address3@yahoo.co.jp"};
    int result3 = user_update_test(test_data3);

    USER_TABLE test_data4 = 
        {0, 3, "pass4", "name4", 86.0, 180.0, 
        20, 1, "1990-04-01", 77.0, "2021-2-1", "mail-address4@yahoo.co.jp"};
    int result4 = user_update_test(test_data4);

    int result = result1 + result2 + result3 + result4;
    printf("select test result : %d\n", result);
}

int user_insert_test_start() {
    USER_TABLE test_data1 = 
        {0, 0, "pass1", "name1", 70.0, 165.0, 
        30, 1, "1990-01-01", 60.0, "2021-2-1", "mail-address1@yahoo.co.jp"};
    int result1 = user_insert_test(test_data1);

    USER_TABLE test_data2 = 
        {0, 1, "pass2", "name2", 74.0, 155.0, 
        27, 0, "1990-02-01", 60.0, "2021-2-1", "mail-address2@yahoo.co.jp"};
    int result2 = user_insert_test(test_data2);

    USER_TABLE test_data3 = 
        {0, 2, "pass3", "name3", 90.0, 172.0, 
        24, 1, "1990-03-01", 60.0, "2021-2-1", "mail-address3@yahoo.co.jp"};
    int result3 = user_insert_test(test_data3);

    USER_TABLE test_data4 = 
        {0, 3, "pass4", "name4", 85.0, 179.0, 
        20, 1, "1990-04-01", 60.0, "2021-2-1", "mail-address4@yahoo.co.jp"};
    int result4 = user_insert_test(test_data4);

    int result = result1 + result2 + result3 + result4;
    printf("select test result : %d\n", result);
}

int user_select_test_start() {
    USER_TABLE test_data1 = 
        {0, 0, "pass1", "name1", 70.0, 165.0, 
        30, 1, "1990-01-01", 60.0, "2021-2-1", "mail-address1@yahoo.co.jp"};
    int result1 = user_insert_test(test_data1);
    USER_TABLE resp_data1 = user_select(result1);
    print_ut(resp_data1);

    USER_TABLE test_data2 = 
        {0, 0, "pass1", "name1", 70.0, 165.0, 
        30, 1, "1990-01-01", 60.0, "2021-2-1", "mail-address1@yahoo.co.jp"};
    int result2 = user_insert_test(test_data2);
    USER_TABLE resp_data2 = user_select(result2);
    print_ut(resp_data2);

    USER_TABLE test_data3 = 
        {0, 0, "pass1", "name1", 70.0, 165.0, 
        30, 1, "1990-01-01", 60.0, "2021-2-1", "mail-address1@yahoo.co.jp"};
    int result3 = user_insert_test(test_data3);
    USER_TABLE resp_data3 = user_select(result3);
    print_ut(resp_data3);

    USER_TABLE test_data4 = 
        {0, 0, "pass1", "name1", 70.0, 165.0, 
        30, 1, "1990-01-01", 60.0, "2021-2-1", "mail-address1@yahoo.co.jp"};
    int result4 = user_insert_test(test_data4);
    USER_TABLE resp_data4 = user_select(result4);
    print_ut(resp_data4);
}

void print_ut(USER_TABLE ut) {
    printf("id              : %d\n", ut.id);
    printf("    pass        : %s\n", ut.pass);
    printf("    name        : %s\n", ut.name);
    printf("    weight      : %lf\n", ut.weight);
    printf("    height      : %lf\n", ut.height);
    printf("    age         : %d\n", ut.age);
    printf("    sex         : %d\n", ut.sex);
    printf("    birth       : %s\n", ut.birth);
    printf("    goal_weight : %lf\n", ut.goal_weight);
    printf("    goal_term   : %s\n", ut.goal_term);
    printf("    mail_addr   : %s\n", ut.mail_address);
}

int user_insert_test(USER_TABLE test_data) {
    // calorie_table access test
    int errno = user_insert(test_data);

    printf("USER_TABLE insert error number : %d\n", errno);

    return errno;
}

int user_update_test(USER_TABLE test_data) {
    // calorie_table access test
    int errno = user_update(test_data);

    printf("USER_TABLE update error number : %d\n", errno);

    return errno;
}
