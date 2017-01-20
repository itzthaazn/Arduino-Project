//Pins
#define ledPin 13
#define ledYellow 29
#define ledRed 31
#define ledGreen 27
#define servoPin 44


//Sensor detector Pins
#define trigX 23
#define echoX 22
#define trigY 21
#define echoY 20

int rangeX = 5;
int rangeY = 5;
const int yButtonPin = 26;
const int xButtonPin = 28;
int xButtonState = 0;
int yButtonState = 0;
//Lib for Servo
#include <Servo.h>
//Lib for Stepper
#include <Stepper.h>
//internal Storage
#include<EEPROM.h>

const int stepsPerRevolution = 200;
const int stepsPerRevolution2 = 200;

//Stepper Motor X and Y
Stepper MotorX(stepsPerRevolution, 46, 48, 50, 52);
Stepper MotorY(stepsPerRevolution2, 47, 49, 51, 53);

//Servo Motor for Pump
Servo servo;
int myArray[10];

void setup() {

  //Setting the speed of the motor
  MotorX.setSpeed(60);
  MotorY.setSpeed(60);
  //Connecting to bluetooth
  Serial.begin(115200);
  //Setting outputs
  pinMode(ledPin, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(servoPin, OUTPUT);
  servo.attach(servoPin);


}

void XButton() {
  pinMode(xButtonPin, INPUT);
  xButtonState = digitalRead(xButtonPin);

do
{
      MoveLeft();
      xButtonState = digitalRead(xButtonPin);
}while(xButtonState == LOW);
    Serial.println("X is at initial");
}

void YButton() {
  pinMode(yButtonPin, INPUT);
  xButtonState = digitalRead(yButtonPin);

do
{
      MoveUp();
      yButtonState = digitalRead(yButtonPin);
}while(yButtonState == LOW);
    Serial.println("Y is at initial");

}


void LedOn() {
  Serial.println("LED ON");
  digitalWrite(ledPin, HIGH);
  delay(500);
}


// Detecting if theY Motor is at initial point
int ReturnInitial() {

  int x = XSensor();
  int y = YSensor();
  do {
    x = XSensor();
    MoveLeft();

  } while (x > rangeX );

  do {
    y = YSensor();
    MoveUp();

  } while (y > rangeY );
}




int XSensor() {

  pinMode(trigX, OUTPUT);
  pinMode(echoX, INPUT);

  int duration , distance;
  digitalWrite(trigX, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigX, LOW);

  //measure time
  duration = pulseIn(echoX, HIGH);
  distance = (duration / 2) / 29.1 ; // find the cm

  Serial.println("Distance X cm :");
  Serial.println(distance);

  return distance;
}

// Detecting if Y motor is at initial point
int YSensor() {
  pinMode(trigY, OUTPUT);
  pinMode(echoY, INPUT);

  int durationY , distanceY;
  digitalWrite(trigY, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigY, LOW);

  //measure time
  durationY = pulseIn(echoY, HIGH);
  // find the cm
  distanceY = (durationY / 2) / 29.1 ;

  Serial.println("Distance Y cm :");
  Serial.println(distanceY);

  return distanceY;
}

void LedOff() {
  Serial.println("LED OFF");
  digitalWrite(ledPin, LOW);
  delay(500);
}

void LedYellowOn() {
  Serial.println("LED YELLOW On");
  digitalWrite(ledYellow, HIGH);
  delay(500);
}

void LedYellowOff() {
  Serial.println("LED RED Off");
  digitalWrite(ledYellow, LOW);
  delay(500);
}

void LedRedOn() {
  Serial.println("LED RED Off");
  digitalWrite(ledRed, HIGH);
  delay(500);
}

void LedRedOff() {
  Serial.println("LED RED Off");
  digitalWrite(ledRed, LOW);
  delay(500);
}

void LedGreenOn() {
  Serial.println("LED Green Off");
  digitalWrite(ledGreen, HIGH);
  delay(500);
}

void LedGreenOff() {
  Serial.println("LED Green Off");
  digitalWrite(ledGreen, LOW);
  delay(500);
}

void MoveLeft() {
  Serial.println("Move Left");
  MotorX.step(-stepsPerRevolution);
  delay(500);
}

void MoveRight() {

  Serial.println("Move Right");
  MotorX.step(stepsPerRevolution);
  delay(500);

}
void MoveUp() {

  Serial.println("Move Up");
  MotorY.step(-stepsPerRevolution);
  delay(500);


}
void MoveDown() {
  Serial.println("Move Down");
  MotorY.step(stepsPerRevolution);
  delay(500);
}

void MoveBackX() {
  int right = 16;
  for (right = 16; right >= 0; right -= 1) {
    MoveLeft();
  }
}

void MoveBackY() {
  int down = 16;
  for (down = 16; down >= 0; down -= 1) {
    MoveUp();
  }
}

void Icing() {
  int pos = 0;

  LedRedOff();
  LedGreenOn();
    Serial.println("ICING OPEN");
  for (pos = 0; pos <= 380; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
  
    servo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
    
  }

  LedGreenOff();
  LedRedOn();


}

void loop() {

  if (Serial.available())  {
    char read = Serial.read();


    switch (read) {
      case 'a':
        Serial.write("LED ON");
        LedOn();
        break;
      case 'b':
        Serial.write("LED OFF");
        LedOff();
        break;

      case 'c':
        Serial.write("Moving Right");
        Serial.println("Moving Right");
        MoveRight();

        break;

      case 'd':
        Serial.write("Moving Left");
        Serial.println("Moving Left");
        MoveLeft();
        break;

      case 'e':
        Serial.write("Moving UP");
        Serial.println("Moving Up");
        MoveUp();

        break;

      case 'f':
        Serial.write("Moving Down");
        Serial.println("Moving Down");
        MoveDown();

        break;

      case'g':
        Icing();

        break;

      case'h':
        LedYellowOn();
        delay(250);
        LedRedOn();
        delay(250);
        LedGreenOn();
        break;

      case'i':
        LedYellowOff();
        delay(250);
        LedRedOff();
        delay(250);
        LedGreenOff();
        break;

      case'j':
        MoveBackX();
        MoveBackY();
        break;

      case'k':
        YSensor();
        delay(500);
        XSensor();
        break;

      case'l':

        ReturnInitial();
        break;

      case'm':
      XButton();
      YButton();
      break;
      case 'n':
        {
          //XButton();
          //YButton();



      int i;
for (i = 0; i < 5; i = i + 1) {
  Serial.println(myArray[i]);
}
     // myArray[9]    contains 11
     // myArray[10]   is invalid and contains random information (other memory address)
          

        if (serial.read(x)){
          
        }
          
          word image2[3] = {
            0b000,
            0b000,
            0b111,

          };
          for (int row1 = 0; row1 < 3; row1++) {

            LedOff(); // icing off
            for (int column1 = 0; column1 < 3; column1++) {
              boolean pixel1 = bitRead(image2[row1], column1);

              if (pixel1 == 1) {

                //move X-Axis forward 5 steps for each bit in the array
                MoveRight();

                delay(500);
                LedOn();// icing on
                delay(250);
                Serial.write("Icing On");
                Icing();
                delay(1000);
                Serial.write("Icing Off");


              }
              else {

                LedOff(); // icing off

                //move X-Axis forward 5 steps for each bit in the array
                MoveRight();
                delay(15);

              }
            }

            LedOff(); // icing

            //Move back to initial X
            //MoveBackX();
            MoveLeft();
            MoveLeft();
            MoveLeft();



            //Position Y-Axis for next row
            MoveDown();
            delay(15);
          }

          LedOff(); // icing off
          //Moves back to inititial when printing completed.
          XButton();
          YButton();


        }
        break;



      case 'z':

        MoveBackX();
        MoveBackY();
        word image[16] = {
          0b0000001110000000,
          0b0010011111000100,
          0b0010001110000100,
          0b0010000100000100,
          0b0011111111111100,
          0b0000011111000000,
          0b0000011111000000,
          0b0000001110000000,
          0b0000011111000000,
          0b0000011111000000,
          0b0000110001100000,
          0b0001100000110000,
          0b0001100000110000,
          0b0011100000111000,
          0b0011100000111000,
          0b1111111111111111
        };

        for (int row = 0; row < 16; row++) {

          LedOff(); // icing off

          for (int column = 0; column < 16; column++) {
            boolean pixel = bitRead(image[row], column);

            if (pixel == 1) {

              //move X-Axis forward 5 steps for each bit in the array

              MoveRight();
              delay(500);
              LedOn();// icing on
              delay(250);
              Serial.write("Icing On");
              Icing();
              delay(1000);
              Serial.write("Icing Off");

              //stepperX.step(10);
              //x_inc = x_inc + 10;

            }
            else {

              LedOff(); // icing off

              //move X-Axis forward 5 steps for each bit in the array
              MoveRight();
              delay(15);

            }
          }

          LedOff(); // icing

          //Move back to initial X
          MoveBackX();

          //Position Y-Axis for next row
          MoveDown();
          delay(15);
        }

        LedOff(); // icing off
        //Moves back to inititial when printing completed.
        MoveBackX();
        MoveBackY();
        break;

        //Endless Loop
        while (1) {
          loop();

        }
    }
  }
}





