import socket
mysoc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
adir = ("", 1234)
mysoc.bind(adir)
print("Listening for a connection")
mysoc.listen(5)
print("Accepting a connection...")
conn,addr = mysoc.accept()
print("Connection accepted")
print("Connected to ")
print(addr)
#while True:
#    data = conn.recv(1000)
#    if data == b'\n':
#        break
#    else:
#        print ("Got a request!")
#        print (data)

#conn.close()
#mysoc.close()

while True:
    data = conn.recv(4096)
    #if not data: break
    print("Received data: ", data)
    #conn.send(data)
    data = 0

#conn.close() 
