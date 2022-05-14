# ARDUINO SWERVE DRIVE
###### tags: `self-learing`

專案照片:
<i class="fa fa-google fa-fw"></i> GoogleDrive: [ARDU swerve](https://drive.google.com/drive/folders/1MsAM1nn1kDWHH7wUMu0TGPgG4Fxg6Fsx?usp=sharing)

# 甚麼是SWERVE?
```Swerve Drive``` is a drivetrain that is specifically designed so that the robot can spin while traveling along any path across the terrain. With each wheel rotating while also pivoting on the vertical axes, the maneuverability is unstoppable.
>擷取自heyiamindians

![](https://i.imgur.com/UCt7HGN.png)
>MK2 swerve from FRC2910
# SWERVE概述
## swerve底盤有三種移動方式
![](https://i.imgur.com/8MVn2QX.png)
## 通常使用joystick來控制
![](https://i.imgur.com/9sCxgXq.png)

需要三個參數
1. 移動角度
2. 動力
3. 自轉動力

前兩項可以用以下程式得到
```arduino
  xpos = analogRead(xpin); //接收類比搖桿訊號
  ypos = analogRead(ypin);
  xpos = map(xpos, 0, 1023, -200, 200) + 8; //轉換為座標並消除搖桿誤差
  ypos = map(ypos, 0, 1023, -200, 200) + 5;

  theta = atan2(ypos, xpos) / PI * 1.8 * 100; //利用三角函數求出移動角度
  power = hypot(xpos, ypos); //算出直角三角形的斜邊常作為動力

  double sub_theta;
```
>而自轉動力可以直接藉由搖桿的另一軸得到
## 優點
* 靈活性極高
* 抓地力大於 mecanum wheel
* 速度大於一般輪組
## 缺點
* 機構複雜
* 高成本
* 對駕駛要求高

# BOM
</table>
<table>
  <thead>
	<tr>
    <th>Amount</th>
    <th>Part Type</th>
    <th>Properties</th>
    </tr>
  </thead>
  <tbody>
<tr>
    <td>4</td>
    <td>Basic Servo</td>
    <td class="props"></td>
</tr><tr>
    <td>1</td>
    <td>Power plug</td>
    <td class="props"></td>
</tr><tr>
    <td>2</td>
    <td>L9110 H-bridge module</td>
    <td class="props">variant variant 1; part number L9110 H-bridge</td>
</tr><tr>
    <td>1</td>
    <td>Arduino Uno (Rev3)</td>
    <td class="props">Arduino UNO (Rev3)</td>
</tr><tr>
    <td>2</td>
    <td>Black Joystick KY-023</td>
    <td class="props">variant variant 1</td>
</tr>
  </tbody>
</table>



# 單輪組測試
## 機構
![](https://i.imgur.com/aI6c95V.jpg)

利用兩個伺服馬達驗證搖桿指向與輪組指向、驅動輪轉向的關係是否正確
## 程式
```arduino=
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
```
>宣告腳位及變數
```arduino=+
void setup() {
  Serial.begin(9600);
  base.attach(8);
  wheel.attach(9);
  pinMode(button, INPUT);
}
```
>設定腳位狀態
```arduino=+
void loop() {
  xpos = analogRead(xpin);
  ypos = analogRead(ypin);
  xpos = map(xpos, 0, 1023, -200, 200) + 8;
  ypos = map(ypos, 0, 1023, -200, 200) + 5;
```
>將搖桿訊號轉為座標
```arduino=+
  theta = atan2(ypos, xpos) / PI * 1.8 * 100;
```
>利用三角函數算出theta角
```arduino=+
  if (theta >  0) {
    base.write(theta);
    sub_theta = theta;
  } else if (theta <  0) {
    base.write(theta + 180); //受限於servo只能轉180度的限制，必須讓他轉到極限後將角度歸零並改變驅動輪轉向
  }
```
>設定各輪子方向
```arduino=+  
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
}
```
>設定各輪子轉向

# 全機測試
## 機構
![](https://i.imgur.com/ykLG9Pc.jpg)
![](https://i.imgur.com/hTOFRfq.jpg)

貼上各接腳腳位可以讓寫程式時減少錯誤
## 程式
```arduino=
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
```
>宣告腳位及變數
```arduino=+
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
```
>設定腳位狀態並開啟Serial
```arduino=+
}

void loop() {
  xpos = analogRead(joystickAX);
  ypos = analogRead(joystickAY);
  tpos = analogRead(joystickBY);

  xpos = map(xpos, 0, 1023, -200, 200) + 8;
  ypos = map(ypos, 0, 1023, -200, 200) + 5;
  tpos = map(tpos, 0, 1023, -45, 45) + 2;
```
>將搖桿訊號轉為座標
```arduino=+
  tpos = pow(pow(tpos, 2), 0.5); //絕對值
```
>自轉參數
```arduino=+
  theta = atan2(ypos, xpos) / PI * 1.8 * 100; //搖桿角度
```
>利用三角函數算出theta角
```arduino=+  
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
```
>消除雜訊並計算各輪組角度
```arduino=+ 
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
```
>動作

# 改進

# 參考資料:
* https://www.youtube.com/watch?v=0Xi9yb1IMyA&t=393s&ab_channel=FRC0toAutonomous
* https://www.youtube.com/watch?v=vS7AwmvIekA&ab_channel=KeplerElectronics
* https://www.youtube.com/watch?v=iJ2aso9Hsg0&ab_channel=RyanMcGee
* https://team1640.com/wiki/index.php/Swerve_Central
* https://botspace.github.io/differential-swerve-drive/
* https://compendium.readthedocs.io/en/latest/tasks/drivetrains/swerve.html
* https://www.heyiamindians.com/how-does-a-swerve-drive-work/
* https://robotics.choate.edu/wp-content/uploads/2022/02/NASA-RAP-Design-Guide.pdf
* https://www.swervedrivespecialties.com/

---

文章作者: [@wayne1211](https://hackmd.io/@wayne1211)

文章連結: https://hackmd.io/@wayne1211/ARDUswerve

版權聲明: 本HackMD所有文章除特別聲明外，均採用 CC BY-NC-SA 4.0 許可協議。轉載請註明來自@wayne1211


<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="創用 CC 授權條款" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a><br />本著作係採用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">創用 CC 姓名標示-非商業性-相同方式分享 4.0 國際 授權條款</a>授權.
