//uselog_get.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mysql/mysql.h>
//void usedlog_update();
//書き換え不要

typedef struct {
   int id;
   char datetime[20];
   float distance;
   char jogtime[9];
   int calorie;
} ULT;

// 引数のデータをデータベースへinsert
int usedlog_insert(ULT ult);
// 引数のidに該当するデータを取得
void usedlog_select(int id);
// mallocしたデータを出力
void print_ult(ULT *ult, int n);
// 1ヶ月以上前の日付を文字列で取得
void month_ago();
// 1ヶ月以上前のデータを全て削除
int usedlog_delete(int id);

int main() {
    // usedlog_select(0);
    // ULT insert_data = {1, "2020-02-02 20:30:20", 222, "00:20:20", 222};
    // printf("%d\n", usedlog_insert(insert_data));

    usedlog_delete(0);
    usedlog_select(0);
}
   
//追加
int usedlog_insert(ULT ult){
    MYSQL *conn     = NULL;
    char sql_str[255];
    char *sql_serv  = "localhost";
    char *user      = "root";
    char *passwd    = "mariadb";
    char *db_name   = "jogging";

    // SQL発行
    // cast
    char id_buf[9];
    snprintf(id_buf, 9, "%08d", ult.id);
    char distance_buf[7];
    snprintf(distance_buf, 7, "%4.1f", ult.distance);
    char calorie_buf[5];
    snprintf(calorie_buf, 5, "%d", ult.calorie);
    
    // write to buffer
    sprintf(sql_str, "INSERT INTO USEDLOG_TABLE VALUES('%8s', '%19s', %s, '%s', %s)", \
            id_buf, ult.datetime, distance_buf, ult.jogtime, calorie_buf);
    
    // mysql接続
    conn = mysql_init(NULL);
    if( !mysql_real_connect(conn,sql_serv,user,passwd,db_name,0,NULL,0) ){
        // error
        return 1;""
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

void usedlog_select(int id) {
    MYSQL *conn     = NULL;
    MYSQL_RES *resp = NULL;
    MYSQL_ROW row;
    char sql_str[511];
    char *sql_serv  = "localhost";
    char *user      = "root";
    char *passwd    = "mariadb";
    char *db_name   = "jogging";

    // 該当データ数
    int n = 0, i;

    // 返信用のデータ
    ULT *res_data;

    memset( &sql_str[0] , 0x00 , sizeof(sql_str) );

    // 1ヶ月以前のデータ削除
    usedlog_delete(id);

    // SQL発行
    char id_buf[9];
    snprintf(id_buf, 9, "%08d", id);

    // mysql接続
    conn = mysql_init(NULL);
    if( !mysql_real_connect(conn,sql_serv,user,passwd,db_name,0,NULL,0) ){
        // error
        exit(-1);
    }

    // count
    sprintf(sql_str, "SELECT count(*) FROM USEDLOG_TABLE where id='%s'", id_buf);
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
        n = atoi(row[0]);
    }
    mysql_free_result(resp);

    res_data = (ULT *)malloc(sizeof(ULT) * n);

    // アクセスSQL文
    sprintf(sql_str, "SELECT * FROM USEDLOG_TABLE where id='%s'", id_buf);

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
        sprintf(res_data[i].datetime, "%s", row[1]);
        res_data[i].distance = atof(row[2]);
        sprintf(res_data[i].jogtime, "%s", row[3]);
        res_data[i].calorie = atoi(row[4]);
        i++;
    }
    mysql_free_result(resp);

    print_ult(res_data, n);
}

int usedlog_delete(int id) {
    MYSQL *conn     = NULL;
    char sql_str[255];
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

void print_ult(ULT *ult, int n) {
    printf("id : %d\n", ult[0].id);

    int i = 0;
    for(i = 0; i < n; i++) {
        printf("    datetime : %s\n", ult[i].datetime);
        printf("    distance : %1.2f\n", ult[i].distance);
        printf("    jogtime  : %8s\n", ult[i].jogtime);
        printf("    calorie  : %d\n", ult[i].calorie);
        printf("\n");
    }
}