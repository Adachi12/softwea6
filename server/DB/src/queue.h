#ifndef jog_request_queue_h
#define jog_request_queue_h

#define QUEUE_SIZE 100
typedef struct {
    int ip;
    int a_t;
    int op;
} request ;

enum access_target {
    CALORIE_TABLE,
    SAVED_ROUTE_TABLE,
    USEDLOG_TABLE,
    USER_TABLE
} ;

enum operation {
    select,
    update,
    insert
} ;

request *request_queue;
request *request_queue_ahead;
request *request_queue_tail;
int request_queue_element_n;

request *request_queue_init();
int enqueue_request(request elem);
request dequeue_request();

#endif