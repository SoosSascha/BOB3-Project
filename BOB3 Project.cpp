#include <BOB3.h>

void setup() {

}

void AnschalteAnimation() { 
    //Define col mintGreen
    long mintGreen = 0x42f5c2;
    //Start Animation Sequence 
    delay(10);
    for (int i = 0; i < 4; i++) {	
        bob3.setEyes(mintGreen, mintGreen);
        bob3.setWhiteLeds(ON, ON);
        delay(300);
        bob3.setEyes(OFF, OFF);
        bob3.setWhiteLeds(OFF, OFF);
        delay(50);
    }
}

void loop() {
  	//Initialize Vars
    int on = 0;
    int run = 0;
    int arm1 = 0;
    int arm2 = 0;
    int time = 0;
    int ptime = 0;
  
  	//Arm Input
	arm1 = bob3.getArm(1);
    arm2 = bob3.getArm(2);

  	//Checks if BOB is On & If not -> Initialize turn on sequence
	if ((arm1 > 0 && on == 0) && (arm2 > 0 && on == 0)) {
		AnschalteAnimation();
      	on = 1;
      	delay(100);
      	bob3.setWhiteLeds(ON, ON);
    	delay(700);
        bob3.setWhiteLeds(OFF, OFF);
    }
	
    //Input Loop
    while (on == 1) {
        //Get Arm Input
        arm1 = bob3.getArm(1);
        arm2 = bob3.getArm(2);
        //One side only safety
        if ((arm1 > 0 && arm2 > 0) && (arm1 != 2 && arm2 != 2)) {
        arm1 = 0;
    	arm2 = 0;
        }
        //Arm Input Translation
        //Both Middle Arm (Timer Loop Start)
        if (arm1 == 2 && arm2 == 2) {
			bob3.setWhiteLeds(ON, ON);
        	delay(1000);
   			bob3.setWhiteLeds(OFF, OFF);
            delay(500);
            arm1 = 0;
    	    arm2 = 0;
            on = 0;
            run = 1;
        }      
        //Upper Arm1 (- Arbeitszeit)
      	if (arm1 == 1) {
        	time++;
        	bob3.setLed(1, BLUE);
        	delay(100);
        	bob3.setLed(1, OFF);
            delay(100);
        }
      	//Middle Arm1 (Check Arbeitszeit)
        else if (arm1 == 2 && time != 0) {
            int checktime = time;
            while (checktime > 9) {
        		bob3.setLed(1, VIOLET);
        		delay(250);
        		bob3.setLed(1, OFF);
                delay(250);
                checktime = checktime - 10;
            }
            while (checktime > 0) {
        		bob3.setLed(1, SEAGREEN);
        		delay(250);
        		bob3.setLed(1, OFF);
            	delay(250);
                checktime--;
            }
            delay(500);
        }
        //Lower Arm1 (- Arbeitszeit)
        else if (arm1 == 3 && time > 0) {
        	time--;
        	bob3.setLed(1, RED);
        	delay(100);
        	bob3.setLed(1, OFF);
            delay(100);
        }
        else if (arm1 == 3 && time < 1) {
        	bob3.setWhiteLeds(ON, ON);
        	delay(100);
   			bob3.setWhiteLeds(OFF, OFF);
            delay(100);
        }
        //Upper Arm2 (+ Pausenzeit)
        if (arm2 == 1) {
            ptime++;
        	bob3.setLed(2, BLUE);
        	delay(100);
        	bob3.setLed(2, OFF);
            delay(100);
        } 
        //Middle Arm2 (Check Pausenzeit)
        else if (arm2 == 2 && ptime != 0) {
            int checkptime = ptime;
            while (checkptime > 9) {
			    bob3.setLed(2, VIOLET);
        		delay(250);
        		bob3.setLed(2, OFF);
            	delay(250);
                checkptime = checkptime - 10;
            }
            while (checkptime > 0) {
        		bob3.setLed(2, SEAGREEN);
        		delay(250);
        		bob3.setLed(2, OFF);
           		delay(250);
                checkptime--;
            }
            delay(500);
        }
        //Lower Arm2 (- Pausenzeit)
        else if (arm2 == 3 && ptime > 0) {
        	ptime--;
        	bob3.setLed(2, RED);
        	delay(100);
        	bob3.setLed(2, OFF);
            delay(100);
        }
        else if (arm2 == 3 && ptime < 1) {
        	bob3.setWhiteLeds(ON, ON);
        	delay(100);
   			bob3.setWhiteLeds(OFF, OFF);
            delay(100);
        }
	}
    //Run Timer Loop
    while (run == 1) {
      	//Arbeitszeit
      	for (int i = (time*60)+1; i > 0; i--) {
          	bob3.setEyes(PURPLE, PURPLE);
          	delay(500);
            bob3.setEyes(OFF, OFF);
            //Check if User wants to stop
            arm1 = bob3.getArm(1);
        	arm2 = bob3.getArm(2);
            if (arm1 > 0 && arm2 > 0) {
               run = 0;
               break;
            }
            delay(500);
        }
      	//Pausenzeit
      	if (run != 0) {
      		for (int j = (ptime*60)+1; j > 0; j--) {
        		bob3.setEyes(AQUAMARINE, AQUAMARINE);
          		delay(500);
            	bob3.setEyes(OFF, OFF);
            	//Check if User wants to stop
                arm1 = bob3.getArm(1);
        		arm2 = bob3.getArm(2);
            	if (arm1 > 0 && arm2 > 0) {
               		run = 0;
               		break;
            	}
            delay(500);
        	}
        }
      	else {
        //End Animation
    	bob3.setEyes(RED, RED);
      	bob3.setWhiteLeds(ON, ON);
    	delay(1500);
    	bob3.setEyes(OFF, OFF);
      	bob3.setWhiteLeds(OFF, OFF);
        }
    }
}