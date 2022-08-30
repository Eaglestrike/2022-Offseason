#pragma once

#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/geometry/Pose2d.h>
#include <iostream>
#include <frc/MathUtil.h>

#define M_PI 3.14159265358979323846

namespace GeneralConstants{ 
    const double goalHeight = 2.641;
    const double targetHeightUpper = 2.641;
    const double targetHeightLower = targetHeightUpper - 0.0508;
    const double cameraHeight = 1.384; //1.19
    const double cameraPitch = 22;
    const double radius = 0.6096;
}

typedef std::pair<double, double> LLCoordinate;
typedef std::vector<LLCoordinate> LLRectangle;
typedef std::pair<double, double> LLAnglePair;

struct LL3DCoordinate {
    double x;
    double y;
    double z;
};

class Limelight{
    public:

        Limelight();

        double getXOff();
        double getYOff();
        bool targetAquired();

        std::vector<LLRectangle> getCorners();
        void setLEDMode(std::string mode);
        double getDist(double navx, double turretAngle);
        frc::Pose2d getPose(double navx, double turretAngle);
        std::shared_ptr<nt::NetworkTable> GetNetworkTable();

        std::vector<LL3DCoordinate> getCoords();

        //should be private
        LL3DCoordinate getCenter(std::vector<LL3DCoordinate> points, double precision); //for testing purposes
        LL3DCoordinate angleToCoords(double ax, double ay, double targetHeight); //for testing purposes

    private:
        void ReadPeriodicIn();
        // void adjustAngles(double& ax, double& ay);
        // double getAdjustedX();

        std::shared_ptr<nt::NetworkTable> network_table;
        std::string table_name = "limelight";

        const int PIPELINE = 0; //can change if we want non-default pipeline

        //in meters. should be pretty close?
        //TODO: confirm measurements, make separate namespace in constants
        const double TURRET_ANGLE_OFFSET = 0.0; //todo: confirm
        const double HUB_HEIGHT = 2.7178; 
        const double CAM_HEIGHT = 0.52324;
        const double CAM_ANGLE = 40; //40 degrees I think

        LLCoordinate pixelsToAngle(double px, double py);
        
        LLRectangle sortCorners(LLRectangle rectCorners);

        //LL3DCoordinate getCenter(std::vector<LL3DCoordinate> points, double precision);
        double calcResidual(double radius, std::vector<LL3DCoordinate> points, LL3DCoordinate center);
};