#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>

#define PORT 12345

int main(void) {
    int listen_fd, conn_fd;
    struct sockaddr_in server_addr;
    int opt = 1;

    // ソケット作成
    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // ソケットオプション設定
    if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // バインド設定
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // 待ち受け開始
    if (listen(listen_fd, 1) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("ServerB: ポート %d で待ち受け中...\n", PORT);

    // 接続受け入れ
    if ((conn_fd = accept(listen_fd, NULL, NULL)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    printf("ServerB: 接続を受け付けました。3秒後に接続をクローズします。\n");
    sleep(3);

    // ソケットクローズ
    close(conn_fd);
    printf("ServerB: 接続をクローズしました。\n");

    close(listen_fd);
    return 0;
}

