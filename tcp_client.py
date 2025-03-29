import socket
import time

def client():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('localhost', 12345))

    # クライアント側でデータを送信（バッファに残る）
    client_socket.sendall(b"Hello, Server!")
    
    # サーバ側がソケットをクローズするまで待機
    time.sleep(1)

    # サーバ側がクローズした後にデータ送信を再試行
    try:
        client_socket.sendall(b"Another message")
        print("Message sent successfully.")
    except Exception as e:
        print(f"Error occurred: {e}")

    client_socket.close()

if __name__ == '__main__':
    client()
