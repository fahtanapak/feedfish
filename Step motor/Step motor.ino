#include <Stepper.h>

#define STEPS_PER_360_DEGREE 2038
const int STEPS_PER_360_DEGREE = 180;
Stepper stepper(STEPS_PER_360_DEGREE, 8, 10, 9, 11); // IN1 IN2 IN3 IN4

void setup() {
  Serial.begin(9600);

  stepper.setSpeed(16); // Unit as RPM (revolutions per minute) MIN 0-16 RPM
}
void loop() {
  Serial.println("CW 360");
  stepper.step(STEPS_PER_360_DEGREE);
  delay(1000);

  Serial.println("CCW 360");
  stepper.step(-STEPS_PER_360_DEGREE);
  delay(1000);

  Serial.println("CW 180");
  stepper.step(STEPS_PER_360_DEGREE/2);
  delay(1000);

  Serial.println("CW 90");
  stepper.step(STEPS_PER_360_DEGREE/4);
  delay(1000);
}