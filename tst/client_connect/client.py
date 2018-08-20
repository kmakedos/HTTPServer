import socket
import sys
class client:
    '''
    '''
    def __init__(self, sock = None):
        if sock is None:
            self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        else:
            self.sock = sock

    def connect(self, host, port):
        self.sock.connect((host, port))

    def send_some(self, msg = "Hello"):
        totalsent = 0
        sent = self.sock.send(msg)

        #MSGLEN = len(msg)
        #while totalsent < MSGLEN:
        #    sent = self.sock.send(msg[totalsent:])
        #    if sent == 0:
        #        raise RuntimeError("socket connection broken")
        #    totalsent = totalsent + sent

    def receive_some(self):
        chunk = self.sock.recv(1)
        print(chunk)
        while chunk:
            chunk = self.sock.recv(1)
            print(chunk)
        #    if chunk == '':
        #        raise RuntimeError("socket connection broken")
        #    chunks.append(chunk)
        #    bytes_recvd += len(chunk)
        #return ''.join(chunks)
