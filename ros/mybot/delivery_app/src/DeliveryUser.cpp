	#include "delivery_app/DeliveryUser.h"
	#include "delivery_app/DeliveryConfiguration.h"


	DeliveryUser::DeliveryUser(const std::string& nodeName) : SimpleOperator(nodeName)
	{
		myLocalConfig = DeliveryConfiguration::getInstance();
		init();
	}


	void DeliveryUser::init()
	{
		ROS_INFO("Delivery User intiliazing topics subscription and publication...");

		createSubscriber("req_sub", "local_request", &DeliveryUser::requestCallback, this);

		createSubscriber("sta_from_json", "DeliveryStatusMsg/from_json", &DeliveryUser::statusCallback, this);

		createSubscriber("res_from_json", "DeliveryResultMsg/from_json", &DeliveryUser::resultCallback, this);

		createPublisher<delivery_app::DeliveryRequestMsg>("req_to_json", "DeliveryRequestMsg/to_json");

		delivery_app::DeliveryRequestMsg msg;
		msg.source_x=0.1;
		msg.source_y=0.3;
		msg.target_x=0.9;
		msg.target_y=0.4;
		msg.agent_address="127.0.0.1";
		msg.agent_id=1;
		msg.message_code=3;
		msg.header.distribution_mode="unicast";
		msg.header.message_code=3;
		//publishMessage("req_to_json", msg);
		ROS_INFO("Delivery User finished topics initialization.");

		ros::spin();
	}


	void DeliveryUser::requestCallback(const delivery_app::DeliveryRequestMsg::ConstPtr& msg)
	{
		ROS_INFO("Delivery User received/forwarded Delivery request message.");

		publishMessage("req_to_json", msg);
	}


	void DeliveryUser::statusCallback(const delivery_app::DeliveryStatusMsg::ConstPtr& msg)
	{
		ROS_INFO("Delivery User received Status message...");

		if (msg->delivery_status == "Busy")
		{
			ROS_INFO("... Robot %d is unavailable for delivery, please select another robot.", msg->agent_id);
		}
		else if (msg->delivery_status == "Ready")
		{
			ROS_INFO("... Robot %d accepted the delivery request, and it is on its way to the delivery source.", msg->agent_id);
		}
		else if (msg->delivery_status == "Source") // arrived to the source
		{
			ROS_INFO("... Robot %d arrived to the delivery source.", msg->agent_id);
		}
		else if (msg->delivery_status == "Mission")  // in delivery mission
		{
			ROS_INFO("... Robot %d is on its way to the delivery destination.", msg->agent_id);
		}
		else if (msg->delivery_status == "Target") // arrived to the destination
		{
			ROS_INFO("... Robot %d arrived to target and finished its mission.", msg->agent_id);
		}
		else if (msg->delivery_status == "Home")
		{
			ROS_INFO("... Robot %d going back to its initial location.", msg->agent_id);
		}

	}


	void DeliveryUser::resultCallback(const delivery_app::DeliveryResultMsg::ConstPtr& msg)
	{
		ROS_INFO("Delivery User received Result message...");

		ROS_INFO("... Robot %d finished delivery with cost %lf.", msg->agent_id, msg->agent_cost);

		ROS_INFO("Delivery User terminate mission.");
	}


	std::string DeliveryUser::process(BaseMessage* m)
	{
		std::string str = "";
		return str;
	}


