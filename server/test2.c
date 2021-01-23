#include"jogging.h"

char head_buf;
void main() {
    CALORIE_TABLE ct = {0, 0, "らぁめん", 600};
    /*
    char ct_cast[] = "ラーメン\n50";
    ct = ct_str2tab_select(ct_cast);
    */
    char ct_buf[BUFSIZE];
    ct_tab2str_select(&ct_buf[0], ct);

    //printf("CALORIE_TABLE_SELECT:%s, %d\n", ct.food_name, ct.food_calorie);
    printf("%s\n", ct_buf);
    
    SAVED_ROUTE_TABLE srt = {0, 0, "", "", "", "", ""};
    /*
    char srt_cast[] = "0000010\nroute1\nroute2";
    srt = srt_str2tab_select(srt_cast);
    */
    char srt_buf[BUFSIZE];
    srt_tab2str_select(&srt_buf[0], srt);
    printf("SAVED_ROUTE_TABLE:\nユーザID：%d\nルート1%s\nルート2%s\n", srt.id, srt.saved_route1, srt.saved_route2);
    printf("%s\n", srt_buf);
    
    USEDLOG_TABLE ult = {0, 0, "", 0, "", 0};
    /* select用
    char ult_cast[] = "2021-01-07/03:21:52\n200\n24:21:59\n10000";
    ult = ult_str2tab_select(ult_cast);
    printf("USEDLOG_TABLE_SELECT:\n 走行日時：%s\n走行距離：%lf\n走行時間：%s\n運動燃焼量：%d\n", ult.jog_datetime, ult.jog_distance, ult.jog_time, ult.burned_calorie);
    */
    char ult_buf[BUFSIZE * 8];
    ult_tab2str_select(&ult_buf[0], &ult, 5);
    printf("ult_tab2str_select:%s\n", ult_buf);
    
    //insert用
    char ult_cast[] = "34\n1\n2021-01-07/03:21:52\n200\n24:21:59\n10000";
    ult = ult_str2tab_insert(ult_cast);
    printf("USEDLOG_TABLE_SELECT:\nヘッダ：%d\nユーザID：%d\n走行日時：%s\n走行距離：%lf\n走行時間：%s\n運動燃焼量：%d\n", head_buf, ult.id, ult.jog_datetime, ult.jog_distance, ult.jog_time, ult.burned_calorie);
    
    /* select用
    USER_TABLE ut = {0, 0000010, "loginname", "password", "name", 56.2, 181.1, 21, 1, "1999-12-31", 60.3, "2022-12-31", "mail-address@exaple.ex"};
    char ut_cast[] = "loginname\nname\n56.2\n181.1\n21\n1\n1999-12-31\n60.3\n2022-12-31\nmail-address@exaple.ex";
    ut = ut_str2tab_select(ut_cast);
    printf("USER_TABLE_SELECT:\nログイン名：%s\n氏名：%s\n体重：%lf\n身長：%lf\n年齢：%d\n性別：%d\n生年月日：%s\n目標体重：%lf\n目標期間%s\nメアド：%s\n", ut.login_name, ut.name, ut.weight, ut.height, ut.age, ut.sex, ut.birth, ut.goal_weight, ut.goal_term, ut.mail_address);
    */
    //insert用
    USER_TABLE ut = {0, 1, "password", "name", 56.2, 181.1, 21, 1, "1999-12-31", 60.3, "2022-12-31", "mail-address@exaple.ex"};
    char ut_cast[] = "49\n1\npassword\nname\n56.2\n181.1\n21\n1\n1999-12-31\n60.3\n2022-12-31\nmail-address@exaple.ex";
    
    char ut_buf[BUFSIZE];
    ut_tab2str_select(&ut_buf[0], ut);
    printf("ut_tab2str_select:%s\n", ut_buf);
    
    ut = ut_str2tab_update(ut_cast);
    printf("USER_TABLE_SELECT_update:ヘッダ：%d\nユーザID%d\nパスワード：%s\n氏名：%s\n体重：%lf\n身長：%lf\n年齢：%d\n性別：%d\n生年月日：%s\n目標体重：%lf\n目標期間%s\nメアド：%s\n", head_buf, ut.id, ut.pass, ut.name, ut.weight, ut.height, ut.age, ut.sex, ut.birth, ut.goal_weight, ut.goal_term, ut.mail_address);
    
    ut = ut_str2tab_insert(ut_cast);
    printf("USER_TABLE_SELECT_insert:ヘッダ：%d\nユーザID%d\nパスワード：%s\n氏名：%s\n体重：%lf\n身長：%lf\n年齢：%d\n性別：%d\n生年月日：%s\n目標体重：%lf\n目標期間%s\nメアド：%s\n", head_buf, ut.id, ut.pass, ut.name, ut.weight, ut.height, ut.age, ut.sex, ut.birth, ut.goal_weight, ut.goal_term, ut.mail_address);
    
    
}