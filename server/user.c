#include "jogging.h"

USER_TABLE user_select(int id) {
    MYSQL *conn     = NULL;
    MYSQL_RES *resp = NULL;
    MYSQL_ROW row;
    char sql_str[511];
    char *sql_serv  = "localhost";
    char *user      = "root";
    char *passwd    = "mariadb";
    char *db_name   = "jogging";

    USER_TABLE res_data;

    memset( &sql_str[0] , 0x00 , sizeof(sql_str) );

    //SQL発行
    snprintf( &sql_str[0] , sizeof(sql_str)-1 ,\
    "SELECT weight, height, age, sex, birth, goal_weight, goal_term\
    from USER_TABLE where id = '%08d'", id);

    // mysql接続
    conn = mysql_init(NULL);
    if( !mysql_real_connect(conn,sql_serv,user,passwd,db_name,0,NULL,0) ){
        // error
        printf("error!");
        res_data.error = 1;
        return res_data;
    }

    // クエリ実行
    if( mysql_query( conn , &sql_str[0] ) ){
        // error
        mysql_close(conn);
        res_data.error = 1;
        return res_data;
    }

    // レスポンス
    resp = mysql_use_result(conn);
    while((row = mysql_fetch_row(resp)) != NULL ){
        res_data.id = id;
        res_data.weight = atof(row[0]);
        res_data.height = atof(row[1]);
        res_data.age = atoi(row[2]);
        res_data.sex = atoi(row[3]);
        sprintf(res_data.birth, "%s", row[4]); 
        res_data.goal_weight = atof(row[5]);
        sprintf(res_data.goal_term, "%s", row[6]);
    }

    // 後片づけ
    mysql_free_result(resp);
    mysql_close(conn);

    // 誕生日
    int birthyear, birthmonth, birthday;
    sscanf(res_data.birth, "%d-%d-%d", &birthyear, &birthmonth, &birthday);

    // 今日
    int localyear, localmonth, localday;
    time_t timer;
    struct tm *local;

    timer = time(NULL);
    local = localtime(&timer);
    localyear = local->tm_year + 1900;
    localmonth = local->tm_mon + 1;
    localday = local->tm_mday;

    if( (localmonth < birthmonth)  || (localmonth == birthmonth && localday < birthday) ) {
        res_data.age = localyear - birthyear - 1;
        user_update(res_data);
    } else {
        res_data.age = localyear - birthyear;
        user_update(res_data);
    }
    
    return res_data;
}

//更新
int user_update(USER_TABLE ut){
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
        return 1;
    }

    // クエリ実行
    char id_buf[9];
    snprintf(id_buf, 9, "%08d", ut.id);
    snprintf( &sql_str[0] , sizeof(sql_str)-1 ,
        "UPDATE USER_TABLE SET \
        weight = %3.1f, \
        height = %3.1f, \
        age = %d, \
        goal_weight = %3.1f, \
        goal_term = '%s', \
        mail_address = '%s'\
        where id = '%s'", \
        ut.weight, ut.height, ut.age, ut.goal_weight, 
        ut.goal_term, ut.mail_address, id_buf);
    if( mysql_query( conn , &sql_str[0] ) ){
        // error
        mysql_close(conn);
        return 1;
    }
    
    // 後片づけ
    mysql_close(conn);
    return 0;
}

//追加
int user_insert(USER_TABLE ut) {
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
        return 1;
    }

    char id_buf[9];
    snprintf(id_buf, 9, "%08d", ut.id);
    sprintf(sql_str, 
        "INSERT INTO USER_TABLE \
         VALUES(%d, '%08d', '%s', '%s', '%s', %lf, %lf, %d, %d, '%s', %lf, '%s', '%s')",
        ut.id, ut.login_name, ut.pass, ut.name, ut.weight, ut.height, 
        ut.age, ut.sex, ut.birth, ut.goal_weight, ut.goal_term, ut.mail_address);
    if( mysql_query( conn , &sql_str[0] ) ){
        // error
        mysql_close(conn);
        return 1;
    }
    //後片付け
    mysql_close(conn);

    saved_route_insert(ut.id);

    return 0;
}