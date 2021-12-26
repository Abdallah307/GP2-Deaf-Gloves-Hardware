#include <Wire.h>
#include <MPU6050.h>
#include <AsyncDelay.h>

AsyncDelay delay_1s;

int flex1 = A0;
int flex2 = A1;
int flex3 = A2;
int flex4 = A3;
int flex5 = A6;

String kalima = "";

int buttonOldState = 1;
int buttonNewState;
volatile int gloveState = 0;
int buttonPin = 2;

MPU6050 mpu;

// Timers
unsigned long timer = 0;
float timeStep = 0.01;

// Pitch, Roll and Yaw values
float pitch = 0;
float roll = 0;
float yaw = 0;


char * temp = "0";

void printfun(char * cp)
{
  if (cp != temp)
  {
    // kalima += cp;
    Serial.write(cp, 2);
    temp = cp;
  }
}

void changeButtonState() {
  delay(100);
  buttonNewState = digitalRead(buttonPin);
  if (buttonOldState == 0 && buttonNewState == 1) {
    if (gloveState == 0) {
      gloveState = 1;
    }
    else {
      gloveState = 0;
    }
    //Serial.println(gloveState);
  }
  buttonOldState = buttonNewState;
}


void setup() {
  Serial.begin(115200);
  while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    //    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }

  mpu.calibrateGyro();
  // mpu.setThreshold(3);

  pinMode(flex1, INPUT);
  pinMode(flex2, INPUT);
  pinMode(flex3, INPUT);
  pinMode(flex4, INPUT);
  pinMode(flex5, INPUT);
  pinMode(3, OUTPUT);
  pinMode(buttonPin , INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), changeButtonState, CHANGE);

  //  byte msg[2] = "م";
  //Serial.write(msg,2);

  // Serial.write()
  delay_1s.start(1000, AsyncDelay::MILLIS);

}

void loop() {

  //  if (gloveState == 1) {
  // run the glove


  timer = millis();
  Vector norm = mpu.readNormalizeGyro();
  //y
  pitch = pitch + norm.YAxis * timeStep;
  //X
  roll = roll + norm.XAxis * timeStep;
  //Z
  yaw = yaw + norm.ZAxis * timeStep;



  // Output raw
  //          Serial.print(" Y-Pitch = ");
  //          Serial.print(pitch);
  //          Serial.print(" X-Roll = ");
  //          Serial.print(roll);
  //          Serial.print(" Z-Yaw = ");
  //          Serial.println(yaw);
  if (delay_1s.isExpired()) {
    float data1 =  analogRead(flex1);
  float data2 =  analogRead(flex2);
  float data3 =  analogRead(flex3);
  float data4 =  analogRead(flex4);
  float data5 =  analogRead(flex5);

  if (data1 <= 200 && data2 <= 200 && data3 <= 200 && data4 >= 245 && data5 < 200) {
    printfun("ب");
  }

  else if (data1 <= 200 && data2 <= 200 && data3 <= 200 && (data4 >= 200 && data4 <= 240) && data5 < 200) {
    printfun("ر");
  }

  else if (data3 >= 150 && data3 <= 165 && data4 >= 210 && data5 >= 150 && data5 <= 160) {
    printfun("ط");
  }

  else if (pitch >= 15 && roll >= 50) {
    printfun("ن");
  }

  else if (yaw <= -12 && data1 <= 200 && data2 <= 200 && data3 <= 200 && data4 > 210 && data5 >= 200) {
    //Serial.println("LLLLLLLLLLLLLLLLLLLLLLLLLL");
    printfun("ل");
  }

  else if (data1 <= 200 && data2 <= 200 && data3 <= 200 && data4 > 210 && data5 >= 200) {
    printfun("د");
  }

  else if (data3 >= 200 && data4 >= 200 && data5 >= 200 && data1 < 200 && data2 < 200) {
    // Serial.println("RRRRRRRRRRRRRRRRRRRR");
    printfun("ع");
  }

  else if (data1 <= 200 && data2 <= 200 && data3 >= 210 && data4 > 210) {
    printfun("ت");
  }

  else if (data1 <= 200 && data2 >= 210 && data3 >= 210 && data4 > 210) {
    printfun("ث");
  }

  else if (yaw >= 45 && data1 <= 200 && data2 <= 200 && data3 <= 200 && data4 <= 200 && data5 <= 190) {
    // Serial.println("TTTTTTTTTTTTTTTTTTTTTT");
    printfun("ج");
  }

  else if (yaw >= 45 && data1 <= 200 && data2 <= 200 && data3 <= 200 && data4 <= 200 && data5 >= 200) {
    // Serial.println("GGGGGGGGGGGGGGGGGGGGG");
    printfun("ح");
  }

  //  else if ((data1 >= 155 && data1 <= 195 && data2 >= 155 && data2 <= 195 && data3 >= 155 && data3 <= 195 && data4 >= 155 && data4 <= 195) && data5 <= 135) {
  //    printfun("ج");
  //  }
  else if (data1 >= 200 && data2 >= 200 && data3 >= 200 && data4 >= 200 && data5 >= 200) {
    printfun("س");
  }
  else if (data1 >= 200 && data2 >= 200 && data3 >= 200 && data4 >= 200 && data5 < 190) {
    printfun("ك");
  }
  else if (data1 >= 200 && data4 >= 200) {
    printfun("لا");
  }

  else if (data1 >= 200 && data5 >= 200 && data2 <= 225  && data3 <= 200 && data4 <= 200) {
    // analogWrite(3, 0);
    printfun("ي");
  }

  else if (data1 >= 200) {
    // analogWrite(3, 70);
    printfun("م");

  }
  //  else if ((data1 >= 155 && data1 <= 195 && data2 >= 155 && data2 <= 195 && data3 >= 155 && data3 <= 195 && data4 >= 155 && data4 <= 195) && data5 >= 210) {
  //    printfun("ح");
  //  }






  //  else if (data1 <= 150 && data2 <= 150 && data3 <= 150 && data4 <= 150 && data5 >= 210) {
  //    printfun("خ");
  //  }

  else if (data3 >= 170 && data3 <= 180) {
    printfun("ز");
  }

  else if (pitch >= 45 && data1 <= 190 && data2 <= 190 && data3 <= 190 && data4 <= 190 && data5 >= 200) {
    //  Serial.println("Hello Mother");
    printfun("أ");
  }

  else if (pitch <= -45 && data1 <= 190 && data2 <= 190 && data3 <= 190 && data4 <= 190 && data5 >= 200) {
    //Serial.println("WoooooW");
    printfun("و");
  }

  else if (data1 <= 190 && data2 <= 190 && data3 <= 190 && data4 <= 190 && data5 >= 200) {
    //Serial.println("Oleeeeeeeeeeeeeey");
    printfun("خ");
  }

  else if (data1 <= 190 && data2 <= 190 && data3 <= 190 && data4 <= 190 && data5 <= 190) {
    printfun("ص");
  }

  else if (data1 >= 200 && data2 >= 200 && data3 >= 200 && data4 >= 200 && data5 < 190) {
    printfun("ك");
  }

  //  else if (pitch >=15 && roll >= 50) {
  //    printfun("ن");
  //  }

  //      Serial.println(data1);
  //      Serial.println(data2);
  //      Serial.println(data3);
  //      Serial.println(data4);
  //      Serial.println(data5);

  //delay(800);
  //delay((timeStep * 1000) - (millis() - timer));

  //  } // if glove state
  //  else if(kalima.length() != 0) {
  //    //Serial.print("Kalima is : ");
  //    Serial.println("s");
  //    kalima = "";
  //  }
  delay_1s.repeat();
  } // if async expired

//  float data1 =  analogRead(flex1);
//  float data2 =  analogRead(flex2);
//  float data3 =  analogRead(flex3);
//  float data4 =  analogRead(flex4);
//  float data5 =  analogRead(flex5);
//
//  if (data1 <= 200 && data2 <= 200 && data3 <= 200 && data4 >= 245 && data5 < 200) {
//    printfun("ب");
//  }
//
//  else if (data1 <= 200 && data2 <= 200 && data3 <= 200 && (data4 >= 200 && data4 <= 240) && data5 < 200) {
//    printfun("ر");
//  }
//
//  else if (data3 >= 150 && data3 <= 165 && data4 >= 210 && data5 >= 150 && data5 <= 160) {
//    printfun("ط");
//  }
//
//  else if (pitch >= 15 && roll >= 50) {
//    printfun("ن");
//  }
//
//  else if (yaw <= -12 && data1 <= 200 && data2 <= 200 && data3 <= 200 && data4 > 210 && data5 >= 200) {
//    //Serial.println("LLLLLLLLLLLLLLLLLLLLLLLLLL");
//    printfun("ل");
//  }
//
//  else if (data1 <= 200 && data2 <= 200 && data3 <= 200 && data4 > 210 && data5 >= 200) {
//    printfun("د");
//  }
//
//  else if (data3 >= 200 && data4 >= 200 && data5 >= 200 && data1 < 200 && data2 < 200) {
//    // Serial.println("RRRRRRRRRRRRRRRRRRRR");
//    printfun("ع");
//  }
//
//  else if (data1 <= 200 && data2 <= 200 && data3 >= 210 && data4 > 210) {
//    printfun("ت");
//  }
//
//  else if (data1 <= 200 && data2 >= 210 && data3 >= 210 && data4 > 210) {
//    printfun("ث");
//  }
//
//  else if (yaw >= 45 && data1 <= 200 && data2 <= 200 && data3 <= 200 && data4 <= 200 && data5 <= 190) {
//    // Serial.println("TTTTTTTTTTTTTTTTTTTTTT");
//    printfun("ج");
//  }
//
//  else if (yaw >= 45 && data1 <= 200 && data2 <= 200 && data3 <= 200 && data4 <= 200 && data5 >= 200) {
//    // Serial.println("GGGGGGGGGGGGGGGGGGGGG");
//    printfun("ح");
//  }
//
//  //  else if ((data1 >= 155 && data1 <= 195 && data2 >= 155 && data2 <= 195 && data3 >= 155 && data3 <= 195 && data4 >= 155 && data4 <= 195) && data5 <= 135) {
//  //    printfun("ج");
//  //  }
//  else if (data1 >= 200 && data2 >= 200 && data3 >= 200 && data4 >= 200 && data5 >= 200) {
//    printfun("س");
//  }
//  else if (data1 >= 200 && data2 >= 200 && data3 >= 200 && data4 >= 200 && data5 < 190) {
//    printfun("ك");
//  }
//  else if (data1 >= 200 && data4 >= 200) {
//    printfun("لا");
//  }
//
//  else if (data1 >= 200 && data5 >= 200 && data2 <= 225  && data3 <= 200 && data4 <= 200) {
//    // analogWrite(3, 0);
//    printfun("ي");
//  }
//
//  else if (data1 >= 200) {
//    // analogWrite(3, 70);
//    printfun("م");
//
//  }
//  //  else if ((data1 >= 155 && data1 <= 195 && data2 >= 155 && data2 <= 195 && data3 >= 155 && data3 <= 195 && data4 >= 155 && data4 <= 195) && data5 >= 210) {
//  //    printfun("ح");
//  //  }
//
//
//
//
//
//
//  //  else if (data1 <= 150 && data2 <= 150 && data3 <= 150 && data4 <= 150 && data5 >= 210) {
//  //    printfun("خ");
//  //  }
//
//  else if (data3 >= 170 && data3 <= 180) {
//    printfun("ز");
//  }
//
//  else if (pitch >= 45 && data1 <= 190 && data2 <= 190 && data3 <= 190 && data4 <= 190 && data5 >= 200) {
//    //  Serial.println("Hello Mother");
//    printfun("أ");
//  }
//
//  else if (pitch <= -45 && data1 <= 190 && data2 <= 190 && data3 <= 190 && data4 <= 190 && data5 >= 200) {
//    //Serial.println("WoooooW");
//    printfun("و");
//  }
//
//  else if (data1 <= 190 && data2 <= 190 && data3 <= 190 && data4 <= 190 && data5 >= 200) {
//    //Serial.println("Oleeeeeeeeeeeeeey");
//    printfun("خ");
//  }
//
//  else if (data1 <= 190 && data2 <= 190 && data3 <= 190 && data4 <= 190 && data5 <= 190) {
//    printfun("ص");
//  }
//
//  else if (data1 >= 200 && data2 >= 200 && data3 >= 200 && data4 >= 200 && data5 < 190) {
//    printfun("ك");
//  }
//
//  //  else if (pitch >=15 && roll >= 50) {
//  //    printfun("ن");
//  //  }
//
//  //      Serial.println(data1);
//  //      Serial.println(data2);
//  //      Serial.println(data3);
//  //      Serial.println(data4);
//  //      Serial.println(data5);
//
//  //delay(800);
  delay((timeStep * 1000) - (millis() - timer));
//
//  //  } // if glove state
//  //  else if(kalima.length() != 0) {
//  //    //Serial.print("Kalima is : ");
//  //    Serial.println("s");
//  //    kalima = "";
//  //  }

}
