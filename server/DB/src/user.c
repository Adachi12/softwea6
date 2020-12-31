//user_get.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
void user_update();

typedef struct {
    int id;
    char loginname[10];
    char pass[32];
    char name[96];
    float weight;
    float height;
    int age;
    int sex;
    char birth[11];
    float gweight;
    char term[11];
    char mail[30];
   } UT;

//更新
void user_update(UT ut){
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
  //snprintf( &sql_str[0] , sizeof(sql_str)-1 , "UPDATE USER_TABLE\
  //set user_weight=315.8,user_height=127.7,goal_weight=35.7,goal_term='2020/76/93',mail_address='yamada_sphere@komaso.ku'\
  //where user_id = '00000000'" );
    char id_buf[9];
    snprintf(id_buf, 9, "%08d", ut.id);
    snprintf( &sql_str[0] , sizeof(sql_str)-1 , "UPDATE USER_TABLE\
    SET weight = %3.1f, height = %3.1f, age = %d, goal_weight = %3.1f, goal_term = '%s', mail_address = '%s'\
    where id = '%s'" \
            , ut.weight, ut.height, ut.age, ut.gweight, ut.term, ut.mail, id_buf);
    if( mysql_query( conn , &sql_str[0] ) ){
        // error
        mysql_close(conn);
        exit(-1);
    }

  // 後片づけ
  mysql_free_result(resp);
  mysql_close(conn);
}
//追加
//void user_insert(int id, char loginname[10], char pass[32], char name[], float weight, float height, int age, char sex[], float gweight, char term[10], char mail[30], char sql_str[255]) {
void user_insert(UT ut, char sql_str[255]) {
   
   char id_buf[9];
   snprintf(id_buf, 9, "%08d", ut.id);
   
   char weight_buf[6];
   snprintf(weight_buf, 6, "%3.1f", ut.weight);
   
   char height_buf[6];
   snprintf(height_buf, 6, "%3.1f", ut.height);
   
   char age_buf[4];
   snprintf(age_buf, 4, "%d", ut.age);
    
    char sex_buf[2];
    snprintf(sex_buf, 2, "%d", ut.sex);
   
   char gweight_buf[6];
   snprintf(gweight_buf, 6, "%3.1f", ut.gweight);
   
   sprintf(sql_str, "INSERT INTO USER_TABLE VALUES('%s', '%s', '%s', '%s', %s, %s, %s, %s, '%s', %s, '%s', '%s')"\
          , id_buf, ut.loginname, ut.pass, ut.name, weight_buf, height_buf, age_buf, sex_buf, ut.birth, gweight_buf, ut.term, ut.mail);
}

//追加
int main(){
    // クエリ実行
    //UT ut = {3, "MJ", "makeinu", "マケイヌ・ジャクサン", 64.0, 168.7, 45, 1, "2009-06-25", 45.0, "2021/04/01", "goodloser@goodluck.hg"};
    UT ut = {3, "MJ", "makeinu", "マケイヌ・ジャクサン", 64.0, 168.7, 45, 1, "2009-06-25", 45.0, "2021/12/31", "goodloser@goodluck.hg"};
    //user_insert(ut, sql_str);
    user_update(ut);
}
