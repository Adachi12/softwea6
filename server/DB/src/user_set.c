//user_get.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
void user_update();
void user_insert();
int main(void){
   user_insert();
}

//更新
void user_update(){
  MYSQL *conn     = NULL;
  MYSQL_RES *resp = NULL;
  MYSQL_ROW row;
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
  snprintf( &sql_str[0] , sizeof(sql_str)-1 , "update USER_TABLE\
  set user_weight=315.8,user_height=127.7,goal_weight=35.7,goal_term='2020/76/93',mail_address='yamada_sphere@komaso.ku'\
  where user_id = '00000000'" );
  if( mysql_query( conn , &sql_str[0] ) ){
    // error
    mysql_close(conn);
    exit(-1);
  }

  // レスポンス
  resp = mysql_use_result(conn);
  while((row = mysql_fetch_row(resp)) != NULL ){
    printf( "%d : %s : %d\n" , atoi(row[0]) , row[1], atoi(row[2]));
  }

  // 後片づけ
  mysql_free_result(resp);
  mysql_close(conn);
}

//追加
void user_insert(){
  MYSQL *conn     = NULL;
  MYSQL_RES *resp = NULL;
  MYSQL_ROW row;
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
  snprintf( &sql_str[0] , sizeof(sql_str)-1 , "INSERT INTO USER_TABLE\
  VALUES('00000001','TokugawaIeyasu','Amaterasu','賭苦皮威愛遣酢',94.8,163.6,52,'牡',53.5,'1582/15/82',edobaku.ieyasu@edo.ed");
  if( mysql_query( conn , &sql_str[0] ) ){
    // error
    mysql_close(conn);
    exit(-1);
  }

  // レスポンス
  resp = mysql_use_result(conn);
  while((row = mysql_fetch_row(resp)) != NULL ){
    printf( "%d : %s : %d\n" , atoi(row[0]) , row[1], atoi(row[2]));
  }

  // 後片づけ
  mysql_free_result(resp);
  mysql_close(conn);

}