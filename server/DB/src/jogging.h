#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<mysql/mysql.h>

#ifndef jog_h
#define jog_h

// 型定義
typedef struct {
    int     error;
    int     id;
    char    saved_route1[31];
    char    saved_route2[31];
    char    saved_route3[31];
    char    saved_route4[31];
    char    saved_route5[31];
} SAVED_ROUTE_TABLE;

typedef struct {
    int     error;
    int     food;
    char    food_name[256];
    int     food_calorie;
} CALORIE_TABLE;

typedef struct {
    int     error;
    int     id;
    char    jog_datetime[20];
    double  jog_distance;
    char    jog_time[9];
    int     burned_calorie;
} USEDLOG_TABLE;

typedef struct {
    int     error;
    int     id;
    char    login_name[11];
    char    pass[33];
    char    name[256];
    double  weight;
    double  height;
    int     age;
    int     sex;
    char    birth[11];
    double  goal_weight;
    char    goal_term[11];
    char    mail_address[30];
} USER_TABLE;

// 関数宣言

// USER_TABLE access
int user_insert(USER_TABLE ut);
int user_update(USER_TABLE ut);
USER_TABLE user_select(int id);

// USEDLOG_TABLE access
int usedlog_insert(USEDLOG_TABLE ult);
int usedlog_update(USEDLOG_TABLE ult);
int usedlog_delete(int id);
void month_ago(char *buf);
void print_ult(USEDLOG_TABLE *ult, int n);
USEDLOG_TABLE *usedlog_select(int id, int *n);

// SAVED_ROUTE_TABLE access
int saved_route_update(int user_id, int route_id, char *route_file[])
SAVED_ROUTE_TABLE saved_route_select(int  id);

// CALORIE_TABLE random access
CALORIE_TABLE calorie_select();


// db_access
MYSQL_RES db_access(char *sql_str[511]);

#endif