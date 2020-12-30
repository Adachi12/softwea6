//uselog_get.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
//void usedlog_update();
//書き換え不要

// 引数のデータをデータベースへinsert
void usedlog_insert(UL ul);
// 引数のidに該当するデータを取得
UL usedlog_insert(int id);

typedef struct {
   int id;
   char date[10];
   char time[8];
   float distance;
   char jogtime[8];
   int calorie;
   char route[15];
} UL;

int main() {

}
   
//追加
//void usedlog_insert(int id, char date[10], char time[8], float distance, char jogtime[8], int calorie, char route[15], char sql_str[255]) {
void usedlog_insert(UL ul){
    MYSQL *conn     = NULL;
    char sql_str[255];
    char *sql_serv  = "localhost";
    char *user      = "root";
    char *passwd    = "mariadb";
    char *db_name   = "jogging";

    // SQL発行
    // cast
    char id_buf[9];
    snprintf(id_buf, 9, "%08d", ul.id);
    char distance_buf[7];
    snprintf(distance_buf, 7, "%4.2f", ul.distance);
    char calorie_buf[5];
    snprintf(calorie_buf, 5, "%d", ul.calorie);
    
    // write to buffer
    sprintf(sql_str, "INSERT INTO USEDLOG_TABLE VALUES('%s', '%s', '%s', %s, '%s', %s, '%s')"\
            , id_buf, ul.date, ul.time, distance_buf, ul.jogtime, calorie_buf, ul.route);
    
    // mysql接続
    conn = mysql_init(NULL);
    if( !mysql_real_connect(conn,sql_serv,user,passwd,db_name,0,NULL,0) ){
        // error
        exit(-1);
    }

    // クエリ実行
    UL ul = {6, "2020/12/29","20:42:43", 4.5, "01:23:41", 320, "testtoute"};
    if( mysql_query( conn , &sql_str[0] ) ){
        // error
        printf("error!\n");
        mysql_close(conn);
        exit(-1);
    }
    
    mysql_close(conn);
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

    // 返信用のデータ
    UL res_data;

    memset( &sql_str[0] , 0x00 , sizeof(sql_str) );

    // SQL発行
    char id_buf[9];
    snprintf(id_buf, 9, "%08d", id);
    sprintf(sql_str, "SELECT * FROM USEDLOG_TABLE where user_id=%s", id_buf);

    // mysql接続
    conn = mysql_init(NULL);
    if( !mysql_real_connect(conn,sql_serv,user,passwd,db_name,0,NULL,0) ){
        // error
        exit(-1);
    }

    // 実行
    if( mysql_query( conn , &sql_str[0] ) ){
        // error
        printf("error!\n");
        mysql_close(conn);
        exit(-1);
    }
   
   //レスポンス
   resp = mysql_use_result(conn);
   while((row = mysql_fetch_row(resp)) != NULL ){
      sprintf(res_data.date, "%s", row[3]);
      sprintf(res_data.time, "%s", row[3]);
      sprintf(res_data.distance, "%s", row[3]);
      sprintf(res_data.jogtime, "%s", row[3]);
   }
      
}

//DELETE文の発行
void usedlog_delete(int id, char date, char time) {
    MYSQL *conn     = NULL;
    MYSQL_RES *resp = NULL;
    MYSQL_ROW row;
    char sql_str[511];
    char *sql_serv  = "localhost";
    char *user      = "root";
    char *passwd    = "mariadb";
    char *db_name   = "jogging";
    
    memset( &sql_str[0] , 0x00 , sizeof(sql_str) );

    // SQL発行
    char id_buf[9];
    snprintf(id_buf, 9, "%08d", id);
    sprintf(sql_str, "DELETE FROM USEDLOG_TABLE where user_id=%s", id_buf);

    // mysql接続
    conn = mysql_init(NULL);
    if( !mysql_real_connect(conn,sql_serv,user,passwd,db_name,0,NULL,0) ){
        // error
        exit(-1);
    }
