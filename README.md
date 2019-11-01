A CoAPthon docker container as server, and an Arduino coap-simple-library client.
========

Originals:

https://github.com/hirotakaster/CoAP-simple-library

https://github.com/Tanganelli/CoAPthon

How to
========
========


Install git
========

$ sudo apt install git

Install Arduino and clone Coap-simple-library
========

$ sudo apt install arduino

$ cd /home/user/Arduino/libraries

$ git clone https://github.com/hirotakaster/CoAP-simple-library

Install Docker
========

$ sudo apt install docker.io

Clone CoAPthon
========

$ cd /home/user/Documents/coapthon-server

git clone https://github.com/Tanganelli/CoAPthon

Dockerizing CoAPthon
========

$ cd /home/user/Documents/coapthon-server/CoAPthon

Download coapserver-simples.py

$ cd /home/user/Documents/coapthon-server/

Download Dockerfile

$ sudo docker build -t coapthon-server /home/gustavo/Documentos/coapthon-server/

$ sudo docker run -it --rm --name coapthon-server -p 5683:5683 coapthon-server

Atention
========

For Arduino to connect to the server, you need a route to the 172.17.0.0/16 network using the Linux host IP address as the gateway.

On your router, in my case, OpenWrt
Interface - lan  
Target - 172.17.0.0  
IPv4-Netmask - 255.255.0.0  
IPv4-Gateway - 192.168.1.192  
Metric - 0  
MTU - 1500  
Route type - Unicast  


