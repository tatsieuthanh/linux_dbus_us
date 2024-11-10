#include <stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include "processD_dbus_us.h"
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/unix_socket"

void *hello_processD()
{   while (1){
        printf("Hello from process D\n");
        sleep(1);
        
    }
    return 0;

}

static int init_client(){
    int client_fd;
    struct sockaddr_un server_addr;
    
    // Tạo socket
    if ((client_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket error");
        exit(1);
    }

    // Cấu hình địa chỉ server
    memset(&server_addr, 0, sizeof(struct sockaddr_un));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    // Kết nối đến server
    if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr_un)) == -1) {
        perror("connect error");
        close(client_fd);
        exit(1);
    }
    return client_fd;
}

static void send_message(int client_fd){
    char *message = "Unix socket message";
    int n = 0;
    while(1){
        // Gửi tin nhắn đến server
        if (asprintf(&message, "Unix socket message %d", n) == -1) {
            fprintf(stderr, "Failed to allocate memory for message\n");
            return;
        }
        if (send(client_fd, message, strlen(message),0) == -1) {
            perror("write error");
            free(message);  
            close(client_fd);
            exit(1);
        }
        n++;
        printf("Client đã gửi tin nhắn: %s\n", message);
        free(message);
        sleep(2);

    }

}

void  *recieved_us() {
    
    int client_fd = init_client();
        
    // Gửi tin nhắn liên tục
    send_message(client_fd);

    // Đóng kết nối khi hoàn thành (mặc dù trong trường hợp này sẽ không bao giờ đến do vòng lặp vô hạn)
    close(client_fd);
    return NULL;

}
