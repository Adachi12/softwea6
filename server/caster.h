#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<mysql/mysql.h>

//SAVED_ROUTE_TABLE
//SELECT
SAVED_ROUTE_TABLE srt_str2tab_select(char * srt_cast);
int srt_tab2str_select(char * srt_buf, SAVED_ROUTE_TABLE srt);
//UPDATE
SAVED_ROUTE_TABLE srt_str2tab_update(char *srt_cast);

//CALORIE_TABLE
//SELECT
CALORIE_TABLE ct_str2tab_select(char * ct_cast);
int ct_tab2str_select(char * ct_buf, CALORIE_TABLE ct);
//UPDATE

//USEDLOG_TABLE
//SELECT
USEDLOG_TABLE ult_str2tab_select(char * ult_cast);
int ult_tab2str_select(char * ult_buf, USEDLOG_TABLE ult);
//INSERT
USEDLOG_TABLE ult_str2tab_insert(char * ult_cast);

//USER_TABLE
//SELECT
USER_TABLE ut_str2tab_select(char * ut_cast);
int ut_tab2str_select(char * ut_buf, USER_TABLE ut);
//UPDATE
USER_TABLE ut_str2tab_update(char * ut_cast);
//INSERT
USER_TABLE ut_str2tab_insert(char * ut_cast);
