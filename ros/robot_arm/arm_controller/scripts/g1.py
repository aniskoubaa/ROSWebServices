#!/usr/bin/env python

""" 
  Copyright (c) 2011 Michael E. Ferguson. All right reserved.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software Foundation,
  Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
"""

import roslib; roslib.load_manifest('arbotix_controllers')
import rospy
import actionlib
import sys

from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint
from control_msgs.msg import *

servos = ['gripper_joint']

forward = [1.5]
to_side = [0.2]
tucked = [1.5]

class tuck_arm:
    
    def __init__(self, client=None):
        if client != None:
            self._client = client
        else:
            self._client = actionlib.SimpleActionClient('gripper_controller/gripper_action', FollowJointTrajectoryAction)
        self._client.wait_for_server()

    def tuck(self):
        # prepare a joint trajectory
        msg = JointTrajectory()
        msg.joint_names = servos
        msg.points = list()
    
        point = JointTrajectoryPoint()
        point.positions = forward
        point.velocities = [ 0.0 for servo in msg.joint_names ]
        point.time_from_start = rospy.Duration(5.0)
        msg.points.append(point)
       # point = JointTrajectoryPoint()
        #point.positions = to_side
        #point.velocities = [ 0.0 for servo in msg.joint_names ]
        #point.time_from_start = rospy.Duration(8.0)
        #msg.points.append(point)
        #point = JointTrajectoryPoint()
        #point.positions = tucked
        #point.velocities = [ 0.0 for servo in msg.joint_names ]
        #point.time_from_start = rospy.Duration(11.0)
        #msg.points.append(point)

        # call action
        msg.header.stamp = rospy.Time.now() + rospy.Duration(0.1)
        goal = FollowJointTrajectoryGoal()
        goal.trajectory = msg
        self._client.send_goal(goal)
        
    def untuck(self):
        # prepare a joint trajectory
        msg = JointTrajectory()
        msg.joint_names = servos
        msg.points = list()
        
        point = JointTrajectoryPoint()
        point.positions = to_side
        point.velocities = [ 0.0 for servo in msg.joint_names ]
        point.time_from_start = rospy.Duration(3.0)
        msg.points.append(point)

        # call action
        msg.header.stamp = rospy.Time.now() + rospy.Duration(0.1)
        goal = FollowJointTrajectoryGoal()
        goal.trajectory = msg
        self._client.send_goal(goal)
    
if __name__=="__main__":
    rospy.init_node("tuck_arm")
    tuck = tuck_arm()
    
    # tucking or untucking?
    if len(sys.argv) > 1 and sys.argv[1].find("u") > -1:
        tuck.untuck()
    else:
        tuck.tuck()
    
    # sleep three secs (while latched)
    rospy.sleep(3)


