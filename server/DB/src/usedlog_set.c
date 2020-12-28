//uselog_get.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
//void usedlog_update();
//書き換え不要

//追加
void usedlog_insert(int id, char date[10], char time[8], float distance, char jogtime[8], int calorie, char route[15], char sql_str[255]) {
   
   char id_buf[9];
   snprintf(id_buf, 9, "%08d", id);
   
   char distance_buf[7];
   snprintf(distance_buf, 7, "%4.2f", distance);
   
   char calorie_buf[5];
   snprintf(calorie_buf, 5, "%d", calorie);
      
   sprintf(sql_str, "INSERT INTO USEDLOG_TABLE VALUES('%s', '%s', '%s', %s, '%s', %s, '%s')"\
          , id_buf, date, time, distance_buf, jogtime, calorie_buf, route);
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
  usedlog_insert(5,"2020/12/31", "00:23:50", 1.02, "02:00:12", 342, "tyoukyou", &sql_str[0]);
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
