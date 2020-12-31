#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void calorie_insert(int id, char name[], int cal, char sql_str[511]);

int main(void){
    MYSQL *conn     = NULL;
    char sql_str[511];
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
    calorie_insert(5, "ペヤング大盛り", 1081, &sql_str[0]);
    printf("%s\n", sql_str);
    if( mysql_query( conn , &sql_str[0] ) ) {
        // error
        printf("error\n");
        mysql_close(conn);
        exit(-1);
    }

    mysql_close(conn);

    return 0;
}

// 挿入するデータと
void calorie_insert(int id, char name[], int cal, char sql_str[511]) {
    char id_buf[9];
    snprintf(id_buf, 9, "%08d", id);
    
    char cal_buf[5];
    snprintf(cal_buf, 5, "%d", cal);

    sprintf(sql_str, "INSERT INTO CALORIE_TABLE values('%s', '%s', %s)",\
        id_buf, name, cal_buf);
}