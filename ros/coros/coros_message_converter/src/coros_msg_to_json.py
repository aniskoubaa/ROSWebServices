#!/usr/bin/env python

import sys
from importlib import import_module

import rospy
from rospy_message_converter import json_message_converter
from coros_messages.msg import OutBoxMsg

#publisher object
pub = None

#message type
typ = None

def callback(message):
    global typ
    returned_json = json_message_converter.convert_ros_message_to_json(message)
    outbox_message = OutBoxMsg(header=message.header, message_type=typ, message_content=returned_json)
    pub.publish(outbox_message)

def listener(topic_name, message_type):
    rospy.Subscriber(topic_name, message_type, callback)
    rospy.spin()
   
if __name__ == '__main__':
    rospy.init_node('coros_msg_to_json', anonymous=True)
    if len(sys.argv) > 2:
	pkg = sys.argv[1]+".msg"          #string represents the package of the ros messages
        typ = sys.argv[1]+"/"+sys.argv[2]
        mod = import_module(pkg)
        pub = rospy.Publisher("out_box", OutBoxMsg, queue_size=100)
        listener("to_json", eval("mod."+sys.argv[2]))
    else:
        rospy.loginfo("Missing script parameters. Usage: coros_msg_to_json.py  message_package message_type")
