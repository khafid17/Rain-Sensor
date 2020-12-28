// Pendeteksi Keringat

int rainsense= A0; // analog sensor pin A0 untuk input raindrop
int buzzerout= D7; // digital pin nomor 7 untuk output buzzer
int countval= 0; // counter value mulai 0 
int ledout= D13; // digital pin nomor 13 untuk output led
 
void setup(){

   Serial.begin(9600);
   pinMode(buzzerout, OUTPUT);
   pinMode(ledout, OUTPUT); 
   pinMode(rainsense, INPUT);
}
void loop(){

   int rainSenseReading = analogRead(rainsense);
   Serial.println(rainSenseReading); // untuk monitoring output bila berkeringat
   delay(250);// keringat value dari 0 ke 1023.
   // dari berkeringat sampai tidak berkeringat
   if (countval >= 1){                // delay percount
      Serial.print("Keringat");
      digitalWrite(buzzerout, HIGH);  // buzzer nyala
      digitalWrite(ledout, HIGH);     // led nyala
   }
   if (rainSenseReading <500){ 
      countval++; // naik count value
   }
   else if (rainSenseReading >500) { // jika tidak hujan
      digitalWrite(buzzerout, LOW); // buzzer mati
      digitalWrite(ledout, LOW); // led mati
      countval = 0; // reset count ke 0
   }
   delay(1000);
}

