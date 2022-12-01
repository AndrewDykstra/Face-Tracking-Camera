#include<Servo.h>

Servo servoVer; //Vertical Servo
Servo servoHor; //Horizontal Servo

int x;
int y;

int prevX;
int prevY;
int servoX = 90;
int servoY = 90;

void setup()
{
  Serial.begin(9600);
  servoVer.attach(5); //Attach Vertical Servo to Pin 5
  servoHor.attach(6); //Attach Horizontal Servo to Pin 6
  servoVer.write(servoY);
  servoHor.write(servoX);
}

void Pos()
{
  if(prevX != x || prevY != y)
  {
    //tune this range to generate map
    int deltaX = map(x, 500, 0, -15, 15); 
    //tune this range to generate map
    int deltaY = map(y, 0, 450, 15, -15);

    servoX += deltaX;
    servoY += deltaY;

    servoX = min(servoX, 160);
    servoX = max(servoX, 20);
    servoY = min(servoY, 150);
    servoY = max(servoY, 90);
    
    servoHor.write(servoX);
    servoVer.write(servoY);

    prevX = x;
    prevY = y;
  }
}

void loop()
{
  if(Serial.available() > 0)
  {
    if(Serial.read() == 'X')
    {
      x = Serial.parseInt();
      if(Serial.read() == 'Y')
      {
        y = Serial.parseInt();
       Pos();
      }
    }
    while(Serial.available() > 0)
    {
      Serial.read();
    }
  }
}
