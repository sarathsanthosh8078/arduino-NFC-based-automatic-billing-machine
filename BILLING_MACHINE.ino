#include <SPI.h>
#include <MFRC522.h>                         //   NFC READER MODULE LIBRERY 
#include <LiquidCrystal_I2C.h>              //    LIQUID CRYSTAL LCD DISPLAY LIBRERY
#include <Wire.h>


int total_cost=0,rate=0,balance=0,a;                           //GLOBAL VARIABLE
int price=0,total=0,sum=0;


LiquidCrystal_I2C lcd(0x27, 16, 2);       // I2C MODULE ADDRESS ADDRESSING

#define RST_PIN         9           // Configurable, see typical pin layout above    tagID.concat(String(mfrc522.buffer2[i], HEX)); // Adds the 4 bytes in a single String variable
#define SS_PIN          10          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

//*****************************************************************************************//
void setup() {
  pinMode(2,INPUT); 
  pinMode(3,OUTPUT); 
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);                                           // Initialize serial communications with the PC
  SPI.begin();                                                  // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522 card****************************  RST-9;****** SDA-10;****MOSI-11;*****MISO-12;****SCK-13;  
  //lcd.setCursor(0,0);
 // lcd.print("MEMBERS-ANUPAMA:ARYA:ANULEKSHMI:ANEENA");
 
}

void loop() {
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
                                                              //int a=digitalRead(2); UNCOMMENT IF PRODUCT REMOVAL CODE IS USED 
  int cost[20];
  char buffer2[18];
  byte block;                                                // VARIABLE DECLARATION
  byte block2;
  byte len;
  MFRC522::StatusCode status;
   if ( ! mfrc522.PICC_IsNewCardPresent()) {
    //digitalWrite(3,HIGH);
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.println(F("**Card Detected:**"));
  Serial.print(F("Name: "));

  
  block = 1;
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 1, &key, &(mfrc522.uid));
  status = mfrc522.MIFARE_Read(block, buffer2, &len);
  lcd.setCursor(0, 0); 
  for (uint8_t i = 0; i < 16; i++) 
 {  Serial.write(buffer2[i]);                               // LINE TO PRINT THE NAME OF PRODUCT TO THE LCD DISPLAY
   lcd.write((buffer2[i])); 
   

 /*  if((price==150)&&(a==1))
{ lcd.setCursor(0, 0);
  lcd.print("A product removed!!!!! ");
  total_sub(150);
}

else if((price==5)&&(a==1))
{ lcd.setCursor(0, 0);
  lcd.print("A product removed!!!!! ");
  total_sub(5);                                                     //  CODE FORE REMOVING THE PRODUCT         BUT NOT PERFECTLY WORKING!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}
else if(price== 150&&(a==0))
{ lcd.setCursor(0, 0);
  lcd.print("A product removed!!!!! ");
  digitalWrite(3,HIGH); 
}

else if(price== 150&&(a==0))
{ lcd.setCursor(0, 0);
  lcd.print("A product removed!!!!! ");
digitalWrite(3,HIGH); 
}
  */
  }
 
   byte buffer1[18];
   block = 4;
   len = 18;
   status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(mfrc522.uid));
   status = mfrc522.MIFARE_Read(block, buffer1, &len);

  for (uint8_t i = 0; i < 16; i++)
  {
    if (buffer1[i] != 32)                                  // TRANSFERRIND THE PRICE TO THE INIGER ARRAY cost[i]
    {
      cost[i]=buffer1[i]; 
   }
  }
  
  block = 1;
  

  mfrc522.PCD_StopCrypto1();
   price= atoi(buffer1);
   lcd.setCursor(9,0);                                   // CURSERE WILL START FROM COLOUM 9 AND ROW 0      D1 6A E8 19        52 0C 84 1B


   lcd.print("Rs:");
   lcd.print(price);
   Serial.print(price);
   
   Total(price);                                       // CALLS THE FUNCTION FOR FINDING THE TOTAL
   delay(1000);

}
int Total(int price) 
{
  
  total_cost=sum;
  total_cost=total_cost+price;                      // FUNCTION FOR FINDING THE TORTAL PRICE OF THE PRODUCTS
  sum=total_cost;
  lcd.setCursor(0,1);
  lcd.print("TOTAL: ");
  lcd.print(total_cost);
  lcd.print(" Rps");
  Serial.print(total_cost);
  
}
int total_sub(int rate)
{                                                   //   FUNCTION TO SUBSTRACT PRICE FROM TOTAL
  balance=sum-rate;
  lcd.setCursor(0,1);
  lcd.print("TOTAL: ");
  lcd.print(balance);
  lcd.print(" Rps");
  
}
