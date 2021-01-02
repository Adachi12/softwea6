#include "queue.h"

int main() {
    request test1 = {0x12345678, calorie_table, select};
    request test2 = {0x12345678, usedlog_table, select};
    request test3 = {0x87654321, user_table, insert};
    request test4 = {0x87654321, saved_route_table, select};

    request *queue = request_queue_init();
    enqueue_request(test1);
    enqueue_request(test2);
    enqueue_request(test3);
    enqueue_request(test4);

    dequeue_request();
    dequeue_request();
    dequeue_request();
    dequeue_request();

    return 0;
}