    /*  Arduino DC Motor Control - PWM | H-Bridge | L298N  -  Example 01
        by Dejan Nedelkovski, www.HowToMechatronics.com
    */
    #define enA 9
    #define in1 6
    #define in2 7
    int rotDirection = 0;
    int pressed = false;
    void setup() {
      pinMode(enA, OUTPUT);
      pinMode(in1, OUTPUT);
      pinMode(in2, OUTPUT);
      
      // Set initial rotation direction
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      Serial.begin(9600);
    }
    void loop() {
/*
       for (int i=50; i < 255;i++) { 
            analogWrite(enA,i);
            Serial.print("Motor speed:");
            Serial.println(i);
            delay(100);
       }
       delay(2000);
       
       for (int i=255; i > 50;i--) {
             analogWrite(enA,i);
             Serial.print("Motor speed:");
             Serial.println(i);
             delay(100);
       }
       delay(2000);
       */

       analogWrite(enA,100);
       digitalWrite(in1,LOW);
       digitalWrite(in2,HIGH);
       Serial.println("IN1: LOW IN2: HIGH");
       

       delay(5000);
       Serial.println("IN1: HIGH IN2: LOW");
       analogWrite(enA,100);
       digitalWrite(in1,HIGH);
       digitalWrite(in2,LOW);
       delay(5000);
        Serial.println("IN1: LOW IN2: HIGH");
       analogWrite(enA,100);
       digitalWrite(in1,LOW);
       digitalWrite(in2,HIGH);

       delay(5000);
    }
