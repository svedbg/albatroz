#include <Servo.h>

Servo Rservo; // create servo object to control a Right servo 
Servo Lservo; // create servo object to control a Left servo 
Servo ScanHead; // create servo object to control a ScanHead servo 
int HeadPos; // Variable for holding scan head position
int HeadAdj; // Variable for holding scan head changes

void setup() {
    delay(3000); // Chunk of time to let go of the bot
    Rservo.attach(0); // attaches the servo on pin 0 to the servo object 
    Lservo.attach(1); // attaches the servo on pin 1 to the servo object 
    ScanHead.attach(12); // attaches the servo on pin 12 to the servo object 
    Serial.begin(9600); // initialize serial communication at 9600 bits per second:
    HeadPos = 1500; //Start Scan head in the middle
    HeadAdj = 25; // Set the scan speed
}

void loop() {
    if (HeadPos < 1000) // Set the far left position
    {
        HeadAdj = 25; // Determines speed and direction of Scanhead rotation
    }
    if (HeadPos > 1900) // Set the far right position
    {
        HeadAdj = -25; // Determines speed and direction of Scanhead rotation
    }
    HeadPos = HeadPos + HeadAdj; //Set the scan head position
    ScanHead.write(HeadPos); // move the Scan Head

    int senValue0 = analogRead(A0); // read the input on analog pin 0:
    Serial.print("Sen1 = ");
    Serial.println(senValue0);
    int LsenValue = analogRead(A1); // read the input on analog pin 1:
    Serial.print("L Sen = ");
    Serial.println(LsenValue);
    int RsenValue = analogRead(A2); // read the input on analog pin 2:
    Serial.print("R Sen = ");
    Serial.println(RsenValue);

    // Turn to face opponent if to one side
    if (HeadPos < 1200) {
        if (senValue0 > 350) //Set the distance..bigger is closer
        {
            for (int dur = 10; dur >= 2; dur--) // set the distance the robot turns
            {
                Rservo.writeMicroseconds(1000); // sets the servo position to 1ms
                Lservo.writeMicroseconds(1000); // sets the servo position to 1ms
                delay(10);
            }
        }
    }
    // Turn to face opponent if to the other side
    if (HeadPos > 1700) {
        if (senValue0 > 350) //Set the distance..bigger is closer
        {
            for (int dur = 10; dur >= 2; dur--) {
                Rservo.writeMicroseconds(2000); // sets the servo position to 2ms
                Lservo.writeMicroseconds(2000); // sets the servo position to 2ms
                delay(10);
            }
        }
    }

    if (LsenValue < 500) //go forward if on white
    {
        Rservo.writeMicroseconds(1000); // sets the servo position to 1ms
        Lservo.writeMicroseconds(2000); // sets the servo position to 2ms
        delay(10);
    }
    if (RsenValue < 500) //go forward if on white
    {
        Rservo.writeMicroseconds(1000); // sets the servo position to 1ms
        Lservo.writeMicroseconds(2000); // sets the servo position to 2ms
        delay(10);
    }


    if (LsenValue > 500) //turn away if on black
    {
        for (int dur = 50; dur >= 2; dur--) {
            Rservo.writeMicroseconds(2000); // sets the servo position to 1ms
            Lservo.writeMicroseconds(2000); // sets the servo position to 2ms
            delay(10);
        }
    }
    if (RsenValue > 500) //turn away if on black
    {
        for (int dur = 30; dur >= 2; dur--) {
            Rservo.writeMicroseconds(1000); // sets the servo position to 1ms
            Lservo.writeMicroseconds(1000); // sets the servo position to 2ms
            delay(10);
        }
    }

}
