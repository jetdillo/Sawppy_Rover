//#include <ArduinoTcpHardware.h>
#include <ros.h>
#include <ros/time.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>

#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include <sensor_msgs/Range.h>

geometry_msgs::TransformStamped t;
tf::TransformBroadcaster broadcaster;

//#include <ArduinoHardware.h>

    #define rf_sonar 0
    #define lf_sonar 1
    #define cf_sonar 2
    

    #define enable_A 2
    #define enable_B 4
    #define enable_C 3
    #define enable_D 5
    #define enable_E 6
    #define enable_F 7
    
    #define A1 23  //Left Front IN1
    #define A2 25  //Left Front IN2
    #define C3 27  //Left Mid IN3
    #define C4 29  //Left Mid IN4
    #define B1 31  //Right Front IN1
    #define B2 33  //Right Front IN2
    #define D3 35  //Right MID IN3
    #define D4 37  //Right MID IN4
    #define E1 39  //Left Rear IN1
    #define E2 41  //Left Rear IN2 
    #define F1 43  //Right Rear IN1
    #define F2 45  //Right Rear IN2

    #define encoder_1_A 38    
    #define encoder_1_B 40
    
    #define encoder_2_A 42
    #define encoder_2_B 44
    
    #define encoder_4_A 18
    #define encoder_4_B 19
    
    #define encoder_3_A 20
    #define encoder_3_B 21
    
    #define SPEED_MIN 50
    #define SPEED_CRUISE 75
    #define SPEED_FAST 90
    #define SPEED_MAX 180

    #define DRIVE_FWD 10
    #define DRIVE_REV 20
    #define DRIVE_LFT 30
    #define DRIVE_RT 40
    #define DRIVE_STOP 50

    #define FRONT_LEFT_SERVO 1
    #define FRONT_RIGHT_SERVO 2
    #define BACK_LEFT_SERVO 5 
    #define BACK_RIGHT_SERVO 6

    #define STEER_HOME 355
    #define STEER_STEP 20
    #define STEER_LEFT_MIN 140
    #define STEER_RIGHT_MAX 615


/* 
 *   Motor labeling/numbering is as follows:
 *      FRONT
 *  [1][A] [2][B]
 *    \\   //
 *[3][C]== ==[4][D]
 *    //   \\
 *[5][E]     [6][F]                                              
 *      REAR
 */

    int rotDirection = 0;
    int pressed = false;

    int motor_dir_ctl[6][2]={ {A1,A2},{B1,B2},{C3,C4},{D3,D4},{F1,F2},{E1,E2} };
    int motor_speed_ctl[6]={enable_A,enable_B,enable_C,enable_D,enable_E,enable_F};
    int corner_steering[4]={FRONT_LEFT_SERVO,FRONT_RIGHT_SERVO,BACK_LEFT_SERVO,BACK_RIGHT_SERVO};
   
    float twist_linear=0.0;
    float twist_angular=0.0;
    
// variables will change:
    int buttonState = 0;         // variable for reading the pushbutton status

    int buttons[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    boolean skid_state = false;
    int skid_dir = 0;
    unsigned long e3a_ts;
    unsigned long e3b_ts;
    unsigned long e4a_ts;
    unsigned long e4b_ts;

sensor_msgs::Range range_msg_lf; 
sensor_msgs::Range range_msg_rf;
sensor_msgs::Range range_msg_cf;
    
ros::Publisher pub_range_lf( "/ultrasound/lf", &range_msg_lf);
ros::Publisher pub_range_rf("/ultrasound/rf", &range_msg_rf);
ros::Publisher pub_range_cf("/ultrasound/cf",&range_msg_cf);

ros::NodeHandle nh;

char frameid[]="/ultrasound";

//int lticks,rticks;

void TwistCb(const geometry_msgs::Twist& vel_msg) { 
     twist_linear=(float)vel_msg.linear.x;
     twist_angular=(float)vel_msg.angular.z;
}

void sonar_sweep() { 

    sensor_msgs::Range sm[3];
    for (int i=0;i < 3;i++) { 
      sm[i].range=read_sonar(i);
      sm[i].radiation_type = sensor_msgs::Range::ULTRASOUND;
      sm[i].header.frame_id =  frameid;
      sm[i].field_of_view = 0.1;  // fake
      sm[i].min_range = 0.0;
      sm[i].max_range = 6.47;
      delay(50);
    }

    range_msg_rf= sm[0];
    range_msg_lf= sm[1];
    range_msg_cf= sm[2];

    pub_range_lf.publish(&range_msg_lf);
    pub_range_rf.publish(&range_msg_rf);
    pub_range_cf.publish(&range_msg_cf);
    
}

float read_sonar(int pin_num){
  int val = 0;
  for(int i=0; i<4; i++) val += analogRead(pin_num);
  float range =  val;
  return range /322.519685;   // (0.0124023437 /4) ; //cvt to meters
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", TwistCb);

//ros::Subscriber<sensor_msgs::Joy> sub("joy", JoyModeCb);

    void setup() {

      nh.initNode();
      nh.subscribe(sub);
      nh.advertise(pub_range_lf);
      nh.advertise(pub_range_rf);
      nh.advertise(pub_range_cf);
      
      for (int k=2; k<=8;k++) { 
        pinMode(k,OUTPUT);
      }

       // Set initial rotation direction
       // Serial.begin(115200);
       // Open serial port to receive commands
       Serial2.begin(115200);
 }
 
 
 //We make direct calls to manipulate the motors for speed
 //as looping and calling functions can be expensive time-wise
 
 void loop() {

     int drive_cmd=1024;
     float drive_speed=0.0;
     int drive_dir=0;
     int dirbtn=0;

      drive_speed = twist_linear * SPEED_MAX;
      //Serial2.println(drive_speed);
      
       if (drive_speed >0) {
         //  Serial2.print("FORWARD ");
         //  Serial2.println(drive_speed);
          
           digitalWrite(23,LOW);
           digitalWrite(25,HIGH);
           
           digitalWrite(27,LOW);
           digitalWrite(29,HIGH);
           
           
           digitalWrite(31,LOW);
           digitalWrite(33,HIGH);
           
           
          digitalWrite(35,LOW);
          digitalWrite(37,HIGH);
          
           
           digitalWrite(39,LOW);
           digitalWrite(41,HIGH);
           
           digitalWrite(43,LOW);
           digitalWrite(45,HIGH);
          
           analogWrite(2,(int)drive_speed);
           analogWrite(3,(int)drive_speed);
           
           analogWrite(4,(int)drive_speed);
           analogWrite(5,(int)drive_speed);

           analogWrite(6,(int)drive_speed);
           analogWrite(7,(int)drive_speed);
         
         //  delay(10);
           
       }
       if (drive_speed < 0) {
         // Serial2.print("REVERSE ");
         // Serial2.println(drive_speed);
           
           digitalWrite(23,HIGH);
           digitalWrite(25,LOW);
           
           digitalWrite(27,HIGH);
           digitalWrite(29,LOW);
           
           
           digitalWrite(31,HIGH);
           digitalWrite(33,LOW);
           
           digitalWrite(35,HIGH);
           digitalWrite(37,LOW);
          

            digitalWrite(39,HIGH);
           digitalWrite(41,LOW);
           
           
            digitalWrite(43,HIGH);
           digitalWrite(45,LOW);
           
           
           analogWrite(2,(int)(drive_speed*-1));
           analogWrite(3,(int)(drive_speed*-1));
     
           analogWrite(4,(int)(drive_speed*-1));
           analogWrite(5,(int)(drive_speed*-1));
           
           analogWrite(6,(int)(drive_speed*-1));
           analogWrite(7,(int)(drive_speed*-1));
           
          // delay(10);
       }

       if (drive_speed == 0) {
            for(int i =0; i < 6; i++) { 
                 digitalWrite(motor_dir_ctl[i][0],LOW);
                 digitalWrite(motor_dir_ctl[i][1],LOW);
                 analogWrite(motor_speed_ctl[i],0);
              }
            //delay(10);
       }
       sonar_sweep();
       //delay(10);
       nh.spinOnce();
}
