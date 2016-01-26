#include "delivery_app/DeliveryOperator.h"
#include "delivery_app/DeliveryResultMsg.h"
#include "delivery_app/DeliveryStatusMsg.h"

#include "coros_tasks/SimpleMoveToTask.h"

DeliveryOperator::DeliveryOperator(int robotId, const std::string& nodeName) : RobotOperator(robotId, nodeName) 
{
  myLocalConfig = DeliveryConfiguration::getInstance();
  init();
}

void DeliveryOperator::init()
{
  ROS_INFO("Delivery Operator intiliazing topics subscription and publication...");  
  
  createSubscriber("req_from_json", "DeliveryRequestMsg/from_json", &DeliveryOperator::requestCallback, this); 

  createPublisher<delivery_app::DeliveryStatusMsg>("sta_to_json", "DeliveryStatusMsg/to_json"); 
  
  createPublisher<delivery_app::DeliveryResultMsg>("res_to_json", "DeliveryResultMsg/to_json"); 

  ROS_INFO("Delivery Operator finished topics initialization.");
  
  ros::spin();
}


void DeliveryOperator::requestCallback(const delivery_app::DeliveryRequestMsg::ConstPtr& msg)
{
  ROS_INFO("Courier Robot Operator received Request message from the Courier Robot server.");
  
  // save the request source/target coordinates
  myLocalConfig->setSourcePositionX( msg->source_x );
  myLocalConfig->setSourcePositionY( msg->source_y );
  myLocalConfig->setTargetPositionX( msg->target_x );
  myLocalConfig->setTargetPositionY( msg->target_y );

  // prepare the header of the status message
  delivery_app::DeliveryStatusMsg status_message;
  status_message.header.distribution_mode = "unicast";
  status_message.header.ip_addresses.push_back( msg->agent_address );
  status_message.header.ports.push_back( msg->agent_port );

  status_message.agent_id = myLocalConfig->getAgentId();
  
  if (myLocalConfig->isUnavailableAgent())
  {
      // send busy.
     status_message.delivery_status = "Busy";
     publishMessage("sta_to_json", status_message);
  } 
  else
  {
     myLocalConfig->setUnavailableAgentStatus();
     
     // send ready
     status_message.delivery_status = "Ready";
     publishMessage("sta_to_json", status_message);

     // moving to the source
     SimpleMoveToTask task(0,
			   myLocalConfig->getAgentRunningMode(),
			   myLocalConfig->getSourcePositionX(),
			   myLocalConfig->getSourcePositionY());
     perform(&task);

     // send source // arrived to source
     status_message.delivery_status = "Source";
     publishMessage("sta_to_json", status_message);

     // wait until putting on the delivery object
     ROS_INFO("Please put the object to be delivered in the specific plane, then press 'Enter'...");
     getchar();
     
     // send mission
     status_message.delivery_status = "Mission";
     publishMessage("sta_to_json", status_message);
 
     // moving to the target
     task.setTargetX( myLocalConfig->getTargetPositionX() );
     task.setTargetY( myLocalConfig->getTargetPositionY() );
     perform(&task);

     // send target // arrived to the target
     status_message.delivery_status = "Target";
     publishMessage("sta_to_json", status_message);

     // wait until getting off the delivery object
     ROS_INFO("Please get off the delivered object, then press 'Enter'...");
     getchar();

     // send home // in the way to its initial localtion.
     status_message.delivery_status = "Home";
     publishMessage("sta_to_json", status_message);

     // moving to the initial position
     task.setTargetX( task.getInitialPositionX() );
     task.setTargetY( task.getInitialPositionY() );
     perform(&task);

     // send Result message 
     delivery_app::DeliveryResultMsg result_message;
     result_message.header.distribution_mode = "unicast";
     result_message.header.ip_addresses.push_back( msg->agent_address );
     result_message.header.ports.push_back( msg->agent_port );
     
     result_message.agent_id     = myLocalConfig->getAgentId();
     result_message.agent_cost   = task.getCost();
     result_message.source_x	 = myLocalConfig->getSourcePositionX();
     result_message.source_y	 = myLocalConfig->getSourcePositionY();
     result_message.target_x	 = myLocalConfig->getTargetPositionX();
     result_message.target_y	 = myLocalConfig->getTargetPositionY();

     publishMessage("res_to_json", result_message);

     myLocalConfig->setAvailableAgentStatus();
  } 
 
}

std::string DeliveryOperator::process(BaseMessage* m)
{
  std::string str = "";
  return str;
}
