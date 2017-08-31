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
	m_GetAjustment.open("Ajustment.txt");
	if(!m_GetAjustment.is_open())
	{
		m_GetAjustment.close();
		m_SetAjustment.open("Ajustment.txt");
		m_SetAjustment<< 0 <<std::endl<< 0 <<std::endl<< 0 <<std::endl<< 0 <<std::endl;
		m_SetAjustment.close();
		m_GetAjustment.open("Ajustment.txt");
	}
	char num[17];



	for(int i =0; i <4; ++i)
	{
		m_bittointeger[i] = 0;

		 m_GetAjustment.getline(num,17);
		 m_ajustments = (double)num;
	}
	m_GetAjustment.close();


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

		std::cout<<m_FrontRight.Get();
		m_Clock.Set(false); // stop clock


	}
	std::cout<<std::endl;

	m_ChipSelect.Set(true); // tell encoder to stop reading
	std::cout<<"CHIPdisable"<<std::endl;



}

double SPIEncoder::ReturnAngle(int position)
{
	return ((m_bittointeger[position]*1/4096*360)/2)+ m_ajustments;
}

void SPIEncoder::Ajustments()
{
	m_SetAjustment.open("Ajustment.txt"); // open the ajustment file

	this->GetAngle();
	for(int i = 0; i<4;++i)
	{
		m_SetAjustment << m_bittointeger[i]<< std::endl;
	}

	m_SetAjustment.close();
	//SmartDashboard::PutNumber("Front-Right",m_ajustments[SPIEncoder::kFrontRight]);
	//SmartDashboard::PutNumber("Front-Left",m_ajustments[SPIEncoder::kFrontLeft]);
	//SmartDashboard::PutNumber("Back-Left",m_ajustments[SPIEncoder::kBackLeft]);
	//SmartDashboard::PutNumber("Back-Right",m_ajustments[SPIEncoder::kBackRight]);
}

/*
 * // Example program
#include <iostream>
#include <string>
#include <math.h>

int main()
{
    int bit = 0;
    int integer = 0;
    int a=0;
    char aa[10];
    fgets (aa, 10, stdin);

    bit = atoi(aa);

  for(int i = 0; bit != 0 ; ++i )
  {
      a = bit % 10;
      bit= (bit)/10;//(a>1? 1:0))/10;
      std::cout<< bit <<std::endl;

     if(a>0)
     {
      integer += pow(2,i);
     }

  }
  std::cout<< integer<<std::endl;

}
 */
