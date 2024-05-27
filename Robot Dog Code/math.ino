void math()
{
//Mathematical monstrocity... Enjoy ;)


    //Yaw//
    // Front Right Leg
    FRaddAngle = atan(FRx / FRy); // Calculate the additional angle based on x and y
    FRradius = FRx / sin(FRaddAngle); // Calculate the radius
    FRtAngle = group1Yaw + FRaddAngle; // Add the yaw angle to the additional angle
    FRXout = FRradius * sin(FRtAngle); // Calculate the new x position
    FRYout = FRradius * cos(FRtAngle); // Calculate the new y position

    // Front Left Leg
    FLaddAngle = atan(FLx / FLy); 
    FLradius = FLx / sin(FLaddAngle);
    FLtAngle = group2Yaw + FLaddAngle;
    FLXout = FLradius * sin(FLtAngle);
    FLYout = FLradius * cos(FLtAngle);

    // Back Right Leg
    BRaddAngle = atan(BRx / BRy); 
    BRradius = BRx / sin(BRaddAngle);
    BRtAngle = group2Yaw + BRaddAngle;
    BRXout = BRradius * sin(BRtAngle);
    BRYout = BRradius * cos(BRtAngle);

    // Back Left Leg
    BLaddAngle = atan(BLx / BLy);
    BLradius = BLx / sin(BLaddAngle);
    BLtAngle = group1Yaw + BLaddAngle;
    BLXout = BLradius * sin(BLtAngle);
    BLYout = BLradius * cos(BLtAngle);

    // Adjust leg positions based on the body width and length
    FLXout += bodyWidth;
    FLYout += bodyLength;

    FRXout -= bodyWidth;
    FRYout -= bodyLength;

    BLXout += bodyWidth;
    BLYout -= bodyLength;

    BRXout -= bodyWidth;
    BRYout += bodyLength;

    // Roll//
    // Front Right Leg
    XoffFR = cos(roll) * bodyWidth;
    ZoffFR = sin(roll) * bodyWidth;
    rollZDistFR = FRheight + ZoffFR;
    rollDiffXFR = (FRXout + bodyWidth - XoffFR + shoulderConst);
    rollAdditionalAngleFR = atan(rollDiffXFR / rollZDistFR);
    rollHypFR = rollZDistFR / cos(rollAdditionalAngleFR);
    rollTotalAngleFR = (-roll) + rollAdditionalAngleFR;
    ZoutFR = cos(rollTotalAngleFR) * rollHypFR;
    XoutFR = sin(rollTotalAngleFR) * rollHypFR;

    // Back Right Leg
    XoffBR = cos(roll) * bodyWidth;
    ZoffBR = sin(roll) * bodyWidth;
    rollZDistBR = BRheight + ZoffBR;
    rollDiffXBR = (BRXout + bodyWidth - XoffBR + shoulderConst);
    rollAdditionalAngleBR = atan(rollDiffXBR / rollZDistBR);
    rollHypBR = rollZDistBR / cos(rollAdditionalAngleBR);
    rollTotalAngleBR = (-roll) + rollAdditionalAngleBR;
    ZoutBR = cos(rollTotalAngleBR) * rollHypBR;
    XoutBR = sin(rollTotalAngleBR) * rollHypBR;

    // Front Left Leg
    XoffFL = cos(-roll) * bodyWidth;
    ZoffFL = sin(-roll) * bodyWidth;
    rollZDistFL = FLheight + ZoffFL;
    rollDiffXFL = (FLXout + bodyWidth - XoffFL + shoulderConst);
    rollAdditionalAngleFL = atan(rollDiffXFL / rollZDistFL);
    rollHypFL = rollZDistFL / cos(rollAdditionalAngleFL);
    rollTotalAngleFL = roll + rollAdditionalAngleFL;
    ZoutFL = cos(rollTotalAngleFL) * rollHypFL;
    XoutFL = sin(rollTotalAngleFL) * rollHypFL;

    // Back Left Leg
    XoffBL = cos(-roll) * bodyWidth;
    ZoffBL = sin(-roll) * bodyWidth;
    rollZDistBL = BLheight + ZoffBL;
    rollDiffXBL = (BLXout + bodyWidth - XoffBL + shoulderConst);
    rollAdditionalAngleBL = atan(rollDiffXBL / rollZDistBL);
    rollHypBL = rollZDistBL / cos(rollAdditionalAngleBL);
    rollTotalAngleBL = roll + rollAdditionalAngleBL;
    ZoutBL = cos(rollTotalAngleBL) * rollHypBL;
    XoutBL = sin(rollTotalAngleBL) * rollHypBL;

    // Pitch//
    // Front Right Leg
    oppFR = sin(-pitch) * bodyLength;
    distanceYFR = cos(-pitch) * bodyLength;
    offsetZFR = ZoutFR + oppFR;
    diffYFR = FRYout + bodyLength - distanceYFR;
    additionalAngleFR = atan(diffYFR / offsetZFR);
    legLengthFR = offsetZFR / cos(additionalAngleFR);
    femurAngleFR = pitch + additionalAngleFR;
    outputZFR = cos(femurAngleFR) * legLengthFR;
    outputYFR = sin(femurAngleFR) * legLengthFR;

    // Back Right Leg
    oppBR = sin(pitch) * bodyLength;
    distanceYBR = cos(pitch) * bodyLength; 
    offsetZBR = ZoutBR + oppBR;
    diffYBR = BRYout + bodyLength - distanceYBR;
    additionalAngleBR = atan(diffYBR / offsetZBR);
    legLengthBR = offsetZBR / cos(additionalAngleBR);
    femurAngleBR = pitch + additionalAngleBR;
    outputZBR = cos(femurAngleBR) * legLengthBR;
    outputYBR = sin(femurAngleBR) * legLengthBR;

    // Front Left Leg
    oppFL = sin(-pitch) * bodyLength;
    distanceYFL = cos(-pitch) * bodyLength;
    offsetZFL = ZoutFL + oppFL;
    diffYFL = FLYout + bodyLength - distanceYFL;
    additionalAngleFL = atan(diffYFL / offsetZFL);
    legLengthFL = offsetZFL / cos(additionalAngleFL);
    femurAngleFL = pitch + additionalAngleFL;
    outputZFL = cos(femurAngleFL) * legLengthFL;
    outputYFL = sin(femurAngleFL) * legLengthFL;

    // Back Left Leg
    oppBL = sin(pitch) * bodyLength;
    distanceYBL = cos(pitch) * bodyLength; 
    offsetZBL = ZoutBL + oppBL;
    diffYBL = BLYout + bodyLength - distanceYBL;
    additionalAngleBL = atan(diffYBL / offsetZBL);
    legLengthBL = offsetZBL / cos(additionalAngleBL);
    femurAngleBL = pitch + additionalAngleBL;
    outputZBL = cos(femurAngleBL) * legLengthBL;
    outputYBL = sin(femurAngleBL) * legLengthBL;

    // Side-to-side//
    // Front Right Leg
    FRtheta1 = atan(XoutFR / outputZFR);
    FRhypotenuse = XoutFR / sin(FRtheta1);
    FRZ1 = sqrt(sq(FRhypotenuse) - sq(shoulderConst));
    FRtheta2 = acos(shoulderConst / FRhypotenuse);
    FRSval = (FRtheta1 + FRtheta2);

    // Front Left Leg
    FLtheta1 = atan(XoutFL / outputZFL);
    FLhypotenuse = XoutFL / sin(FLtheta1);
    FLZ1 = sqrt(sq(FLhypotenuse) - sq(shoulderConst));
    FLtheta2 = acos(shoulderConst / FLhypotenuse);
    FLSval = (FLtheta1 + FLtheta2);

    // Back Right Leg
    BRtheta1 = atan(XoutBR / outputZBR);
    BRhypotenuse = XoutBR / sin(BRtheta1);
    BRZ1 = sqrt(sq(BRhypotenuse) - sq(shoulderConst));
    BRtheta2 = acos(shoulderConst / BRhypotenuse);
    BRSval = (BRtheta1 + BRtheta2);

    // Back Left Leg
    BLtheta1 = atan(XoutBL / outputZBL);
    BLhypotenuse = XoutBL / sin(BLtheta1);
    BLZ1 = sqrt(sq(BLhypotenuse) - sq(shoulderConst));
    BLtheta2 = acos(shoulderConst / BLhypotenuse);
    BLSval = (BLtheta1 + BLtheta2);

    // Back-and-forth adjustments
    // Front Right Leg
    FRtheta = atan(outputYFR / FRZ1);
    FRZ2 = FRZ1 / cos(FRtheta);

    // Front Left Leg
    FLtheta = atan(outputYFL / FLZ1);
    FLZ2 = FLZ1 / cos(FLtheta);

    // Back Right Leg
    BRtheta = atan(outputYBR / BRZ1);
    BRZ2 = BRZ1 / cos(BRtheta);

    // Back Left Leg
    BLtheta = atan(outputYBL / BLZ1);
    BLZ2 = BLZ1 / cos(BLtheta);

    // Up-and-down//
    // Front Right Leg
    FRfemurVal = acos((sq(femur) + sq(FRZ2) - sq(tibia)) / (2 * femur * FRZ2));
    FRtibiaVal = acos((sq(tibia) + sq(femur) - sq(FRZ2)) / (2 * tibia * femur));

    // Front Left Leg
    FLfemurVal = acos((sq(femur) + sq(FLZ2) - sq(tibia)) / (2 * femur * FLZ2));
    FLtibiaVal = acos((sq(tibia) + sq(femur) - sq(FLZ2)) / (2 * tibia * femur));

    // Back Right Leg
    BRfemurVal = acos((sq(femur) + sq(BRZ2) - sq(tibia)) / (2 * femur * BRZ2));
    BRtibiaVal = acos((sq(tibia) + sq(femur) - sq(BRZ2)) / (2 * tibia * femur));

    // Back Left Leg
    BLfemurVal = acos((sq(femur) + sq(BLZ2) - sq(tibia)) / (2 * femur * BLZ2));
    BLtibiaVal = acos((sq(tibia) + sq(femur) - sq(BLZ2)) / (2 * tibia * femur));

    // Convert radians to degrees//
    // Front Right Leg
    FRfemurVal = FRfemurVal * 180 / PI;
    FRtibiaVal = FRtibiaVal * 180 / PI;  
    FRtheta = FRtheta * 180 / PI;
    FRSval = FRSval * 180 / PI;

    // Front Left Leg
    FLfemurVal = FLfemurVal * 180 / PI;
    FLtibiaVal = FLtibiaVal * 180 / PI;  
    FLtheta = FLtheta * 180 / PI;
    FLSval = FLSval * 180 / PI;

    // Back Right Leg
    BRfemurVal = BRfemurVal * 180 / PI;
    BRtibiaVal = BRtibiaVal * 180 / PI;  
    BRtheta = BRtheta * 180 / PI;
    BRSval = BRSval * 180 / PI;

    // Back Left Leg
    BLfemurVal = BLfemurVal * 180 / PI;
    BLtibiaVal = BLtibiaVal * 180 / PI;  
    BLtheta = BLtheta * 180 / PI;
    BLSval = BLSval * 180 / PI;

    //Ratio Conversion (my servos are 270 deg)//
    // Front Right Leg
    FRSval = FRSval * 2 / 3;
    FRfemurVal = (120 - FRfemurVal) * 2 / 3;
    FRtibiaVal = FRtibiaVal * 2 / 3;
    FRtheta = FRtheta * 2 / 3;
    FRfemurVal += FRtheta;

    // Front Left Leg
    FLSval = FLSval * 2 / 3;
    FLfemurVal = (120 - FLfemurVal) * 2 / 3;
    FLtibiaVal = FLtibiaVal * 2 / 3;
    FLtheta = FLtheta * 2 / 3;
    FLfemurVal += FLtheta;

    // Back Right Leg
    BRSval = BRSval * 2 / 3;
    BRfemurVal = (120 - BRfemurVal) * 2 / 3;
    BRtibiaVal = BRtibiaVal * 2 / 3;
    BRtheta = BRtheta * 2 / 3;
    BRfemurVal += BRtheta;

    // Back Left Leg
    BLSval = BLSval * 2 / 3;
    BLfemurVal = (120 - BLfemurVal) * 2 / 3;
    BLtibiaVal = BLtibiaVal * 2 / 3;
    BLtheta = BLtheta * 2 / 3;
    BLfemurVal += BLtheta;

    // Map angles to microseconds for servo control
    // Front Right Leg
    FRSval = map(FRSval, 0, 270, 500, 2500);
    FRfemurVal = map(FRfemurVal, 0, 270, 500, 2500);
    FRtibiaVal = map(FRtibiaVal, 0, 270, 500, 2500);
    
    // Front Left Leg
    FLSval = map(FLSval, 0, 270, 2500, 500);
    FLfemurVal = map(FLfemurVal, 0, 270, 2500, 500);
    FLtibiaVal = map(FLtibiaVal, 0, 270, 2500, 500);

    // Back Right Leg
    BRSval = map(BRSval, 0, 270, 500, 2500);
    BRfemurVal = map(BRfemurVal, 0, 270, 500, 2500);
    BRtibiaVal = map(BRtibiaVal, 0, 270, 500, 2500);

    // Back Left Leg
    BLSval = map(BLSval, 0, 270, 2500, 500);
    BLfemurVal = map(BLfemurVal, 0, 270, 2500, 500);
    BLtibiaVal = map(BLtibiaVal, 0, 270, 2500, 500);
}