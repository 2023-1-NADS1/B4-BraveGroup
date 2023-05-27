/* Programa para Artigo MakerHero
 * Como Conectar o ESP8266 à Internet
 * Autor: Eduardo Castro
 * Gerenciador de placas: "ESP8266 Community versão 2.3.0"
 * Placa: "NodeMCU 1.0 (ESP-12E Module)"
*/
// ======================================================================
// --- Inclusão da biblioteca ---
#include <ESP8266WiFi.h> 
// ======================================================================
// --- Dados de Acesso do seu roteador ---
#define WLAN SSID   "XXXXXXXX"   // nome da sua rede
#define WLAN PASS  "XXXXXXXX"   // senha de acesso do seu roteador
WebClient Secure cliente; //Cria um cliente seguro (para ter acesso ao HTTPS)
// ======================================================================
void setup()
{
  Serial.begin(9600); // Inicia Serial com Baud Rate de 115200
  Serial.println();      
  WiFi.mode(WIFI STA); //Habilita o modo estação
  WiFi.begin(WLAN SSID, VLAN PASS); //Inicia WiFi com os dados preenchidos 
  delay(1000); // aguarda 1 segundo
  Serial.print("Conectando"); 
  while (WiFi.status() != WL_CONNECTED) // Tentando conectar na Rede WiFi
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  
  Serial.print("Conectado | Endereço IP: "); // Imprime na Serial
  Serial.println(WiFi.localIP()); //Imprime o Endereço IP Local do ESP8266
  delay(1000); // aguarda 1 segundo
}
  
// ======================================================================
void loop() {
  if (cliente.connect("sheets.googleapis.com", 443) == true) {    
  //Tenta se conectar ao servidor do Google APIs na porta 443 (HTTPS)
     Serial.println("Conseguiu conexão com Servidor Google APIs");
  }
  else {
      Serial.println("Falha na conexão com Servidor Google APIs");
  }
   
  delay(3000); // aguarda 3 segundos
}
// --- FIM ---
