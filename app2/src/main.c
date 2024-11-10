#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <dbus/dbus.h>
#include <pthread.h>
#include "processC_dbus_us.h"
#include "processD_dbus_us.h"



int main() {
    // Gọi các hàm từ thư viện chia sẻ
    hello_processC();
    printf("Process B: Waiting for messages...\n");
    pthread_t thread_id3, thread_id4;
    if (pthread_create(&thread_id3, NULL, receive_message, NULL) != 0) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    if (pthread_create(&thread_id4, NULL, recieved_us, NULL) != 0) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    pthread_join(thread_id3, NULL);
    pthread_join(thread_id4, NULL);
    return 0;
}