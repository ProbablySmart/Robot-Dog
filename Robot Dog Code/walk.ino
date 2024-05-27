void walk()
{
    static int prev_sine_value = 0;
    static float phase = 0.0; // start from 0 and I don't want it to reset
    float increment = 2 * PI * frequency * resolution; // Calculate the phase increment for each step based on frequency and resolution
    phase += increment;// Increment phase by the calculated increment


    // optional: limit, so it doesn't go past 2PI (useful for timing)
    if (phase >= 2 * PI) 
    {
        phase -= 2 * PI;
    }
// Calculate the sine value with the given amplitude
    sine_value = amplitude * sin(phase); 
    sine_value += amplitude;


//step sequence: 0 --> 1 --> 2 --> 3 --> 0 --> 1 --> 2 --> 3 --> etc.
    if (sine_value > prev_sine_value && stage == 0) 
    {
        stage = 1; 
    }
    else if (sine_value < prev_sine_value && stage == 1) 
    {
        stage = 2; 
    } 
    else if (sine_value > prev_sine_value && stage == 2) 
    {
        stage = 3; 
    } 
    else if (sine_value < prev_sine_value && stage == 3) 
    {
        stage = 0; 
    } 



    prev_sine_value = sine_value;//updates previous sine val from current 


//leg stages: set heights & positions for leg groups to create a walking gait

    //stage 0
    if (stage == 0)
    {
        FRheight = BLheight = 5.5;
        FLheight = BRheight = 4;
        FRy = BLy = .01;
        FRx = BLx = .01;
        FLy = BRy = walkValY + .01;
        FLx = BRx = walkValX + .01;
        group1Yaw = yaw;
        group2Yaw = .001;
    }

    //stage 1
    if (stage == 1)
    {
        FRheight = BLheight = 4;
        FLheight = BRheight = 5.5;
        FRy = BLy = .01;
        FRx = BLx = .01;
        FLy = BRy = walkValY + .01;
        FLx = BRx = walkValX + .01;
        group1Yaw = yaw;
        group2Yaw = .001;
    }
    //stage 2
    if (stage == 2)
    {
        FRheight = BLheight = 4;
        FLheight = BRheight = 5.5;
        FRy = BLy = walkValY +  .01;
        FRx = BLx = walkValX + .01;
        FLy = BRy =  .01;
        FLx = BRx =  .01;
        group2Yaw = yaw;
        group1Yaw = .001;
    }
    //stage 3
    if (stage == 3)
    {
        FRheight = BLheight = 5.5;
        FLheight = BRheight = 4;
        FRy = BLy = walkValY +  .01;
        FRx = BLx = walkValX + .01;
        FLy = BRy =  .01;
        FLx = BRx =  .01;
        group2Yaw = yaw;
        group1Yaw = .001;
    }
}