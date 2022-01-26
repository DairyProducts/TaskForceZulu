#include "vex.h"

using namespace vex;

int Brain_precision = 0, Console_precision = 0, Vision5_objectIndex = 0;

float myVariable;

event message1 = event();
event JoesVizion = event();

// "when I receive JoesVizion" hat block
void onevent_JoesVizion_0() {
  Vision5.takeSnapshot(Vision5__REDD);
  MotorGroup3.spinFor(forward, 740.0, degrees, true);
  Drivetrain.driveFor(forward, 10.0, inches, true);
  Drivetrain.setTurnVelocity(10.0, percent);
  while (!(Vision5.objects[Vision5_objectIndex].width > 240.0 || Vision5.objects[Vision5_objectIndex].centerY > 180.0)) {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Vision5.takeSnapshot(Vision5__REDD);
    if (Vision5.objectCount > 0) {
      if (Vision5.objects[Vision5_objectIndex].centerX > 130.0 && Vision5.objects[Vision5_objectIndex].centerX < 170.0) {
        Brain.Screen.print("forward");
        Drivetrain.driveFor(forward, 2.0, inches, true);
      }
      else {
        if (Vision5.objects[Vision5_objectIndex].centerX > 130.0) {
          Drivetrain.turn(right);
          Brain.Screen.print("right");
        }
        else {
          if (Vision5.objects[Vision5_objectIndex].centerX < 170.0) {
            Drivetrain.turn(left);
            Brain.Screen.print("left");
          }
        }
      }
    }
    else {
      Drivetrain.turn(right);
      Brain.Screen.print("right circle");
    }
    wait(0.1, seconds);
    Vision5.takeSnapshot(Vision5__REDD);
  wait(5, msec);
  }
  Brain.Screen.print("go forward till goal");
  Drivetrain.setTurnVelocity(0.0, percent);
  Drivetrain.driveFor(forward, 20.0, inches, true);
  MotorGroup3.spinFor(reverse, 300.0, degrees, true);
}

// "when started" hat block
int whenStarted1() {
  JoesVizion.broadcast();
  return 0;
}


int main() {
  // register event handlers
  JoesVizion(onevent_JoesVizion_0);

  wait(15, msec);
  whenStarted1();
}
