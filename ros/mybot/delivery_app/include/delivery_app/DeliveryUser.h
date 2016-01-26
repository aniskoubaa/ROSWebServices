#ifndef DELIVERY_USER_H
#define DELIVERY_USER_H

#include "coros_operator/SimpleOperator.h"
#include "delivery_app/DeliveryConfiguration.h"

#include "delivery_app/DeliveryResultMsg.h"
#include "delivery_app/DeliveryRequestMsg.h"
#include "delivery_app/DeliveryStatusMsg.h"


class DeliveryUser : public SimpleOperator
{

public:
  
  DeliveryUser(const std::string& nodeName);
  
  void requestCallback(const delivery_app::DeliveryRequestMsg::ConstPtr& msg);

  void statusCallback(const delivery_app::DeliveryStatusMsg::ConstPtr& msg);
  
  void resultCallback(const delivery_app::DeliveryResultMsg::ConstPtr& msg); 
     
protected:
  
  void init();
  
  std::string process(BaseMessage*);

  DeliveryConfiguration* myLocalConfig;
 
};
#endif // DELIVERY_USER_H
