#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

typedef struct {
    int id;
    char half_p[30];
    char saved_r1[30];
    char saved_r2[30];
    char saved_r3[30];
    char saved_r4[30];
    char saved_r5[30];
} SRT ;

void saved_route_update();
void saved_route_insert(SRT srt);
void saved_route_select(int id);

int main(void){
    // insertするデータを設定
    SRT srt = {1, "half_p", "sr1", "sr2", "sr3", "sr4", "sr5"};

    // insert文実行
    saved_route_insert(srt);
    saved_route_select(5);
}

void saved_route_update() {

}

void saved_route_insert(SRT srt) {
    MYSQL *conn     = NULL;
    char sql_str[511];
    char *sql_serv  = "localhost";
    char *user      = "root";
    char *passwd    = "mariadb";
    char *db_name   = "jogging";

    memset( &sql_str[0] , 0x00 , sizeof(sql_str) );

    // SQL発行
    char id_buf[9];
    snprintf(id_buf, 9, "%08d", srt.id);
    sprintf(sql_str, "INSERT INTO SAVED_ROUTE_TABLE \
        values('%s', '%s', '%s', '%s', '%s', '%s', '%s')",\
        id_buf, srt.half_p, srt.saved_r1, srt.saved_r2,\
        srt.saved_r3, srt.saved_r4, srt.saved_r5);

    // mysql接続
    conn = mysql_init(NULL);
    if( !mysql_real_connect(conn,sql_serv,user,passwd,db_name,0,NULL,0) ) {
        // error
        exit(-1);
    }
    // 実行
    if( mysql_query( conn , &sql_str[0] ) ){
        // error
        printf("error!\n");
        mysql_close(conn);
        exit(-1);
    }

    mysql_close(conn);
}


void saved_route_select(int id) {
    MYSQL *conn     = NULL;
    MYSQL_RES *resp = NULL;
    MYSQL_ROW row;
    char sql_str[511];
    char *sql_serv  = "localhost";
    char *user      = "root";
    char *passwd    = "mariadb";
    char *db_name   = "jogging";

    // 返信用のデータ
    SRT res_data;

    memset( &sql_str[0] , 0x00 , sizeof(sql_str) );

    // SQL発行
    char id_buf[9];
    snprintf(id_buf, 9, "%08d", id);
    sprintf(sql_str, "SELECT * FROM SAVED_ROUTE_TABLE where user_id=%s", id_buf);

    // mysql接続
    conn = mysql_init(NULL);
    if( !mysql_real_connect(conn,sql_serv,user,passwd,db_name,0,NULL,0) ){
        // error
        exit(-1);
    }

    // 実行
    if( mysql_query( conn , &sql_str[0] ) ){
        // error
        printf("error!\n");
        mysql_close(conn);
        exit(-1);
    }

    // レスポンス
    resp = mysql_use_result(conn);
    while((row = mysql_fetch_row(resp)) != NULL ){
        // printf( "%s : %s : %s : %s : %s : %s : %s\n",\
        //     row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
        res_data.id = atoi(row[0]);
        sprintf(res_data.half_p, "%s", row[1]);
        sprintf(res_data.saved_r1, "%s", row[2]);
        sprintf(res_data.saved_r2, "%s", row[3]);
        sprintf(res_data.saved_r3, "%s", row[4]);
        sprintf(res_data.saved_r4, "%s", row[5]);
        sprintf(res_data.saved_r5, "%s", row[6]);
    }

    mysql_free_result(resp);
    mysql_close(conn);

    // test
    printf("id: %d\n", res_data.id);
    printf("    half_p: %s\n", res_data.half_p);
    printf("    sr1: %s\n", res_data.saved_r1);
    printf("    sr2: %s\n", res_data.saved_r2);
    printf("    sr3: %s\n", res_data.saved_r3);
    printf("    sr4: %s\n", res_data.saved_r4);
    printf("    sr5: %s\n", res_data.saved_r5);
}