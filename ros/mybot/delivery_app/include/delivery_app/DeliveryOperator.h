#ifndef DELIVERY_OPERATOR_H
#define DELIVERY_OPERATOR_H

#include "coros_operator/RobotOperator.h"
#include "delivery_app/DeliveryConfiguration.h"
#include "delivery_app/DeliveryRequestMsg.h"

class DeliveryOperator : public RobotOperator
{

public:
  
  DeliveryOperator(int robotId, const std::string& nodeName);
   
  void requestCallback(const delivery_app::DeliveryRequestMsg::ConstPtr& msg);
  
protected:
  
  void init();
  
  std::string process(BaseMessage*);

  DeliveryConfiguration* myLocalConfig;
   
};
#endif // DELIVERY_OPERATOR_H
