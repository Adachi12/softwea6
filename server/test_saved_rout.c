#include"jogging.h"

int saved_route_select_test_start();
int saved_route_update_test_start();

int main(int argc, char *argv[]) {
    if ( argc != 2 ) {
        perror("Invalid command line argument\n");
        return 1;
    }

    if ( strcmp(argv[1], "update") == 0 ) {
        saved_route_update_test_start();
    } else if ( strcmp(argv[1], "select") == 0 ) {
        saved_route_select_test_start();
    } else {
        perror("Invalid command line argument\n");
    }

    return 0;
}

int saved_route_update_test_start() {
    int error_sum = 0;
    FILE *fp01, *fp02, *fp11;
    char file_name01[] = "ssr0-0";
    char file_name02[] = "ssr0-1";
    char file_name11[] = "ssr1-0";

    fp01 = fopen(file_name01, "w");
    fprintf(fp01, "saved0-0\n");
    fclose(fp01);

    fp02 = fopen(file_name02, "w");
    fprintf(fp02, "saved0-1\n");
    fclose(fp02);

    fp11 = fopen(file_name11, "w");
    fprintf(fp11, "saved1-0\n");
    fclose(fp11);

    error_sum += saved_route_update(0, 1, file_name01);
    error_sum += saved_route_update(0, 2, file_name02);
    error_sum += saved_route_update(1, 1, file_name11);

    printf("USEDLOG_TABLE update result : %d\n", error_sum);

    return error_sum;
}

int saved_route_select_test_start() {
    int error_sum = 0;
    FILE *fp01, *fp02, *fp11;

    fp01 = saved_route_select(0, 1);
    fp02 = saved_route_select(0, 2);
    fp11 = saved_route_select(1, 1);

    if ( fp01 == NULL || fp02 == NULL || fp11 == NULL ) {
        printf("Error!\n");
    }
}