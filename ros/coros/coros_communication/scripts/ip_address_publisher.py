#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import String
import netifaces as ni

ip='127.0.0.1'

def isAnInterfaceUp(anInterface):
    addr = ni.ifaddresses(anInterface)
    return ni.AF_INET in addr

def findValidIPAddress():
    global ip
    print ni.interfaces()
    validIPFound=False
    #ni.interfaces()
    if 'eth1' in ni.interfaces():
      #print 'eth1 interface found. Is eth1 up: %s'% isAnInterfaceUp('eth1') 
      if (isAnInterfaceUp('eth1')):
	ni.ifaddresses('eth1')
	ip = ni.ifaddresses('eth1')[2][0]['addr']
	#print ip  # should print "192.168.100.37"
	validIPFound=True
    elif 'eth0' in ni.interfaces():
      #print 'eth0 interface found. Is eth0 up: %s'% isAnInterfaceUp('eth1') 
      if (isAnInterfaceUp('eth0')):
	ni.ifaddresses('eth0')
	ip = ni.ifaddresses('eth0')[2][0]['addr']
	#print ip  # should print "192.168.100.37"
	validIPFound=True
    elif 'wlan0' in ni.interfaces():
      #print 'eth0 interface found. Is eth0 up: %s'% isAnInterfaceUp('eth1')
      if (isAnInterfaceUp('wlan0')):
	ni.ifaddresses('wlan0')
	ip = ni.ifaddresses('wlan0')[2][0]['addr']
	#print ip  # should print "192.168.100.37"
	validIPFound=True
    elif 'wlan1' in ni.interfaces():
      #print 'eth0 interface found. Is eth0 up: %s'% isAnInterfaceUp('eth1')
      if (isAnInterfaceUp('wlan1')):
	ni.ifaddresses('wlan1')
	ip = ni.ifaddresses('wlan1')[2][0]['addr']
	#print ip  # should print "192.168.100.37"
	validIPFound=True
    if validIPFound==False:
      ip='127.0.0.1'
    
def ip_publisher():
    global ip
    pub = rospy.Publisher('local_ip_address', String, queue_size=10)
    rospy.init_node('local_ip_address_node', anonymous=True)
    message_rate = rospy.get_param('~message_rate', 1);
    print message_rate
    rate = rospy.Rate(message_rate) # 10hz
    while not rospy.is_shutdown():
	findValidIPAddress()
        rospy.loginfo(ip)
        pub.publish(ip)
        rate.sleep()

if __name__ == '__main__':
    try:
        ip_publisher()
    except rospy.ROSInterruptException:
        pass
