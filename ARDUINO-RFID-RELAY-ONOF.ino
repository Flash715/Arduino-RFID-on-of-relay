//Credit Ivan F

#include <SPI.h>

#include <MFRC522.h>

 

#define SS_PIN 10

#define RST_PIN 9

#define LED_Hijau 5 //LED Hijau

#define LED_Merah 4 //LED Merah

#define RELAY 3 //Relay

#define BUZZER 2 //Buzzer Speaker

#define ACCESS_DELAY 2000

#define DENIED_DELAY 1000

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

 int kondisi;

void setup() 

{

  Serial.begin(9600);   // Initiate a serial communication

  SPI.begin();          // Initiate  SPI bus

  mfrc522.PCD_Init();   // Initiate MFRC522

  pinMode(LED_Hijau, OUTPUT);

  pinMode(LED_Merah, OUTPUT);

  pinMode(RELAY, OUTPUT);

  pinMode(BUZZER, OUTPUT);

  noTone(BUZZER);

  digitalWrite(RELAY, HIGH);

  Serial.println("Tempelkan Kartu Anda...");

  Serial.println();
  kondisi = 0;


}

void loop() 

{

  // Look for new cards

  if ( ! mfrc522.PICC_IsNewCardPresent()) 

  {

    return;

  }

  // Select one of the cards

  if ( ! mfrc522.PICC_ReadCardSerial()) 

  {

    return;

  }

  //Show UID on serial monitor

  Serial.print("UID tag :");

  String content= "";

  byte letter;

  for (byte i = 0; i < mfrc522.uid.size; i++) 

  {

     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");

     Serial.print(mfrc522.uid.uidByte[i], HEX);

     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));

     content.concat(String(mfrc522.uid.uidByte[i], HEX));

  }

  Serial.println();

  Serial.print("Message : ");

  content.toUpperCase();

  if (content.substring(1) == "35 4B C5 2F") //Ganti UID ini dengan UID kamu.

  {

    if (kondisi == 0)
    {
      digitalWrite(BUZZER, HIGH);
      delay(100);
      digitalWrite(BUZZER, LOW);
      // relay dinyalakan
      // alat dalam kondisi "ON"
      // buzzer menyala
      digitalWrite(RELAY, LOW);
      digitalWrite(BUZZER, LOW);
      delay(1000);
      // buzzer dimatikan
      
      // kondisi menjadi = 1
      kondisi = 1;
    }else if (kondisi == 1)
    {
      digitalWrite(BUZZER, HIGH);
      delay(100);
      digitalWrite(BUZZER, LOW);
      // relay dimatikan
      // alat dalam kondisi "ON"
      // buzzer menyala
      digitalWrite(RELAY, HIGH);
      digitalWrite(BUZZER, LOW);
      delay(1000);
      // buzzer dimatikan
      
      // kondisi menjadi = 0
      kondisi = 0;
    }
  }

 

 else   {

    Serial.println(" UID DItolak");

    digitalWrite(LED_Merah, HIGH);
    tone(BUZZER, 300);
    delay(DENIED_DELAY);
    digitalWrite(LED_Merah, LOW);
    noTone(BUZZER);
    delay(100);
    digitalWrite(LED_Merah, HIGH);
    tone(BUZZER, 300);
    delay(DENIED_DELAY);
    digitalWrite(LED_Merah, LOW);
    noTone(BUZZER);
    delay(100);
    digitalWrite(LED_Merah, HIGH);
    tone(BUZZER, 300);
    delay(DENIED_DELAY);
    digitalWrite(LED_Merah, LOW);
    noTone(BUZZER);
    delay(100);

  }

}