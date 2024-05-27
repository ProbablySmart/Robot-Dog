/////////////////////////////////////////////Receiver////////////////////////////////////////////////////
#include <Servo.h>
#include <RF24.h>
#include <SPI.h>
#include <MPU6050_light.h> 
#include <Wire.h> 

MPU6050 mpu(Wire);




//Servo Init
Servo BLshoulder, BLfemur, BLtibia;
Servo BRshoulder, BRfemur, BRtibia;
Servo FLshoulder, FLfemur, FLtibia;
Servo FRshoulder, FRfemur, FRtibia;

//NRF24/Radio
RF24 radio(7, 8);  //CE and CSN pins
const byte address[] = "00001";

//Leg Measurements
const float femur = 3.45;  //b
const float tibia = 4.1;  //a
const float shoulderConst = 1.666;

//NRF24 Data
struct Data 
{
  short X, Y, Z,test;
  bool toggle1, toggle2, toggle3;
  float MPU_roll, MPU_pitch, MPU_yaw;

};
Data data;

// walking sequence values
const int amplitude = 100; 
const float sampling = 1000.0;
const float resolution = 1.0 / sampling; // sampling (data collection) (time / how many times you want to read)
const float frequency = 70; //frequency of the sine wave in Hz
int sine_value;
int stage;

const int shoulderWalk = 0;

//Terminology:  b/B = Back  f/F = Front  l/L = Left  r/R = Right S = Side  x/X = x axis y/Y = y axis z/Z = z axis

float y, x, X, z;// Axis values for individual legs


//Front Right Leg
float FRtibiaVal, FRfemurVal, FRheight, FRy;
float FRhypotenuse, FRtheta1, FRtheta2, FRZ1, FRx, FRSval;
float FRZ2, FRnewShoulder, FRtheta;

//Back Right Leg
float BRtibiaVal, BRfemurVal, BRheight, BRy;
float BRhypotenuse, BRtheta1, BRtheta2, BRZ1, BRx, BRSval;
float BRZ2, BRnewShoulder, BRtheta;

//Front Left Leg
float FLtibiaVal, FLfemurVal, FLheight, FLy;
float FLhypotenuse, FLtheta1, FLtheta2, FLZ1, FLx, FLSval;
float FLZ2, FLnewShouldeL, FLtheta;

//Back Left Leg
float BLtibiaVal, BLfemurVal, BLheight, BLy;
float BLhypotenuse, BLtheta1, BLtheta2, BLZ1, BLx, BLSval;
float BLZ2, BLnewShouldeL, BLtheta;


//axis values for individual legs 
float frheight, flheight, brheight, blheight, fry, fly, bry, bly, frx, flx, brx, blx;

float walkValY, walkValX;

//yaw calc values
float yaw;
float group1Yaw, group2Yaw;
float FRaddAngle, FRradius, FRtAngle, FRXout, FRYout;
float FLaddAngle, FLradius, FLtAngle, FLXout, FLYout;
float BRaddAngle, BRradius, BRtAngle, BRXout, BRYout;
float BLaddAngle, BLradius, BLtAngle, BLXout, BLYout;

//pitch calc values
float pitch;
float bodyLength = 3.75;
float oppFR, additionalAngleFR, offsetZFR, outputZFR, outputYFR, oppBR, additionalAngleBR, offsetZBR, outputZBR, outputYBR;
float oppFL, additionalAngleFL, offsetZFL, outputZFL, outputYFL, oppBL, additionalAngleBL, offsetZBL, outputZBL, outputYBL;
float diffYFR, diffYBR, distanceYFR, distanceYBR, legLengthFR, legLengthBR, femurAngleFR, femurAngleBR;
float diffYFL, diffYBL, distanceYFL, distanceYBL, legLengthFL, legLengthBL, femurAngleFL, femurAngleBL;

//roll calc values
float roll;
float bodyWidth = 1.946;
float XoffFR, ZoffFR, rollHypFR, rollAdditionalAngleFR,rollTotalAngleFR, ZoutFR, XoutFR, rollZDistFR, rollDiffXFR;
float XoffBR, ZoffBR, rollHypBR, rollAdditionalAngleBR,rollTotalAngleBR, ZoutBR, XoutBR, rollZDistBR, rollDiffXBR; 
float XoffFL, ZoffFL, rollHypFL, rollAdditionalAngleFL,rollTotalAngleFL, ZoutFL, XoutFL, rollZDistFL, rollDiffXFL;  
float XoffBL, ZoffBL, rollHypBL, rollAdditionalAngleBL,rollTotalAngleBL, ZoutBL, XoutBL, rollZDistBL, rollDiffXBL; 

//smoothed values 
  //shoulders
  float smoothedBLS, smoothedBRS, smoothedFRS, smoothedFLS;
  float previousBLS , previousBRS, previousFRS, previousFLS;

  //femurs
  float smoothedBLfemur, smoothedBRfemur, smoothedFRfemur, smoothedFLfemur;
  float previousBLfemur, previousBRfemur, previousFRfemur, previousFLfemur;

  //tibias
  float smoothedBLtibia, smoothedBRtibia, smoothedFRtibia, smoothedFLtibia;
  float previousBLtibia, previousBRtibia, previousFRtibia, previousFLtibia;

// map function that allows decimals
float mapFloat(float x, float fromLow, float fromHigh, float toLow, float toHigh) 
{
  return (x - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}

void setup() 
{
  Serial.begin(115200);//debug console


   // Servo Pin Assignments
  FLshoulder.attach(34,500,2500);
  FLfemur.attach(32,500,2500);
  FLtibia.attach(30,500,2500);

  FRshoulder.attach(36,500,2500);
  FRfemur.attach(38,500,2500);
  FRtibia.attach(40,500,2500);


  BLshoulder.attach(35,500,2500);
  BLfemur.attach(33,500,2500);
  BLtibia.attach(31,500,2500);

  BRshoulder.attach(37,500,2500);
  BRfemur.attach(39,500,2500);
  BRtibia.attach(41,500,2500);

    //start servos at default position
    BLshoulder.writeMicroseconds(1930-50);
    BLfemur.writeMicroseconds(2182+10);
    BLtibia.writeMicroseconds(2093+20);

    FLshoulder.writeMicroseconds(1960-80); 
    FLfemur.writeMicroseconds(2182+50);
    FLtibia.writeMicroseconds(2093+120);


    BRshoulder.writeMicroseconds(1040+20);
    BRfemur.writeMicroseconds(818+15);
    BRtibia.writeMicroseconds(907-30);     


    FRshoulder.writeMicroseconds(1040-30);
    FRfemur.writeMicroseconds(818+15);
    FRtibia.writeMicroseconds(907+30);


  
  Wire.begin();
  mpu.begin();   
  mpu.calcOffsets(true, true);     

  // Radio startup
  radio.begin();
  radio.setChannel(100);// set channel value between 0-127 if any interference issue pops up
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();


}

void loop() 
{
  // Update math calculations (the function math() should be defined and used properly)
  math();

  if (radio.available()) 
  {
    radio.read(&data, sizeof(data));

    if (data.toggle1 == 1)
    {
      // IK Mode: Direct control via joystick

      // Map joystick values to desired ranges
      x = mapFloat(data.X, 0, 1023, 1.66, -1.66); 
      y = mapFloat(data.Y, 0.0, 1023.0, -3.0, 3.0);
      z = mapFloat(data.Z, 0.0, 1023.0, 7.0, 1.0);

      // Disable pitch, roll, and yaw by setting them to small values
      pitch = .001;
      roll = .001;
      group1Yaw = group2Yaw = yaw = .001;

      // Set all leg heights to the same z value
      FRheight = FLheight = BRheight = BLheight = z;

      // Apply height offsets specific to the robot's design
      BLheight += .5;
      FRheight += .5;

      // Set all leg y positions to the same y value
      FRy = FLy = BRy = BLy = y;

      // Apply y offsets specific to the robot's design
      BLy += 1.25;
      BRy += 1.5;
      FLy += .5;
      FRy += 1;
      
      // Set all leg x positions to the same x value
      FRx = FLx = BRx = BLx = x;

      // Flip directions for x values for front and back legs
      FRx = -x;
      FLx = x;
      BRx = -x;
      BLx = x;
    }

    if (data.toggle2 == 1)
    {
      // Update leg positions based on joystick and sensor data

      // Map joystick values to desired ranges
      x = mapFloat(data.X, 0, 1023, 1.66, -1.66); 
      y = mapFloat(data.Y, 0.0, 1023.0, -3.0, 3.0);
      z = mapFloat(data.Z, 0.0, 1023.0, 7.0, 1.0);

      // Map yaw value from sensor data
      yaw = mapFloat(data.test, 0.0, 1023.0, -1.0, 1.0);

      // Convert roll and pitch from degrees to radians
      roll = data.MPU_roll * PI / 180 * -1;
      pitch = data.MPU_pitch * PI / 180 * -1;
      yaw = mapFloat(data.test, 0.0, 1030.0, 1, -1);

      // Update yaw values for both leg groups
      group1Yaw = group2Yaw = yaw; 

      // Set all leg heights to the same z value
      FRheight = FLheight = BRheight = BLheight = z;
      
      // Apply height offsets specific to the robot's design
      BLheight += .5;
      FRheight += .5;

      // Set all leg y positions to the same y value
      FRy = FLy = BRy = BLy = y;

      // Apply y offsets specific to the robot's design
      BLy += 1.25;
      BRy += 1.5;
      FLy += .5;
      FRy += 1;

      // Set all leg x positions to the same x value
      FRx = FLx = BRx = BLx = x;

      // Flip directions for x values for front and back legs
      FRx = -x;
      FLx = x;
      BRx = -x;
      BLx = x;
    }

    if (data.toggle3 == 1) 
    { 
      // Walking mode
      walk();

      // Map joystick values to desired ranges
      walkValX = mapFloat(data.X, 0, 1023, 1.66, -1.66); 
      walkValY = mapFloat(data.Y, 0, 1023, 3, -3);

      // Map yaw value from sensor data
      yaw = mapFloat(data.test, 0.0, 1030.0, 1, -1);

      // Flip directions for x values for front and back legs
      FRx = -FRx;
      FLx = FLx;
      BRx = -BRx;
      BLx = BLx;

      // Apply y offsets specific to the robot's design
      BLy += 1.25;
      BRy += 1.5;
      FLy += .5;
      FRy += 1; 
    }

    // Ensure x and y axis values are not zero to avoid division by zero errors
    if (BRx == 0.0) BRx = .01;
    if (BLx == 0.0) BLx = .01;
    if (FRx == 0.0) FRx = .01;
    if (FLx == 0.0) FLx = .01;
    if (y == 0) y = 0.01;

    // Write smoothed values to servos
    smoothedFRS = (FRSval * .4) + (previousFRS * .6);
    previousFRS = smoothedFRS;
    smoothedFLS = (FLSval * .4) + (previousFLS * .6);
    previousFLS = smoothedFLS;
    smoothedBRS = (BRSval * .4) + (previousBRS * .6);
    previousBRS = smoothedBRS;
    smoothedBLS = (BLSval * .4) + (previousBLS * .6);
    previousBLS = smoothedBLS;

    smoothedFRfemur = (FRfemurVal * .4) + (previousFRfemur * .6);
    previousFRfemur = smoothedFRfemur;
    smoothedFLfemur = (FLfemurVal * .4) + (previousFLfemur * .6);
    previousFLfemur = smoothedFLfemur;
    smoothedBRfemur = (BRfemurVal * .4) + (previousBRfemur * .6);
    previousBRfemur = smoothedBRfemur;
    smoothedBLfemur = (BLfemurVal * .4) + (previousBLfemur * .6);
    previousBLfemur = smoothedBLfemur;

    smoothedFRtibia = (FRtibiaVal * .4) + (previousFRtibia * .6);
    previousFRtibia = smoothedFRtibia;
    smoothedFLtibia = (FLtibiaVal * .4) + (previousFLtibia * .6);
    previousFLtibia = smoothedFLtibia;
    smoothedBRtibia = (BRtibiaVal * .4) + (previousBRtibia * .6);
    previousBRtibia = smoothedBRtibia;
    smoothedBLtibia = (BLtibiaVal * .4) + (previousBLtibia * .6);
    previousBLtibia = smoothedBLtibia;

    BLshoulder.writeMicroseconds(BLSval - 150);
    BLfemur.writeMicroseconds(BLfemurVal - 30);
    BLtibia.writeMicroseconds(BLtibiaVal - 50);

    FLshoulder.writeMicroseconds(FLSval - 150); 
    FLfemur.writeMicroseconds(FLfemurVal - 20);
    FLtibia.writeMicroseconds(FLtibiaVal + 50);

    BRshoulder.writeMicroseconds(BRSval + 100);
    BRfemur.writeMicroseconds(BRfemurVal + 20);
    BRtibia.writeMicroseconds(BRtibiaVal + 50);

    FRshoulder.writeMicroseconds(FRSval + 100);
    FRfemur.writeMicroseconds(FRfemurVal + 20);
    FRtibia.writeMicroseconds(FRtibiaVal + 50);

    // Debug output to Serial Monitor
    Serial.print("z: "); Serial.print(z); Serial.print(", ");
    Serial.print("walkValY: "); Serial.print(walkValY); Serial.print(", ");
    Serial.print("walkValX: "); Serial.print(walkValX); Serial.print(", ");
    Serial.print("FRx: "); Serial.print(FRx); Serial.print(", ");  
    Serial.print("FRy: "); Serial.print(FRy); Serial.print(", ");    
    Serial.print("stage: "); Serial.print(stage); Serial.print(", ");
    Serial.println();

    // Update leg positions based on body dimensions
    FLx -= bodyWidth;
    FLy -= bodyLength;

    FRx += bodyWidth;
    FRy += bodyLength;

    BLx -= bodyWidth;
    BLy += bodyLength;

    BRx += bodyWidth;
    BRy -= bodyLength;
  }
}