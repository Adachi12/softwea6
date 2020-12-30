//user_set.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

typedef struct {
    int id;
    char loginname[10];
    char pass[32];
    char name[96];
    double weight;
    double height;
    int age;
    int sex;
    char birth[11];
    double gweight;
    char term[11];
    char mail[30];
} UT;


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
    snprintf( &sql_str[0] , sizeof(sql_str)-1 ,\
    "SELECT weight, height, age, sex, birth, goal_weight, goal_term\
    from USER_TABLE where 'id' = %s", id_buf );

    // mysql接続
    conn = mysql_init(NULL);
    if( !mysql_real_connect(conn,sql_serv,user,passwd,db_name,0,NULL,0) ){
        // error
        printf("error!");
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
        res_data.weight = atof(row[0]);
        res_data.height = atof(row[1]);
        res_data.age = atoi(row[2]);
        res_data.sex = atoi(row[3]);
        sprintf(res_data.birth, "%s", row[4]); 
        res_data.gweight = atof(row[5]);
        sprintf(res_data.term, "%s", row[6]);
    }

    // 後片づけ
    mysql_free_result(resp);
    mysql_close(conn);

    printf("ユーザID：%d\n", res_data.id);
    printf("体重：%f\n", res_data.weight);
    printf("身長：%f\n", res_data.height);
    printf("年齢：%d\n", res_data.age);
    printf("性別：%d\n", res_data.sex);
    printf("生年月日：%s\n", res_data.birth);
    printf("目標体重：%f\n", res_data.gweight);
    printf("目標期間：%s\n", res_data.term);
    
}


int main(void){
    user_select(0);
}
