/*
 * MybotCallOperator.h
 *
 *  Created on: May 9, 2015
 *      Author: akoubaa
 */

#ifndef MYBOTCALLOPERATOR_H_
#define MYBOTCALLOPERATOR_H_

#include "coros_operator/RobotOperator.h"
//#include "delivery_app/DeliveryConfiguration.h"
#include "mybot_call_app/CallRequestMsg.h"

class MybotCallOperator : public RobotOperator
{

public:

	MybotCallOperator(int robotId, const std::string& nodeName);

  void requestCallback(const mybot_call_app::CallRequestMsg::ConstPtr& msg);

protected:

  void init();

  std::string process(BaseMessage*);

};

#endif // MYBOTCALLOPERATOR_H_

