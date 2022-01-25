#define GREENLED 6
#define REDLED 7
#define BUZZER 5
#define YELLOWLED 8

void setup() {
  pinMode(GREENLED, OUTPUT); //green LED
  pinMode(REDLED, OUTPUT); //red LED
  pinMode(YELLOWLED, OUTPUT);
  pinMode(BUZZER, OUTPUT); //buzzer
  Serial.begin(1200);
}

boolean isBeat;
int beatCount, bpm, ppgValue;
unsigned long millisCount;

void loop() {
  ppgValue = analogRead(A0);
  //Serial.println(ppgValue);
  if (isBeat == 0) { //not at peak
    if (ppgValue > 180) {
      isBeat = 1; //set peak
      beatCount++;
      digitalWrite(YELLOWLED, HIGH);
      tone(BUZZER, 2500);
      Serial.println("Heartbeat detected!");
      Serial.print("beatCount: ");
      Serial.println(beatCount);
      delay(100);
      digitalWrite(YELLOWLED, LOW);
      noTone(BUZZER);
    }
  } else {
    if (ppgValue < 160) {
      isBeat = 0;
    }
  }
  if (millis() - millisCount > 15000) { //15s
    bpm = beatCount * 4; //1 min
    if (bpm >= 60 && bpm <= 100) { //healthy HR: 60 to 100 bpm
      digitalWrite(GREENLED, HIGH); //healthy heart rate
      digitalWrite(REDLED, LOW);
    }
    else {
      digitalWrite(REDLED, HIGH); //unhealthy heart rate
      digitalWrite(GREENLED, LOW);
    }
    
    beatCount = 0; //reset beatCount
    Serial.print("BPM: ");
    Serial.println(bpm);
    delay(2000);
    digitalWrite(GREENLED, LOW);
    digitalWrite(REDLED, LOW); //reset both LEDs
    millisCount = millis(); //reset millisCount so that start new cycle

  }
  delay(1);
}
