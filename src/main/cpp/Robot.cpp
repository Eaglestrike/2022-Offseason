// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <fmt/core.h>

#include <frc/smartdashboard/SmartDashboard.h>

  void Robot::RobotInit() {}
  void Robot::RobotPeriodic() {}
  void Robot::AutonomousInit() {}
  void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
  //  try
  //   {
  //       navx_ = new AHRS(frc::SPI::Port::kMXP);
  //   }
  //   catch (const std::exception &e)
  //   {
  //       std::cout << e.what() << std::endl;
  //   }
  //   navx_->ZeroYaw();
}

void Robot::TeleopPeriodic() {
  frc::Pose2d x = limelight_.getPose(0, 0);
  
}

  void Robot::TestInit() {}
  void Robot::TestPeriodic() {
  }

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::SimulationInit() {}

void Robot::SimulationPeriodic() {}

Robot::~Robot() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
