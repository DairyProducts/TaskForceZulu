using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor liftthing;
extern motor belt;
extern drivetrain Drivetrain;
extern motor_group lifter;
extern motor_group upperbodylift;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );