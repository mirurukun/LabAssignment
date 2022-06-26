import socket

ClientSocket = socket.socket()
port = 8888

print('Waiting for connection')
try:
    ClientSocket.connect(('192.168.202.5', port))
except socket.error as e:
    print(str(e))

Response = ClientSocket.recv(2048)
print(Response)
print("\nCalculator for Log, Square root and exponential :)\n\n")

while True:

    choice=input(" 1 for LOG \n 2 for Square Root \n 3 for Exponential \n Enter stop to terminate : ")
    if(choice=='1'):    
        number=input("Enter number:")
    elif(choice=='2'):
        number=input("Enter number:")
    elif(choice=='3'):
        number=input("Enter number:")
    elif(choice=='stop'):
        print("connection terminated")
        break

    message=choice+" "+number
    ClientSocket.send(str.encode(message))
    Response = ClientSocket.recv(2048)
    print(Response.decode('utf-8'))

ClientSocket.close()

