#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<mysql/mysql.h>
#include"DB/src/jogging.h"

//文字列を構造体にキャスト
CALORIE_TABLE ct_str2tab_select(char * ct_cast) {
    CALORIE_TABLE ct = {0, -1, "", -1};

    sscanf(ct_cast, "%s\n%d", &ct.food_name[0], &ct.food_calorie);
    
    return ct;
}

//構造体を文字列にキャスト
int ct_tab2str_select(char * ct_buf, CALORIE_TABLE ct) {
    sprintf(ct_buf, "%s\n%d", ct.food_name, ct.food_calorie);
    return 0;
}

SAVED_ROUTE_TABLE srt_str2tab_select(char * srt_cast) {
    SAVED_ROUTE_TABLE srt = {0, 0, "", "", "", "", ""};
    
    sscanf(srt_cast, "%d\n%s\n%s", &srt.id, &srt.saved_route1[0],&srt.saved_route2[0]);
    
    return srt;
}

int srt_tab2str_select(char * srt_buf, SAVED_ROUTE_TABLE srt) {
    sprintf(srt_buf, "%d\n%s\n%s", srt.id, srt.saved_route1, srt.saved_route2);
    return 0;
}

SAVED_ROUTE_TABLE srt_str2tab_update(char *srt_cast) {
    SAVED_ROUTE_TABLE srt = {0, 0, "", "", "", "", ""};
    
    sscanf(srt_cast, "%d\n%s\n%s", &srt.id, &srt.saved_route1[0],&srt.saved_route2[0]);
    
    return srt;
}

USEDLOG_TABLE ult_str2tab_select(char * ult_cast) {
    USEDLOG_TABLE ult = {0, 0, "2021-01-07/03:21:52", 2000, "24:21:59", 10000};
    
    sscanf(ult_cast,  "%s\n%d\n%s\n%d", &ult.jog_datetime[0], &ult.jog_distance, &ult.jog_time[0], &ult.burned_calorie);
    
    return ult;
}

int ult_tab2str_select(char * ult_buf, USEDLOG_TABLE ult) {
    sprintf(ult_buf, "%s\n%d\n%s\n%d", ult.jog_datetime, ult.jog_distance, ult.jog_time, ult.burned_calorie);
    return 0;
}
//
USEDLOG_TABLE ult_str2tab_insert(char * ult_cast) {
    USEDLOG_TABLE ult = {0, 0, "2021-01-07/03:21:52", 2000, "24:21:59", 10000};
    
    int head_buf;
    
    sscanf(ult_cast,  "%d\n%d\n%s\n%d\n%s\n%d", &head_buf, &ult.id, &ult.jog_datetime[0], &ult.jog_distance, &ult.jog_time[0], &ult.burned_calorie);
    
    return ult;
}

USER_TABLE ut_str2tab_select(char * ut_cast) {
    USER_TABLE ut = {0, 0, "loginname", "password", "name", 56.2, 181.1, 21, 1, "1999-12-31", 60.3, "2022-12-31", "mail-address@exaple.ex"};
    
    sscanf(ut_cast,  "%s\n%s\n%lf\n%lf\n%d\n%d\n%s\n%lf\n%s\n%s", &ut.login_name[0], &ut.name[0], &ut.weight, &ut.height, &ut.age, &ut.sex, &ut.birth[0], &ut.goal_weight, &ut.goal_term[0], &ut.mail_address);
    
    return ut;
}

int ut_tab2str_select(char * ut_buf, USER_TABLE ut) {
    sprintf(ut_buf, "%s\n%s\n%lf\n%lf\n%d\n%d\n%s\n%lf\n%s\n%s", ut.login_name, ut.name, ut.weight, ut.height, ut.age, ut.sex, ut.birth, ut.goal_weight, ut.goal_term, ut.mail_address);
    return 0;
}

USER_TABLE ut_str2tab_update(char * ut_cast) {
    USER_TABLE ut = {0, 0, "loginname", "password", "name", 56.2, 181.1, 21, 1, "1999-12-31", 60.3, "2022-12-31", "mail-address@exaple.ex"};
    
    int head_buf;
    
    sscanf(ut_cast,  "%s\n%d\n%s\n%s\n%s\n%lf\n%lf\n%d\n%d\n%s\n%lf\n%s\n%s", &head_buf, &ut.id, &ut.login_name[0], &ut.pass[0], &ut.name[0], &ut.weight, &ut.height, &ut.age, &ut.sex, &ut.birth[0], &ut.goal_weight, &ut.goal_term[0], &ut.mail_address);
    
    return ut;
}

USER_TABLE ut_str2tab_insert(char * ut_cast) {
    USER_TABLE ut = {0, 0, "loginname", "password", "name", 56.2, 181.1, 21, 1, "1999-12-31", 60.3, "2022-12-31", "mail-address@exaple.ex"};
    
    int head_buf;
    
    sscanf(ut_cast,  "%d\n%d\n%s\n%s\n%s\n%lf\n%lf\n%d\n%d\n%s\n%lf\n%s\n%s", &head_buf,  &ut.id, &ut.login_name[0], &ut.pass[0], &ut.name[0], &ut.weight, &ut.height, &ut.age, &ut.sex, &ut.birth[0], &ut.goal_weight, &ut.goal_term[0], &ut.mail_address);
    
    return ut;
}
