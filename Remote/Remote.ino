#include <RFduinoBLE.h>
#include "Button.h"
#include "MultiColorLed.h"

using namespace RemoteSpotify;

// pin 2 on the RFDuino is used for the Next Button
Button nextBtn(2);
// pin 3 on the RFDuino is used for the Pause Button
Button pauseBtn(3);
// pin 4 on the RFDuino is used for the Prev Button
Button prevBtn(4);

void setup() {
  Serial.begin(9600);

  // this is the data we want to appear in the advertisement
  // (the deviceName length plus the advertisement length must be <= 18 bytes
  RFduinoBLE.advertisementData = "rspotify";
  
  // set the power level to a low value since the distance between the RFduino and iPhone should be minimal
  RFduinoBLE.txPowerLevel = -20;
  
  // start the BLE stack
  Serial.println("Starting BLE stack");
  RFduinoBLE.begin();
  
  // setup pinwake callbacks
  Serial.println("Configuring pinWake callbacks");
  RFduino_pinWakeCallback(nextBtn.GetPin(), HIGH, nextBtnPressed);
  RFduino_pinWakeCallback(prevBtn.GetPin(), HIGH, prevBtnPressed);
  RFduino_pinWakeCallback(pauseBtn.GetPin(), HIGH, pauseBtnPressed);
  
  // turn on red led to indicate no connection
 // led.TurnOn(red);
}

int nextBtnPressed(uint32_t ulPin)
{
  Serial.println("Entered nextBtn pinwake callback");
  if (nextBtn.Debounce(HIGH))
  {
    Serial.println("Sending nextBtn signal");
    RFduinoBLE.send(0);
   // led.BlinkAndRestoreState(300, 0, 1, blue);
    return 1;
  }
  
  return 0;  // don't exit RFduino_ULPDelay
}

int prevBtnPressed(uint32_t ulPin)
{
  Serial.println("Entered prevBtn pinwake callback");
  if (prevBtn.Debounce(HIGH))
  {
    Serial.println("Sending prevBtn signal");
    RFduinoBLE.send(1);
    //led.BlinkAndRestoreState(300, 0, 1, blue);
    return 1;
  }
  
  return 0;  // don't exit RFduino_ULPDelay
}

int pauseBtnPressed(uint32_t ulPin)
{
  Serial.println("Entered prevBtn pinwake callback");
  if (pauseBtn.Debounce(HIGH))
  {
    Serial.println("Sending pauseBtn signal");
    RFduinoBLE.send(2);
    //led.BlinkAndRestoreState(300, 0, 1, blue);
    return 1;
  }
  
  return 0;  // don't exit RFduino_ULPDelay
}

void loop() {
  Serial.println("Entering ULPDelay(INFINITE) in delay_until_button");
  // switch to lower power mode until a button edge wakes us up
  RFduino_ULPDelay(INFINITE);
  Serial.println("Leaving ULPDelay(INFINITE) in delay_until_button");
  
  // clear pin wake when the button is released - this will cause it to enter low power mode the next time through the loop
  if ((RFduino_pinWoke(nextBtn.GetPin()) && nextBtn.Debounce(LOW)) || (RFduino_pinWoke(prevBtn.GetPin()) && prevBtn.Debounce(LOW)))
  {
      RFduino_resetPinWake(nextBtn.GetPin());
      RFduino_resetPinWake(prevBtn.GetPin());
  }
  
  // if any button has been down for over 3 seconds, shut down
  if (nextBtn.GetHoldDuration() > 3000 || pauseBtn.GetHoldDuration() > 3000 || prevBtn.GetHoldDuration() > 3000)
      shutdown();
}

void RFduinoBLE_onConnect() {
 // led.TurnOn(green);
}

void RFduinoBLE_onDisconnect()
{
 // led.TurnOn(red);
}

void shutdown()
{
  // blink the red led to indicate shutdown
  // led.Blink(200, 200, 5, red);
  
  // this is so that the button release doesn't wake us up again
  delay(3000);
  RFduino_systemOff();
}

