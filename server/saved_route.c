#include "jogging.h"

int saved_route_update(int user_id, int route_id, char route_file[]) {
    MYSQL *conn     = NULL;
    char sql_str[511];
    char *sql_serv  = "localhost";
    char *user      = "root";
    char *passwd    = "mariadb";
    char *db_name   = "jogging";

    memset( &sql_str[0] , 0x00 , sizeof(sql_str) );

    if ( !(1 <= route_id && route_id <= 5) ) {
        return 1;
    }

    // SQL発行
    sprintf(sql_str, "UPDATE SAVED_ROUTE_TABLE SET saved_route%d='%s' where id = '%08d'", 
        route_id, &route_file[0], user_id);
    printf("RUN : %s\n", sql_str);

    // mysql接続
    conn = mysql_init(NULL);
    if( !mysql_real_connect(conn,sql_serv,user,passwd,db_name,0,NULL,0) ) {
        // error
        return 1;
    }
    // 実行
    if( mysql_query( conn , &sql_str[0] ) ){
        // error
        mysql_close(conn);
        return 1;
    }

    mysql_close(conn);

    return 0;
}

int saved_route_insert(int user_id) {
    MYSQL *conn     = NULL;
    char sql_str[511];
    char *sql_serv  = "localhost";
    char *user      = "root";
    char *passwd    = "mariadb";
    char *db_name   = "jogging";

    memset( &sql_str[0] , 0x00 , sizeof(sql_str) );

    // SQL発行
    sprintf(sql_str, 
        "INSERT INTO SAVED_ROUTE_TABLE values('%08d', \"\", \"\", \"\", \"\", \"\")", 
        user_id);

    // mysql接続
    conn = mysql_init(NULL);
    if( !mysql_real_connect(conn,sql_serv,user,passwd,db_name,0,NULL,0) ) {
        // error
        return 1;
    }

    // 実行
    if( mysql_query( conn , &sql_str[0] ) ){
        // error
        mysql_close(conn);
        return 2;
    }

    mysql_close(conn);

    return 0;
}


FILE *saved_route_select(int user_id, int route_id) {
    MYSQL *conn     = NULL;
    MYSQL_RES *resp = NULL;
    MYSQL_ROW row;
    char sql_str[511];
    char *sql_serv  = "localhost";
    char *user      = "root";
    char *passwd    = "mariadb";
    char *db_name   = "jogging";

    // 返信用のデータ
    char file_name[7];
    FILE *fp = NULL;

    memset( &sql_str[0] , 0x00 , sizeof(sql_str) );

    // SQL発行
    sprintf(sql_str, "SELECT saved_route%d FROM SAVED_ROUTE_TABLE where id='%08d'", 
        route_id, user_id);
    printf("RUN : %s\n", sql_str);

    // mysql接続
    conn = mysql_init(NULL);
    if( !mysql_real_connect(conn,sql_serv,user,passwd,db_name,0,NULL,0) ){
        // error
        return fp;
    }

    // 実行
    if( mysql_query( conn , &sql_str[0] ) ){
        // error
        mysql_close(conn);
        return fp;
    }

    // レスポンス
    resp = mysql_use_result(conn);
    while((row = mysql_fetch_row(resp)) != NULL ){
        snprintf(file_name, 7, "%s", row[0]);
        printf("Access to %s\n", file_name);
        fp = fopen(file_name, "r");
    }

    mysql_free_result(resp);
    mysql_close(conn);

    return fp;
}