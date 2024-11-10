#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dbus/dbus.h>
#include <pthread.h>
#include "processA_dbus_us.h"
#include "processB_dbus_us.h"

int main() {
    hello_processA();
    
    DBusConnection *conn = setup_dbus_connection();
    pthread_t thread_id1, thread_id2;
    if (pthread_create(&thread_id1, NULL, send_message_thread, conn) != 0) {
        fprintf(stderr, "Error creating thread\n");
        dbus_connection_unref(conn);
        return 1;
    }

    if (pthread_create(&thread_id2, NULL, send_us, conn) != 0) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    // Đợi cho đến khi thread kết thúc
    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
    dbus_connection_unref(conn);  // Đảm bảo huỷ kết nối sau khi xong
    return 0;
}
