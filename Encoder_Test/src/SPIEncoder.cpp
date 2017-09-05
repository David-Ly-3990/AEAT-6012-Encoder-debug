/*
 * SPIEncoder.cpp
 *
 *  Created on: 9 mai 2017
 *      Author: 14141106
 */

#include <SPIEncoder.h>

SPIEncoder::SPIEncoder():
m_FrontRight(3),
m_Clock(5),
m_ChipSelect(4)


{
	m_GetAjustment.open("Ajustment.txt"); // open ajustment text file to read
	if(!m_GetAjustment.is_open()) // check if the file can be openned
	{
		SmartDashboard::PutNumber("Text file", 0);
		m_GetAjustment.close(); // close file if previous is failed
		m_SetAjustment.open("Ajustment.txt"); // create a  text file
		m_SetAjustment<< 0 <<std::endl<< 0 <<std::endl<< 0 <<std::endl<< 0 <<std::endl; // set all 4 value to 0
		m_SetAjustment.close();	// close file
		m_GetAjustment.open("Ajustment.txt"); //open file to read

	}
	else SmartDashboard::PutNumber("Text file", 1);
	char num[17];




	for(int i =0; i <4; ++i)
	{
		m_bittointeger[i] = 0; // reset all values

		 m_GetAjustment.getline(num,17); // Get ajustment values
		 m_ajustments[i] = std::atof(num); // Set ajustment values in a variable
	}
	m_GetAjustment.close(); // close file
	m_GetAjustment.open("Ajustment.txt");
	m_GetAjustment.getline(num,17);
	SmartDashboard::PutString("Value", num);

m_timer.Start();
m_timer.Stop();
m_timer.Reset();
m_ChipSelect.Set(false);
}

SPIEncoder::~SPIEncoder() {
	// TODO Auto-generated destructor stub
}

void SPIEncoder::GetAngle()
{

	for(int i = 0; i<4;++i) // reset angle values
	{
		m_bittointeger[i] = 0;
	}
	m_ChipSelect.Set(false); // tell encoder to start reading soon
	std::cout<<"CHIPENABLE"<<std::endl;
	m_timer.Start();	// start timer for encoder to boot up

	if(m_timer.HasPeriodPassed(0.001)) return; //wait
	m_timer.Stop(); //stop timer
	m_timer.Reset(); //reset timer

	for(int i =0; i <12;++i) // a FOR to read all 10 bits
	{
		// 1 clock tick = 1 bit


		m_Clock.Set(true); // activates clock

		m_bittointeger[SPIEncoder::kFrontRight] += pow(2,12-i)*((int)m_FrontRight.Get()); // get the bit value and convert it to decimal

		m_Clock.Set(false); // stop clock


	}


	m_ChipSelect.Set(true); // tell encoder to stop reading




}

double SPIEncoder::ReturnAngle(int position)
{
	return fmod((m_bittointeger[position]*1/4096*360)/2 - m_ajustments[position] + 360,360);
}

void SPIEncoder::Ajustments()
{
	m_SetAjustment.open("Ajustment.txt"); // open the ajustment file

	this->GetAngle();

		m_SetAjustment << m_bittointeger[0] << std::endl;


	m_SetAjustment.close();
	//SmartDashboard::PutNumber("Front-Right",m_ajustments[SPIEncoder::kFrontRight]);
	//SmartDashboard::PutNumber("Front-Left",m_ajustments[SPIEncoder::kFrontLeft]);
	//SmartDashboard::PutNumber("Back-Left",m_ajustments[SPIEncoder::kBackLeft]);
	//SmartDashboard::PutNumber("Back-Right",m_ajustments[SPIEncoder::kBackRight]);
}


