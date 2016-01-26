#!/usr/bin/env python

import sys
from importlib import import_module

import rospy
from std_msgs.msg import String
from rospy_message_converter import json_message_converter

#publisher object
pub = None

#message type
typ = None

def callback(message):
    global typ
    #message.data = message.data.rstrip()
    #print message.data
    jsn=""
    jsn = message.data.replace("\'", '"')
    jsn = jsn[:jsn.index("}")+1]
    print "message: " 
    print message
    print "\n\njsn "
    print jsn 
    print typ
    returned_message = json_message_converter.convert_json_to_ros_message(typ, jsn)
    print returned_message
    #jsn2=json_message_converter.convert_ros_message_to_json(returned_message)
    #returned_message = json_message_converter.convert_json_to_ros_message(typ, jsn2)
    
    pub.publish(returned_message) #forward the message

def listener(topic_name, message_type):
    rospy.Subscriber(topic_name, message_type, callback)
    rospy.spin()
   
if __name__ == '__main__':
    rospy.init_node('coros_msg_from_json', anonymous=True)
    if len(sys.argv) > 2:
        pkg = sys.argv[1]+".msg"          #string represents the package of the ros messages
        typ = sys.argv[1]+"/"+sys.argv[2] #string represents the message type
        mod = import_module(pkg)          #imports the package containing the ros message type
        pub = rospy.Publisher("from_json", eval("mod."+sys.argv[2]), queue_size=100)
        listener("in_box", String)
    else:
        rospy.loginfo("Missing script parameters. Usage: coros_msg_from_json.py message_package message_type")

