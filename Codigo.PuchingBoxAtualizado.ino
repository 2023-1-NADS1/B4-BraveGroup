////
//
// General code from http://www.pushingbox.com for Arduino + Ethernet Shield (ENC28J60)
// Library EtherCard from https://github.com/jcw/ethercard is under mit license
//
////

  /////////////////
 // MODIFY HERE //
/////////////////
static byte mymac[] = {0x24,0x99,0x46,0xAD,0x30,0x31};   // Be sure this address is unique in your network

//Your secret DevID from PushingBox.com. You can use multiple DevID  on multiple Pin if you want
char DEVID1[] = "vF25B87D979379B4";        //Scenario : "The mailbox is open"

//Numeric Pin where you connect your switch
uint8_t pinDevid1 = 0;  // Example : the mailbox switch is connect to the Pin 3

// Debug mode
boolean DEBUG = true;
  ///////
 //End//
///////

const char website[] PROGMEM = "api.pushingbox.com";
boolean pinDevid1State = false;  // Save the last state of the Pin for DEVID1

void setup () {
  Serial.begin(9600);
  pinMode(pinDevid1, INPUT);
  
  if(DEBUG){Serial.println("\n[getDHCPandDNS]");}
  
  
  // Wait until we have an IP from the DHCP
    if(DEBUG){Serial.println("Error: DHCP failed. Can't get an IP address, let's retry...");}
  }
  
void loop () {
 
    
      ////
      // Listening for the pinDevid1 state
      ////
      if (digitalRead(pinDevid1) == HIGH && pinDevid1State == false) // switch on pinDevid1 is ON 
      {
        if(DEBUG){Serial.println("pinDevid1 is HIGH");}
        pinDevid1State = true;
        //Sending request to PushingBox when the pin is HIGHT
        delay(500);  
      }
       if (digitalRead(pinDevid1) == LOW && pinDevid1State == true) // switch on pinDevid1 is OFF
      {
        if(DEBUG){Serial.println("pinDevid1 is LOW");}
        pinDevid1State = false;
        //Sending request to PushingBox when the pin is LOW
        //ether.browseUrl(PSTR("/pushingbox?devid="), DEVID1, website, my_callback);
        delay(500);
      }
      
}

// called when the client request is complete
static void my_callback (byte status, word off, word len) {
  Serial.println(">>>");
  Serial.println("...");
}
