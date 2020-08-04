//#include <ArduinoTcpHardware.h>
#include <ros.h>
#include <ros/time.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>

#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>

geometry_msgs::TransformStamped t;
tf::TransformBroadcaster broadcaster;

//#include <ArduinoHardware.h>

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
    #define SPEED_MAX 120

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
 *   [1]     [2]
 *    \\   //
 *   [3]== ==[4]
 *    //   \\
 *   [5]     [6]
 *      REAR
 */

    int rotDirection = 0;
    int pressed = false;

   // int motor_dir_ctl[6][2]={ {39,41},{43,45},{31,33},{35,37},{A1,A2},{C3,29} };
    int motor_dir_ctl[6][2]={ {A1,A2},{B1,B2},{C3,C4},{D3,D4},{F1,F2},{E1,E2} };
   // int motor_speed_ctl[6]={8,9,10,11,12,13};
    int motor_speed_ctl[6]={enable_A,enable_B,enable_C,enable_D,enable_E,enable_F};
    int corner_steering[4]={FRONT_LEFT_SERVO,FRONT_RIGHT_SERVO,BACK_LEFT_SERVO,BACK_RIGHT_SERVO};
   
    float twist_linear=0.0;
    
// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

unsigned long e3a_ts;
unsigned long e3b_ts;
unsigned long e4a_ts;
unsigned long e4b_ts;

ros::NodeHandle nh;

//int lticks,rticks;

void TwistCb(const geometry_msgs::Twist& vel_msg) { 
     twist_linear=(float)vel_msg.linear.x;
}

void leftCb() { 
    int aval=digitalRead(encoder_3_A);
    int bval=digitalRead(encoder_3_B);
    Serial2.print("leftCB:" );
    if (bval
}

void rightCb() { 

   int aval=digitalRead(encoder_4_A);
   int bval=digitalRead(encoder_4_B);
   Serial2.print("rightCB:");
    
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", TwistCb);

    void setup() {

      nh.initNode();
      nh.subscribe(sub);
      
      for (int k=2; k<=8;k++) { 
        pinMode(k,OUTPUT);
      }
        
        pinMode(encoder_3_A,INPUT_PULLUP);
        pinMode(encoder_3_B,INPUT_PULLUP);
        pinMode(encoder_4_A,INPUT_PULLUP);
        pinMode(encoder_4_B,INPUT_PULLUP);

        attachInterrupt(digitalPinToInterrupt(encoder_3_A), leftCb, CHANGE);
        attachInterrupt(digitalPinToInterrupt(encoder_3_B), leftCb, CHANGE);
        attachInterrupt(digitalPinToInterrupt(encoder_4_A), rightCb, CHANGE);
        attachInterrupt(digitalPinToInterrupt(encoder_4_B), rightCb, CHANGE);
        
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
           Serial2.print("FORWARD ");
           Serial2.println(drive_speed);
          
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
         
           delay(100);
           
       }
       if (drive_speed < 0) {
          Serial2.print("REVERSE ");
          Serial2.println(drive_speed);
           
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
           
           delay(100);
       }

       if (drive_speed == 0) {
            for(int i =0; i < 6; i++) { 
              digitalWrite(motor_dir_ctl[i][0],LOW);
              digitalWrite(motor_dir_ctl[i][1],LOW);
              analogWrite(motor_speed_ctl[i],0);
           }
            delay(100);
       }
       nh.spinOnce();
}
