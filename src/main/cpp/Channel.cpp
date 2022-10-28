#include "Channel.h"

Channel::Channel()
{
    ballCount_ = 0;
    ballsShot_ = 0;
    //seeingBall_ = false;
}

void Channel::periodic()
{
    //int proximity = colorSensor_.GetProximity();
    //int proximity2 = colorSensor2_.GetProximity();
    /*if(!seeingBall_ && proximity > ChannelConstants::BALL_PROXIMITY)
    {
        increaseBallCount();
        seeingBall_ = true;
    }

    if(seeingBall_ && proximity < ChannelConstants::BALL_PROXIMITY)
    {
        seeingBall_ = false;
    }

    frc::SmartDashboard::PutNumber("Ball Count", ballCount_);

    if(ballCount_ == 0 && proximity > ChannelConstants::BALL_PROXIMITY)
    {
        ballCount_ = 1;
    }*/

    /*if(proximity > ChannelConstants::BALL_PROXIMITY || proximity2 > ChannelConstants::BALL_PROXIMITY_2)
    {
        ballCount_ = 1;
    }
    else
    {
        ballCount_ = 0;
    }*/

    if(!photogate_.Get())
    {
        ballCount_ = 1;
        frc::Color color = colorSensor_.GetColor();

        Color ballColor;
        if(color.red > 1.35 * color.blue || color.red > 0.3)
        {
            ballColor = RED;
        }
        else if(color.blue > 1.35 * color.red || color.blue > 0.3)
        {
            ballColor = BLUE;
        }
        else
        {
            ballColor = UNKNOWN;
        }

        //frc::SmartDashboard::PutNumber("r", color.red);
        //frc::SmartDashboard::PutNumber("g", color.green);
        //frc::SmartDashboard::PutNumber("b", color.blue);

        badIdea_ = (ballColor != color_ && ballColor != UNKNOWN);
    }
    else
    {
        ballCount_ = 0;
        badIdea_ = false;
    }
}

void Channel::setColor(Color color)
{
    color_ = color;
}

Channel::Color Channel::getColor()
{
    return color_;
}

bool Channel::badIdea()
{
    /*frc::Color color = colorSensor_.GetColor();
    frc::Color color2 = colorSensor2_.GetColor();
    int proximity = colorSensor_.GetProximity();
    int proximity2 = colorSensor2_.GetProximity();

    frc::SmartDashboard::PutNumber("prox", proximity);
    frc::SmartDashboard::PutNumber("prox2", proximity2);

    frc::SmartDashboard::PutNumber("r", color.red);
    frc::SmartDashboard::PutNumber("g", color.green);
    frc::SmartDashboard::PutNumber("b", color.blue);
    frc::SmartDashboard::PutNumber("r2", color2.red);
    frc::SmartDashboard::PutNumber("g2", color2.green);
    frc::SmartDashboard::PutNumber("b2", color2.blue);

    if(proximity2 > proximity)
    {
        color = color2;
    }

    Color ballColor;
    if(color.red > 1.5 * color.blue)
    {
        ballColor = RED;
    }
    else if(color.blue > 1.5 * color.red)
    {
        ballColor = BLUE;
    }
    else
    {
        ballColor = UNKNOWN;
    }
    //0.394, 0.1856, red
    //0.5003, 0.1207, red
    //0.3907, 0.1861, red

    //0.2625, 0.2432, neither


    if(proximity < ChannelConstants::BALL_PROXIMITY && proximity2 < ChannelConstants::BALL_PROXIMITY_2)
    {
        return false;
    }

    bool badIdea = (ballColor != color_ && ballColor != UNKNOWN);

    return badIdea;*/

    return badIdea_;
}

int Channel::getBallCount()
{
    return ballCount_;
}

int Channel::getBallsShot()
{
    return ballsShot_;
}

void Channel::increaseBallCount()
{
    if(ballCount_ < GeneralConstants::MAX_BALL_COUNT)
    {
        ++ballCount_;
    }
}

void Channel::decreaseBallCount()
{
    if(ballCount_ > 0)
    {
        --ballCount_;
        ++ballsShot_;
    }
}

void Channel::setBallCount(int ballCount)
{
    if(ballCount < 0)
    {
        ballCount_ = 0;
    }
    else if(ballCount > GeneralConstants::MAX_BALL_COUNT)
    {
        ballCount_ = GeneralConstants::MAX_BALL_COUNT;
    }
    else
    {
        ballCount_ = ballCount;
    }
}

void Channel::setBallsShot(int ballsShot)
{
    ballsShot_ = ballsShot;
}

/*void Channel::setSeeingBall(bool seeingBall)
{
    seeingBall_ = seeingBall;
}*/