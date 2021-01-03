#ifndef jog_request_queue_h
#define jog_request_queue_h

#define QUEUE_SIZE 100
typedef struct {
    int ip;
    int access_target;
    int op;
} request ;

enum access_target {
    calorie_table,
    saved_route_table,
    usedlog_table,
    user_table
} ;

enum operation {
    select_t,
    update_t,
    insert_t
} ;

request *request_queue;
request *request_queue_ahead;
request *request_queue_tail;
int request_queue_element_n;

request *request_queue_init();
int enqueue_request(request elem);
request dequeue_request();
void print_request_elem(request elem);

#endif