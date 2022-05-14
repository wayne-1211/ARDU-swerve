#include <Servo.h>

Servo base;
Servo wheel;

#define xpin A0
#define ypin A1
#define button 7

double xpos = 0;
double ypos = 0;
double theta;
double power;

void setup() {
  Serial.begin(9600);
  base.attach(8);
  wheel.attach(9);
  pinMode(button, INPUT);
}

void loop() {
  xpos = analogRead(xpin);
  ypos = analogRead(ypin);
  xpos = map(xpos, 0, 1023, -200, 200) + 8;
  ypos = map(ypos, 0, 1023, -200, 200) + 5;

  theta = atan2(ypos, xpos) / PI * 1.8 * 100;
  power = hypot(xpos, ypos);

  double sub_theta;
  
  if (theta >  0) {
    base.write(theta);
    sub_theta = theta;
  } else if (theta <  0) {
    base.write(theta + 180);
    sub_theta = theta + 180; 
  }
  
  if (ypos > 0) {
    wheel.write(45);
  } else if (ypos < 0) {
    wheel.write(135);
  } else if (xpos > 0) {
    wheel.write(45);
  } else if (xpos < 0) {
    wheel.write(135);
  } else {
    wheel.write(90);
  }
  //TODO: power控制
  

  //pow(pow(x, 2), 0.5)) x的絕對值

  //Serial.print(xpos);
  //Serial.print(" ");
  //Serial.print(ypos);
  //Serial.print(" ");
  Serial.print(theta);
  Serial.print(" ");
  Serial.println(sub_theta);
  //Serial.println(power);
  //
  delay(100);

}
