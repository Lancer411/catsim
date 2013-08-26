/*
 * LightSignal.cpp
 *
 *  Created on: 03.06.2013
 *      Author: ekaterina
 */

#include "lightsignal.h"


lightsignal::lightsignal() {
	// TODO Auto-generated constructor stub

}
lightsignal::lightsignal(int durationGreen, int durationYellow, int durationRed, light_signal_state currentSignal)
{
	setWorking(true);
	setSignal(currentSignal);
	setDurations(durationGreen,durationYellow, durationRed);
	resetCounter();
}

void lightsignal::setDurations(int durationGreen, int durationYellow, int durationRed)
{
	this->durationGreen = durationGreen;
	this->durationYellow = durationYellow;
	this->durationRed = durationRed;
	totalDuration = durationGreen + durationYellow + durationRed + cadef::get_ready_duration;
}

void lightsignal::iterate()
{

	if (working)
	{
		if (++counter <= totalDuration)
			resetSignal();
		else
		{
			counter = 0;
			currentSignal = Green;
		}
	}
}

void lightsignal::resetCounter()
{
	if (currentSignal == Green)
		counter = 0;
	else if (currentSignal == GreenBlink)
		counter = durationGreen - cadef::blink_duration;
	else if (currentSignal == Yellow)
		counter = durationGreen;
	else if (currentSignal == Red)
		counter = durationGreen + durationYellow;
	else if (currentSignal == GetReady)
		counter = totalDuration - cadef::get_ready_duration;
}

void lightsignal::resetSignal()
{
	if ((counter >= 0) && (counter <= durationGreen - cadef::blink_duration))
		currentSignal = Green;
	else if ((counter > durationGreen - cadef::blink_duration) && (counter <= durationGreen))
		currentSignal = GreenBlink;
	else if ((counter > durationGreen) && (counter <= durationGreen + durationYellow))
		currentSignal = Yellow;
	else if ((counter > durationGreen + durationYellow) && (counter <= totalDuration - cadef::get_ready_duration))
		currentSignal = Red;
	else if (counter > totalDuration - cadef::get_ready_duration)
		currentSignal = GetReady;
}

void lightsignal::setWorking(bool working)
{
	this->working = working;
	if (!working)
	{
		signalBeforeBroken = currentSignal;
		currentSignal = Broken;
	}
	else
		currentSignal = signalBeforeBroken;
}

std::string lightsignal::getsignalColor() const
{
	switch(currentSignal)
	{
		case Green:
			return "Green";
			break;
		case GreenBlink:
			return "GreenBlink";
			break;
		case Yellow:
			return "Yellow";
			break;
		case Red:
			return "Red";
			break;
		case GetReady:
			return "GetReady";
			break;
		case Broken:
			return "Broken";
			break;
	}
}
lightsignal::~lightsignal() {
	// TODO Auto-generated destructor stub
}
