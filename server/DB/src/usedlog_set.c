//uselog_get.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
//void usedlog_update();
//書き換え不要

typedef struct {
   int id;
   char date[10];
   char time[8];
   float distance;
   char jogtime[8];
   int calorie;
   char route[15];
} UL;
   
//追加
//void usedlog_insert(int id, char date[10], char time[8], float distance, char jogtime[8], int calorie, char route[15], char sql_str[255]) {
void usedlog_insert(UL ul, char sql_str[255]){
   
   char id_buf[9];
   snprintf(id_buf, 9, "%08d", ul.id);
   
   char distance_buf[7];
   snprintf(distance_buf, 7, "%4.2f", ul.distance);
   
   char calorie_buf[5];
   snprintf(calorie_buf, 5, "%d", ul.calorie);
      
   sprintf(sql_str, "INSERT INTO USEDLOG_TABLE VALUES('%s', '%s', '%s', %s, '%s', %s, '%s')"\
          , id_buf, ul.date, ul.time, distance_buf, ul.jogtime, calorie_buf, ul.route);
}

int main(){
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
   UL ul = {6, "2020/12/29","20:42:43", 4.5, "01:23:41", 320, "testtoute"};
   usedlog_insert(ul, sql_str);
   if( mysql_query( conn , &sql_str[0] ) ){
      // error
      printf("error!");
      printf("%s\n", sql_str);
      mysql_close(conn);
      exit(-1);
   }

  // 後片づけ
  mysql_close(conn);
}
