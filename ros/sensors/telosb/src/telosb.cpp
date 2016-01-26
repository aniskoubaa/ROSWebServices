
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <ros/ros.h>
#include <telosb/TelosBMsg.h>


#define BUFSIZE 12

int _handle;

typedef unsigned char BYTE;

int open_usb(char* device, int baudrate)
{
	struct termios options;
	int bitrate;

	fprintf(stderr, "\nconnecting to %s (%d)\n", device, baudrate);

	//_handle= open(device, O_RDWR | O_NOCTTY );
	_handle = open(device, O_RDWR | O_NOCTTY | O_NDELAY | O_SYNC );

	if (_handle < 0)
	{

		printf ("handle = %d, exit function open_usb\n",_handle);
		_handle = 0;
		return -1;
	}
	speed_t speed = B115200;
	//speedname = "115200";
	cfsetispeed(&options, speed);
	cfsetospeed(&options, speed);

	/* Enable the receiver and set local mode */
	options.c_cflag |= (CLOCAL | CREAD);
	/* Mask the character size bits and turn off (odd) parity */
	options.c_cflag &= ~(CSIZE|PARENB|PARODD);
	/* Select 8 data bits */
	options.c_cflag |= CS8;

	/* Raw input */
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	/* Raw output */
	options.c_oflag &= ~OPOST;

	if (tcsetattr(_handle, TCSANOW, &options) < 0) {
		perror("could not set options");
		exit(-1);
	}
	/*
    tcgetattr(_handle, &options);

    options.c_cflag = bitrate | CS8 | CREAD | CLOCAL;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;

    options.c_cc[VMIN]  = 1;
    options.c_cc[VTIME] = 0;

    tcsetattr(_handle, TCSANOW, &options);
	 */
	fflush(stdout);
	fflush(stdout);
	return 1;
}


int close_usb()
{
	if (!_handle)
		return -1;

	close(_handle);
	_handle = 0;

	return 1;
}

int flush_usb()
{
	if (!_handle)
		return -2;

	return tcflush(_handle, TCIFLUSH) == 0;
}

int read_usb(BYTE *pBuffer, int size, int *pHasRead)
{
	fflush(stdout);
	if (!_handle)
		return -1;

	//_hexdump(pBuffer, size);
	//printf ("read_usb: Wait for bytes ... \n");
	do{
		*pHasRead = read(_handle, pBuffer, size);
	}while (*pHasRead==0);
	//printf (" %d bytes read... \n", *pHasRead);
	if (*pHasRead < 0)
		return -1;
	int j;



	fflush(stdout);
	return 1;
}

BYTE frame[BUFSIZE];
int current_index=0;

	//ros::Publisher telosb_publisher;
	//ros::Rate loop_rate(10);

int main(int argc, char **argv)/*the main function*/
{

	/** Initialize ROS node.
	 * It must be declared in the begining of the program because of TF Listener
	 *This specifies the name of the node **/
	ros::init(argc, argv, "telosb_node");
	//create a node handle
	ros::NodeHandle nh ("~");
	std::string port;//"/dev/telosb";
	nh.getParam("port",port);


	    printf ("Starting TelosB Node ... \n");
	//char* device = "/dev/ttyUSB0";
	//char* device = "/dev/telosb";
	
	 char *device = (char *) malloc(100);;
	 printf ("set device name ... \n");
	 strcpy(device,port.c_str());
	 //printf ("cout ... \n");
	std::cout <<device<<std::endl;
	if (device == NULL ) 
	  device = "/dev/ttyUSB0";
printf("attempting to open %s", device);
	int baudrate = 115200;
	printf ("open USB port ... \n");
	int b = open_usb(device, baudrate);
	

	//first, discard any previous data
	flush_usb();
	if (b==1)
		printf ("USB Port Open \n");
	if (b==-1)
		printf ("USB Port NOT Open \n");
	int r, i, j;
	BYTE buffer[BUFSIZE];
	BYTE read_buffer[BUFSIZE];
	int received_bytes;
	int count =0;

	//must be defined after opening the USB port!!
	ros::Publisher telosb_publisher= nh.advertise<telosb::TelosBMsg>("telosb_topic",1000);

	while (ros::ok())
	{
		//fflush(stdout);

		//printf ("before read_usd \n");
		read_usb(read_buffer, BUFSIZE, &r);
		//printf ("after read_usd \n");
		//printf("r=%d\n ",r);
		printf("count=%d\n ",count);
		//printf("%s\n",buffer);
		//printf("current index = %d \n ", current_index);
		if(r!=0){
			//fflush(stdout);

			int offset=count;
			count = count+r;
			int i=0;
			//printf ("before for ( i = 0; i<r; i++) %d, offset = %d\n", r, offset);
			for ( i = 0; i<r; i++){
				buffer[i+offset]=read_buffer[i];
			}
			//printf ("after for ( i = 0; i<r; i++) \n");
			//printf ("before if (count==12) \n");
			if (count==12){
				count = 0;
				received_bytes=0;//re-init received_bytes
				//fflush(stdout);

				printf ("before id = \n");
				int id = (buffer[2]-'0')+((buffer[1]-'0')*10)+(buffer[0]-'0')*100;
				int light = (buffer[5]-'0')+((buffer[4]-'0')*10)+(buffer[3]-'0')*100;
				int temp = (buffer[8]-'0')+((buffer[7]-'0')*10)+(buffer[6]-'0')*100;
				int humidity = (buffer[11]-'0')+((buffer[10]-'0')*10)+(buffer[9]-'0')*100;
				//printf ("r=%d \n", r);
				//printf ("Sensor reading \n");
				printf ("before Sensor ID = \n");
				printf ("Sensor ID  : %d \n", id);
				printf ("Light      : %d Lux\n", light);
				printf ("Temperature: %d °C\n", temp);
				printf ("Humidity   : %d %%\n\n", humidity);
				//printf("%d\n ",i);

				telosb::TelosBMsg telosb_msg;
				telosb_msg.sensorID=id;
				telosb_msg.temperature=temp;
				telosb_msg.humidity=humidity;
				telosb_msg.light=light;
				ROS_INFO("\n[ID = %d]: temperature: %d C, light: %d Lux, Humidity: %d \n",
						telosb_msg.sensorID, telosb_msg.temperature, telosb_msg.light, telosb_msg.humidity);

				telosb_publisher.publish(telosb_msg);
				ros::spinOnce();
				//loop_rate.sleep();

			}
		}
	}

	printf ("  read usb completed. \n");
	return 1;
}


