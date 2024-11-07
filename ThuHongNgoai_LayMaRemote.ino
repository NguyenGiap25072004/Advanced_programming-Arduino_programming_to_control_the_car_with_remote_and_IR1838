#include<IRremote.h>
const int chanRemote=8;
IRrecv irrecv(chanRemote);
decode_results results;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(irrecv.decode(&results))
  {
    Serial.println(results.value, HEX);
    delay(200);
    irrecv.resume();
  }
}
