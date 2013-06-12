/*
 * LightSignal.h
 *
 *  Created on: 03.06.2013
 *      Author: ekaterina
 */

#ifndef LIGHTSIGNAL_H_
#define LIGHTSIGNAL_H_
#include "define/cadef.h"
#include "entity.h"

class lightsignal:public entity
{
	bool working;

	light_signal_state currentSignal;
	light_signal_state signalBeforeBroken;
	std::string note;
	int durationGreen;
	int durationYellow;
	int durationRed;
	int counter;
	int totalDuration;

public:
	lightsignal();
	lightsignal(int durationGreen, int durationYellow, int durationRed,	light_signal_state currentSignal);
	virtual ~lightsignal();
	void setDurations(int durationGreen, int durationYellow, int durationRed);
	void setSignal (light_signal_state sig) { this->currentSignal = sig;};
	light_signal_state getSignal() const {return currentSignal; };
	std::string getsignalColor() const;
	void resetCounter();
	void resetSignal();
	int getDuration() const {return totalDuration; };
	int getGreenDuration() const {return totalDuration; };
	int getYellowDuration() const {return totalDuration; };
	int getRedDuration() const {return totalDuration; };
	void tick() { iterate();};
	std::string getNote() const { return note;};
	void setNote(std::string note) { this->note = note;};
	bool isWorking() const { return working;};
	void setWorking(bool working);
private:
	void iterate();
};
typedef boost::shared_ptr<lightsignal> lightsignal_ptr;
#endif /* LIGHTSIGNAL_H_ */
