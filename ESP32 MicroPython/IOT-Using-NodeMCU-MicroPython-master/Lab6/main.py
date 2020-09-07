import socket
import gc
import utime

def connect_to_ap():
    import network
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    wlan.isconnected()
    if not wlan.isconnected():
        print('connecting to network')
        wlan.connect('L&F','41992549713')
        while not wlan.isconnected():
            utime.sleep(1)  
            pass
    print('network config', wlan.ifconfig())

def starwars():
    gc.collect()
    addr_info = socket.getaddrinfo("towel.blinkenlights.ln",23)
    addr = addr_info[0][-1]
    s = socket.socket()
    s.connect(addr)
    while True:
        data = s.recv(1000)
        print(str(data,'utf8'),end='')

def main():
    connect_to_ap()
    starwars()


if __name__ == '__main__':
    main()
    
exit()

