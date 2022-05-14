// 20220509 WayneLin
# include <Servo.h>
Servo FR; //右前
Servo FL; //左前
Servo BR; //右後
Servo BL; //左後

#define FRA 2
#define FRB 3
#define FLA 8
#define FLB 9
#define BRA 4
#define BRB 5
#define BLA 6
#define BLB 7

#define joystickAX A0
#define joystickAY A1
#define joystickBY A2

#define LED 1

double xpos = 0;
double ypos = 0;
double tpos = 0;
double theta;
double power;
double turn;

void setup() {
  Serial.begin(9600);
  
  FR.attach(13);
  FL.attach(11);
  BR.attach(12);
  BL.attach(10);

  pinMode(FRA, OUTPUT);
  pinMode(FRB, OUTPUT);
  pinMode(FLA, OUTPUT);
  pinMode(FLB, OUTPUT);
  pinMode(BRA, OUTPUT);
  pinMode(BRB, OUTPUT);
  pinMode(BLA, OUTPUT);
  pinMode(BLB, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(joystickAX, INPUT);
  pinMode(joystickAY, INPUT);
  pinMode(joystickBY, INPUT);

  //test
  //test();
}

void loop() {
  xpos = analogRead(joystickAX);
  ypos = analogRead(joystickAY);
  tpos = analogRead(joystickBY);

  xpos = map(xpos, 0, 1023, -200, 200) + 8;
  ypos = map(ypos, 0, 1023, -200, 200) + 5;
  tpos = map(tpos, 0, 1023, -200, 200);

  theta = atan2(ypos, xpos) / PI * 1.8 * 100; //搖桿角度
  
  double noise = 3.5;
  if ((xpos > noise || xpos < -noise) && (ypos > noise || ypos < -noise)){ //noise control
    if (theta >  0) {
      FR.write(theta);
      FL.write(theta);
      BR.write(theta);
      BL.write(theta);
      if (theta = 0) {
        FR.write(theta);
      }
    } else if (theta <  0) {
      theta += 180;
      FR.write(theta);
      FL.write(theta);
      BR.write(theta);
      BL.write(theta);
      if (theta = 0) {
        FR.write(theta);
      }
    }
    //delay(5);
  }
  
  if (tpos > 10 || tpos < -10) {
    FR.write(135);
    FL.write(45);
    BR.write(45);
    BL.write(135);
    /*
    if (tpos > 15) {
      theta += 135;
    } else {
      theta += 45;
    }*/
  }
  //Serial.print(xpos);
  //Serial.print(" ");
  //Serial.print(ypos);
  //Serial.print(" ");
  //Serial.println(theta);
  Serial.println(tpos);
}
/*
void test() {
  for(int i = 0; i < 180; i++) {
    FR.write(i);
    FL.write(i);
    BR.write(i);
    BL.write(i);
    delay(10);
  }
  for(int i = 180; i > 0; i--) {
    FR.write(i);
    FL.write(i);
    BR.write(i);
    BL.write(i);
    delay(10);
  }
}
void BlinkWithoutDelay(int ledPin, int interval) {
  unsigned long currentMillis = millis();
  unsigned long previousMillis = 0;
  int ledState = LOW;
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(ledPin, ledState);
  }
}
*/
