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
// liftthing            motor         1   
// belt                 motor         5             
// Drivetrain           drivetrain    2, 12           
// lifter               motor_group   3, 13           
// upperbodylift        motor_group   9, 14           
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

bool holding = false;
bool lifting = false;
bool folded = false;

void spinlift(){
  liftthing.stop();
  liftthing.setVelocity(80, percent);
  if (holding == false){
    liftthing.spin(forward);
    holding = true;
  }
  else{
    liftthing.spin(reverse);
    holding = false;
    
  }
}

void lift(){
  lifter.setVelocity(100, percent);
  if (lifting == true){
    lifter.spinFor(forward, 350, degrees);
    lifting = false;
  } else{
    lifter.spinFor(reverse, 350, degrees);
    lifting = true;
  }
}

void foldbody(){
  upperbodylift.setVelocity(100, percent);
  if (lifting == true){
    upperbodylift.spinFor(forward, 20, degrees);
    lifting = false;
  } else{
    upperbodylift.spinFor(reverse, 20, degrees);
    lifting = true;
  }
}

void auton(){
  Drivetrain.setDriveVelocity(100, percent);
  Drivetrain.driveFor(reverse, 50, inches);
  lifter.spinFor(reverse, 350, degrees);
  Drivetrain.turnFor(right, 120, degrees);
  Drivetrain.driveFor(reverse, 26, inches);
  lifter.spinFor(forward, 350, degrees);
  Drivetrain.driveFor(forward, 9, inches);
  Drivetrain.turnFor(right, 120, degrees);

}

int armliftup() {
  if (Controller1.ButtonL1.pressing()) {
    lifter.spin(forward);
  }
  return 0;
}

bool beltIsSpinning = false;

void belttoggle() {
  if (beltIsSpinning){
    belt.stop();
    beltIsSpinning = false;
  } else{
    belt.setVelocity(70, percent);
    belt.spin(reverse);
    beltIsSpinning = true;
  }

}

void movetoacceptrings() {
  lifter.spinFor(forward, 237.5, degrees);
}

int main() {
  vexcodeInit();
  lifter.setVelocity(85, percent);
  upperbodylift.setVelocity(100, percent);
  Drivetrain.setDriveVelocity(100, percent);
  // auto
  Controller1.ButtonX.pressed(movetoacceptrings);
  Controller1.ButtonY.pressed(belttoggle);
  // driver control
  
  // Controller1.ButtonL2.pressed(spinlift);
  /*while (!Controller1.ButtonL1.pressing() || !Controller1.ButtonL2.pressing() || 
  !Controller1.ButtonR1.pressing() || !Controller1.ButtonR2.pressing()){
    lifter.stop();
  }*/
  // Controller1.ButtonL1.pressed(lift);
  // armliftup();
  //if (Controller1.ButtonL2.pressing()){
  //  lifter.spin(reverse);
  //}
  /*if (Controller1.ButtonR1.pressing()){
    upperbodylift.spinFor(forward, 400, degrees);
  }
  if (Controller1.ButtonR2.pressing()){
    upperbodylift.spinFor(reverse, 400, degrees);
  }*/
  Controller1.ButtonA.pressed(spinlift);
  // Controller1.ButtonR1.pressed(foldbody);
  
}
