#include<stdio.h>
#include<stdlib.h>
#include "jogging.h"

CALORIE_TABLE calorie_select() {
    MYSQL *conn     = NULL;
    MYSQL_RES *resp = NULL;
    MYSQL_ROW row;
    char sql_str[511];
    char *sql_serv  = "localhost";
    char *user      = "root";
    char *passwd    = "mariadb";
    char *db_name   = "jogging";

    int rand_id = rand()%5;   // random access variable
    CALORIE_TABLE resp_data;

    snprintf(&sql_str[0], sizeof(sql_str)-1, \
        "SELECT * FROM CALORIE_TABLE where id='%08d'", \
        rand_id);

    // mysql接続
    conn = mysql_init(NULL);
    if( !mysql_real_connect(conn,sql_serv,user,passwd,db_name,0,NULL,0) ){
        // error
        printf("error!");
        exit(-1);
    }

    // クエリ実行
    if( mysql_query( conn , &sql_str[0] ) ){
        // error
        mysql_close(conn);
        exit(-1);
    }

    // レスポンス
    resp = mysql_use_result(conn);
    while((row = mysql_fetch_row(resp)) != NULL ){
        resp_data.food = atoi(row[0]);
        sprintf(resp_data.food_name, "%s", row[1]);
        resp_data.food_calorie = atoi(row[2]);
    }

    // 後片づけ
    mysql_free_result(resp);
    mysql_close(conn);
    
    return resp_data;
}