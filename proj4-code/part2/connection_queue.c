#include <stdio.h>
#include <string.h>
#include "connection_queue.h"

int connection_queue_init(connection_queue_t *queue) {
    // TODO Not yet implemented
    
    queue->length = 0;
    queue->read_idx = 0;
    queue->write_idx = 0;
    queue->shutdown = 0;
    pthread_cond_init(&queue->queue_full, NULL);
    pthread_cond_init(&queue->queue_empty, NULL);
    pthread_mutex_init(&queue->lock, NULL);
    return 0;
}

int connection_enqueue(connection_queue_t *queue, int connection_fd) {
    // TODO Not yet implemented
    return 0;
}

int connection_dequeue(connection_queue_t *queue) {
    // TODO Not yet implemented
    return 0;
}

int connection_queue_shutdown(connection_queue_t *queue) {
    // TODO Not yet implemented
    return 0;
}

int connection_queue_free(connection_queue_t *queue) {
    // TODO Not yet implemented
    return 0;
}
