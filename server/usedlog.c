#include "jogging.h"

int usedlog_insert(USEDLOG_TABLE ult){
    MYSQL *conn     = NULL;
    char sql_str[511];
    char *sql_serv  = "localhost";
    char *user      = "root";
    char *passwd    = "mariadb";
    char *db_name   = "jogging";

    // SQL発行
    sprintf(sql_str, "INSERT INTO USEDLOG_TABLE \
        VALUES('%08d', '%19s', %lf, '%s', %d)", \
        ult.id, ult.jog_datetime, ult.jog_distance, ult.jog_time, ult.burned_calorie);
    
    // mysql接続
    conn = mysql_init(NULL);
    if( !mysql_real_connect(conn,sql_serv,user,passwd,db_name,0,NULL,0) ){
        // error
        return 1;
    }

    // クエリ実行
    if( mysql_query( conn , &sql_str[0] ) ){
        // error
        printf("error!\n%s\n", sql_str);
        mysql_close(conn);
        return 1;
    }
    
    mysql_close(conn);
    return 0;
}

USEDLOG_TABLE *usedlog_select(int id, int *n) {
    MYSQL *conn     = NULL;
    MYSQL_RES *resp = NULL;
    MYSQL_ROW row;
    char sql_str[511];
    char *sql_serv  = "localhost";
    char *user      = "root";
    char *passwd    = "mariadb";
    char *db_name   = "jogging";

    // ループインデックス
    int i = 0;

    // 返信用のデータ
    USEDLOG_TABLE *res_data;

    memset( &sql_str[0] , 0x00 , sizeof(sql_str) );

    // 1ヶ月以前のデータ削除
    usedlog_delete(id);

    // mysql接続
    conn = mysql_init(NULL);
    if( !mysql_real_connect(conn,sql_serv,user,passwd,db_name,0,NULL,0) ){
        // error
        res_data[0].error = 1;
        return res_data;
    }

    // count
    sprintf(sql_str, "SELECT count(*) FROM USEDLOG_TABLE where id='%08d'", id);
    // 実行
    if( mysql_query( conn , &sql_str[0] ) ){
        // error
        printf("error!\n%s\n", sql_str);
        mysql_close(conn);
        res_data[0].error = 1;
        return res_data;
    }
    // レスポンス
    resp = mysql_use_result(conn);
    while((row = mysql_fetch_row(resp)) != NULL ){
        *n = atoi(row[0]);
    }
    mysql_free_result(resp);
    
    res_data = (USEDLOG_TABLE *)malloc(sizeof(USEDLOG_TABLE) * (*n));


    // アクセスSQL文
    sprintf(sql_str, "SELECT * FROM USEDLOG_TABLE where id='%08d'", id);

    // 実行
    if( mysql_query( conn , &sql_str[0] ) ){
        // error
        printf("error!\n%s\n", sql_str);
        mysql_close(conn);
        res_data[0].error = 1;
        return res_data;
    }

    // レスポンス
    resp = mysql_use_result(conn);
    while((row = mysql_fetch_row(resp)) != NULL ) {
        res_data[i].error = 0;
        res_data[i].id = id;
        sprintf(res_data[i].jog_datetime, "%19s", row[1]);
        res_data[i].jog_distance = atof(row[2]);
        sprintf(res_data[i].jog_time, "%9s", row[3]);
        res_data[i].burned_calorie = atoi(row[4]);
        i++;
    }
    mysql_free_result(resp);

    return res_data;
}

int usedlog_delete(int id) {
    MYSQL *conn     = NULL;
    char sql_str[511];
    char *sql_serv  = "localhost";
    char *user      = "root";
    char *passwd    = "mariadb";
    char *db_name   = "jogging";

    // SQL発行
    char month_ago_buf[20];
    month_ago(month_ago_buf);
    
    // write to buffer
    sprintf(sql_str, "DELETE from USEDLOG_TABLE where jog_datetime <= '%s'", 
        &month_ago_buf[0]);
    printf("%s\n", sql_str);

    // mysql接続
    conn = mysql_init(NULL);
    if( !mysql_real_connect(conn,sql_serv,user,passwd,db_name,0,NULL,0) ){
        // error
        return 1;
    }

    // クエリ実行
    if( mysql_query( conn , &sql_str[0] ) ){
        // error
        printf("error!\n");
        mysql_close(conn);
        return 1;
    }
    
    mysql_close(conn);
    return 0;
}

void month_ago(char *buf) {
    struct tm tm;
    time_t t = time(NULL);
    localtime_r(&t, &tm);
    int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // 1ヶ月前の日付に直す
    int diff = 30 - tm.tm_mday;
    tm.tm_mday = days[tm.tm_mon] - diff;
    if (tm.tm_mon == 0) {
        tm.tm_mon = 11;
        tm.tm_year--;
    } else {
        tm.tm_mon--;
    }

    // 求めた日付をもとに文字列を生成
    snprintf(buf, 20, "%04d/%02d/%02d %02d:%02d:%02d", \
        tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday - 1, \
        tm.tm_hour, tm.tm_min, tm.tm_sec);
}