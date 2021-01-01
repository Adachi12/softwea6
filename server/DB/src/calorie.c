#include<stdio.h>
#include<time.h>
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

    unsigned int seed = (unsigned int)time(NULL);
    srand(seed);   // random access variable
    int rand_id = rand()%5;
    CALORIE_TABLE resp_data = {1, -1, "", -1};

    snprintf(&sql_str[0], sizeof(sql_str)-1, \
        "SELECT * FROM CALORIE_TABLE where food='%08d'", \
        rand_id);

    // mysql接続
    conn = mysql_init(NULL);
    if( !mysql_real_connect(conn,sql_serv,user,passwd,db_name,0,NULL,0) ){
        // error
        return resp_data;
    }

    // クエリ実行
    printf("%s\n", sql_str);
    if( mysql_query( conn , &sql_str[0] ) ){
        // error
        mysql_close(conn);
        return resp_data;
    }

    // レスポンス
    resp = mysql_use_result(conn);
    resp_data.error = 0;
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