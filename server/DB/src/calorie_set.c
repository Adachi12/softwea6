#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void calorie_update();
void calorie_insert();

int main(void){
    calorie_insert();

    return 0;
}

void calorie_update() {
    MYSQL *conn     = NULL;
    char sql_str[255];
    char *sql_serv  = "localhost";
    char *user      = "root";
    char *passwd    = "mariadb";
    char *db_name   = "jogging";

    memset( &sql_str[0] , 0x00 , sizeof(sql_str) );

    // mysql接続
    conn = mysql_init(NULL);
    if( !mysql_real_connect(conn,sql_serv,user,passwd,db_name,0,NULL,0) ){
        // error
        exit(-1);
    }

    // クエリ実行
    snprintf( &sql_str[0] , sizeof(sql_str)-1 , "update CALORIE_TABLE SET food_calorie=909 where food=1" );
    if( mysql_query( conn , &sql_str[0] ) ){
        // error
        mysql_close(conn);
        exit(-1);
    }

    mysql_close(conn);
}

void calorie_insert() {
    MYSQL *conn     = NULL;
    char sql_str[255];
    char *sql_serv  = "localhost";
    char *user      = "root";
    char *passwd    = "mariadb";
    char *db_name   = "jogging";

    memset( &sql_str[0] , 0x00 , sizeof(sql_str) );

    // mysql接続
    conn = mysql_init(NULL);
    if( !mysql_real_connect(conn,sql_serv,user,passwd,db_name,0,NULL,0) ) {
        // error
        exit(-1);
    }

    // クエリ実行
    snprintf( &sql_str[0] , sizeof(sql_str)-1 , "INSERT into CALORIE_TABLE values(2, 'ラーメン', 436)" );
    if( mysql_query( conn , &sql_str[0] ) ){
        // error
        mysql_close(conn);
        exit(-1);
    }

    mysql_close(conn);
}