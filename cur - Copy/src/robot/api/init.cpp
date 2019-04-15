#include "robot/api/init.hpp"
#include "main.h"
#include "robot/api/auto.hpp"
#include "robot/control/auton/selection.hpp"
#include "robot/control/modes/auton.hpp"
#include "robot/control/systems/lift.hpp"
#include "robot/control/systems/puncher.hpp"

bool inited = false;
void systemInit() {  // custom robot init dont trust the reliability of
                     // initialize && competition_initialize
  if (!inited) {
    inited = true;
    Catapult::motor.tarePosition();
    drive::LeftN.set_limits(drive::LeftN.get_changeMsec(),-drive::LeftN.get_changeMsec(),0,0);
    drive::RightN.set_limits(drive::RightN.get_changeMsec(),-drive::RightN.get_changeMsec(),0,0);
    drive::LeftS.set_limits(drive::LeftS.get_changeMsec(),-drive::LeftS.get_changeMsec(),0,0);
    drive::RightS.set_limits(drive::RightS.get_changeMsec(),-drive::RightS.get_changeMsec(),0,0);
  }
}
void initialize() {
  auton::selection::screenInit();

  Lift::motor.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  intake::motor.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
  flipper::motor.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
      std::cout<<"inited"<<std::endl;

}
void disabled(void) {
  auton::autonTask.suspend();
  auton::set_auton(false);
  // drive::front_left_motor.moveVelocity(0);
  // drive::front_right_motor.moveVelocity(0);
  // drive::back_left_motor.moveVelocity(0);
  // drive::back_right_motor.moveVelocity(0);
  // Catapult::motor.moveVelocity(0);
  // Lift::motor.moveVelocity(0);
  // intake::motor.moveVelocity(0);
}
void competition_initialize(void) {
  // AutonTask.suspend();
  // auton::inAuton=false;
  // Catapult::motor.tarePosition();
}
