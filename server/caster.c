#include"jogging.h"

//構造体を文字列にキャスト
int ct_tab2str_select(char *ct_buf, CALORIE_TABLE ct) {
    sprintf(
        ct_buf, 
        "%s\n%d", 
        ct.food_name, ct.food_calorie
    );
    return 0;
}

SAVED_ROUTE_TABLE srt_str2tab_select(char *srt_cast) {
    SAVED_ROUTE_TABLE srt = {0, 0, "", "", "", "", ""};
    
    sscanf(
        srt_cast, 
        "%d\n%s\n%s", 
        &srt.id, 
        &srt.saved_route1[0],
        &srt.saved_route2[0]
    );
    
    return srt;
}

int srt_tab2str_select(char *srt_buf, SAVED_ROUTE_TABLE srt) {
    sprintf(
        srt_buf, 
        "%d\n%s\n%s", 
        srt.id, 
        srt.saved_route1, 
        srt.saved_route2
    );
    return 0;
}

SAVED_ROUTE_TABLE srt_str2tab_update(char *srt_cast) {
    SAVED_ROUTE_TABLE srt = {0, 0, "", "", "", "", ""};
    
    sscanf(
        srt_cast, 
        "%d\n%s\n%s", 
        &srt.id, 
        &srt.saved_route1[0],
        &srt.saved_route2[0]
    );
    
    return srt;
}

USEDLOG_TABLE ult_str2tab_select(char *ult_cast) {
    USEDLOG_TABLE ult = {0, 0, "2021-01-07/03:21:52", 2000, "24:21:59", 10000};
    
    sscanf(
        ult_cast, 
        "%s\n%d\n%s\n%d", 
        &ult.jog_datetime[0], 
        &ult.jog_distance, 
        &ult.jog_time[0], 
        &ult.burned_calorie
    );
    
    return ult;
}

FILE *ult_tab2str_select(char *ult_buf, USEDLOG_TABLE *ult, int n) {
    FILE *fp;
    int i;
    char file_name[] = "XXXXXX";
    mkstemp(file_name);

    fp = fopen(file_name, "w");

    for (i = 0; i < n; i++) {
        fprintf(
            fp,
            "[%s\n%lf\n%s\n%d\n]\n", 
            ult[i].jog_datetime, 
            ult[i].jog_distance, 
            ult[i].jog_time, 
            ult[i].burned_calorie
        );
    }
    fclose(fp);
    remove(file_name);
    
    return 0;
}

USEDLOG_TABLE ult_str2tab_insert(char *ult_cast) {
    USEDLOG_TABLE ult = {0, 0, "2021-01-07/03:21:52", 2000, "24:21:59", 10000};

    int head_buf;

    sscanf(
        ult_cast, 
        "%d\n%d\n%s\n%d\n%s\n%d", 
        &head_buf, &ult.id, &ult.jog_datetime[0], 
        &ult.jog_distance, &ult.jog_time[0], &ult.burned_calorie
    );

    return ult;
}

USER_TABLE ut_str2tab_select(char *ut_cast) {
    USER_TABLE ut = 
        {0, 0, "password", "name", 56.2, 181.1, 21, 1, 
        "1999-12-31", 60.3, "2022-12-31", "mail-address@exaple.ex"};

    sscanf(
        ut_cast, 
        "%d\n%s\n%s\n%lf\n%lf\n%d\n%d\n%s\n%lf\n%s\n%s", 
        &ut.id,  &ut.pass[0], &ut.name[0], 
        &ut.weight, &ut.height, &ut.age, &ut.sex, &ut.birth[0], 
        &ut.goal_weight, &ut.goal_term[0], &ut.mail_address
    );

    return ut;
}

int ut_tab2str_select(char *ut_buf, USER_TABLE ut) {
    sprintf(
        ut_buf, 
        "%d\n%s\n%s\n%lf\n%lf\n%d\n%d\n%s\n%lf\n%s\n%s", 
        ut.id, ut.pass, ut.name, ut.weight,
        ut.height, ut.age, ut.sex, ut.birth, ut.goal_weight,
        ut.goal_term, ut.mail_address
    );
    return 0;
}

USER_TABLE ut_str2tab_update(char *ut_cast) {
    USER_TABLE ut = 
        {0, 0, "password", "name", 56.2, 181.1, 21, 1, 
        "1999-12-31", 60.3, "2022-12-31", "mail-address@exaple.ex"};

    int head_buf;

    sscanf(
        ut_cast, 
        "%s\n%d\n%s\n%s\n%lf\n%lf\n%d\n%d\n%s\n%lf\n%s\n%s", 
        &head_buf, &ut.id, &ut.pass[0], &ut.name[0], 
        &ut.weight, &ut.height, &ut.age, &ut.sex, &ut.birth[0], 
        &ut.goal_weight, &ut.goal_term[0], &ut.mail_address
    );

    return ut;
}

USER_TABLE ut_str2tab_insert(char *ut_cast) {
    USER_TABLE ut = 
        {0, 0, "password", "name", 56.2, 181.1, 21, 1, 
        "1999-12-31", 60.3, "2022-12-31", "mail-address@exaple.ex"};

    int head_buf;

    sscanf(
        ut_cast, 
        "%d\n%d\n%s\n%s\n%lf\n%lf\n%d\n%d\n%s\n%lf\n%s\n%s", 
        &head_buf,  &ut.id, &ut.pass[0], &ut.name[0], 
        &ut.weight, &ut.height, &ut.age, &ut.sex, &ut.birth[0], 
        &ut.goal_weight, &ut.goal_term[0], &ut.mail_address
    );

    return ut;
}
