import socket
import sys
import time
import math
import errno
from multiprocessing import Process



def process_start(s_sock):
    s_sock.send(str.encode('Welcome to Online Calculator Server'))

    while True:
        data = s_sock.recv(2048)
        data=data.decode('utf-8')

        try:
            choice,number=data.split(" ",2)
        except:
            print("Cannot receive data")
            break


        if(choice=='1'):
            answer=calcLOG(number)
        elif(choice=='2'):
            answer=calcSquareRoot(number)
        elif(choice=='3'):
            answer=calcExponential(number)
        elif(choice=='stop'):
            break
        equal="\nAnswer:%s\n"% str(answer)
        s_sock.sendall(str.encode(equal))
    s_sock.close()

def calcLOG(i):
    print("\nCalculating Log:",i)
    i=float(i)
    answer=math.log(i)
    return answer


def calcSquareRoot(i):
    print("\nCalculating Square Root:",i)
    i=float(i)
    answer=math.sqrt(i)
    return answer


def calcExponential(i):
    print("\nCalculating Exponential:",i)
    i=float(i)
    answer=math.exp(i)
    return answer




if __name__ == '__main__':
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind(("",8888))
    print("Listening...")
    s.listen(3)
    try:
        while True:
            try:
                s_sock, s_addr = s.accept()
                p = Process(target=process_start, args=(s_sock,))
                p.start()

            except socket.error:

                print('got a socket error')

    except Exception as e:
            print('an exception occurred!')
            print(e)
            sys.exit(1)
    finally:
           s.close()
