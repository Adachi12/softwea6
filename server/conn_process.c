#include"conn_process.h"
#include"DB/src/jogging.h"

void conn_calorie_select(int connfd) {
    CALORIE_TABLE resp_data = calorie_select();
    char buf[BUFSIZ];
    char *resp_bytes[BUFSIZ];

    if ( calorie_tab2str(&resp_bytes, resp_data) == 1 || \
            resp_data.error == 1 ) {
        conn_error(connfd);
    }
    snprintf(buf, 260, "%s", resp_bytes);
    printf("%s\n", buf);
    write(connfd, resp_bytes, 260);
}

void conn_saved_route_select(int connfd) {

}

void conn_saved_route_update(int connfd) {

}

void conn_usedlog_select(int connfd) {
}

void conn_usedlog_insert(int connfd) {
}

void conn_user_insert(int connfd) {
    USER_TABLE insert_data_ut;
    SAVED_ROUTE_TABLE insert_data_srt;
    char buf[BUFSIZ];

    read(connfd, buf, 390);
    insert_data_ut = user_str2tab(buf);
    insert_data_srt = {insert_data_ut.id, "", "", "", "", ""};

    int i = user_insert(insert_data_ut) + \
            saved_route_insert(insert_data_srt);

    if ( i > 0 ) {
        conn_error(connfd);
    }

    buf[0] = 0x00;
    write(connfd, buf, 1);
}

void conn_user_update(int connfd) {
    USER_TABLE insert_data;
    char buf[BUFSIZ];

    read(connfd, buf, 390);
    insert_data = user_str2tab(buf);

    if ( user_update(insert_data) == 1 ) {
        conn_error(connfd);
    }

    buf[0] = 0x00;
    write(connfd, buf, 1);
}

void conn_user_select(int connfd) {
    USER_TABLE resp_data;
    int id;
    char buf[BUFSIZ];
    char *resp_bytes[BUFSIZ];

    read(connfd, buf, 4);
    id = atoi(buf);

    resp_data = user_select(id);

    if ( calorie_tab2str(&resp_bytes, resp_data) || \
            resp_data.error == 1 ) {
        conn_error(connfd);
    }

    snprintf(buf, 390, "%s", resp_data);
    printf("%s\n", buf);
    write(connfd, buf, 260);
}


void conn_error(int connfd) {
    char buf[BUFSIZ];

    perror("Error\n");
    buf[0] = 0x01;
    write(connfd, buf, 1);
}