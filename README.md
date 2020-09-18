# tcp-syn-flood
synflood

## Usage

```
python3 tcp_syn.py -h
usage: tcp_syn.py [-h] [--target TARGET] [--port PORT] [--count COUNT] [--flags FLAGS] [--version]

optional arguments:
  -h, --help            show this help message and exit
  --target TARGET, -t TARGET
                        target IP address
  --port PORT, -p PORT  target port number
  --count COUNT, -c COUNT
                        number of packets
  --flags FLAGS, -f FLAGS
                        tcp flags
  --version, -v         show program's version number and exit

Usage: python3 py3_synflood_cmd.py -t 10.20.30.40 -p 8080 -c 1
```

## Install

##### requirements

* python3.6+
* scapy==2.4.4
