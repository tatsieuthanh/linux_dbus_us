#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dbus/dbus.h>
#include "processA_dbus_us.h"


int hello_processA()
{
    printf("Hello from process A\n");
    return 0;
}

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
    dbus_uint32_t serial = 0;
    char *message = NULL;

    if (asprintf(&message, "Dbus send %d", n) == -1) {
        fprintf(stderr, "Failed to allocate memory for message\n");
        return;
    }

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

void* send_message_thread(void *arg) {
    DBusConnection *conn = (DBusConnection *)arg;
    int n = 1;
   
    while (1) {
        send_message(n, conn);
        sleep(2);
        n++;
    }

    return NULL;
}