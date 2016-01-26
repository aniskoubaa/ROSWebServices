#!/usr/bin/env python

from coros_messages.srv import *
import rospy
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
      print 'eth1 interface found'
      print 'eth1 is up? : %s' % isAnInterfaceUp('eth1')
      if (isAnInterfaceUp('eth1')):
	ni.ifaddresses('eth1')
	ip = ni.ifaddresses('eth1')[2][0]['addr']
	#print ip  # should print "192.168.100.37"
	validIPFound=True
    elif 'eth0' in ni.interfaces():
      print 'eth0 interface found'
      print 'eth0 is up? : %s' % isAnInterfaceUp('eth0')
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

def handle_ip_address_provision(req):
    global ip
    if req.ip_address_request == 'all_interfaces':
      print "Returning list of all interfaces: %s"%(ni.interfaces())
      return ';'.join(e for e in ni.interfaces())
    elif req.ip_address_request == 'local_ip':
      findValidIPAddress()
      print "Returning IP Address: [%s]"%(ip)
      return IPAddressServiceResponse(ip)
    else:
      return '127.0.0.1'

def ip_address_server():
    rospy.init_node('ip_address_server_node')
    s = rospy.Service('ip_address_service', IPAddressService, handle_ip_address_provision)
    print "ready to serve the local IP Address."
    rospy.spin()

if __name__ == "__main__":
    ip_address_server()