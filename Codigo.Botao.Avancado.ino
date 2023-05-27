void setup()
{
   Serial.begin(9600);
   Serial.println("Leitura do Botão");
   pinMode(D1,OUTPUT);
   pinMode(D2,INPUT);
}
void loop()
{
   digitalWrite(D1,digitalRead(D2));
   if(digitalRead(D2)==0)
   {
    Serial.println("");
    delay(1000);
   }
   else{
    Serial.println("Possível alerta!");
    delay(1000);
   }

}
