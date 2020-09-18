#!/usr/bin/python3

import sys
import socket

from multiprocessing import Process

max_port = 3000
min_port = 1

target_host = sys.argv[1]

def port_scan(target_host, port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    return_code = sock.connect_ex((target_host, port))
    sock.close()

    if not return_code:
        print(f"Port Open {port}")


def main():
    for i in range(max_port):
        proccess = Process(target=port_scan, args=[target_host, i])
        proccess.start()

    proccess.join()


if __name__ == '__main__':
    main()
