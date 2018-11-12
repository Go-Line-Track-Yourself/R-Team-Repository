#include "robot-config.h"
#include <cmath>
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VCS VEX V5                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/

//Creates a competition object that allows access to Competition methods.
vex::competition    Competition;
bool BPressed = false;
bool DPressed = false;
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
	Brain.Screen.print("Hey Ellison, good Luck!!:)");
	Ellisons_Controller.Screen.print("Hey Ellison, good Luck!!:)");
	JawMotor.setStopping(vex::brakeType::coast);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/

void autonomous(void) {

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

void LiftController()
{
	//Control for the Lift

	if (Ellisons_Controller.ButtonL2.pressing())
	{
		LiftMotor1.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
		LiftMotor2.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
	}
	else if (Ellisons_Controller.ButtonL1.pressing())
	{
		LiftMotor1.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
		LiftMotor2.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
	}
	else
	{
		LiftMotor1.stop(vex::brakeType::hold);
		LiftMotor2.stop(vex::brakeType::hold);
	}
}

void JawIntake()
{
	//Control for the Jaw 

	if (Ellisons_Controller.ButtonR1.pressing() && JawIntakePressed == false) {
		JawIntakePressed = true;
		JawMotor.startRotateTo(JawIntakeInverse ? 10 : 100, vex::rotationUnits::deg, 100, vex::velocityUnits::pct);
		JawIntakeInverse = !JawIntakeInverse;
	}

	if (!Ellisons_Controller.ButtonR1.pressing() && JawIntakePressed == true)
	{
		JawIntakePressed = false;
	}

}
void ArmIntake()
{
	//Control for the Arm

	if (Ellisons_Controller.ButtonR2.pressing() && ArmIntakePressed == false)
	{
		ArmIntakePressed = true;
		ArmMotor.startRotateTo(ArmIntakeInverse ? 5 : 175, vex::rotationUnits::deg, 100, vex::velocityUnits::pct);
		ArmIntakeInverse = !ArmIntakeInverse;
	}

	if (!Ellisons_Controller.ButtonR2.pressing() && ArmIntakePressed == true)
	{
		ArmIntakePressed = false;
	}
}
//copy function and change motor object and change Rpm for direction
//run this in a task so it doesnt stop the main cood loop
int LastRotation = 0;
int JawCal() {
	int Rpm = -200;       //Velocity to hit the end stop
	int TimeOut = 1000;   //Max time to hit end stop
	int UpdateMsec = 20;  //the time delay in the loop
	int CalTimer = 0;     //resets a local timer
	JawMotor.spin(vex::directionType::fwd, Rpm, vex::velocityUnits::rpm);   //starts the spin to hit the end stop 
	double MinChange = Rpm / 240000 * UpdateMsec;                                 ///(1/2)*(Rpm/60/1000); MinChange = 1/4 of requested rpm changed into msec instead of min
	LastRotation = JawMotor.rotation(vex::rotationUnits::rev) + 4 * MinChange;    //makes sure that the while loop starts
	vex::task::sleep(100);                                                  //wait for the motor get some speed
	while (std::abs(JawMotor.rotation(vex::rotationUnits::rev) - LastRotation)>MinChange && CalTimer<TimeOut) {//while the motors displacement is more then the MinChange and while the the timer is less then the timeout time
		LastRotation = JawMotor.rotation(vex::rotationUnits::rev);//update LastRotation
		CalTimer = CalTimer + UpdateMsec;   //add time to the timer
		vex::task::sleep(UpdateMsec);   //wait for the motor to spin
	}                                   //motor stoped spinning or time ran out
										//	if (CalTimer >= TimeOut) return 0;     //if timed out return error code 0 or false
										//	else {                               //hit the end stop
	JawMotor.resetRotation();           //reset the rotation
	JawMotor.stop();                    //dont burn out the motor
	return 1;                           //return 1 or true
										//	}
}

int LastRotation2 = 0;
int ArmCal() {
	int Rpm = -200;       //Velocity to hit the end stop
	int TimeOut = 1000;   //Max time to hit end stop
	int UpdateMsec = 20;  //the time delay in the loop
	int CalTimer = 0;     //resets a local timer
	ArmMotor.spin(vex::directionType::fwd, Rpm, vex::velocityUnits::rpm);   //starts the spin to hit the end stop 
	double MinChange = Rpm / 240000 * UpdateMsec;                                 ///(1/2)*(Rpm/60/1000); MinChange = 1/4 of requested rpm changed into msec instead of min
	LastRotation = ArmMotor.rotation(vex::rotationUnits::rev) + 4 * MinChange;    //makes sure that the while loop starts
	vex::task::sleep(200);                                                  //wait for the motor get some speed
	while (std::abs(ArmMotor.rotation(vex::rotationUnits::rev) - LastRotation)>MinChange && CalTimer<TimeOut) {//while the motors displacement is more then the MinChange and while the the timer is less then the timeout time
		LastRotation = ArmMotor.rotation(vex::rotationUnits::rev);//update LastRotation
		CalTimer = CalTimer + UpdateMsec;   //add time to the timer
		vex::task::sleep(UpdateMsec);   //wait for the motor to spin
	}                                   //motor stoped spinning or time ran out
										//	if (CalTimer >= TimeOut) return 0;     //if timed out return error code 0 or false
										//	else {                               //hit the end stop
	ArmMotor.resetRotation();           //reset the rotation
	ArmMotor.stop();                    //dont burn out the motor
	return 1;                           //return 1 or true
										//	}
}
void ReCals() {
	if (Ellisons_Controller.ButtonB.pressing() && !BPressed) {
		BPressed = true;
		vex::task JawCalTask(JawCal);
	}
	else if (!Ellisons_Controller.ButtonB.pressing() && BPressed)    BPressed = false;

	if (Ellisons_Controller.ButtonDown.pressing() && !DPressed) {
		DPressed = true;
		vex::task ArmCalTask(ArmCal);
	}
	else if (!Ellisons_Controller.ButtonDown.pressing() && DPressed) DPressed = false;
}
void usercontrol(void)
{

	vex::task JawCalTask(JawCal);
	vex::task ArmCalTask(ArmCal);
	while (1) {
		Brain.Screen.newLine();
		Brain.Screen.print(ArmMotor.rotation(vex::rotationUnits::deg));
		//        Ellisons_Controller.Screen.print(std::abs(JawMotor.rotation(vex::rotationUnits::rev) - LastRotation)>0.0166666666666667);
		LeftBackMotor.spin(vex::directionType::fwd, Ellisons_Controller.Axis3.value(), vex::velocityUnits::pct);
		LeftFrontMotor.spin(vex::directionType::fwd, Ellisons_Controller.Axis3.value(), vex::velocityUnits::pct);
		RightBackMotor.spin(vex::directionType::rev, Ellisons_Controller.Axis2.value(), vex::velocityUnits::pct);
		RightFrontMotor.spin(vex::directionType::rev, Ellisons_Controller.Axis2.value(), vex::velocityUnits::pct);
		LiftController();
		JawIntake();
		ArmIntake();
		ReCals();

		vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
	}
}

//
// Main will set up the competition functions and callbacks.
//
int main() {

	//Run the pre-autonomous function. 
	pre_auton();

	//Set up callbacks for autonomous and driver control periods.
	Competition.autonomous(autonomous);
	Competition.drivercontrol(usercontrol);

	//Prevent main from exiting with an infinite loop.                        
	while (1) {
		vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
	}

}