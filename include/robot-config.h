using namespace vex;

extern brain Brain;
extern controller Controller1;
extern motor elev_hook;
extern motor belt;
extern drivetrain Drivetrain;
extern motor_group arms;
extern motor_group elevator;
extern vision Vision5;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
