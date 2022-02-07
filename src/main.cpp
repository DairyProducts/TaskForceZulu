/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
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

#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;
int Brain_precision = 0, Console_precision = 0, Vision5_objectIndex = 0;
vision::signature Vision5__YELOW = vision::signature (1, 2993, 3705, 3350,-3941, -3387, -3664,2.5, 0);
vision Vision5 = vision (PORT20, 30, Vision5__YELOW);
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
  belt.setVelocity(75, percent);
  
  Drivetrain.setDriveVelocity(100, percent);
  arms.spinToPosition(760, degrees);
  //wait(5, seconds);
  Drivetrain.driveFor(forward, -20, inches);
  Vision5.takeSnapshot(Vision5__YELOW);
  while (!(Vision5.objects[Vision5_objectIndex].height > 100.0 || Vision5.objects[Vision5_objectIndex].centerY > 140.0)) {
    Vision5.takeSnapshot(Vision5__YELOW);
    if(Vision5.objects[Vision5_objectIndex].centerX > 120 && Vision5.objects[Vision5_objectIndex].centerX < 160){
      Drivetrain.setDriveVelocity(50, percent);
      Drivetrain.driveFor(forward, -3, inches);
    }
    else if (Vision5.objects[Vision5_objectIndex].centerX <= 120){
      Drivetrain.turn(left);
    }
    else if(Vision5.objects[Vision5_objectIndex].centerX >= 160){
      Drivetrain.turn(right);
    } else{
      Drivetrain.turn(left);
    }
  }
  Brain.Screen.print("VEXcode");
  Drivetrain.driveFor(forward, -2, inches);
  Drivetrain.setDriveVelocity(0, percent);
  //The conveyor belt stuff
  arms.spinToPosition(520, degrees);
  //conveyor.spin(forward);
  Drivetrain.setDriveVelocity(0, percent);
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
    //wait(0.4, seconds);
    //elev_hook.stop();
    ehook_on = false;
  }
}



// toggle arms between positions based on arms_on
void togl_arms(){
  arms.setVelocity(75, percent);
  if (arms_on == true){
    arms.spinToPosition(520, degrees);
    arms_on = false;
  } else{
    arms.spinToPosition(760, degrees);
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
    belt.setVelocity(80, percent);
    belt.spin(reverse);
    belt_on = true;
  }

}

void speeddown(){
  Drivetrain.setDriveVelocity(75, percent);
}

void speedup(){
  Drivetrain.setDriveVelocity(100, percent);
}

// autonmous
void auton(){
  Drivetrain.setDriveVelocity(100, percent);
  Drivetrain.driveFor(forward, 46, inches);
  Drivetrain.setDriveVelocity(25, percent);
  Drivetrain.driveFor(forward, 7, inches);
  wait(0.3, seconds);
  togl_ehook();
  wait(0.3, seconds);
  Drivetrain.setDriveVelocity(100, percent);
  Drivetrain.driveFor(reverse, 40, inches);

}

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  arms.setVelocity(40, percent);
  elevator.setVelocity(85, percent);
  Drivetrain.setDriveVelocity(100, percent);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  Drivetrain.setDriveVelocity(100, percent);
  elevator.spinFor(reverse, 20, degrees);
  auton();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void drivercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    Controller1.ButtonX.pressed(togl_arms);
    Controller1.ButtonY.pressed(togl_belt);
    Controller1.ButtonA.pressed(togl_ehook);
    Controller1.ButtonUp.pressed(speedup);
    Controller1.ButtonDown.pressed(speeddown);
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(drivercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
