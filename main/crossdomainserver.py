#echo crossdomain program

import socket

HOST = ''
PORT = 843
s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.bind((HOST,PORT))
s.listen(1)
conn, addr = s.accept()
print 'Connected by', addr

while 1:
  data = conn.recv(1024)
  if not data: break
  f =open('crossdomain.xml')
  policydata = f.read()
  conn.send(policydata + "\0")
conn.close()