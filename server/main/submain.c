#include<unistd.h>
#include<sys/wait.h>
#include "queue.h"
#include "../DB/src/jogging.h"

int main() {

}


void *access_table(request r) {
    switch (r.access_target) {
        calorie_table:
            switch (r.op) {
                select_t:
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
                select_t:
                    SAVED_ROUTE_TABLE *resp_data;
                    resp_data = saved_route_select();
                    return resp_data;
                insert_t:
                    return saved_route_insert(test_data);
                update_t:
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
                select_t:
                    USEDLOG_TABLE *resp_data;
                    resp_data = usedlog_select();
                    return resp_data;
                insert_t:
                    return usedlog_insert(test_data);
                update_t:
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
                select_t:
                    USER_TABLE *resp_data;
                    resp_data = user_select();
                    return resp_data;
                insert_t:
                    return user_insert(test_data);
                update_t:
                    return user_update(test_data);
                default:
                    break;
            }
    }
}