#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "gfx.h"


void calculations(double posX[], double posY[], double time, double mass, double deltaD, double angleRad, double veloX[], double veloY[]);
void graphics(double posX[], double posY[], double time);

int main ()
{
	double posX[999], posY[999], veloY[999], veloX[999], time;
	double angleDeg, angleRad, deltaDcm, deltaD, mass;
	double xcoor, ycoor;
	char click;

	//printf("\nPlease enter the angle of shot (in degrees): ");		//legacy input
	//scanf("%lf", &angleDeg);
	//printf("\nPlease enter the distance of pull (in cm): ");
	//scanf("%lf", &deltaDcm);

do {

	while(1) {															//new input
		printf("\nPlease enter the mass of the projectile: ");
		scanf("%lf", &mass);

		gfx_open(1280, 720, "Primitive Angry Birds");
		gfx_clear_color(153,204,255);
		gfx_clear();
		//gfx_color(255, 255, 255);
	
		gfx_color(250,250,0);//sun
		gfx_fillcircle(1110,40,90);
		
		gfx_color(250,250,250);//cloud
		gfx_fillcircle(1000,90,100);//2
		gfx_fillcircle(1060,90,140);//2
		gfx_fillcircle(1110,130,90);//2
		gfx_fillcircle(1160,90,110);//2
		gfx_fillcircle(100,230,100);//1
		gfx_fillcircle(160,230,140);//1
		gfx_fillcircle(210,270,90);//1
		gfx_fillcircle(260,230,110);//1
			
		gfx_color(172,10,0);//castle
		gfx_fillrectangle(900,510,300,210);
		gfx_fillrectangle(950,400,200,200);
		gfx_color(49,19,0);
		gfx_fillrectangle(1010,590,80,120);
		gfx_fillcircle(1050,590,80);
		gfx_fillrectangle(980,460,30,40);
		gfx_fillrectangle(1080,460,30,40);

		gfx_color(0,255,0);
		gfx_fillrectangle(0,650,1380,400);  //land graphics
	
		gfx_color(0,0,0);//pole
		gfx_line(725,300,800,330);
		gfx_line(725,360,800,330);
		gfx_color(255,255,255);
		gfx_fillrectangle(725,260,5,400);
		gfx_color(255,178,103);
		gfx_fillrectangle(700,640,50,40);
		gfx_color(255,255,0);
		gfx_fillcircle(725,265,30);

		gfx_color(139,69,19);
		gfx_fillrectangle(100,550,5,100);
		//gfx_fillrectangle(8,14,5,7);
		//gfx_fillrectangle(12,14,5,7); //slingshot handle graphics

		gfx_color(139,69,19);
		gfx_fillcircle(100, 550, 40); //slingshot graphics
		gfx_color(153,204,255);
		gfx_fillcircle(100, 545, 30);
		
		gfx_color(10,10,10);
		gfx_line(85,545,120,545);  //band

		gfx_color(255,0,0);
		gfx_fillcircle(100, 545, 10);
		gfx_line(0, 550, 100, 550);
		gfx_line(100, 550, 100, 650); //region of input

		
		click = gfx_wait();
		if (click==0x03)
		{
			xcoor = gfx_xpos(); 
			ycoor = gfx_ypos();
			break;
		}
	}
	printf("Input X:%f\tInput Y:%f\n", xcoor, ycoor);
	//convert xcoor and ycoor to actual length?
	
	

	if (xcoor<=100 && ycoor>=550) {   //to avoid out of bound inputs

		deltaDcm = sqrt(((100-xcoor)*(100-xcoor))/((ycoor-550)*(ycoor-550)))*100;	
		printf("Length of pull (cm): %f\n", deltaDcm);		
		angleRad = atan((ycoor-500)/(deltaDcm));
		//printf("Angle of shot: %f\n", angleDeg);
		

		//converting degree to radian
		//angleRad = (angleDeg*3.14159)/180;
		printf("Angle (rad): %f\n", angleRad);
		//converting cm to m	
		deltaD = deltaDcm*0.01;
		printf("Length of pull (m): %f\n", deltaD);
	
		calculations(posX, posY, time, mass, deltaD, angleRad, veloY, veloX);
		graphics(posX, posY, time);
	}
	else {
		printf("You have selected an area which is out of bounds, terminating program.\n");
	}
	return 0;
} while (click!=0x03);
}

void calculations(double posX[], double posY[], double time, double mass, double deltaD, double angleRad, double veloY[], double veloX[])
{
	double g = -9.81; //gravitational acceleration
	double springConstant = 400.7;
	
	double initialVelo, initialVeloX, initialVeloY;
	int i;

	posX[0] = 0.0;
	posY[0] = 1.0; //height of catapult (not in coordinate form)
	time = 0.0; //time starts at 0

	initialVelo = sqrt((springConstant*deltaD)/mass);

	initialVeloX = initialVelo*cos(angleRad);
	initialVeloY = initialVelo*sin(angleRad);
	

	printf("Initial Vox: %f\t\tInitial Voy: %f\n", initialVeloX, initialVeloY);

	printf("\tTime(s)\tPosition X (m)\tPosition Y (m)\tVelocity X (m/s)\tVelocity Y (m/s)\n");
	printf("\t%.2f\t\t%.2f\t\t%.2f\t\t%.2f\t\t%.2f\n", time, posX[0], posY[0], initialVeloX, initialVeloY);

	for (i=0; i>=0; i++) {
		//time[i] = time[i-1] + time[99]/99.0;
		posX[i] = initialVeloX*time;
		posY[i] = initialVeloY*time + 0.5*g*time*time + posY[0];
		veloX[i] = initialVelo;
		veloY[i] = initialVeloY - g*time;		


		if (posY[i] >= 0) {
			time = time + 0.01;
			printf("\t%.2f\t\t%.2f\t\t%.2f\t\t%.2f\t\t%.2f\n", time, posX[i], posY[i], veloX[i], veloY[i]);		
			}
		else {
			i = -10;
		}
	}
	
}

void graphics(double posX[], double posY[], double time)
{
	int i, n;
	char fclick;
	
	for (i=0; i>=0; i++)
	{
		if (posY[i] >= 0) {		
		//gfx_point((posX[i]*533/posX[99])+200, (300-posY[i]*300/posY[24])+100);
//		gfx_color(i,255-2*i,i);	
//		gfx_point(posX[i]*100, posY[i]*100);
		gfx_line(100+posX[i]*(100), 640-posY[i]*(100), 100+posX[i+1]*(100), 640-posY[i+1]*(100));
		
//		gfx_line((posX[i]*533/posX[99])+100, (100-posY[i]*300/posY[24])+310, (posX[i+1]*533/posX[99])+100, (100-posY[i+1]*300/posY[24])+310);
//		gfx_line((posX[i]*533/posX[99])+200, (300-posY[i]*300/posY[24])+100, (posX[i+1]*533/posX[99])+200, (300-posY[i+1]*300/posY[24])+100);
		//if (posX[i]<=posX[99]-50)
		//	n=i;	
		} else {
			i = -10;
		}
	} gfx_flush();

	//animation

	for (n=0; n>=0; n++)
	{
		if (posY[n] >= 0) {
			gfx_fillcircle(100+posX[n]*100, 640-posY[n]*100, 10);
			gfx_flush();
			usleep(40000);	
			gfx_flush();
			gfx_clear();
			gfx_clear_color(153,204,255);
			gfx_clear();
			//gfx_color(255, 255, 255);
		
			gfx_color(250,250,0);//sun
			gfx_fillcircle(1110,40,90);
			
			gfx_color(250,250,250);//cloud
			gfx_fillcircle(1000,90,100);//2
			gfx_fillcircle(1060,90,140);//2
			gfx_fillcircle(1110,130,90);//2
			gfx_fillcircle(1160,90,110);//2
			gfx_fillcircle(100,230,100);//1
			gfx_fillcircle(160,230,140);//1
			gfx_fillcircle(210,270,90);//1
			gfx_fillcircle(260,230,110);//1
				
			gfx_color(172,10,0);//castle
			gfx_fillrectangle(900,510,300,210);
			gfx_fillrectangle(950,400,200,200);
			gfx_color(49,19,0);
			gfx_fillrectangle(1010,590,80,120);
			gfx_fillcircle(1050,590,80);
			gfx_fillrectangle(980,460,30,40);
			gfx_fillrectangle(1080,460,30,40);


			gfx_color(0,255,0);
			gfx_fillrectangle(0,650,1380,400);  //land graphics
	
			gfx_color(0,0,0);//pole
			gfx_line(725,300,800,330);
			gfx_line(725,360,800,330);
			gfx_color(255,255,255);
			gfx_fillrectangle(725,260,5,400);
			gfx_color(255,178,103);
			gfx_fillrectangle(700,640,50,40);
			gfx_color(255,255,0);
			gfx_fillcircle(725,265,30);
			
			gfx_color(139,69,19);
			gfx_fillrectangle(100,550,5,100); //slingshot handle graphics

			gfx_color(139,69,19);
			gfx_fillcircle(100, 550, 40); //slingshot graphics
			gfx_color(153,204,255);
			gfx_fillcircle(100, 545, 30);
			gfx_color(153,204,255);

			gfx_color(255,0,0);
			gfx_line(0, 550, 100, 550);
			gfx_line(100, 550, 100, 650); //region of input
		} else { n = -10; }
	}

	
	//gfx_line(150, 400, 750, 400);
	//gfx_line((posX[i]*533/posX[99])-200, 500, (posX[i]*533/posX[99])-200, 520); //vertical left
	//gfx_line((posX[i]*533/posX[99])+200, 500, (posX[i]*533/posX[99])+200, 520); //vertical right
	//gfx_line((posX[i]*533/posX[99])-200, 510, (posX[i]*533/posX[99]-100)+200, 510); //horizontal

	gfx_color(0,0,0);
	gfx_line(1000, 670, 1100, 670); //horizontal
	gfx_line(1000, 665, 1000, 675); //vertical left
	gfx_line(1100, 665, 1100, 675);	//vertical right
	gfx_text("Scale:             1m", 980, 700);
}

















