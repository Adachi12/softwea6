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
        srt.saved_route1, srt.saved_route2, srt.saved_route3, \
        srt.saved_route4, srt.saved_route5, srt.id);

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

int saved_route_insert(SAVED_ROUTE_TABLE srt) {
    MYSQL *conn     = NULL;
    char sql_str[511];
    char *sql_serv  = "localhost";
    char *user      = "root";
    char *passwd    = "mariadb";
    char *db_name   = "jogging";

    memset( &sql_str[0] , 0x00 , sizeof(sql_str) );

    // SQL発行
    sprintf(sql_str, "INSERT INTO SAVED_ROUTE_TABLE \
        values('%08d', %s', '%s', '%s', '%s', '%s')",\
        srt.id, srt.saved_route1, srt.saved_route2,\
        srt.saved_route3, srt.saved_route4, srt.saved_route5);

    // mysql接続
    conn = mysql_init(NULL);
    if( !mysql_real_connect(conn,sql_serv,user,passwd,db_name,0,NULL,0) ) {
        // error
        return 1;
    }
    // 実行
    if( mysql_query( conn , &sql_str[0] ) ){
        // error
        printf("error!\n");
        mysql_close(conn);
        return 1;
    }

    mysql_close(conn);

    return 0;
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
    SAVED_ROUTE_TABLE resp_data = \
        {1, "", "", "", "", ""};

    memset( &sql_str[0] , 0x00 , sizeof(sql_str) );

    // SQL発行
    sprintf(sql_str, "SELECT * FROM SAVED_ROUTE_TABLE where id='%08d'", id);

    // mysql接続
    conn = mysql_init(NULL);
    if( !mysql_real_connect(conn,sql_serv,user,passwd,db_name,0,NULL,0) ){
        // error
        return resp_data;
    }

    // 実行
    if( mysql_query( conn , &sql_str[0] ) ){
        // error
        mysql_close(conn);
        return resp_data;
    }

    // レスポンス
    resp = mysql_use_result(conn);
    while((row = mysql_fetch_row(resp)) != NULL ){
        resp_data.error = 0;
        resp_data.id = atoi(row[0]);
        sprintf(resp_data.saved_route1, "%s", row[1]);
        sprintf(resp_data.saved_route2, "%s", row[2]);
        sprintf(resp_data.saved_route3, "%s", row[3]);
        sprintf(resp_data.saved_route4, "%s", row[4]);
        sprintf(resp_data.saved_route5, "%s", row[5]);
    }

    mysql_free_result(resp);
    mysql_close(conn);

    return resp_data;
}