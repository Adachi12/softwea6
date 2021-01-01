//uselog_get.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include <mysql/mysql.h>
#include "jogging.h"
//書き換え不要

/*
int main() {
    USEDLOG_TABLE insert_data = {1, "2020-02-02 20:30:20", 222, "00:20:20", 222};
    usedlog_delete(1);
    usedlog_insert(insert_data);
    usedlog_select(1);
    usedlog_delete(1);
}
*/
    
//追加
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

    // レスポンスのループインデックス
    int i;

    // 返信用のデータ
    USEDLOG_TABLE *res_data;

    memset( &sql_str[0] , 0x00 , sizeof(sql_str) );

    // 1ヶ月以前のデータ削除
    usedlog_delete(id);

    // mysql接続
    conn = mysql_init(NULL);
    if( !mysql_real_connect(conn,sql_serv,user,passwd,db_name,0,NULL,0) ){
        // error
        exit(-1);
    }

    // count
    sprintf(sql_str, "SELECT count(*) FROM USEDLOG_TABLE where id='%08d'", id);
    // 実行
    if( mysql_query( conn , &sql_str[0] ) ){
        // error
        printf("error!\n%s\n", sql_str);
        mysql_close(conn);
        exit(-1);
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
        exit(-1);
    }

    // レスポンス
    resp = mysql_use_result(conn);
    i = 0;
    while((row = mysql_fetch_row(resp)) != NULL ) {
        res_data[i].id = atoi(row[0]);
        sprintf(res_data[i].jog_datetime, "%s", row[1]);
        res_data[i].jog_distance = atof(row[2]);
        sprintf(res_data[i].jog_time, "%s", row[3]);
        res_data[i].burned_calorie = atoi(row[4]);
        i++;
    }
    mysql_free_result(resp);

    //print_ult(res_data, n);
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
    // cast
    char id_buf[9];
    snprintf(id_buf, 9, "%08d", id);

    char month_ago_buf[20];
    month_ago(month_ago_buf);
    
    // write to buffer
    sprintf(sql_str, "DELETE from USEDLOG_TABLE \
        where id ='%s' AND jog_datetime <= '%s'", id_buf, &month_ago_buf[0]);
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
        tm.tm_mon = 12;
    } else {
        tm.tm_mon--;
    }

    // 求めた日付をもとに文字列を生成
    snprintf(buf, 20, "%04d/%02d/%02d %02d:%02d:%02d", \
        tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, \
        tm.tm_hour, tm.tm_min, tm.tm_sec);
}

void print_ult(USEDLOG_TABLE *ult, int n) {
    printf("id : %d\n", ult[0].id);

    int i = 0;
    for(i = 0; i < n; i++) {
        printf("    datetime : %s\n", ult[i].jog_datetime);
        printf("    distance : %1.2f\n", ult[i].jog_distance);
        printf("    jogtime  : %8s\n", ult[i].jog_time);
        printf("    calorie  : %d\n", ult[i].burned_calorie);
        printf("\n");
    }
}
