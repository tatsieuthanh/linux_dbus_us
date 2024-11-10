#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dbus/dbus.h>
#include "processA_dbus_us.h"
#include "processB_dbus_us.h"

DBusConnection* setup_dbus_connection() {
    DBusError err;
    DBusConnection *conn;

    dbus_error_init(&err);

    conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
    if (dbus_error_is_set(&err)) {
        fprintf(stderr, "Connection Error (%s)\n", err.message);
        dbus_error_free(&err);
        exit(1);
    }
    if (conn == NULL) {
        fprintf(stderr, "Failed to connect to the D-Bus session bus.\n");
        exit(1);
    }

    // Yêu cầu quyền đặt tên trên bus chỉ một lần
    int ret = dbus_bus_request_name(conn, "org.example.processA", DBUS_NAME_FLAG_REPLACE_EXISTING, &err);
    if (dbus_error_is_set(&err)) {
        fprintf(stderr, "Name Error (%s)\n", err.message);
        dbus_error_free(&err);
        dbus_connection_unref(conn);
        exit(1);
    }

    if (ret != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER) {
        fprintf(stderr, "Not Primary Owner.\n");
        dbus_connection_unref(conn);
        exit(1);
    }

    return conn;  // Trả về kết nối DBus
}

void send_message(int n, DBusConnection *conn) {
    DBusMessage *msg;
    DBusMessageIter args;
    char *message = NULL;
    if (asprintf(&message, "Hello World! %d", n) == -1) {
        fprintf(stderr, "Failed to allocate memory for message\n");
        return;
    }

    dbus_uint32_t serial = 0;

    // Tạo tin nhắn
    msg = dbus_message_new_signal("/org/example/processA", "org.example.processA", "SendHello");
    if (msg == NULL) {
        fprintf(stderr, "Failed to create message (msg is NULL)\n");
        return;
    }

    dbus_message_iter_init_append(msg, &args);

    if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &message)) {
        fprintf(stderr, "Out Of Memory when appending argument!\n");
        return;
    }

    // Gửi tin nhắn và đợi cho đến khi được gửi xong
    if (!dbus_connection_send(conn, msg, &serial)) {
        fprintf(stderr, "Out Of Memory while sending message!\n");
        return;
    }

    dbus_connection_flush(conn);
    dbus_message_unref(msg);
    printf("Process A: Sent '%s'\n", message);
}

int main() {
    int n = 1;
    hello_processA();
    hello_processB();
    DBusConnection *conn = setup_dbus_connection();
    printf("Start sending message\n");
    while (1) {
        send_message(n,conn);
        sleep(1);  
        n++;
    }
    return 0;
}
