#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <dbus/dbus.h>
#include "processC_dbus_us.h"
#include "processD_dbus_us.h"

void receive_message() {
    DBusMessage *msg;
    DBusMessageIter args;
    DBusError err;
    DBusConnection *conn;
    char *sigvalue;

    // Khởi tạo lỗi
    dbus_error_init(&err);

    // Kết nối tới D-Bus (bus session mặc định)
    conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
    if (dbus_error_is_set(&err)) {
        fprintf(stderr, "Connection Error (%s)\n", err.message);
        dbus_error_free(&err);
    }
    if (conn == NULL) {
        exit(1);
    }

    // Yêu cầu quyền đặt tên trên bus
    int ret = dbus_bus_request_name(conn, "org.example.processB", DBUS_NAME_FLAG_REPLACE_EXISTING , &err);
    if (dbus_error_is_set(&err)) {
        fprintf(stderr, "Name Error (%s)\n", err.message);
        dbus_error_free(&err);
    }
    if (ret != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER) {
        exit(1);
    }

    // Thêm rule để nhận tín hiệu từ Process A
    dbus_bus_add_match(conn, "type='signal',interface='org.example.processA'", &err);
    dbus_connection_flush(conn);
    if (dbus_error_is_set(&err)) {
        fprintf(stderr, "Match Error (%s)\n", err.message);
        exit(1);
    }

    // Chờ và xử lý tin nhắn
    while (1) {
        // Chặn chờ tin nhắn đến
        dbus_connection_read_write(conn, 0);
        msg = dbus_connection_pop_message(conn);

        // Nếu không có tin nhắn thì bỏ qua
        if (msg == NULL) {
            usleep(100000);
            continue;
        }

        // Kiểm tra xem có phải là tin nhắn mong đợi không
        if (dbus_message_is_signal(msg, "org.example.processA", "SendHello")) {
            // Đọc tin nhắn
            if (!dbus_message_iter_init(msg, &args))
                fprintf(stderr, "Message has no arguments!\n");
            else if (DBUS_TYPE_STRING != dbus_message_iter_get_arg_type(&args))
                fprintf(stderr, "Argument is not string!\n");
            else {
                dbus_message_iter_get_basic(&args, &sigvalue);
                printf("Process B: Received '%s'\n", sigvalue);
            }
        }

        // Giải phóng tin nhắn
        dbus_message_unref(msg);
    }
}

int main() {
    // Gọi các hàm từ thư viện chia sẻ
    hello_processC();
    hello_processD();
    printf("Process B: Waiting for messages...\n");
    receive_message();
    return 0;
}