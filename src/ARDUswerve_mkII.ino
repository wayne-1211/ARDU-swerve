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
}

void loop() {
  xpos = analogRead(joystickAX);
  ypos = analogRead(joystickAY);
  tpos = analogRead(joystickBY);

  xpos = map(xpos, 0, 1023, -200, 200) + 8;
  ypos = map(ypos, 0, 1023, -200, 200) + 5;
  tpos = map(tpos, 0, 1023, -45, 45) + 2;

  tpos = pow(pow(tpos, 2), 0.5); //絕對值

  theta = atan2(ypos, xpos) / PI * 1.8 * 100; //搖桿角度
  
  double noise = 3.5;
  if ((xpos > noise || xpos < -noise) && (ypos > noise || ypos < -noise) || (tpos > 10 || tpos < -10)){ //noise control
    FR.attach(13);
    FL.attach(11);
    BR.attach(12);
    BL.attach(10);
    if (theta <  0) {
      theta += 180;
    }
    if (!((xpos > noise || xpos < -noise) && (ypos > noise || ypos < -noise)) && (tpos > 10 || tpos < -10)){
      theta = 0;
    }
    FL.write((theta + tpos) > 0 ? theta + tpos : theta + tpos - 180);
    FR.write((theta - tpos) > 0 ? theta - tpos : theta - tpos + 180);
    BL.write((theta - tpos) > 0 ? theta - tpos : theta - tpos + 180);
    BR.write((theta + tpos) > 0 ? theta + tpos : theta + tpos - 180);
  } else {
    FL.detach();
    FR.detach();
    BL.detach();
    BR.detach();
  }
}
