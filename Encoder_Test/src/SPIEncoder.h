/*
 * SPIEncoder.h
 *
 *  Created on: 9 mai 2017
 *      Author: 14141106
 */

#include "WPILib.h"
#include <DigitalInput.h>
#include <DigitalOutput.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <math.h>

#define FRONTRIGHTENCODER 3
#define CLOCK 5
#define CHIPSELECT 4

#ifndef SRC_SPIENCODER_H_
#define SRC_SPIENCODER_H_

class SPIEncoder {
public:

	enum Position { kFrontRight, kFrontLeft, kBackLeft, kBackRight};
	SPIEncoder();
	virtual ~SPIEncoder();

	void GetAngle(); //get all angles
	double ReturnAngle(int position); //return the value of the requested value
	void Ajustments();
private:

	DigitalInput m_FrontRight;
	DigitalOutput m_Clock;
	DigitalOutput m_ChipSelect;

	Timer m_timer;

	double m_bittointeger[4];
	double m_ajustments[4];

	std::ifstream m_GetAjustment;
	std::ofstream m_SetAjustment;
};

#endif /* SRC_SPIENCODER_H_ */
