#include <stdio.h>
#include <unistd.h>
#include "processB_dbus_us.h"
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

#define SOCKET_PATH "/tmp/unix_socket"
#define BUFFER_SIZE 128

// Hàm hiển thị thông báo từ process B
void *hello_processB() {
    while (1) {
        printf("Hello from process B\n");
        sleep(1);
    }
    return NULL;
}

// Hàm khởi tạo server
static int init_server() {
    int server_fd;
    struct sockaddr_un server_addr;

    // Tạo socket
    if ((server_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket error");
        exit(1);
    }

    // Xóa file socket nếu đã tồn tại
    unlink(SOCKET_PATH);

    // Cấu hình địa chỉ socket
    memset(&server_addr, 0, sizeof(struct sockaddr_un));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    // Liên kết socket với địa chỉ
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr_un)) == -1) {
        perror("bind error");
        close(server_fd);
        exit(1);
    }

    // Lắng nghe kết nối
    if (listen(server_fd, 5) == -1) {
        perror("listen error");
        close(server_fd);
        exit(1);
    }

    printf("Server đã khởi tạo và đang chờ kết nối...\n");
    return server_fd;
}

// Hàm lắng nghe và xử lý kết nối từ client
static void listen_server(int server_fd) {
    int client_fd;
    char buffer[BUFFER_SIZE];

    while (1) {
        // Chấp nhận kết nối từ client
        if ((client_fd = accept(server_fd, NULL, NULL)) == -1) {
            perror("accept error");
            continue;  // Tiếp tục chờ kết nối nếu có lỗi
        }

        // Nhận dữ liệu từ client
        int recv_bytes = read(client_fd, buffer, BUFFER_SIZE);
        if (recv_bytes > 0) {
            buffer[recv_bytes] = '\0';
            printf("Server nhận: %s\n", buffer);
        }

        // Đóng kết nối với client sau khi xử lý
        close(client_fd);
    }

    // Đóng server socket khi muốn dừng server
    close(server_fd);
    unlink(SOCKET_PATH);
}

// Hàm khởi tạo và bắt đầu lắng nghe
void *send_us() {
    int server_fd = init_server();
    if (server_fd == -1) {
        fprintf(stderr, "Không thể khởi tạo server\n");
    }

    // Bắt đầu lắng nghe và xử lý kết nối
    listen_server(server_fd);
    return NULL;
}
