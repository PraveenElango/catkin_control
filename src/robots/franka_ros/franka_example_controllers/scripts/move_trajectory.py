#!/usr/bin/env python

import rospy
from moveit_commander import MoveGroupCommander
from actionlib_msgs.msg import GoalStatusArray
from geometry_msgs.msg import Twist
import numpy as np
import time

def talker():
    pub = rospy.Publisher('/cartesian_pose_trajectory_controller/cartesian_pose', Twist, queue_size=10)
    count = 0
    elapsed_time_ = 0
    radius = 0.3
    
    twist = Twist()
    count = 0
    t = rospy.Time.from_sec(time.time())
    seconds = t.to_sec()
    print(t)
    while not rospy.is_shutdown():

    
        d = rospy.Duration(0.001).to_sec()
        
        '''
        if elapsed_time_ < 1:
            count += 1
        '''
        #print(count)
        elapsed_time_ += d
        angle = np.pi / 4 * (1 - np.cos(np.pi / 5.0 * elapsed_time_))
        twist.linear.x = angle
        pub.publish(twist)


if __name__ == '__main__':
    rospy.init_node('move_trajectory')
    talker()
