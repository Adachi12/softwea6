#include<stdlib.h>
#include "queue.h"

request *request_queue_init() {
    request_queue = (request *)malloc(sizeof(request) * QUEUE_SIZE);
    request_queue_ahead = request_queue;
    request_queue_tail = request_queue;
    request_queue_element_n = 0;
    return request_queue;
}

int enqueue_request(request elem) {
    // キューにもうデータが入らない時の処理
    if (request_queue_element_n > QUEUE_SIZE) {
        // error
        return 1;
    }

    // malloc領域の最後尾に到達した時の処理
    if (request_queue_tail == request_queue + QUEUE_SIZE) {
        // 先頭に帰ってくる
        request_queue_tail = request_queue;
    }

    request_queue_element_n++;
    request_queue[request_queue_element_n] = elem;
    return 0;
}

request dequeue_request() {
    request resp = {-1, -1, -1};

    // データがひとつもない場合
    if (request_queue_element_n == 0)
        return resp;

    // 正常な値を返す
    resp = *request_queue_ahead;

    if (request_queue_ahead == request_queue + QUEUE_SIZE) {
        // 先頭に帰ってくる
        request_queue_ahead = request_queue;
    }
    request_queue_ahead++;
    return resp;
}