#!/usr/bin/env python
import rospy
from rospy_message_converter import json_message_converter


def test_json_with_taskmsg():
	from coros_messages.msg import TaskMsg
	print("Hola 1:")
        #expected_message = String(data = 'Hello')
	expected_message = TaskMsg(robot_id = 1, message_code= 100, task_id= 20)
	#json_str = '{"data": "Hello"}'
	json_str = '{"robot_id": 1, "message_code": 100, "task_id": 2}'
	print("Hola 1:")
        message = json_message_converter.convert_json_to_ros_message('coros_messages/TaskMsg', json_str)
	print(message)

if __name__ == '__main__':
    test_json_with_taskmsg()



