//user_set.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

typedef struct {
   int id;
   char logonname[10];
   char pass[32];
   char name[96];      
   float weight;
   float height;
   int age;
   char sex[8];
   float gweight;
   char term[10];
   char mail[30];
} UT;


int main(void){
   user_select(1);
}

void user_select(int id){
  MYSQL *conn     = NULL;
  MYSQL_RES *resp = NULL;
  MYSQL_ROW row;
  char sql_str[255];
  char *sql_serv  = "localhost";
  char *user      = "root";
  char *passwd    = "mariadb";
  char *db_name   = "jogging";
   
   UT res_data;

  memset( &sql_str[0] , 0x00 , sizeof(sql_str) );
   
   //SQL発行
   char id_buf[9];
   snprintf(id_buf, 9, "%08d", id);
   snprintf( &sql_str[0] , sizeof(sql_str)-1 , "SELECT user_weight, user_height, user_age, user_sex, goal_weight, goal_term,\
  from USER_TABLE\
  where id = %s", id_buf );

  // mysql接続
  conn = mysql_init(NULL);
  if( !mysql_real_connect(conn,sql_serv,user,passwd,db_name,0,NULL,0) ){
    // error
    exit(-1);
  }

  // クエリ実行
  if( mysql_query( conn , &sql_str[0] ) ){
    // error
    mysql_close(conn);
    exit(-1);
  }

  // レスポンス
   resp = mysql_use_result(conn);
   //printf( "ユーザID : ログイン名 : パスワード\n");
   while((row = mysql_fetch_row(resp)) != NULL ){
      //printf( "%d : %s : %s\n" , atoi(row[0]) , row[1], row[2]);
      res_data.id = id;
      
      sprintf()
      printf("ユーザID：%s", row[0]);
      printf("体重：%f", row[4]);
      printf("身長：%f", row[5]);
      printf("年齢：%d", row[6]);
      printf("性別：%s", row[7]);
      printf("目標体重：%f", row[8]);
      printf("目標期間：%s", atoi(row[9]));
   }

  // 後片づけ
  mysql_free_result(resp);
  mysql_close(conn);
  return 0;
}