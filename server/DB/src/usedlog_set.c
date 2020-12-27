//uselog_get.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
void usedlog_update();
void usedlog_insert();
int main(void){
   usedlog_insert();
}
//書き換え不要

//追加
void usedlog_insert(){
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
  snprintf( &sql_str[0] , sizeof(sql_str)-1 , "insert into USEDLOG_TABLE values('00000001','2020/13/32','27:75:89',400,'84:32:98',1000000,'yes')" );
  if( mysql_query( conn , &sql_str[0] ) ){
    // error
    mysql_close(conn);
    exit(-1);
  }

  // 後片づけ
  mysql_close(conn);
}