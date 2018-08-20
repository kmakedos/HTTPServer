#!/usr/bin/env python
import sys
from client_connect.client import client
f = open(sys.argv[1], 'r')
data = f.read()
c = client()
c.connect("localhost", 8000)
c.send_some(data)
print(c.receive_some())
c.shutdown(SHUT_WR)
