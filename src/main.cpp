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
#include <string>
#include <sstream>

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
//bool belt_on = false;
double maxtemp = 75.0;

// toggle elev_hook between lock and unlock based on ehook_on
/*void togl_ehook(){
  elev_hook.stop();
  if (ehook_on == false){
    ehook_on = true;
    elev_hook.spinFor(forward, 180, degrees);
    
    elev_hook.setVelocity(0, percent);
    //elev_hook.spinFor(300, degrees);
    
  }
  else{
    ehook_on = false;
    elev_hook.setVelocity(80, percent);
    elev_hook.spinFor(reverse, 180, degrees);
  }
}*/
void togl_ehook(){
  elev_hook.stop();
  elev_hook.setVelocity(100, percent);
  if (ehook_on == true){
    //ehook_on = false;
    elev_hook.stop(brakeType::coast);
    elev_hook.spin(reverse);
    wait(0.4, seconds);
    //elev_hook.spinFor(forward, 0.001, degrees);
    //elev_hook.setStopping(hold);
    
    elev_hook.setVelocity(0, percent);
    ehook_on = false;
    //elev_hook.spin(forward);
    
  }
  else{
    //ehook_on = true;
    elev_hook.stop(brakeType::hold);
    elev_hook.setVelocity(100, percent);
    elev_hook.spin(forward);
    wait(0.7, seconds);
    elev_hook.setVelocity(0, percent);
    ehook_on = true;
    //elev_hook.setStopping(coast);
    
    //elev_hook.spin(reverse);
  }
}


// toggle arms between positions based on arms_on
void togl_arms(){
  arms.setVelocity(100, percent);
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
/*void togl_belt() {
  if (belt_on){
    belt.stop();
    belt_on = false;
  } else{
    belt.setVelocity(90, percent);
    belt.spin(reverse);
    belt_on = true;
  }

}*/

/*void speeddown(){
  Drivetrain.setDriveVelocity(75, percent);
}*/

/*void speedup(){
  Drivetrain.setDriveVelocity(100, percent);
}*/
// autonmous
void auton(){
  arms.setVelocity(100, percent);
  arms.spinToPosition(760, degrees, false);
  Drivetrain.setDriveVelocity(100, percent);
  Drivetrain.driveFor(reverse, 49, inches);
  arms.spinToPosition(300, degrees, true);
  Drivetrain.setDriveVelocity(25, percent);
  Drivetrain.driveFor(reverse, 3, inches);
  Drivetrain.setDriveVelocity(100, percent);
  Drivetrain.driveFor(forward, 15, inches);
  
}

// winpoint  lowside with conveyor
/*void winpointlowconveyor(){
  Drivetrain.setDriveVelocity(80, percent);
  belt.setVelocity(10, percent);
  // drop donut into goal 1 (change 500)
  togl_belt();
  wait(3, seconds);
  // go backward 3 inches, back away from goal
  Drivetrain.driveFor(forward, 15, inches);
}*/

//win point without conveyor for low side
void winpointlowside(){
  //Drivetrain.setDriveVelocity(100, percent);
  //Drivetrain.driveFor(forward, 6, inches);
  Drivetrain.setDriveVelocity(10, percent);
  Drivetrain.driveFor(forward, 3, inches);
  togl_ehook();
  wait(0.4, seconds);
  Drivetrain.driveFor(reverse, 4, inches);
  togl_ehook();
}
//win point without conveyor for high side
void winpointhighside(){
  Drivetrain.setDriveVelocity(50, percent);
  Drivetrain.driveFor(forward, 6, inches);
  Drivetrain.setDriveVelocity(10, percent);
  Drivetrain.driveFor(forward, 10, inches);
  togl_ehook();
  wait(1, seconds);
  Drivetrain.setDriveVelocity(60, percent);
  Drivetrain.driveFor(reverse, 5, inches);
  Drivetrain.turnFor(left, 60, degrees);
  togl_ehook();
}

void controllerinfo(){
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(0, 0);
  if(ehook_on){
    Controller1.Screen.print("Hook LOCKED");
  } else{
    Controller1.Screen.print("Hook UNLOCKED");
  }
  Controller1.Screen.newLine();
  if(arms.temperature(percent) >= maxtemp || elevator.temperature(percent) >= maxtemp
  || elev_hook.temperature(percent) >= maxtemp || Drivetrain.temperature(percent) >= maxtemp){
    Controller1.Screen.print("OVERHEAT WARN");
  }
}
std::stringstream s;
void braininfo(){
  s.clear();
  // s.str();
  Brain.Screen.clearScreen();
  Brain.Screen.setFont(vex::fontType::mono30);
  Brain.Screen.setCursor(0, 0);
  s << "test: " << 5.0;
  // std::string t = "gi" + 0.5;
  Brain.Screen.newLine();
  if(arms.temperature(percent) >= maxtemp){
    Brain.Screen.setFillColor(red);
    Brain.Screen.print("ARMS OVERHEAT WARN - ");
    Brain.Screen.print(arms.temperature(percent));
    Brain.Screen.print("%");
  } else if(arms.temperature(percent) < maxtemp
   && arms.temperature(percent) > maxtemp - 15){
    Brain.Screen.setFillColor(orange);
    Brain.Screen.print("ARMS CHECK TEMP - ");
    Brain.Screen.print(arms.temperature(percent));
    Brain.Screen.print("%");
    
  } else{
    Brain.Screen.setFillColor(blue);
    Brain.Screen.print("ARMS TEMP OK - ");
    Brain.Screen.print(arms.temperature(percent));
    Brain.Screen.print("%");
    // Brain.Screen.print(t);
    
  }
  Brain.Screen.newLine();
  if(Drivetrain.temperature(percent) >= maxtemp){
    Brain.Screen.setFillColor(red);
    Brain.Screen.print("DT OVERHEAT WARN - ");
    Brain.Screen.print(Drivetrain.temperature(percent));
    Brain.Screen.print("%");
  } else if(Drivetrain.temperature(percent) < maxtemp
   && Drivetrain.temperature(percent) > maxtemp - 15){
     Brain.Screen.setFillColor(orange);
    Brain.Screen.print("DT CHECK TEMP - ");
    Brain.Screen.print(Drivetrain.temperature(percent));
    Brain.Screen.print("%");
  } else{
    Brain.Screen.setFillColor(blue);
    Brain.Screen.print("DT TEMP OK - ");
    Brain.Screen.print(Drivetrain.temperature(percent));
    Brain.Screen.print("%");
  }
  //const char *c = s.c_str();
  Brain.Screen.newLine();
  if(elevator.temperature(percent) >= maxtemp){
    Brain.Screen.setFillColor(red);
    Brain.Screen.print("ELEV OVERHEAT WARN - ");
    Brain.Screen.print(elevator.temperature(percent));
    Brain.Screen.print("%");
  } else if(elevator.temperature(percent) < maxtemp && 
  elevator.temperature(percent) > maxtemp - 15){
    Brain.Screen.setFillColor(orange);
    Brain.Screen.print("ELEV CHECK TEMP - ");
    Brain.Screen.print(elevator.temperature(percent));
    Brain.Screen.print("%");
  } else{
    Brain.Screen.setFillColor(blue);
    Brain.Screen.print("ELEV TEMP OK - ");
    Brain.Screen.print(elevator.temperature(percent));
    Brain.Screen.print("%");
  }
  Brain.Screen.newLine();
  if(elev_hook.temperature(percent) >= maxtemp){
    Brain.Screen.setFillColor(red);
    Brain.Screen.print("CLAMP OVERHEAT WARN - ");
    Brain.Screen.print(elev_hook.temperature(percent));
    Brain.Screen.print("%");
    
  } else if(elev_hook.temperature(percent) < maxtemp && 
  elev_hook.temperature(percent) > maxtemp - 15){
    Brain.Screen.setFillColor(orange);
    Brain.Screen.print("CLAMP CHECK TEMP - ");
    Brain.Screen.print(elev_hook.temperature(percent));
    Brain.Screen.print("%");
  } else{
    Brain.Screen.setFillColor(blue);
    Brain.Screen.print("CLAMP TEMP OK - ");
    Brain.Screen.print(elev_hook.temperature(percent));
    Brain.Screen.print("%");
  }
  Brain.Screen.newLine();
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
  //elevator.spinFor(reverse, 20, degrees);
  auton();
  //winpointhighside();
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
  Drivetrain.setDriveVelocity(80, percent);
  while (1) {
    
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    Controller1.ButtonX.pressed(togl_arms);
    //Controller1.ButtonY.pressed(togl_belt);
    Controller1.ButtonA.pressed(togl_ehook);
    braininfo();
    controllerinfo();
    //Controller1.ButtonUp.pressed(speedup);
    //Controller1.ButtonDown.pressed(speeddown);
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
  
  //auton();
  // Run the pre-autonomous function.
  pre_auton();
  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
