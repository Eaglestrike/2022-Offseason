#include "AutoPaths.h"

AutoPaths::AutoPaths(Channel *channel) : channel_(channel)
{
    pathNum_ = 0;
    dumbTimerStarted_ = false;
    pathSet_ = false;

    intakeState_ = Intake::RETRACTED_IDLE;
    shooterState_ = Shooter::IDLE;
}

void AutoPaths::setPath(Path path)
{
    path_ = path;
    pathNum_ = 0;
    swervePaths_.clear();
    nextPathReady_ = false;
    dumbTimerStarted_ = false;
    failsafeStarted_ = false;
    channel_->setBallsShot(0);

    switch (path_)
    {
    case DEAD_BOT:
    {
        break;
    }
    case TAXI_DUMB:
    {
        break;
    }
    case TWO_DUMB:
    {
        break;
    }
    case ONE_DUMB_DELAYED:
    {
        break;
    }
    case STRAIGHT_BACK:
    {
        SwervePath p1(SwerveConstants::MAX_LA, SwerveConstants::MAX_LV, SwerveConstants::MAX_AA, SwerveConstants::MAX_AV);

        p1.addPoint(SwervePose(0, 0, 180, 0));
        p1.addPoint(SwervePose(0, -2, 180, 0));

        p1.generateTrajectory(false);

        swervePaths_.push_back(p1);
        break;
    }
    case TWO_RIGHT:
    {
        SwervePath p1(SwerveConstants::MAX_LA, SwerveConstants::MAX_LV, SwerveConstants::MAX_AA, SwerveConstants::MAX_AV);

        p1.addPoint(SwervePose(0, 0, 90, 0));
        p1.addPoint(SwervePose(1, 0, 90, 0));

        p1.generateTrajectory(false);

        swervePaths_.push_back(p1);
        break;
    }
    case TWO_MIDDLE:
    {
        SwervePath p1(SwerveConstants::MAX_LA, SwerveConstants::MAX_LV, SwerveConstants::MAX_AA, SwerveConstants::MAX_AV);

        p1.addPoint(SwervePose(0, 0, 135, 0));
        p1.addPoint(SwervePose(0.707, -0.707, 135, 0));

        p1.generateTrajectory(false);

        swervePaths_.push_back(p1);
        break;
    }
    case TWO_LEFT:
    {
        SwervePath p1(SwerveConstants::MAX_LA, SwerveConstants::MAX_LV, SwerveConstants::MAX_AA, SwerveConstants::MAX_AV);

        p1.addPoint(SwervePose(0, 0, -135, 0));
        p1.addPoint(SwervePose(-0.707, -0.707, -135, 0));

        p1.generateTrajectory(false);

        swervePaths_.push_back(p1);
        break;
    }
    case THREE:
    {
        SwervePath p1(SwerveConstants::MAX_LA, SwerveConstants::MAX_LV, SwerveConstants::MAX_AA, SwerveConstants::MAX_AV);

        p1.addPoint(SwervePose(0, 0, 90, 0));
        p1.addPoint(SwervePose(1.1, 0, 90, 0));

        SwervePath p2(SwerveConstants::MAX_LA, SwerveConstants::MAX_LV, SwerveConstants::MAX_AA, SwerveConstants::MAX_AV);

        p2.addPoint(SwervePose(1.1, 0, 90, 0));
        //p2.addPoint(SwervePose(-0.5291328, -2.4728424, -156.77, 1.5)); //-168
        p2.addPoint(SwervePose(0.6-0.0893064, -2.1558504, -156.77, 1.5));

        p1.generateTrajectory(false);
        p2.generateTrajectory(false);

        swervePaths_.push_back(p1);
        swervePaths_.push_back(p2);
        break;
    }
    case BIG_BOY:
    {
        SwervePath p1(SwerveConstants::MAX_LA, SwerveConstants::MAX_LV, SwerveConstants::MAX_AA, SwerveConstants::MAX_AV);

        p1.addPoint(SwervePose(0, 0, 90, 0));
        p1.addPoint(SwervePose(1.1, 0, 90, 0)); // TODO get value
        //p1.addPoint(SwervePose(0, 0, 90, 0));

        SwervePath p2(SwerveConstants::MAX_LA, SwerveConstants::MAX_LV, SwerveConstants::MAX_AA, SwerveConstants::MAX_AV);

        p2.addPoint(SwervePose(1.1, 0, 90, 0));
        //p2.addPoint(SwervePose(-0.5291328, -2.4728424, -150, 1.5));
        p2.addPoint(SwervePose(0.6-0.0893064, -2.1558504, -156.77, 1.5));

        SwervePath p3(SwerveConstants::MAX_LA, SwerveConstants::MAX_LV, SwerveConstants::MAX_AA, SwerveConstants::MAX_AV);

        //p3.addPoint(SwervePose(-0.5291328, -2.4728424, -150, 0));
        p3.addPoint(SwervePose(0.6-0.0893064, -2.1558504, -156.77, 1.5));
        //p3.addPoint(SwervePose(0.1895856, -6.35508, 135, 3));
        p3.addPoint(SwervePose(0.6096-0.75, -5.9021472-0.65, 135, 3));
        //p3.addPoint(SwervePose(-0.0259144, -6.13958, 135, 0));
        p3.addPoint(SwervePose(0.3941-0.75, -5.6866472-0.65, 135, 0));

        SwervePath p4(SwerveConstants::MAX_LA, SwerveConstants::MAX_LV, SwerveConstants::MAX_AA, SwerveConstants::MAX_AV);

        //p4.addPoint(SwervePose(-0.0259144, -6.13958, 135, 0));
        p4.addPoint(SwervePose(0.3941-0.75, -5.6866472-0.65, 135, 0));
        p4.addPoint(SwervePose(-0.5291328, -2.4728424, 135, 0));

        p1.generateTrajectory(false);
        p2.generateTrajectory(false);
        p3.generateTrajectory(false);
        p4.generateTrajectory(false);

        swervePaths_.push_back(p1);
        swervePaths_.push_back(p2);
        swervePaths_.push_back(p3);
        swervePaths_.push_back(p4);
        break;
    }
    case DOMINIC:
    {
        SwervePath p1(SwerveConstants::MAX_LA, SwerveConstants::MAX_LV, SwerveConstants::MAX_AA, SwerveConstants::MAX_AV);

        p1.addPoint(SwervePose(0, 0, -135, 0));
        p1.addPoint(SwervePose(-0.707, -0.707, -135, 0));

        p1.generateTrajectory(false);

        SwervePath p2(SwerveConstants::MAX_LA, SwerveConstants::MAX_LV, SwerveConstants::MAX_AA, SwerveConstants::MAX_AV);

        p2.addPoint(SwervePose(-0.707, -0.707, -135, 0));
        p2.addPoint(SwervePose(-1.726-0.45, -0.2202+0.21, -64.45, 0.5));

        p2.generateTrajectory(false);

        SwervePath p3(SwerveConstants::MAX_LA, SwerveConstants::MAX_LV, SwerveConstants::MAX_AA, SwerveConstants::MAX_AV);

        p3.addPoint(SwervePose(-1.726-0.45, -0.2202+0.21, -64.45, 0));
        p3.addPoint(SwervePose(0, 0, 30, 1));

        p3.generateTrajectory(false);

        SwervePath p4(SwerveConstants::MAX_LA, SwerveConstants::MAX_LV, SwerveConstants::MAX_AA, SwerveConstants::MAX_AV);

        p4.addPoint(SwervePose(0, 0, 30, 0));
        p4.addPoint(SwervePose(-0.819912-0.1207008, 0.691896-0.4797552, -114.15, 0.6));

        p4.generateTrajectory(false);

        swervePaths_.push_back(p1);
        swervePaths_.push_back(p2);
        swervePaths_.push_back(p3);
        swervePaths_.push_back(p4);
        break;
    }
    case EYE_FOR_AN_EYE:
    {
        SwervePath p1(SwerveConstants::MAX_LA, SwerveConstants::MAX_LV, SwerveConstants::MAX_AA, SwerveConstants::MAX_AV);

        p1.addPoint(SwervePose(0, 0, -135, 0));
        p1.addPoint(SwervePose(-0.707, -0.707, -135, 0));

        p1.generateTrajectory(false);

        SwervePath p2(SwerveConstants::MAX_LA, SwerveConstants::MAX_LV, SwerveConstants::MAX_AA, SwerveConstants::MAX_AV);

        p2.addPoint(SwervePose(-0.707, -0.707, -135, 0));
        p2.addPoint(SwervePose(-1.726-0.45, -0.2202+0.21, -64.45, 0.5));

        p2.generateTrajectory(false);

        SwervePath p3(SwerveConstants::MAX_LA, SwerveConstants::MAX_LV, SwerveConstants::MAX_AA, SwerveConstants::MAX_AV);

        p3.addPoint(SwervePose(-1.726-0.45, -0.2202+0.21, -64.45, 0));
        p3.addPoint(SwervePose(1.556004, -1.441704, 110, 2.5));

        p3.generateTrajectory(false);

        SwervePath p4(SwerveConstants::MAX_LA, SwerveConstants::MAX_LV, SwerveConstants::MAX_AA, SwerveConstants::MAX_AV);

        p4.addPoint(SwervePose(1.556004, -1.441704, 110, 0));
        p4.addPoint(SwervePose(0, 0, 20, 1.5));

        p4.generateTrajectory(false);

        SwervePath p5(SwerveConstants::MAX_LA, SwerveConstants::MAX_LV, SwerveConstants::MAX_AA, SwerveConstants::MAX_AV);

        p5.addPoint(SwervePose(0, 0, 20, 0));
        p5.addPoint(SwervePose(-0.819912-0.1207008, 0.691896-0.4797552, -114.15, 0.6));

        p5.generateTrajectory(false);

        swervePaths_.push_back(p1);
        swervePaths_.push_back(p2);
        swervePaths_.push_back(p3);
        swervePaths_.push_back(p4);
        swervePaths_.push_back(p5);
    }
    }

    pathSet_ = true;
}

AutoPaths::Path AutoPaths::getPath()
{
    return path_;
}

Shooter::State AutoPaths::getShooterState()
{
    return shooterState_;
}

Intake::State AutoPaths::getIntakeState()
{
    return intakeState_;
}

void AutoPaths::startTimer()
{
    startTime_ = timer_.GetFPGATimestamp().value();
}

void AutoPaths::setSetPath(bool setPath)
{
    pathSet_ = setPath;
}

void AutoPaths::periodic(double yaw, SwerveDrive *swerveDrive)
{
    if(!pathSet_)
    {
        return;
    }

    double time = timer_.GetFPGATimestamp().value() - startTime_;

    bool pathsOver = false;
    bool endOfSwervePath = false;
    if (path_ != TAXI_DUMB && path_ != TWO_DUMB && path_ != DEAD_BOT && path_ != ONE_DUMB_DELAYED)
    {
        SwervePose *pose = nullptr;
        for (size_t i = pathNum_; i < swervePaths_.size(); ++i)
        {
            pose = swervePaths_[i].getPose(time, endOfSwervePath);
            if (!endOfSwervePath)
            {
                break;
            }

            if (i == swervePaths_.size() - 1 && endOfSwervePath)
            {
                pathsOver = true;
            }

            if (nextPathReady_ && endOfSwervePath && i != swervePaths_.size() - 1)
            {
                nextPathReady_ = false;
                ++pathNum_;
                startTimer();
                time = timer_.GetFPGATimestamp().value() - startTime_;
            }
            else
            {
                break;
            }
        }

        if(pose != nullptr)
        {
            swerveDrive->drivePose(yaw, *pose);
            delete pose;
        }
        
    }
    else
    {
        if (!dumbTimerStarted_)
        {
            timer_.Stop();
            timer_.Reset();
            timer_.Start();
            dumbTimerStarted_ = true;
        }
    }

    switch (path_)
    {
    case DEAD_BOT:
    {
        intakeState_ = Intake::RETRACTED_IDLE;
        shooterState_ = Shooter::IDLE;
        break;
    }
    case TAXI_DUMB:
    {
        intakeState_ = Intake::RETRACTED_IDLE;
        shooterState_ = Shooter::IDLE;
        if (timer_.Get().value() < 2.0)
        {
            swerveDrive->drive(0, 0.2, 0);
        }
        else
        {
            swerveDrive->drive(0, 0, 0);
        }
        break;
    }
    case TWO_DUMB:
    {
        intakeState_ = Intake::INTAKING;
        if (timer_.Get().value() < 2.0)
        {
            shooterState_ = Shooter::TRACKING;
            swerveDrive->drive(0, 0.2, 0);
        }
        else
        {
            swerveDrive->drive(0, 0, 0);
            shooterState_ = Shooter::SHOOTING;
        }
        break;
    }
    case ONE_DUMB_DELAYED:
    {
        intakeState_ = Intake::INTAKING;
        if (timer_.Get().value() < 10.0)
        {
            shooterState_ = Shooter::TRACKING;
            swerveDrive->drive(0, 0.0, 0);
        }
        else if (timer_.Get().value() > 10.0 && timer_.Get().value() < 12.0)
        {
            swerveDrive->drive(0, 0.2, 0);
            shooterState_ = Shooter::TRACKING;
        }
        else
        {
            shooterState_ = Shooter::SHOOTING;
        }
        break;
    }
    case STRAIGHT_BACK:
    {
        intakeState_ = Intake::INTAKING;
        if (pathsOver)
        {
            shooterState_ = Shooter::SHOOTING;
        }
        else
        {
            shooterState_ = Shooter::TRACKING;
        }
        break;
    }
    case TWO_RIGHT:
    {
        intakeState_ = Intake::INTAKING;
        if (pathsOver)
        {
            shooterState_ = Shooter::SHOOTING;
        }
        else
        {
            shooterState_ = Shooter::TRACKING;
        }
        break;
    }
    case TWO_MIDDLE:
    {
        intakeState_ = Intake::INTAKING;
        if (pathsOver)
        {
            shooterState_ = Shooter::SHOOTING;
        }
        else
        {
            shooterState_ = Shooter::TRACKING;
        }
        break;
    }
    case TWO_LEFT:
    {
        intakeState_ = Intake::INTAKING;
        if (pathsOver)
        {
            shooterState_ = Shooter::SHOOTING;
        }
        else
        {
            shooterState_ = Shooter::TRACKING;
        }
        break;
    }
    case THREE:
    {
        intakeState_ = Intake::INTAKING;
        if (endOfSwervePath/* && (channel_->getBallsShot() < 2 || channel_->getBallCount() > 0)*/)
        {
            shooterState_ = Shooter::SHOOTING;
        }
        else
        {
            shooterState_ = Shooter::TRACKING;
        }

        if (pathNum_ == 0 && endOfSwervePath)
        {
            if (!failsafeStarted_)
            {
                failsafeStarted_ = true;
                failsafeTimer_.Stop();
                failsafeTimer_.Reset();
                failsafeTimer_.Start();
            }

            if (failsafeTimer_.Get().value() > 4/* || channel_->getBallsShot() > 1*/)
            {
                //frc::SmartDashboard::PutBoolean("Started second", true);
                failsafeTimer_.Stop();
                failsafeTimer_.Reset();
                failsafeStarted_ = false;
                channel_->setBallsShot(0);
                nextPathReady_ = true;
            }
        }
        break;
    }
    case BIG_BOY:
    {
        intakeState_ = Intake::INTAKING;
        if (!endOfSwervePath)
        {
            shooterState_ = Shooter::REVING;
        }
        else
        {
            if(pathNum_ != 2)
            {
                shooterState_ = Shooter::SHOOTING;
            }
            else
            {
                shooterState_ = Shooter::REVING;
            }

            switch (pathNum_)
            {
            case 0:
            {
                if (!failsafeStarted_)
                {
                    failsafeStarted_ = true;
                    failsafeTimer_.Stop();
                    failsafeTimer_.Reset();
                    failsafeTimer_.Start();
                }

                if (failsafeTimer_.Get().value() > 2/* || channel_->getBallsShot() > 1*/)
                {
                    failsafeTimer_.Stop();
                    failsafeTimer_.Reset();
                    failsafeStarted_ = false;
                    channel_->setBallsShot(0);
                    nextPathReady_ = true;
                }
                break;
            }
            case 1:
            {
                if (!failsafeStarted_)
                {
                    failsafeStarted_ = true;
                    failsafeTimer_.Stop();
                    failsafeTimer_.Reset();
                    failsafeTimer_.Start();
                }

                if (failsafeTimer_.Get().value() > 1 || ((channel_->getBallsShot() > 0) && channel_->getBallCount() == 0))
                {
                    failsafeTimer_.Stop();
                    failsafeTimer_.Reset();
                    failsafeStarted_ = false;
                    channel_->setBallsShot(0);
                    nextPathReady_ = true;
                }
                break;
            }
            case 2:
            {
                if (!failsafeStarted_)
                {
                    failsafeStarted_ = true;
                    failsafeTimer_.Stop();
                    failsafeTimer_.Reset();
                    failsafeTimer_.Start();
                }

                if (failsafeTimer_.Get().value() > 1)
                {
                    failsafeTimer_.Stop();
                    failsafeTimer_.Reset();
                    failsafeStarted_ = false;
                    nextPathReady_ = true;
                }
                break;
            }
            case 3:
            {
                shooterState_ = Shooter::SHOOTING;
                break;
            }
            }
        }
        break;
    }
    case DOMINIC:
    {
        if (pathsOver)
        {
            intakeState_ = Intake::INTAKING;
            shooterState_ = Shooter::SHOOTING;
        }
        else
        {
            switch(pathNum_)
            {
                case 0:
                {
                    intakeState_ = Intake::INTAKING;

                    if(endOfSwervePath)
                    {
                        shooterState_ = Shooter::SHOOTING;

                        if (!failsafeStarted_)
                        {
                            failsafeStarted_ = true;
                            failsafeTimer_.Stop();
                            failsafeTimer_.Reset();
                            failsafeTimer_.Start();
                        }

                        if (failsafeTimer_.Get().value() > 4)
                        {
                            failsafeTimer_.Stop();
                            failsafeTimer_.Reset();
                            failsafeStarted_ = false;
                            channel_->setBallsShot(0);
                            nextPathReady_ = true;
                        }
                    }
                    else
                    {
                        shooterState_ = Shooter::REVING;
                    }

                    break;
                }
                case 1:
                {
                    intakeState_ = Intake::INTAKING;
                    shooterState_ = Shooter::TRACKING;

                    if(endOfSwervePath)
                    {
                        nextPathReady_ = true;
                    }

                    break;
                }
                case 2:
                {
                    if(endOfSwervePath)
                    {
                        intakeState_ = Intake::OUTAKING;
                        shooterState_ = Shooter::OUTAKING;

                        if (!failsafeStarted_)
                        {
                            failsafeStarted_ = true;
                            failsafeTimer_.Stop();
                            failsafeTimer_.Reset();
                            failsafeTimer_.Start();
                        }

                        if (failsafeTimer_.Get().value() > 3)
                        {
                            failsafeTimer_.Stop();
                            failsafeTimer_.Reset();
                            failsafeStarted_ = false;
                            channel_->setBallsShot(0);
                            nextPathReady_ = true;
                        }
                    }
                    else
                    {
                        intakeState_ = Intake::INTAKING;
                        shooterState_ = Shooter::TRACKING;
                    }

                    break;
                }
                case 3:
                {
                    intakeState_ = Intake::INTAKING;
                    break;
                }
            }

        }
        break;
    }
    case EYE_FOR_AN_EYE:
    {
        if (pathsOver)
        {
            intakeState_ = Intake::INTAKING;
            shooterState_ = Shooter::SHOOTING;
        }
        else
        {
            switch(pathNum_)
            {
                case 0:
                {
                    intakeState_ = Intake::INTAKING;

                    if(endOfSwervePath)
                    {
                        shooterState_ = Shooter::SHOOTING;

                        if (!failsafeStarted_)
                        {
                            failsafeStarted_ = true;
                            failsafeTimer_.Stop();
                            failsafeTimer_.Reset();
                            failsafeTimer_.Start();
                        }

                        if (failsafeTimer_.Get().value() > 4)
                        {
                            failsafeTimer_.Stop();
                            failsafeTimer_.Reset();
                            failsafeStarted_ = false;
                            channel_->setBallsShot(0);
                            nextPathReady_ = true;
                        }
                    }
                    else
                    {
                        shooterState_ = Shooter::REVING;
                    }

                    break;
                }
                case 1:
                {
                    intakeState_ = Intake::INTAKING;
                    shooterState_ = Shooter::TRACKING;

                    if(endOfSwervePath)
                    {
                        nextPathReady_ = true;
                    }

                    break;
                }
                case 2:
                {
                    intakeState_ = Intake::INTAKING;
                    shooterState_ = Shooter::TRACKING;

                    if(endOfSwervePath)
                    {
                        nextPathReady_ = true;
                    }

                    break;
                }
                case 3:
                {
                    if(endOfSwervePath)
                    {
                        intakeState_ = Intake::OUTAKING;
                        shooterState_ = Shooter::OUTAKING;

                        if (!failsafeStarted_)
                        {
                            failsafeStarted_ = true;
                            failsafeTimer_.Stop();
                            failsafeTimer_.Reset();
                            failsafeTimer_.Start();
                        }

                        if (failsafeTimer_.Get().value() > 3)
                        {
                            failsafeTimer_.Stop();
                            failsafeTimer_.Reset();
                            failsafeStarted_ = false;
                            channel_->setBallsShot(0);
                            nextPathReady_ = true;
                        }
                    }
                    else
                    {
                        intakeState_ = Intake::INTAKING;
                        shooterState_ = Shooter::TRACKING;
                    }

                    break;
                }
                case 4:
                {
                    intakeState_ = Intake::INTAKING;
                    break;
                }
            }

        }
        break;
    }
    }
}

double AutoPaths::initYaw()
{
    switch (path_)
    {
    case DEAD_BOT:
    {
        return frc::SmartDashboard::GetNumber("Auto Yaw Offset", 0);
        break;
    }
    case TAXI_DUMB:
    {
        return 0;
        break;
    }
    case TWO_DUMB:
    {
        return 0;
        break;
    }
    case ONE_DUMB_DELAYED:
    {
        return 0;
        break;
    }
    case STRAIGHT_BACK:
    {
        return 180;
        break;
    }
    case TWO_RIGHT:
    {
        return 90;
        break;
    }
    case TWO_MIDDLE:
    {
        return 135;
        break;
    }
    case TWO_LEFT:
    {
        return -135;
        break;
    }
    case THREE:
    {
        return 90;
        break;
    }
    case BIG_BOY:
    {
        return 90;
        break;
    }
    case DOMINIC:
    {
        return -135;
        break;
    }
    case EYE_FOR_AN_EYE:
    {
        return -135;
        break;
    }
    }

    return 0;
}

int AutoPaths::pathNum()
{
    return pathNum_;
}