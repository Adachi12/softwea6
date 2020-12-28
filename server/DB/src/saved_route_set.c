#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void saved_route_update();
void saved_route_insert(int id, char half_p[15], char sr1[30], char sr2[30], char sr3[30], char sr4[30], char sr5[30], char sql_str[511]);

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
    if( !mysql_real_connect(conn,sql_serv,user,passwd,db_name,0,NULL,0) ) {
        // error
        exit(-1);
    }

    // クエリ実行
    saved_route_insert(0, "halfway_point", "saved_route1", "saved_route2", "saved_route3",\
        "saved_route4", "saved_route5", sql_str);
    printf("%s\n", sql_str);
    if( mysql_query( conn , &sql_str[0] ) ){
        // error
        printf("error!\n");
        mysql_close(conn);
        exit(-1);
    }

    mysql_close(conn);
}

void saved_route_update() {

}

void saved_route_insert(int id, char half_p[15], char sr1[30], char sr2[30], char sr3[30], char sr4[30], char sr5[30], char sql_str[511]) {
    char id_buf[9];
    snprintf(id_buf, 9, "%08d", id);

    sprintf(sql_str, "INSERT INTO SAVED_ROUTE_TABLE \
        values('%s', '%s', '%s', '%s', '%s', '%s', '%s')",\
        id_buf, half_p, sr1, sr2, sr3, sr4, sr5);
}