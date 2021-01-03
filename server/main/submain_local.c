#include "queue.h"
#include "jogging.h"

void *access_table(request r) {
    switch (r.access_target) {
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