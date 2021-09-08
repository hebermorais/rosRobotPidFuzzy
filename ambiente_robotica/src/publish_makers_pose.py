#! /usr/bin/python

import rospy
from std_msgs import msg
from std_msgs.msg import String
from geometry_msgs.msg import Pose
from ar_track_alvar_msgs.msg import AlvarMarkers

poses = []

def call_back(msg):
    rate = rospy.Rate(10)
    for marker in msg.markers:
        pose = Pose()
        pose = marker.pose.pose
        
        if(marker.id == 1):
            pub = rospy.Publisher('robot_0'+str(marker.id)+'/pose', Pose, queue_size = 10)
        else:
            pub = rospy.Publisher('obstacle_'+str(marker.id)+'/pose', Pose, queue_size = 10)

        pose.position.x = (pose.position.x + 0.5) * 1
        pose.position.y = (pose.position.y + 0.5) * 1
        pose.position.y = (pose.position.y-1) * -1

        x = pose.orientation.x
        y = pose.orientation.y
        z = pose.orientation.z
        w = pose.orientation.w

        pose.orientation.x = 0
        pose.orientation.y = 0
        pose.orientation.z = x
        pose.orientation.w = y
        
        pub.publish(pose)



    if(len(msg.markers) == 0):
        print('nenhum marcador identificado')

if __name__ == '__main__':
    print('publicando posições...')
    rospy.init_node('position_publisher', anonymous = True)
    rospy.Subscriber("/ar_pose_marker", AlvarMarkers, call_back)
    rospy.spin()    
        

        