/*
 * MybotDeliveryOperator.h
 *
 *  Created on: May 17, 2015
 *      Author: mfsriti
 */

#ifndef MYBOTDELIVERYOPERATOR_H_
#define MYBOTDELIVERYOPERATOR_H_

#include "coros_operator/RobotOperator.h"
#include "mybot_delivery_app/DeliveryRequestMsg.h"
#include "sound_play/sound_play.h"
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <kobuki_msgs/AutoDockingAction.h>

class MybotDeliveryOperator : public RobotOperator
{

public:

	MybotDeliveryOperator(int robotId, const std::string& nodeName);

	void requestCallback(const mybot_delivery_app::DeliveryRequestMsg::ConstPtr& msg);
	static const int HELLO_MESSAGE_CODE;
	static const int GO_TO_GOAL_MESSAGE_CODE;
	static const int COURIER_DELIVERY_MESSAGE_CODE;
	static const int COFFEE_DELIVERY_MESSAGE_CODE;

protected:

	void init();

	std::string process(BaseMessage*);
	void processDeliveryRequest(const mybot_delivery_app::DeliveryRequestMsg::ConstPtr& msg);
	void processCoffeeRequest(const mybot_delivery_app::DeliveryRequestMsg::ConstPtr& msg);

	bool moveTo(double x, double y);
	sound_play::SoundClient sc;
	std::string path_to_voices;
	std::string path_to_sounds;
	//actionlib::SimpleActionClient<kobuki_msgs::AutoDockingAction> ac;

};

#endif // MYBOTDELIVERYOPERATOR_H_

