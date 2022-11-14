#include "Intake.h"

Intake::Intake() : intakeMotor_(IntakeConstants::MOTOR_ID), intakePneumatic_(frc::PneumaticsModuleType::CTREPCM, IntakeConstants::SOLENOID_ID)
{
    intakeMotor_.SetNeutralMode(NeutralMode::Coast);

    state_ = RETRACTED_IDLE;
}

Intake::State Intake::getState(){ return state_; }

void Intake::setState(State state)
{
    state_ = state;
}

void Intake::periodic()
{   
    switch(state_)
    {
        case RETRACTED_IDLE:
        {
            stop();
            retract();
            break;
        }
        case EXTENDED_IDLE:
        {
            stop();
            deploy();
            break;
        }
        case LOADING:
        {
            retract();
            run(true);
            break;
        }
        case INTAKING:
        {
            deploy();
            run(true);
            break;
        }
        case OUTAKING:
        {
            deploy();
            run(false);
            break;
        }
    }
}

void Intake::run(bool forward)
{
    if(forward)
    {
        //double speed = frc::SmartDashboard::GetNumber("Sintake", 0.0);
        intakeMotor_.SetVoltage(units::volt_t(IntakeConstants::INTAKE_SPEED));
    }
    else
    {
        intakeMotor_.SetVoltage(units::volt_t(IntakeConstants::OUTAKE_SPEED));
    }
}

void Intake::stop()
{
    intakeMotor_.SetVoltage(units::volt_t(0));
}

void Intake::deploy()
{
    intakePneumatic_.Set(true);
}

void Intake::retract()
{
    intakePneumatic_.Set(false);
}