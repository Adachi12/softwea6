#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<mysql/mysql.h>

#ifndef jog_h
#define jog_h

#define QUEUELIMIT 5
#define MSGSIZE 1024
#define BUFSIZE (MSGSIZE + 1)

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
USEDLOG_TABLE *usedlog_select(int id, int *n);
int usedlog_delete(int id);
void month_ago(char *buf);
void print_ult(USEDLOG_TABLE *ult, int n);

// SAVED_ROUTE_TABLE access
int saved_route_update(int user_id, int route_id, char route_file[]);
int saved_route_insert(int user_id);
FILE *saved_route_select(int user_id, int route_id);

// CALORIE_TABLE random access
CALORIE_TABLE calorie_select();

//SAVED_ROUTE_TABLE
//SELECT
SAVED_ROUTE_TABLE srt_str2tab_select(char *srt_cast);
int srt_tab2str_select(char *srt_buf, SAVED_ROUTE_TABLE srt);
//UPDATE
SAVED_ROUTE_TABLE srt_str2tab_update(char *srt_cast);

//CALORIE_TABLE
//SELECT
int ct_tab2str_select(char *ct_buf, CALORIE_TABLE ct);
//UPDATE

//USEDLOG_TABLE
//SELECT
USEDLOG_TABLE ult_str2tab_select(char *ult_cast);
FILE *ult_tab2str_select(char *ult_buf, USEDLOG_TABLE *ult, int n);
//INSERT
USEDLOG_TABLE ult_str2tab_insert(char *ult_cast);

//USER_TABLE
//SELECT
USER_TABLE ut_str2tab_select(char *ut_cast);
int ut_tab2str_select(char *ut_buf, USER_TABLE ut);
//UPDATE
USER_TABLE ut_str2tab_update(char *ut_cast);
//INSERT
USER_TABLE ut_str2tab_insert(char *ut_cast);

#endif