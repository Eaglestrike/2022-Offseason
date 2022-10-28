#pragma once

#include <frc/Timer.h>

#include "SwerveDrive.h"
#include "Intake.h"
#include "Shooter.h"
#include "SwervePath.h"
#include "Channel.h"
#include "Constants.h"
#include <vector>

class AutoPaths
{
    public:
        enum Path
        {
            DEAD_BOT,
            TAXI_DUMB,
            TWO_DUMB,
            ONE_DUMB_DELAYED,
            STRAIGHT_BACK,
            TWO_RIGHT,
            TWO_MIDDLE,
            TWO_LEFT,
            THREE,
            BIG_BOY,
            DOMINIC,
            EYE_FOR_AN_EYE
        };
        AutoPaths(Channel* channel);
        void setPath(Path path);
        Path getPath();

        Shooter::State getShooterState();
        Intake::State getIntakeState();

        void startTimer();
        void setSetPath(bool setPath);

        void periodic(double yaw, SwerveDrive* swerveDrive);
        double initYaw();

        int pathNum();
    private:
        Channel* channel_;
        Path path_;
        Shooter::State shooterState_;
        Intake::State intakeState_;

        frc::Timer timer_;
        frc::Timer failsafeTimer_;
        double startTime_;
        bool nextPathReady_, failsafeStarted_, dumbTimerStarted_, pathSet_;

        vector<SwervePath> swervePaths_;
        int pathNum_;
};