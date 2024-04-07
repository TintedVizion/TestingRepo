
#include "IRremote.h"
#include "IR.h"
#define ledRed (9)

IRrecv irrecv(RECEIVER);   // Create instance of 'irrecv'
decode_results results;    // Create instance of 'decode_results'
bool ledState;             // Track the on/off state of the LED
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode");
  irrecv.enableIRIn();

  // Set up LED
  ledState = false;
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, ledState);
  pinMode(ledRed, OUTPUT);
}


void loop() {
  // put your main code here, to run repeatedly:
  int tmpValue;
  if (irrecv.decode(&results))  // have we received an IR signal?
  {
    for (int i = 0; i < 23; i++)
    {
      if ((keyValue[i] == results.value) && (i<KEY_NUM))
      {
        Serial.println(keyBuf[i]);
        tmpValue = results.value;

        // Respond to POWER button
        if (keyValue[i] == KEY_POWER) {
          ledState = !ledState; 
          digitalWrite(LED_BUILTIN, ledState);
        }
      }
      else if(REPEAT==i)
      {
        results.value = tmpValue;
      }
    }
    irrecv.resume();  // Receive the next value.
  }
}
