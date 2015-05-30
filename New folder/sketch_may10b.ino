


//  VARIABLES
int pulsePin = 0;                 // Pulse Sensor  στο αναλογικο pin 0
int blinkPin3 = 3;                // pin που θα αναβοσβήνει σε καθε χτύπο της καρδιας
int blinkPin4 = 4;                // pin που θα αναβοσβήνει σε καθε χτύπο της καρδιας
int blinkPin5 = 5;                // pin που θα αναβοσβήνει σε καθε χτύπο της καρδιας
int blinkPin6 = 6;                // pin που θα αναβοσβήνει σε καθε χτύπο της καρδιας
int blinkPin7 = 7;                // pin που θα αναβοσβήνει σε καθε χτύπο της καρδιας


int fadePin = 2;                  // pin για να κανει fading blink σεε καθε χτύπο της καρδιας
int fadeRate = 0;                 // μονάδα αυξησης του fading
int speaker = 13;                 // speaker κανει beep σε καθε χτυπο της καρδιας



volatile int BPM;                   //  ρυθμος πσλμου
volatile int Signal;                //  data εισοδου του heart pulse sensor
volatile int IBI = 600;             //  χρονος μεταξυ των beats
volatile boolean Pulse = false;     // true οταν νιώθει παλμό, false οταν δεν νιώθει παλμο
volatile boolean QS = false;        // γινεται true οταν το Lilypad heard pulse sensor βρει παλμο.


void setup() {
  pinMode(blinkPin3, OUTPUT);        // pin που θα αναβοσβήνει στον χτύπο της καρδιας
  pinMode(blinkPin4, OUTPUT);        // pin που θα αναβοσβήνει στον χτύπο της καρδιας
  pinMode(blinkPin5, OUTPUT);        // pin που θα αναβοσβήνει στον χτύπο της καρδιας
  pinMode(blinkPin6, OUTPUT);        // pin που θα αναβοσβήνει στον χτύπο της καρδιας
  pinMode(blinkPin7, OUTPUT);        // pin που θα αναβοσβήνει στον χτύπο της καρδιας

  pinMode(fadePin, OUTPUT);
  Serial.begin(9600);                // σειριακη ενωση.στο PC  μου ειναι η 9600
  interruptSetup();                  // διαβαζει χτυπο καθε 2mS

  //analogReference(EXTERNAL);
}



void loop() {
  sendDataToProcessing('S', Signal);     // στελνει τα Data γισ υπολογισμο
  if (QS == true) {                      //  flag  when arduino finds a heartbeat
    fadeRate = 255;                      // οταν βρει παλμο οριζει το fadeRate σε 255
    sendDataToProcessing('B', BPM);
    sendDataToProcessing('Q', IBI);
    QS = false;                          // μηδενιζει
    tone(speaker,1047 );                 // συχνοτητα του ηχειου (speaker, μορουμε να το αλλαξουμε αν γινεται ενοχλητικο,η να του
                                         // βαλουμε μια αντισταση για να του μειωσουμε την ενταση.
  }

  ledFadeToBeat();                       //αναβουμε το fadePin

  delay(20);                            //  περιμενει για 20ms
}


void ledFadeToBeat() {
  fadeRate -= 15;

  fadeRate = constrain(fadeRate, 0, 255); //  αποφευγουμε να παρουμε αρνητικές τιμες στο fadeRate
  if (fadeRate == 0) {
    noTone(speaker);
  }
  analogWrite(fadePin, fadeRate);         //  αναβουμε το fadePin
}


void sendDataToProcessing(char symbol, int data ) {
   //Serial.print(symbol);
   //Serial.println(data);
 Serial.print("Your Pulse currently is :    ");    //
 Serial.println(BPM/2);                              //
 Serial.print("\n\n");                       //τυπωνουμε στη σειριακη οθονη
  
      
}


