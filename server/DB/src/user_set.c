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
  mysql_close(conn);
}

//追加
void user_insert(UT ut) {
    MYSQL *conn     = NULL;
    char sql_str[511];
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

    char id_buf[9];
    snprintf(id_buf, 9, "%08d", ut.id);
    sprintf(sql_str, "INSERT INTO USER_TABLE VALUES('%08d', '%s', '%s', '%s', %lf, %lf, %d, %d, '%s', %lf, '%s', '%s')"\
          , ut.id, ut.loginname, ut.pass, ut.name, ut.weight, ut.height, ut.age, ut.sex, ut.birth, ut.gweight, ut.term, ut.mail);
    if( mysql_query( conn , &sql_str[0] ) ){
        // error
        mysql_close(conn);
        exit(-1);
    }
    //後片付け
    mysql_close(conn);
}

//追加:テスト用
int main(){
    // クエリ実行
    //UT ut = {3, "MJ", "makeinu", "マケイヌ・ジャクサン", 64.0, 168.7, 45, 1, "2009-06-25", 45.0, "2021/04/01", "goodloser@goodluck.hg"};
    UT ut = {3, "MJ", "makeinu", "マケイヌ・ジャクサン", 64.0, 168.7, 45, 1, "2009-06-25", 45.0, "2025/12/31", "goodloser@goodluck.hg"};
    //user_insert(ut, sql_str);
    user_update(ut);
}
