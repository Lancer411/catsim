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
	totalDuration = durationGreen + durationYellow + durationRed + DEFAULT_GET_READY_DURATION;
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
		counter = durationGreen - DEFAULT_BLINK_DURATION;
	else if (currentSignal == Yellow)
		counter = durationGreen;
	else if (currentSignal == Red)
		counter = durationGreen + durationYellow;
	else if (currentSignal == GetReady)
		counter = totalDuration - DEFAULT_GET_READY_DURATION;
}

void lightsignal::resetSignal()
{
	if ((counter >= 0) && (counter <= durationGreen - DEFAULT_BLINK_DURATION))
		currentSignal = Green;
	else if ((counter > durationGreen - DEFAULT_BLINK_DURATION) && (counter <= durationGreen))
		currentSignal = GreenBlink;
	else if ((counter > durationGreen) && (counter <= durationGreen + durationYellow))
		currentSignal = Yellow;
	else if ((counter > durationGreen + durationYellow) && (counter <= totalDuration - DEFAULT_GET_READY_DURATION))
		currentSignal = Red;
	else if (counter > totalDuration - DEFAULT_GET_READY_DURATION)
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
