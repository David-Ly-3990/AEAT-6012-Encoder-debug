#include <iostream>
#include <memory>
#include <string>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include "WPIlib.h"
#include "SPIEncoder.h"

class Robot: public frc::IterativeRobot {
public:
	SPIEncoder encoder;
	Joystick m_Pilot;
	VictorSP m_motor;
	Robot():
	m_Pilot(0),
	m_motor(0)
	{

	}

	void RobotInit()
	{

		chooser.AddDefault(autoNameDefault, autoNameDefault);
		chooser.AddObject(autoNameCustom, autoNameCustom);
		frc::SmartDashboard::PutData("Auto Modes", &chooser);
	}



	void TeleopInit() {
		encoder.GetAngle();
	}

	void TeleopPeriodic()
	{
		m_motor.Set(.6);
		encoder.GetAngle();
		SmartDashboard::PutNumber("angle: ", encoder.ReturnAngle(0));
		if(m_Pilot.GetRawButton(0))
		{
			encoder.Ajustments();
		}
	}
void TestInit()
{
	encoder.GetAngle();
	SmartDashboard::PutNumber("angle: ", encoder.ReturnAngle(0));
}
	void TestPeriodic()
	{
		if(m_Pilot.GetRawButton(0)&&m_Pilot.GetRawButton(1))
		{
			encoder.Ajustments();
		}
	}

private:
	frc::LiveWindow* lw = LiveWindow::GetInstance();
	frc::SendableChooser<std::string> chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;
};

START_ROBOT_CLASS(Robot)
