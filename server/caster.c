#include"jogging.h"

//構造体を文字列にキャスト
int ct_tab2str_select(char *ct_buf, CALORIE_TABLE ct) {
    sprintf(
        ct_buf,
        "%s\n%d\n",
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
        "%d\n%s\n%s\n",
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
        "%s\n%lf\n%s\n%d",
        &ult.jog_datetime[0],
        &ult.jog_distance,
        &ult.jog_time[0],
        &ult.burned_calorie
    );

    return ult;
}

int ult_tab2str_select(char *ult_buf, USEDLOG_TABLE *ult, int n) {
    int i;

    for (i = 0; i < n; i++) {
        sprintf(
            ult_buf,
            "[%20s\n%2.2lf\n%8s\n%4d\n]\n",
            ult[i].jog_datetime,
            ult[i].jog_distance,
            ult[i].jog_time,
            ult[i].burned_calorie
        );
    }

    printf("str : %s\n", ult_buf);

    return 0;
}

USEDLOG_TABLE ult_str2tab_insert(char *ult_cast) {
    char header;
    USEDLOG_TABLE ult = {0, 0, "2021-01-07/03:21:52", 2000, "24:21:59", 10000};

    int head_buf;

    sscanf(
        ult_cast,
        "%c\n%d\n%d\n%s\n%le\n%s\n%d\n",
        &header, &head_buf, &ult.id, &ult.jog_datetime[0],
        &ult.jog_distance, &ult.jog_time[0], &ult.burned_calorie
    );

    return ult;
}

USER_TABLE ut_str2tab_select(char *ut_cast) {
    char header;
    USER_TABLE ut =
        {0, 0, "password", "name", 56.2, 181.1, 21, 1,
        "1999-12-31", 60.3, "2022-12-31", "mail-address@exaple.ex"};

    sscanf(
        ut_cast,
        "%c\n%d\n%s\n%s\n%lf\n%lf\n%d\n%d\n%s\n%lf\n%s\n%30s\n",
        &header, &ut.id,  &ut.pass[0], &ut.name[0],
        &ut.weight, &ut.height, &ut.age, &ut.sex, &ut.birth[0],
        &ut.goal_weight, &ut.goal_term[0], &ut.mail_address[0]
    );

    return ut;
}

int ut_tab2str_select(char *ut_buf, USER_TABLE ut) {
    sprintf(
        ut_buf,
        "%d\n%s\n%s\n%lf\n%lf\n%d\n%d\n%s\n%lf\n%s\n%s\n",
        ut.id, ut.pass, ut.name, ut.weight,
        ut.height, ut.age, ut.sex, ut.birth, ut.goal_weight,
        ut.goal_term, ut.mail_address
    );
    printf("ut_buf : %s\n", ut_buf);
    return 0;
}

USER_TABLE ut_str2tab_update(char *ut_cast) {
    unsigned char header;
    USER_TABLE ut =
        {0, 0, "password", "name", 56.2, 181.1, 21, 1,
        "1999-12-31", 60.3, "2022-12-31", "mail-address@exaple.ex"};

    sscanf(
        ut_cast,
        "%c\n%8d\n%[^\n]\n%s\n%lf\n%lf\n%d\n%d\n%s\n%lf\n%s\n%30s\n",
        &header, &ut.id, &ut.pass[0], &ut.name[0],
        &ut.weight, &ut.height, &ut.age, &ut.sex, &ut.birth[0],
        &ut.goal_weight, &ut.goal_term[0], &ut.mail_address[0]
    );

    printf("user_id = %d\npass = %s\n", ut.id, ut.pass);

    return ut;
}

USER_TABLE ut_str2tab_insert(char *ut_cast) {
    unsigned char header;
    USER_TABLE ut =
        {0, 0, "password", "name", 56.2, 181.1, 21, 1,
        "1999-12-31", 60.3, "2022-12-31", "mail-address@exaple.ex"};

    sscanf(
        ut_cast,
        "%c\n%[^\n]\n%s\n%lf\n%lf\n%d\n%d\n%s\n%lf\n%s\n%30s\n",
        &header, &ut.pass[0], &ut.name[0],
        &ut.weight, &ut.height, &ut.age, &ut.sex, &ut.birth[0],
        &ut.goal_weight, &ut.goal_term[0], &ut.mail_address[0]
    );

    return ut;
}