#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogging.h"

int saved_route_update(SAVED_ROUTE_TABLE srt) {
    MYSQL *conn     = NULL;
    char sql_str[511];
    char *sql_serv  = "localhost";
    char *user      = "root";
    char *passwd    = "mariadb";
    char *db_name   = "jogging";

    memset( &sql_str[0] , 0x00 , sizeof(sql_str) );

    // SQL発行
    sprintf(sql_str, "UPDATE SAVED_ROUTE_TABLE SET \
        saved_route1='%s', saved_route2='%s', saved_route3='%s', \
        saved_route4='%s', saved_route5='%s' where id=%08d",\
        srt.saved_r1, srt.saved_r2, srt.saved_r3, \
        srt.saved_r4, srt.saved_r5, srt.id);

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

int saved_route_insert(SAVED_ROUTE_TABLE srt) {
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
        values('%s', %s', '%s', '%s', '%s', '%s')",\
        id_buf, srt.saved_r1, srt.saved_r2,\
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


SAVED_ROUTE_TABLE saved_route_select(int id) {
    MYSQL *conn     = NULL;
    MYSQL_RES *resp = NULL;
    MYSQL_ROW row;
    char sql_str[511];
    char *sql_serv  = "localhost";
    char *user      = "root";
    char *passwd    = "mariadb";
    char *db_name   = "jogging";

    // 返信用のデータ
    SRT resp_data;

    memset( &sql_str[0] , 0x00 , sizeof(sql_str) );

    // SQL発行
    sprintf(sql_str, "SELECT * FROM SAVED_ROUTE_TABLE where id='%08d'", id);

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
        resp_data.id = atoi(row[0]);
        sprintf(resp_data.saved_r1, "%s", row[1]);
        sprintf(resp_data.saved_r2, "%s", row[2]);
        sprintf(resp_data.saved_r3, "%s", row[3]);
        sprintf(resp_data.saved_r4, "%s", row[4]);
        sprintf(resp_data.saved_r5, "%s", row[5]);
    }

    mysql_free_result(resp);
    mysql_close(conn);

    return resp_data;
}