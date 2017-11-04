import socket

def main():
    mysoc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    adir = ("", 1234)
    mysoc.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    mysoc.bind(adir)
    mysoc.listen(5)
    mysoc.settimeout(60)
    print("Listening for connections...")
    conn, addr = mysoc.accept()
    conn.settimeout(5)
    print("Connected to: ", addr[0])
    client_echo_count = 10
    client_message = "Data sent from server to client: "
    while True:
        try:
            data = conn.recv(4096)
        except socket.error as e:
            conn.close()
            mysoc.close()
            del(conn)
            del(mysoc)
            print("Error: Client disconnected...")
            print("Will attempt to reconnect...")
            mysoc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            mysoc.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            adir = ("", 1234)
            mysoc.bind(adir)
            mysoc.listen(5)
            mysoc.settimeout(60)
            print("Listening for connections...")
            conn, addr = mysoc.accept()
            conn.settimeout(5)
            print("Connected to: ", addr[0])
            
            
        print("The number received was: ", data)
        conn.sendall(client_message.encode())
        conn.sendall(str(client_echo_count).encode())
        client_echo_count += 1
        

main()
