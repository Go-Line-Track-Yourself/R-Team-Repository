#include "robot-config.h"
#include <cmath>
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VCS VEX V5                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/

//Creates a competition object that allows access to Competition methods.
vex::competition    Competition;

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

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/


void RightDriveStop()
{
	{
		RightBackMotor.stop(vex::brakeType::coast);
		RightFrontMotor.stop(vex::brakeType::coast);
	}
}
void LeftDriveStop()
{
	{
		LeftBackMotor.stop(vex::brakeType::coast);
		LeftFrontMotor.stop(vex::brakeType::coast);
	}
}
void LeftDrive(int pct)
{
	if (pct == 0)
	{
		LeftDriveStop();
	}
	else {
		LeftFrontMotor.spin(vex::directionType::fwd, pct, vex::velocityUnits::pct);
		LeftBackMotor.spin(vex::directionType::fwd, pct, vex::velocityUnits::pct);
	}
}
void RightDrive(int pct) {
	if (pct == 0)
	{
		RightDriveStop();
	}
	else
	{
		RightFrontMotor.spin(vex::directionType::rev, pct, vex::velocityUnits::pct);
		RightBackMotor.spin(vex::directionType::rev, pct, vex::velocityUnits::pct);
	}
}
void Drive(int same)
{
	LeftDrive(same);
	RightDrive(same);
}

void autonomous(void) {
	Brain.Screen.print("Starting Auton");
	Drive(50);
	Brain.Screen.print("Auton Works");
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

void Feed()
{
	if (Ellisons_Controller.ButtonR1.pressing())
	{
		FeedMotor.spin(vex::directionType::fwd, 100, ::vex::velocityUnits::pct);
	}
	else if (Ellisons_Controller.ButtonUp.pressing())
	{
		FeedMotor.spin(vex::directionType::fwd, -25, ::vex::velocityUnits::pct);
	}
	else
	{
		FeedMotor.stop(vex::brakeType::coast);
	}
}

void Index()
{
	if (Ellisons_Controller.ButtonR2.pressing())

	{
		IndexMotor.spin(vex::directionType::fwd, 100, ::vex::velocityUnits::pct);
	}
	else
	{
		IndexMotor.stop(vex::brakeType::coast);
	}
}

void FlyWheel()
{
	if (Ellisons_Controller.ButtonX.pressing() && FlyWheelPressed == false)
	{
		FlyWheelPressed = true;
		FlyWheelInverse = !FlyWheelInverse;
	}
	if (!Ellisons_Controller.ButtonX.pressing() && FlyWheelPressed == true)
	{
		FlyWheelPressed = false;
	}

	if (FlyWheelInverse)
	{
		FlyWheelMotor.spin(vex::directionType::fwd, 100, ::vex::velocityUnits::pct);
	}
	else if (!FlyWheelInverse)
	{
		FlyWheelMotor.stop(vex::brakeType::coast);
	}
}

int FlipperUp = -370;
int FlipperDown = -5;
int FlipperRequested = FlipperDown;

void Flipper()
{
	if (Ellisons_Controller.ButtonL1.pressing() && FlipperBtnPressed == false)
	{
		FlipperBtnPressed = true;
		if (FlipperRequested == FlipperDown)     FlipperRequested = FlipperUp;
		else if (FlipperRequested == FlipperUp)  FlipperRequested = FlipperDown;
	}
	if (!Ellisons_Controller.ButtonL1.pressing() && FlipperBtnPressed == true)
	{
		FlipperBtnPressed = false;
	}
	FlipperMotor.startRotateTo(FlipperRequested, vex::rotationUnits::deg, 100, vex::velocityUnits::pct);

}
void FlipperManualandToggle()
{
	if (Ellisons_Controller.ButtonDown.pressing() && FlipperModeBtnPressed == false) {
		FlipperModeBtnPressed = true;
		FlipperMode = !FlipperMode;
	}
	if (!Ellisons_Controller.ButtonDown.pressing() && FlipperModeBtnPressed == true) {
		FlipperModeBtnPressed = false;
	}

	if (FlipperMode) {//manual mode
		FlipperMotor.setStopping(vex::brakeType::brake);

		if (Ellisons_Controller.ButtonL1.pressing())
		{
			FlipperMotor.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
		}
		else if (Ellisons_Controller.ButtonL2.pressing())
		{
			FlipperMotor.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
		}
		else
		{
			FlipperMotor.stop(vex::brakeType::brake);
		}
	}
	if (!FlipperMode) {//toggle mode
					   //FlipperMotor.startRotateTo(FlipperDown,vex::rotationUnits::deg,100,vex::velocityUnits::pct);
		if (Ellisons_Controller.ButtonL1.pressing() && FlipperBtnPressed == false)
		{
			FlipperBtnPressed = true;
			if (FlipperRequested == FlipperDown)     FlipperRequested = FlipperUp;
			else if (FlipperRequested == FlipperUp)  FlipperRequested = FlipperDown;
		}
		if (!Ellisons_Controller.ButtonL1.pressing() && FlipperBtnPressed == true)
		{
			FlipperBtnPressed = false;
		}
		FlipperMotor.startRotateTo(FlipperRequested, vex::rotationUnits::deg, 100, vex::velocityUnits::pct);
	}
}
void Descorer()
{
	FlipperMotor.setStopping(vex::brakeType::brake);

	if (Ellisons_Controller.ButtonL1.pressing())
	{
		FlipperMotor.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
	}
	else if (Ellisons_Controller.ButtonL2.pressing())
	{
		FlipperMotor.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
	}
	else
	{
		FlipperMotor.stop(vex::brakeType::brake);
	}

}


void usercontrol(void)
{
	while (1)
	{
		LeftBackMotor.spin(vex::directionType::fwd, Ellisons_Controller.Axis3.value(), vex::velocityUnits::pct);
		LeftFrontMotor.spin(vex::directionType::fwd, Ellisons_Controller.Axis3.value(), vex::velocityUnits::pct);
		RightBackMotor.spin(vex::directionType::rev, Ellisons_Controller.Axis2.value(), vex::velocityUnits::pct);
		RightFrontMotor.spin(vex::directionType::rev, Ellisons_Controller.Axis2.value(), vex::velocityUnits::pct);
		Feed();
		Index();
		FlyWheel();
		FlipperManualandToggle();


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

	FlipperMotor.setStopping(vex::brakeType::coast);
	//Prevent main from exiting with an infinite loop.                        
	while (1) {
		vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
	}

}