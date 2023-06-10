#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <EMailSender.h>



#define PROCESSING_VISUALIZER 1
#define SERIAL_PLOTTER  2


const char* ssid = "MASTERS";
const char* password = "english123";

const char* smtpServer = "smtp.gmail.com";
const int smtpPort = 465;
const char* smtpEmail = "SEU_EMAIL";
const char* smtpPassword = "SUA_SENHA";

float Latitude , Longitude;
int year , month , date, hour , minute , second;
String DateString , TimeString , LatitudeString , LongitudeString;
String batimentos = "";

String s = "";

int pulsePin = 0;               
int blinkPin = 13;             
int fadePin = 5;              
int fadeRate = 0;       

volatile int BPM;                   
volatile int Signal;                
volatile int IBI = 600;             
volatile boolean Pulse = false;     
volatile boolean QS = false;  

static int outputType = SERIAL_PLOTTER;



WiFiClientSecure client;
ESP8266SMTP SMTP(client, smtpServer, smtpPort, smtpEmail, smtpPassword);


const int buttonPin = D1; // TROCAR PELO PINO DO BOTÃO
bool buttonState = false;

void setup() {
   //CONECTANDO NO WIFI 
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  pinMode(buttonPin, INPUT_PULLUP);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando à rede Wi-Fi...");
  }
  
  Serial.println("Conectado à rede Wi-Fi!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
  
  SMTP.begin();

  pinMode(blinkPin,OUTPUT);         // pin that will blink to your heartbeat!
  pinMode(fadePin,OUTPUT);  

  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  
  if (buttonState == LOW) {
    
    
    pegarLocalizacao();
    serialOutput();



    if (QS == true){                
        fadeRate = 255;      
        serialOutputWhenBeatHappens();  
        batimentos += String(BPM) + " ";
        QS = false;                      
    }

    ledFadeToBeat();  


    s+= "<h4>Batimentos: " + batimentos + "<h4>";
    s+= "</body> </html> \n";

    enviarEmail();
    delay(1000); 
  }
}

void enviarEmail() {
  Serial.println("Enviando e-mail...");

  EMailSender emailSend("smtp.account@gmail.com", "password");

  EMailSender::EMailMessage message;
    message.subject = "Notificações";
    message.message = s;
 
    EMailSender::Response resp = emailSend.send("account_to_send@gmail.com", message);


    Serial.println("Sending status: ");
 
    Serial.println(resp.status);
    Serial.println(resp.code);
    Serial.println(resp.desc);
    
}

void pegarLocalizacao(){

    while (SerialGPS.available() > 0)
    if (gps.encode(SerialGPS.read()))
    {
      if (gps.location.isValid())
      {
        Latitude = gps.location.lat();
        LatitudeString = String(Latitude , 6);
        Longitude = gps.location.lng();
        LongitudeString = String(Longitude , 6);
      }

      if (gps.date.isValid())
      {
        DateString = "";
        date = gps.date.day();
        month = gps.date.month();
        year = gps.date.year();

        if (date < 10)
        DateString = '0';
        DateString += String(date);

        DateString += " / ";

        if (month < 10)
        DateString += '0';
        DateString += String(month);
        DateString += " / ";

        if (year < 10)
        DateString += '0';
        DateString += String(year);
      }

      if (gps.time.isValid())
      {
        TimeString = "";
        hour = gps.time.hour()+ 5; //adjust UTC
        minute = gps.time.minute();
        second = gps.time.second();
    
        if (hour < 10)
        TimeString = '0';
        TimeString += String(hour);
        TimeString += " : ";

        if (minute < 10)
        TimeString += '0';
        TimeString += String(minute);
        TimeString += " : ";

        if (second < 10)
        TimeString += '0';
        TimeString += String(second);
      }

    }

    s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n <!DOCTYPE html> <html> <head> <title>NEO-6M GPS Readings</title> <style>";
    s+= "table, th, td {border: 1px solid blue;} </style> </head> <body> <h1  style=";
    s+= "font-size:300%;";
    s+= " ALIGN=CENTER>NEO-6M GPS Readings</h1>";
    s+= "<p ALIGN=CENTER style=""font-size:150%;""";
    s+= "> <b>Location Details</b></p> <table ALIGN=CENTER style=";
    s+= "width:50%";
    s+= "> <tr> <th>Latitude</th>";
    s+= "<td ALIGN=CENTER >";
    s+= LatitudeString;
    s+= "</td> </tr> <tr> <th>Longitude</th> <td ALIGN=CENTER >";
    s+= LongitudeString;
    s+= "</td> </tr> <tr>  <th>Date</th> <td ALIGN=CENTER >";
    s+= DateString;
    s+= "</td></tr> <tr> <th>Time</th> <td ALIGN=CENTER >";
    s+= TimeString;
    s+= "</td>  </tr> </table> ";

     if (gps.location.isValid()){
        s+= "<p align=center><a style=""color:RED;font-size:125%;"" href=""http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=";
        s+= LatitudeString;
        s+= "+";
        s+= LongitudeString;
        s+= """ target=""_top"">Click here</a> to open the location in Google Maps.</p>";
        s+= "<br><br>";
    }

  //s+= "</body> </html> \n";
}

void ledFadeToBeat(){
    fadeRate -= 15;                         //  set LED fade value
    fadeRate = constrain(fadeRate,0,255);   //  keep LED fade value from going into negative numbers!
    analogWrite(fadePin,fadeRate);          //  fade LED
  }