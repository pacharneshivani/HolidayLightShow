import socket
import time
import random

def send_command(socket, command, ip_port):
    socket.sendto(command.encode(), ip_port)
    

def main():
    UDP_IP = "192.168.0.5"
    #UDP_IP1 = "192.168.0.8"
    UDP_PORT = 5005
    #MESSAGE = "Hello, World!"
    #message_count = 0
    print("UDP target IP: ", UDP_IP)
    #print("UDP target IP: ", UDP_IP1)
    print("UDP target port: ", UDP_PORT)
    #print("message:", MESSAGE)
    client_commands = ["R", "B", "G", "A", "N", "RB", "RG", "BG"]
    ip_port = (UDP_IP, UDP_PORT)
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) #Internet, UDP
    while True:
        selection = random.randint(0, 7)
        MESSAGE = client_commands[selection]
        send_command(sock, MESSAGE, ip_port) 
        #print(MESSAGE)
        #print("Sending message #: ", message_count)
        #string = "Delay time: " + str(delay)
        #print(string)
        #print(message_count)
        #sock1 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) #internet, UDP
        #sock.sendto((MESSAGE + " " + str(message_count)).encode(), (UDP_IP, UDP_PORT))
        #sock.sendto(MESSAGE.encode(), (UDP_IP, UDP_PORT))
        #sock1.sendto((MESSAGE + " " + str(message_count)).encode(), (UDP_IP1, UDP_PORT))
        time.sleep(0.1)       
        #print("Sending agiain")
        #message_count += 1


main() 
