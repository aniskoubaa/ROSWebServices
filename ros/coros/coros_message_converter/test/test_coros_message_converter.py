#!/usr/bin/env python
import unittest
import rospy
import rostest

class TestCorosMessageConverter(unittest.TestCase):

    def test_msg_to_json_with_robot_msg(self):
        from coros_messages.msg import RobotMsg
        message = RobotMsg(message_code=100, robot_id = '1', )
        expected_json = '{"message_code": "100", "robot_id": "1"}'
        returned_json = '{"message_code": "100", "robot_id": "1"}'
	
        rospy.init_node('test_coros_message_converter', anonymous=True)
        pub = rospy.Publisher('to_json', RobotMsg, queue_size=50)
        rospy.loginfo("robot_id: " + message.robot_id)
        pub.publish(message)

        self.assertEqual(returned_json, expected_json)
'''
    def test_msg_to_json_with_hello_msg(self):
        from coros_messages import HelloMsg
        rospy.init_node('time_node')
        now_time = rospy.Time.now()
        expected_json = '{{"stamp": {{"secs": {0}, "nsecs": {1}}}, "frame_id": "my_frame", "seq": 3}}'\
            .format(now_time.secs, now_time.nsecs)
        message = Header(stamp = now_time, frame_id = 'my_frame', seq = 3)
        returned_json = json_message_converter.convert_ros_message_to_json(message)
        self.assertEqual(returned_json, expected_json)

    def test_json_with_string(self):
        from std_msgs.msg import String
        expected_message = String(data = 'Hello')
        json_str = '{"data": "Hello"}'
        message = json_message_converter.convert_json_to_ros_message('std_msgs/String', json_str)
        self.assertEqual(message, expected_message)

    def test_json_with_header(self):
        from std_msgs.msg import Header
        rospy.init_node('time_node')
        now_time = rospy.Time.now()
        expected_message = Header(
            stamp = now_time,
            frame_id = 'my_frame',
            seq = 12
        )
        json_str = '{{"stamp": {{"secs": {0}, "nsecs": {1}}}, "frame_id": "my_frame", "seq": 12}}'\
            .format(now_time.secs, now_time.nsecs)
        message = json_message_converter.convert_json_to_ros_message('std_msgs/Header', json_str)
        self.assertEqual(message, expected_message)

    def test_msg_with_invalid_message_fields(self):
        self.assertRaises(ValueError,
                          json_message_converter.convert_json_to_ros_message,
                          'std_msgs/String',
                          '{"not_data": "Hello"}')

'''
PKG = 'coros_message_converter'
NAME = 'test_coros_message_converter'
if __name__ == '__main__':
    rostest.unitrun(PKG, NAME, TestCorosMessageConverter)
