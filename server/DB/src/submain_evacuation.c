#include<stdio.h>
#include<stdlib.h>
#include"jogging.h"
#include"../../main/queue.h"

int main() {
    //1
    //REQUEST_QUEUE rq = ;
    while() {
        request *request_queue_init();
        request r = dequeue_request();
        if(r.ip == -1) {
            continue;
        }
        else {
            //2
            switch(r.access_target) {
                    calorie_table:
                    switch (r.op) {
                            select:
                            CALORIE_TABLE *resp_data;
                            resp_data = calorie_select();
                            return resp_data;
                        default:
                            break;
                    }
                    
                    saved_route_table:
                    SAVED_ROUTE_TABLE test_data = {
                        0, 0,
                        "", "", "", "", ""
                    };
                    switch (r.op) {
                            select:
                            SAVED_ROUTE_TABLE *resp_data;
                            resp_data = saved_route_select();
                            return resp_data;
                            
                            insert:
                            return saved_route_insert(test_data);
                            
                            update:
                            return saved_route_update(test_data);
                        default:
                            break;
                    }
                    
                    usedlog_table:
                    USEDLOG_TABLE test_data = {
                        0, 0, "0000/00/00 00:00:00",
                        0, "00:00:00", 0
                    };
                    switch (r.op) {
                            select:
                            USEDLOG_TABLE *resp_data;
                            resp_data = usedlog_select();
                            return resp_data;
                            
                            insert:
                            return usedlog_insert(test_data);
                            
                            update:
                            return usedlog_update(test_data);
                        default:
                            break;
                    }
                    
                    user_table:
                    USEDLOG_TABLE test_data = {
                        0, 0, "", "", "", 0.0, 0.0, 
                        0, 0, "", 0.0, "", ""
                    };
                    switch (r.op) {
                            select:
                            USER_TABLE *resp_data;
                            resp_data = user_select();
                            return resp_data;
                            
                            insert:
                            return user_insert(test_data);
                            
                            update:
                            return user_update(test_data);
                        default:
                            break;
                    }
            }
        }
    }
}
    //3
        
}

request access_table() {
}

int select_test_ct() {
    int error_sum = 0;

    // calorie_table access test
    CALORIE_TABLE ct = calorie_select();
    error_sum += ct.error;
    printf("id: %d\n", ct.food);
    printf("    food_name    : %s\n", ct.food_name);
    printf("    food_calorie : %d\n", ct.food_calorie);
    
    return error_sum;
}

int select_test_srt() {
    int errror_sum = 0;
    // saved_route access test
    SAVED_ROUTE_TABLE srt0 = saved_route_select(0);
    SAVED_ROUTE_TABLE srt1 = saved_route_select(1);
    SAVED_ROUTE_TABLE srt2 = saved_route_select(2);
    SAVED_ROUTE_TABLE srt3 = saved_route_select(3);

    error_sum += srt0.error + srt1.error + srt2.error + srt3.error;

    print_srt(srt0);
    print_srt(srt1);
    print_srt(srt2);
    print_srt(srt3);

    return error_sum;
}

int select_test_ut() {
    int error_sum = 0;
    
    // user_table access test
    USER_TABLE ut = user_select(1);
    error_sum += ut.error;
    printf("ユーザID：%d\n",ut.id);
    printf("体重：%lf\n", ut.weight);
    printf("身長：%lf\n", ut.height);
    printf("年齢：%d\n", ut.age);
    printf("性別：%d\n", ut.sex);
    printf("生年月日：%s\n", ut.birth);
    printf("目標体重：%lf\n", ut.goal_weight);
    printf("目標期間：%s\n", ut.goal_term);
    
    return error_sum;
    
}

int select_test_ult() {
    int error_sum = 0;
    //usedlog_table access test
    //該当データ数
    int n = 0;
    
    USEDLOG_TABLE *ult = usedlog_select(1, &n);
    error_sum += ult[0].error;
    printf("走行日時：%s\n", ult[1].jog_datetime);
    printf("走行距離：%lf\n", ult[2].jog_distance);
    printf("走行時間：%s\n", ult[3].jog_time);
    printf("運動燃焼量：%d\n", ult[4].burned_calorie);
    print_ult(ult, n);
    free(ult);
    
    return error_sum;
}


