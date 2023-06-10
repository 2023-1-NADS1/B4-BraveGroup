<!DOCTYPE html>
<html>

<head>
  <title>Projeto - Batimentos Localização Email</title>
</head>

<body>
  <h1>Projeto - Batimentos Localização Email</h1>
  <h2>Descrição</h2>
  <p>Este projeto consiste em um sistema que captura os batimentos cardíacos por meio de um sensor Pulse Sensor Amped e envia os dados de localização e batimentos por email.</p>

  <h2>Colaboradores</h2>
  <ul>
    <li>Lucas Silva Cardiais</li>
    <li>Nicolas Zagatto</li>
    <li>Carlos Augusto</li>
    <li>Carlos Augusto</li>
  </ul>

  <h2>Tecnologias Utilizadas</h2>
  <ul>
    <li>Arduino</li>
    <li>TinyGPS++</li>
    <li>SoftwareSerial</li>
    <li>ESP8266WiFi</li>
    <li>EMailSender</li>
  </ul>

  <h2>Instalação</h2>
  <ol>
    <li>Clone o repositório para o seu ambiente local.</li>
    <li>Abra o arquivo "BatimentosLocalizacaoEmail.ino" no Arduino IDE.</li>
    <li>Conecte o sensor Pulse Sensor Amped ao Arduino.</li>
    <li>Configure as credenciais da rede Wi-Fi no código (SSID e senha).</li>
    <li>Configure as informações do servidor SMTP e do email remetente.</li>
    <li>Compile e faça o upload do código para o Arduino.</li>
    <li>Execute o projeto.</li>
  </ol>

  <h2>Erros Encontrados</h2>
  <p>Ao executar o código, os seguintes erros foram encontrados:</p>
  <pre>
In file included from C:\Users\zagat\Downloads\DocumentsArduino\BatimentosLocalizacaoEmail\BatimentosLocalizacaoEmail.ino:4:
C:\Users\zagat\OneDrive\Catálogo bueno.stxre\Documentos\Arduino\libraries\EMailSender/EMailSender.h:324: warning: "EMAIL_NETWORK_CLASS" redefined
  324 |   #define EMAIL_NETWORK_CLASS EMAIL_NETWORK_SSL_CLASS
      | 
In file included from C:\Users\zagat\Downloads\DocumentsArduino\BatimentosLocalizacaoEmail\BatimentosLocalizacaoEmail.ino:4:
C:\Users\zagat\OneDrive\Catálogo bueno.stxre\Documentos\Arduino\libraries\EMailSender/EMailSender.h:157: note: this is the location of the previous definition
  157 | #define EMAIL_NETWORK_CLASS WiFiClient
&lt;command-line&gt;: error: expected unqualified-id before numeric constant
C:\Users\zagat\Downloads\DocumentsArduino\BatimentosLocalizacaoEmail\BatimentosLocalizacaoEmail.ino:43:1: note: in expansion of macro 'ESP8266'
   43 | ESP8266 SMTP(client, smtpServer, smtpPort, smtpEmail, smtpPassword);
      | ^~~
C:\Users\zagat\Downloads\DocumentsArduino\BatimentosLocalizacaoEmail\BatimentosLocalizacaoEmail.ino: In function 'void setup()':
BatimentosLocalizacaoEmail:65
