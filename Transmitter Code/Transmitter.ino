///////////////////////////////////////////// Transmitter ////////////////////////////////////////////////////
#include <RF24.h>
#include <SPI.h>
#include <MPU6050_light.h> 
#include <Wire.h> 

MPU6050 mpu(Wire);

// Analog pins for potentiometers
const int potX = A3; 
const int potY = A6; 
const int potZ = A2; 
const int pot = A1;

// NRF24 radio setup
RF24 radio(7, 8); // CE and CSN pins 
const byte address[] = "00001";

// Button pin assignments
int oldBtn1 = 0;
int btn1; // pin 2

int oldBtn2 = 0;
int btn2; // pin 3

int oldBtn3 = 0;
int btn3; // pin 4

// Data structure for sending
struct Data 
{
  short X, Y, Z, test;
  bool toggle1, toggle2, toggle3;
  float MPU_roll, MPU_pitch, MPU_yaw;
};
Data data; 

void setup()
{
  // Initialize I2C communication and MPU6050
  Wire.begin();
  mpu.begin();   
  mpu.calcOffsets(true, true);   

  // Initialize data toggles
  data.toggle1 = 0;
  data.toggle2 = 0;
  data.toggle3 = 0;

  // Set pin modes for potentiometers and buttons
  pinMode(potX, INPUT);
  pinMode(potY, INPUT);
  pinMode(potZ, INPUT);
  pinMode(pot, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT); 
  pinMode(4, INPUT);

  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Initialize NRF24 radio
  radio.begin(); 
  radio.setChannel(100); // Set channel value between 0-127 if any interference issue pops up
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
}

void loop()
{
  // Update MPU6050 data
  mpu.update();  
  data.MPU_roll = mpu.getAngleY();
  data.MPU_pitch = mpu.getAngleX();
  data.MPU_yaw = mpu.getAngleZ();

  // Default to mode 1 if no modes are active
  if((data.toggle1 + data.toggle2 + data.toggle3) == 0)
  {
    data.toggle1 = 1;
  }
  
  // Mode 1 button toggle
  oldBtn1 = btn1;
  btn1 = digitalRead(2);
  if(btn1 == 0 && oldBtn1 == 1)
  { 
    data.toggle1 = !data.toggle1;
    data.toggle2 = 0;
    data.toggle3 = 0;
  }

  // Mode 2 button toggle
  oldBtn2 = btn2;
  btn2 = digitalRead(3);
  if(btn2 == 0 && oldBtn2 == 1)
  { 
    data.toggle1 = 0;
    data.toggle2 = !data.toggle2;
    data.toggle3 = 0;
  }

  // Mode 3 button toggle
  oldBtn3 = btn3;
  btn3 = digitalRead(4);
  if(btn3 == 0 && oldBtn3 == 1)
  { 
    data.toggle1 = 0;
    data.toggle2 = 0;
    data.toggle3 = !data.toggle3;
  }

  // Debugging: print MPU data
  Serial.print(" MPU_roll = ");
  Serial.print(data.MPU_roll);
  Serial.print(" MPU_pitch = ");
  Serial.print(data.MPU_pitch);
  Serial.println();

  // Read potentiometer values
  data.X = analogRead(potX);
  data.Y = analogRead(potY);
  data.Z = analogRead(potZ);
  data.test = analogRead(pot);

  // Send data via NRF24
  radio.write(&data, sizeof(data)); 
}