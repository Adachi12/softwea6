#include<unistd.h>
#include<sys/wait.h>
#include "queue.h"
#include "../DB/src/jogging.h"

int main() {

}



void *access_table(request r) {
    CALORIE_TABLE *resp_data_cal;
    SAVED_ROUTE_TABLE *resp_data_srt;
    USEDLOG_TABLE *resp_data_ult;
    USER_TABLE *resp_data_ut;

    CALORIE_TABLE test_data_cal;
    SAVED_ROUTE_TABLE test_data_srt;
    USEDLOG_TABLE test_data_ult;
    USER_TABLE test_data_ut;

    switch (r.access_target) {
        calorie_table:
            switch (r.op) {
                select_t:
                    resp_data_cal = calorie_select();
                    return resp_data_cal;
            }
        saved_route_table:
            test_data_srt = {
                0, 0,
                "", "", "", "", ""
            };
            switch (r.op) {
                select_t:
                    resp_data_srt = saved_route_select();
                    return resp_data_srt;
                insert_t:
                    return saved_route_insert(test_data);
                update_t:
                    return saved_route_update(test_data);
                default:
                    break;
            }
        usedlog_table:
            test_data_ult = {
                0, 0, "0000/00/00 00:00:00",
                0, "00:00:00", 0
            };
            switch (r.op) {
                select_t:
                    resp_data_ult = usedlog_select();
                    return resp_data;
                insert_t:
                    return usedlog_insert(test_data);
                update_t:
                    return usedlog_update(test_data);
                default:
                    break;
            }
        user_table:
            test_data_ut = {
                0, 0, "", "", "", 0.0, 0.0, 
                0, 0, "", 0.0, "", ""
            };
            switch (r.op) {
                select_t:
                    resp_data_ut = user_select();
                    return resp_data_ut;
                insert_t:
                    return user_insert(test_data);
                update_t:
                    return user_update(test_data);
                default:
                    break;
            }
    }
}