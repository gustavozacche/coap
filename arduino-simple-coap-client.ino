#include <coap-simple.h>
#include <Ethernet.h>

byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };

// CoAP client response callback
void callback_response(CoapPacket &packet, IPAddress ip, int port);

// UDP and CoAP class
EthernetUDP Udp;
Coap coap(Udp);

// CoAP client response callback
void callback_response(CoapPacket &packet, IPAddress ip, int port) {
  Serial.println("[Ack do Servidor Coap]");

  char p[packet.payloadlen + 1];
  memcpy(p, packet.payload, packet.payloadlen);
  p[packet.payloadlen] = NULL;

  Serial.println(p);
}

//frequência de envio de mensagens
unsigned int tempo = 0;

//número máximo de envios
unsigned int numEnvios = 0;


void setup() 
{
  Serial.begin(9600);

  Ethernet.begin(mac);
  Serial.print("Endereco IP do Arduino: ");
  Serial.print(Ethernet.localIP());
  Serial.println();

  // client response callback.
  // this endpoint is single callback.
  coap.response(callback_response);

  // start coap server/client
  coap.start();

  while (!Serial) 
  {
    ; //enquanto não tem serial, aguarda.
  }

  Serial.println("Entre com o valor do tempo entre as rajadas (em milisegundos):  ");
  tempo = ler();

  Serial.println("Entre com o valor do numero de envios :  ");
  numEnvios = ler();
  
}

int ler()
{
  while(!Serial.available())
  {
    ; //enquanto não tem serial, aguarda.
  }
  unsigned int entrada = 0;
  char buffer[16]; 
  size_t num_read = Serial.readBytesUntil('\r', buffer, sizeof(buffer)-1 );
  buffer[num_read] = '\0';
  sscanf(buffer, "%d", &entrada);   
  return entrada;
}

void loop() 
{
   for (int i = 0; i < numEnvios; i++) 
   {
    coap.put(IPAddress(172, 17, 0, 2), 5683, (char *)"basic", (char *)"0123456789");
   }
   
  delay(tempo);
  coap.loop();
}
