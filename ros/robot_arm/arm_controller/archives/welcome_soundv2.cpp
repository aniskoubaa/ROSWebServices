
#include <sound_play/sound_play.h>
#include <unistd.h>

void sleepok(int t, ros::NodeHandle &nh)
{
  if (nh.ok())
                sleep(t);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "welcome_node");

  ros::NodeHandle nh;
  sound_play::SoundClient sc;

  sleepok(1, nh);
  
  while(nh.ok())
  {
    sc.say("Welcome to The My BOT!");
    sleepok(2, nh);

 
    sc.playWave("/home/ros/catkin_ws/src/_movimp/code/arm_controller/sounds/welcome.wav");
    sleepok(2, nh);

    const char *str2 = "/home/ros/catkin_ws/src/_movimp/code/arm_controller/sounds/arwelcome.wav";
    sc.startWave(str2);
    sleepok(4, nh);
    sc.stopWave(str2);

 
  
  }
}