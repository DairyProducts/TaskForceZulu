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
// arms               motor_group   3, 13           
// elevator        motor_group   9, 14           
// ---- END VEXCODE CONFIGURED DEVICES ----


/*
Controller1: controller
arms: lift arms on front of robot
elevator: lifter for lifting goals onto lever / upper body
elev_hook: hook on elevator
belt: donut processing treads
*/


#include "vex.h"

using namespace vex;

// holding: toggle variable for elev_hook
bool holding = false;
// lifting: toggle variable for arms and elevator, (possibly mistake)
bool lifting = false;
// folded: unused, (possibly mistake)
bool folded = false;

// toggle elev_hook between lock and unlock based on holding
void spinlift(){
  elev_hook.stop();
  elev_hook.setVelocity(80, percent);
  if (holding == false){
    elev_hook.spin(forward);
    holding = true;
  }
  else{
    elev_hook.spin(reverse);
    holding = false;
  }
}
 
// toggle arms between positions based on lifting
void lift(){
  arms.setVelocity(50, percent);
  if (lifting == true){
    arms.spinFor(forward, 350, degrees);
    lifting = false;
  } else{
    arms.spinFor(reverse, 350, degrees);
    lifting = true;
  }
}

// toggle elevator between unextended and extended positions based on lifting
void foldbody(){
  elevator.setVelocity(100, percent);
  if (lifting == true){
    elevator.spinFor(forward, 20, degrees);
    lifting = false;
  } else{
    elevator.spinFor(reverse, 20, degrees);
    lifting = true;
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

// moves arms up when L1 is pressed
int armliftup() {
  if (Controller1.ButtonL1.pressing()) {
    arms.spin(forward);
  }
  return 0;
}

//beltIsSpinning: toggle variable for belt
bool beltIsSpinning = false;

// toggles belt between spinning fore or back based on beltIsSpinning
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

// spin arms
void movetoacceptrings() {
  arms.spinFor(forward, 237.5, degrees);
}

// main
int main() {
  vexcodeInit();
  arms.setVelocity(85, percent);
  elevator.setVelocity(100, percent);
  Drivetrain.setDriveVelocity(100, percent);
  // auto
  Controller1.ButtonX.pressed(movetoacceptrings);
  Controller1.ButtonY.pressed(belttoggle);
  // driver control
  
  // Controller1.ButtonL2.pressed(spinlift);
  /*while (!Controller1.ButtonL1.pressing() || !Controller1.ButtonL2.pressing() || 
  !Controller1.ButtonR1.pressing() || !Controller1.ButtonR2.pressing()){
    arms.stop();
  }*/
  // Controller1.ButtonL1.pressed(lift);
  // armliftup();
  //if (Controller1.ButtonL2.pressing()){
  //  arms.spin(reverse);
  //}
  /*if (Controller1.ButtonR1.pressing()){
    elevator.spinFor(forward, 400, degrees);
  }
  if (Controller1.ButtonR2.pressing()){
    elevator.spinFor(reverse, 400, degrees);
  }*/

  Controller1.ButtonA.pressed(spinlift);
  
  // Controller1.ButtonR1.pressed(foldbody);
  
}
