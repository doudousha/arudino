
int ledDelay  = 10000 ;
int redPin = 10 ;
int yellowPin = 9;
int greenPin = 8 ;
unsigned long changeTime ;
int yellowLedDelay = 2000 ;

void setup() {
  
   Serial.begin(9600);
  pinMode(redPin , OUTPUT);
  pinMode(yellowPin,OUTPUT);
  pinMode(greenPin , OUTPUT);
  changeTime=  millis();
}

void loop() {

  digitalWrite(redPin,HIGH);
  delay(ledDelay);

  yellowShow();
   digitalWrite(redPin,LOW);
   digitalWrite(greenPin,HIGH);
   delay(ledDelay);

   
   yellowShow();
   digitalWrite(yellowPin,LOW);
   digitalWrite(greenPin,LOW);
}

void yellowShow() {
  changeTime=  millis();

   while( (millis() - changeTime)  < yellowLedDelay) {
     digitalWrite(yellowPin,HIGH);
     delay(60);
     digitalWrite(yellowPin,LOW);
     delay(60);
    
   }
}
    
