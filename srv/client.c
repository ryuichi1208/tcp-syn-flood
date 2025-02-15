#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/socket.h>
#include <signal.h>

#define PORT 12345

int main(void) {
    int sock;
    struct sockaddr_in server_addr;
    ssize_t bytes_written;
    int sndbuf;
    socklen_t optlen = sizeof(sndbuf);

    // SIGPIPEを無視する
    signal(SIGPIPE, SIG_IGN);

    // ソケット作成
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // SO_SNDBUFの取得
    if (getsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sndbuf, &optlen) < 0) {
        perror("getsockopt (SO_SNDBUF)");
        exit(EXIT_FAILURE);
    }
    printf("ServerA: 現在の SO_SNDBUF のサイズ: %d バイト\n", sndbuf);

    // サーバBのアドレス設定（localhost）
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("inet_pton");
        exit(EXIT_FAILURE);
    }

    // サーバBへ接続
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        exit(EXIT_FAILURE);
    }
    printf("ServerA: ServerBに接続しました。\n");

    // サーバBが先にソケットをクローズするのを待つ（5秒待機）
    sleep(5);

    // 送信データを作成（SO_SNDBUF の 2 倍のデータ）
    size_t send_size = sndbuf * 1;
    char *large_message = (char *)malloc(send_size);
    if (!large_message) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    memset(large_message, 'A', send_size);
    large_message[send_size - 1] = '\0';

    // 大量データの書き込み
    printf("ServerA: 大量データ（%zu バイト）を書き込みます...\n", send_size);
    bytes_written = send(sock, large_message, send_size, MSG_NOSIGNAL);
    if (bytes_written < 0) {
        perror("send");
        printf("ServerA: 書き込みに失敗しました。\n");
    } else {
        printf("ServerA: 書き込み成功（%zd バイト送信）\n", bytes_written);
    }

    free(large_message);
    close(sock);
    return 0;
}

