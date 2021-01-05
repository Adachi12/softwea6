#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<mysql/mysql.h>
#include"DB/src/jogging.h"
    
//snprintf(id_buf, 9, "%08d", ut.id);
/*    res_data.id = id;
        res_data.weight = atof(row[0]);
        res_data.height = atof(row[1]);
        res_data.age = atoi(row[2]);
        res_data.sex = atoi(row[3]);
        sprintf(res_data.birth, "%s", row[4]); 
        res_data.goal_weight = atof(row[5]);
        sprintf(res_data.goal_term, "%s", row[6]);
*/
int calorie_table_cast(char * ct_cast, CALORIE_TABLE ct) {
    
    snprintf(ct_cast, 255, "%s", ct.name);
    ct[256] = calorie;
    
    return ct_cast;
}

int usedlog_table_cast(char * ult_cast, USEDLOG_TABLE ult) {
    
    //snprintf(ult_cast, 46, "%s,%d,%s,%lf,%s,%d",ult.op, ult.user_id, ult.jog_datetime, ult.jog_distance, ult.jog_time, ult.burned_calorie);
    ult_cast[0] = アクセス内容;
    ult_cast[1] = ult.id;
    snprintf(ult_cast, 5, "%s", ult.jog_datetime);
    snprintf(ult_cast, 25, "%lf", ult.jog_distance);
    snprintf(ulr_cast, 33, "%s", ult.jog_time);
    ult_cast[42] = burned_calorie;
    
    return ult_cast;
}

int user_table_cast(char * ut_cast, USER_TABLE ut) {
    //char ut_cast[390];
    //snprintf(ut_cast, 390, "%s,%d,%s,%s,%s,%l,%lf,%d,%d,%s,%s,%lf,%s,%s",ut.op, ut.user_id, ut.login_name, ut.pass, ut.name, ut.weight, ut.height, ut.age, ut.sex, ut.birth, ut.goal_weight, ut.goal_term, ut.mail_address);
    snprintf()
    return ut_cast;
}

int saved_route_table_cast(SAVED_ROUTE_TABLE, ) {
}