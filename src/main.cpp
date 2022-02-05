/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Derek L                                                   */
/*    Created:      Tue Nov 30 2021                                           */
/*    Description:  TF Zulu Lite                                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// elev_hook            motor         1   
// belt                 motor         5             
// Drivetrain           drivetrain    2, 12           
// arms                 motor_group   3, 13           
// elevator             motor_group   9, 14 
// Vision5              vision        20          
// ---- END VEXCODE CONFIGURED DEVICES ----

/*
Controller1: controller
arms: lift arms on front of robot
elevator: lifter for arms_on goals onto lever
elev_hook: hook on elevator
belt: donut processing treads
*/


#include "vex.h"
using namespace vex;
using signature = vision::signature;
using code = vision::code;
int Brain_precision = 0, Console_precision = 0, Vision5_objectIndex = 0;
vision::signature Vision5__REDD = vision::signature (1, 1955, 2269, 2112,-3453, -3027, -3240,3, 0);
vision Vision5 = vision (PORT20, 40, Vision5__REDD);
event JoesVizion = event();

// ehook_on: toggle variable for elev_hook
bool ehook_on = false;
// arms_on: toggle variable for arms
bool arms_on = false;
// elev_on: toggle variable for elevator
bool elev_on = false;
//belt_on: toggle variable for belt
bool belt_on = false;

int whenStarted() {
  JoesVizion.broadcast();
  return 0;
}
void onevent_JoesVizion_0() {
  Vision5.takeSnapshot(Vision5__REDD);
  arms.spinFor(forward, 740.0, degrees, true);
  Drivetrain.driveFor(reverse, 10.0, inches, true);
  Drivetrain.setTurnVelocity(10.0, percent);
  while (!(Vision5.objects[Vision5_objectIndex].width > 240.0 || Vision5.objects[Vision5_objectIndex].centerY > 180.0)) {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Vision5.takeSnapshot(Vision5__REDD);
    if (Vision5.objectCount > 0) {
      if (Vision5.objects[Vision5_objectIndex].centerX > 130.0 && Vision5.objects[Vision5_objectIndex].centerX < 170.0) {
        Brain.Screen.print("forward");
        Drivetrain.driveFor(reverse, 2.0, inches, true);
      }
      else {
        if (Vision5.objects[Vision5_objectIndex].centerX > 130.0) {
          Drivetrain.turn(left);
          Brain.Screen.print("right");
        }
        else {
          if (Vision5.objects[Vision5_objectIndex].centerX < 170.0) {
            Drivetrain.turn(right);
            Brain.Screen.print("left");
          }
        }
      }
    }
    else {
      Drivetrain.turn(left);
      Brain.Screen.print("right circle");
    }
    wait(0.1, seconds);
    Vision5.takeSnapshot(Vision5__REDD);
  wait(5, msec);
  }
  Brain.Screen.print("go forward till goal");
  Drivetrain.setTurnVelocity(0.0, percent);
  Drivetrain.driveFor(reverse, 20.0, inches, true);
  arms.spinFor(reverse, 300.0, degrees, true);
}

// toggle elev_hook between lock and unlock based on ehook_on
void togl_ehook(){
  elev_hook.stop();
  elev_hook.setVelocity(80, percent);
  if (ehook_on == false){
    elev_hook.spin(forward);
    ehook_on = true;
  }
  else{
    elev_hook.spin(reverse);
    wait(0.4, seconds);
    elev_hook.stop();
    ehook_on = false;
  }
}



// toggle arms between positions based on arms_on
void togl_arms(){
  arms.setVelocity(100, percent);
  if (arms_on == true){
    arms.spinFor(forward, 350, degrees);
    arms_on = false;
  } else{
    arms.spinFor(reverse, 350, degrees);
    arms_on = true;
  }
}

// moves arms up when L1 is pressed
int lift_arms() {
  if (Controller1.ButtonL1.pressing()) {
    arms.spin(forward);
  }
  return 0;
}


// spin arms to the perfect angle for the goal to receive the rings from the belt
void align_arms() {
  arms.spinFor(reverse, 237.5, degrees);
}

// toggle elevator between unextended and extended positions based on arms_on
void togl_elev(){
  elevator.setVelocity(100, percent);
  if (elev_on == true){
    elevator.spinFor(forward, 20, degrees);
    elev_on = false;
  } else{
    elevator.spinFor(reverse, 20, degrees);
    elev_on = true;
  }
}

// toggles belt between spinning fore or back based on belt_on
void togl_belt() {
  if (belt_on){
    belt.stop();
    belt_on = false;
  } else{
    belt.setVelocity(100, percent);
    belt.spin(reverse);
    belt_on = true;
  }

}



// autonmous
void auton(){
  Drivetrain.setDriveVelocity(100, percent);
  Drivetrain.driveFor(reverse, 50, inches);
  arms.spinFor(reverse, 350, degrees);
  Drivetrain.turnFor(right, 120, degrees);
  Drivetrain.driveFor(reverse, 26, inches);
  arms.spinFor(forward, 350, degrees);
  Drivetrain.driveFor(forward, 9, inches);
  Drivetrain.turnFor(right, 120, degrees);

}

// main
int main() {
  vexcodeInit();
  arms.setVelocity(40, percent);
  elevator.setVelocity(85, percent);
  Drivetrain.setDriveVelocity(100, percent);
  // auto
  Controller1.ButtonX.pressed(align_arms);
  Controller1.ButtonY.pressed(togl_belt);
  Controller1.ButtonB.pressed(onevent_JoesVizion_0);
  // driver control
      // commented out code: see Note A on line 155

  Controller1.ButtonA.pressed(togl_ehook);
  
  // Controller1.ButtonR1.pressed(togl_elev);
  
}


// Note A: commented out code from line 139
  // Controller1.ButtonL2.pressed(togl_ehook);
  /*while (!Controller1.ButtonL1.pressing() || !Controller1.ButtonL2.pressing() || 
  !Controller1.ButtonR1.pressing() || !Controller1.ButtonR2.pressing()){
    arms.stop();
  }*/
  // Controller1.ButtonL1.pressed(lift);
  // lift_arms();
  //if (Controller1.ButtonL2.pressing()){
  //  arms.spin(reverse);
  //}
  /*if (Controller1.ButtonR1.pressing()){
    elevator.spinFor(forward, 400, degrees);
  }
  if (Controller1.ButtonR2.pressing()){
    elevator.spinFor(reverse, 400, degrees);
  }*/