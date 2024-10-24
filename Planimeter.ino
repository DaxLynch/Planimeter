
//https://forum.arduino.cc/t/two-cheap-chinese-quadrature-encoders-on-a-nano/342750 This page was a god send for understanding how to run these encoders.
#define encoderLPinA 2  //interrupt pin for one encoder
#define encoderLPinB 4  //standard pin 
#define encoderRPinA 3  //interrupt pin for one encoder
#define encoderRPinB 5  //standard pin 
#include <LiquidCrystal.h> 
LiquidCrystal lcd(6, 7, 8, 9, 10, 11);   

volatile long posL = 0;         // long can hold far more pulses than int; signed to know direction since start.
volatile boolean CWL = true;    // direction if false it is CCWL
volatile long posR = 0;         
volatile boolean CWR = true;    
// The code above establishes variables for the encoders.

float sum =0;
//This is what will be returned
int ThetaOld = 0;
int ThetaNew = 0;
int ThetaDif = 0;
//This thetadif is the signed change in angle, which is essentially the dr in the integral.
const float RLC = 2.523E-7;
//This is a constant which is equal to (mmPerPulse / 10)**2 * (2pi/1200) / 2. This constant ensures that the radius (in pulses) squared * thetadif has units cm^2
const float mmPerPulse = 0.09809;

void setup()
{
 
 lcd.begin(16,2); 
 
 pinMode(encoderLPinA, INPUT_PULLUP);
 pinMode(encoderLPinB, INPUT_PULLUP);
 
 attachInterrupt(digitalPinToInterrupt(encoderLPinA), doEncoderL, CHANGE);   
 pinMode(encoderRPinA, INPUT_PULLUP);
 
 pinMode(encoderRPinB, INPUT_PULLUP);
 attachInterrupt(digitalPinToInterrupt(encoderRPinA), doEncoderR, CHANGE);    
 
 posR = 246;// This value is here because when the planometer is completely retracted, the closest it can be is (246 pulses * mmPerPulse) milimeters.


 pinMode(A5, OUTPUT); // This handles the sum reset button. Very standard
 digitalWrite(A5, LOW);
 pinMode(A3, INPUT_PULLUP);
}

void loop()
{
 lcd.clear(); // Clears the LCD screen 
 lcd.print("Sum > ");
 lcd.print(sum);
 lcd.setCursor(0,1);  
 lcd.print("Rad > ");
 lcd.print(posR * mmPerPulse /10); //This output cmPerPulse 
 ThetaNew = posL;
 
 ThetaDif = ThetaNew - ThetaOld; //calculates dr
 if (ThetaDif) { //If thetadif is 0, meaning no angle has been traversed, don't do anything!
  sum += float(ThetaDif) * sq(posR) * RLC; //Isn't numerical integration so much better than symbolic???
 }

 ThetaOld = ThetaNew;
 
 if (!digitalRead(A3)){
    sum = 0;
    lcd.clear(); // Clears the LCD screen 
    lcd.print("Resetting");
    lcd.setCursor(0,1);  
    lcd.print("Sum");
    delay(750); //This makes it seem like the button press is doing something. :)
 }
 
 delay(10); //If you dont have this here the screen flickers too much
 
}
//The code below interprets the quadrature signal
void doEncoderL()
{
 // determine direction
 CWL = (digitalRead(encoderLPinB) != digitalRead(encoderLPinA));  

 // update Left wheel position
 if (CWL){
  posL++;
 }
 else { 
  posL--;
 }
}

void doEncoderR()
{
 // determine direction
 CWR = (digitalRead(encoderRPinB) != digitalRead(encoderRPinA));  

 // update Right wheel position
 if (CWR)  posR--;
 else posR++;
}
