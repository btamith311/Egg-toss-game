#include<windows.h>
#include<iostream>
#include<GL/glut.h>
#include<GL/glu.h>
#include<GL/gl.h>
#include<math.h>
#include<stdlib.h>

using namespace std;

#define vel 0.04
#define max 12
#define Pi 3.14159265359

//0.70 is diff
//<0.25,edit
bool flag=false,movedown=false,night=false,play=false,gameover=false;
GLfloat basket1x=0.01,basket1y=0.100,basket2x=0.5,basket2y=0.450,basket3x=0.91,basket3y=0.800;
GLfloat speed1=0.001,speed2=0.001,speed3=0.001;
GLfloat eggx=basket1x+0.035,eggy=basket1y+0.015,eggrx=0.015,eggry=0.025;
GLint currentbasket=1;
int start_game=0;
float velocity=vel,g=0.0018;
GLdouble width=1000,height=1000;
int points=0,life=max,prevlife=max,below=1,above=3;
int circlex=0.100,circley=0.800,radius=0.080,dn=0;

void init()
{
	glClearColor(0,0,0,1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,1,0,1,-1,1);
}

void addtobasket(int b)
{
    if(b==1)
    {
	eggx=basket1x+0.035;
	eggy=basket1y+0.015;
    }
    if(b==2)
    {
	eggx=basket2x+0.035;
	eggy=basket2y+0.015;
    }
    if(b==3)
    {
	eggx=basket3x+0.035;
	eggy=basket3y+0.015;
    }
}

void background()
{
    if(points%2==0 && dn%2==0)
    {
	if(prevlife==life)
	{
	    dn++;
 	    glClearColor(0,0,0,1);
	    glColor3f(1,1,0);
	    //float theta;
	    //GLfloat angle;
	    //glLineWidth(1.5);
	    night=true;
	   // glBegin(GL_POLYGON);
		//for (int i = 0; i <360 ; i++)
		//{
		 //   theta  = i*Pi*i/180;
		  //  glVertex3f(0.500+0.080*cos(theta)/2, 0.600+0.080*sin(theta)/2,-0.5);
		//}
	    //glEnd();
	}
    }
    if(points%4==0 && dn%2==1)
    {
	if(prevlife==life)
	{
	    night=false;
	    dn++;
 	    glClearColor(0,1,1,1);
	    glColor3ub(255,165,0);
	}
    }
}

void decrement()
{
    basket1y-=0.01;
    basket2y-=0.01;
    basket3y-=0.01;
    eggy-=0.01;
    if(currentbasket==1 && basket1y<0.1)
    {
	movedown=false;
	basket1y=0.1;
	basket2y+=0.01;
	basket3y+=0.01;
	eggy+=0.01;
	below=1;
	above=3;
    }
    if(currentbasket==2 && basket2y<0.1)
    {
	movedown=false;
	basket2y=0.1;
	basket1y+=0.01;
	basket3y+=0.01;
	eggy+=00.01;
	below=2;
	above=1;
    }
    if(currentbasket==3 && basket3y<0.1)
    {
	movedown=false;
	basket3y=0.1;
	basket2y+=0.01;
	basket1y+=0.01;
	eggy+=0.01;
	below=3;
	above=2;
    }
    if(basket1y<-0.24)
	basket1y=0.8;
    if(basket2y<-0.24)
	basket2y=0.8;
    if(basket3y<-0.24)
	basket3y=0.8;
}

void displaylife()
{
    glColor3f(0,1,0);
    char data[6]={'L','I','F','E',' ',':'};
    glRasterPos3f(0.05,0.950,-0.7);
    for(int i=0;i<6;i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,data[i]);
    int l=life;
    char val[2];
    val[1]=48+(l%10);
    l=l/10;
    val[0]=48+l;
    glRasterPos3f(0.05,0.920,-0.7);
    for(int i=0;i<2;i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,val[i]);
}

void displayscore()
{
    glColor3f(0,1,0);
    glRasterPos3f(0.870,0.950,-0.7);
    char data[7]={'S','C','O','R','E',' ',':'};
    for(int i=0;i<7;i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,data[i]);
    int p=points;
    char val[2];
    val[1]=48+(p%10);
    p=p/10;
    val[0]=48+p;
    glRasterPos3f(0.870,0.920,-0.7);
    for(int i=0;i<2;i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,val[i]);
}

void displaymenu()
{
    glColor3f(0,1,0);
    glRasterPos3f(0.38,0.970,-0.7);
    char data[22]={'P','R','E','S','S',' ','S','P','A','C','E','B','A','R',' ','T','O',' ','J','U','M','P'};
        for(int i=0;i<22;i++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15,data[i]);
    glRasterPos3f(0.38,0.950,-0.7);
    char data1[21]={'P','R','E','S','S',' ','P',' ','T','O',' ','P','A','U','S','E','/','P','L','A','Y'};
    for(int i=0;i<22;i++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15,data1[i]);
    glRasterPos3f(0.38,0.93,-0.7);
    char data2[15]={'P','R','E','S','S',' ','Q',' ','T','O',' ','Q','U','I','T'};
     for(int i=0;i<15;i++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15,data2[i]);
    glRasterPos3f(0.38,0.910,-0.7);
    char data3[20]={'R','I','G','H','T',' ','C','L','I','C','K',' ','F','O','R',' ','M','E','N','U'};;
     for(int i=0;i<20;i++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15,data3[i]);
}

void drawbasket(GLfloat i,GLfloat j)
{
    glColor3ub(165,42,42);
    glBegin(GL_POLYGON);
        glVertex3f(i,j,0);
        glVertex3f(i+0.02,j-0.03,0);
        glVertex3f(i+0.05,j-0.03,0);
        glVertex3f(i+0.07,j,0);
    glEnd();

}

void ellipse(float x, float y, float a, float b) {
	glPointSize(1.0);
	glBegin(GL_TRIANGLE_FAN);
	glClearColor(0.0, 0.0,0.0,0.0);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(x, y, -0.2);
	for(int i = 0; i <= 360; ++i) {
		glVertex3f((x + a * cos(i*Pi/180)), (y + b * sin(i*Pi/180)), -0.2);
	}
	glEnd();
}

void key(unsigned char k,int x,int y)
{
	if(k=='p'||k=='P'){
	    play=!play;
	    start_game=1;
	    if(gameover) {
		    life=max;
		    points=0;
		    gameover=false;
		    flag=false;movedown=false;night=false;play=false;
		    start_game=0;
		    basket1x=0.01;basket1y=0.100;basket2x=0.5;basket2y=0.450;basket3x=0.91;basket3y=0.800;
		    eggx=basket1x+0.035;eggy=basket1y+0.015;eggrx=0.015;eggry=0.025;
		    currentbasket=1;
		    velocity=vel;g=0.0018;
		    prevlife=max;below=1;above=3;
		    dn=0;
	    }
	}
	if(k=='q'||k=='Q')
	    exit(0);
	if(k==' ')
	{
	    if(movedown==false)
		flag=true;
	}
}

void reshape(int w,int h)
{
	width=(GLdouble)w;
	height=(GLdouble)h;
	glViewport(0,0, (GLsizei)w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
        glOrtho(0, 1, 0, 1, -1, 1);
}

void display()
{

	   if(start_game==0)
	   {
	   	//glClearColor(0,0,0,1);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glColor3ub(0,0,0);
		glBegin(GL_POLYGON);
		    glVertex3f(0,1,-0.800);
		    glVertex3f(0,0,-0.800);
		    glVertex3f(1,0,-0.800);
		    glVertex3f(1,1,-0.800);
		glEnd();
		glLineWidth(1.5);
		glColor3f(0,1,0);
		glBegin(GL_LINE_LOOP);
		    glVertex3f(0.050,0.950,-0.600);
		    glVertex3f(0.050,0.050,-0.600);
		    glVertex3f(0.950,0.050,-0.600);
		    glVertex3f(0.950,0.950,-0.600);
		glEnd();
		char clg[31]={'P','E','S','I','T',' ','-',' ','B','A','N','G','A','L','O','R','E',' ','S','O','U','T','H',' ','C','A','M','P','U','S','.'};
		glColor3f(1,0,0);
		glRasterPos3f(0.3,0.870,-0.5);
		int i;
		for(int i=0;i<31;i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,clg[i]);
		}
		char title[13]={'"','E','G','G',' ','G','A','M','E',' ','2','D','"',};
		glColor3ub(255,165,0);
		glRasterPos3f(0.42,0.770,-0.5);
		for(int i=0;i<13;i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,title[i]);
		}
		char sub[47]={'(','C','O','M','P','U','T','E','R',' ','G','R','A','P','H','I','C','S',' ','A','N','D',' ','L','A','B','A','R','A','T','O','R','Y',' ','M','I','N','I',' ','P','R','O','J','E','C','T',')'};
		glRasterPos3f(0.32,0.745,-0.5);
		for(int i=0;i<47;i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15,sub[i]);
		}
		char guide[100]="Under the guidance of :";
		glColor3ub(180,60,60);
		glRasterPos3f(0.4,0.62,-0.5);
		for(i=0;i<23;i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,guide[i]);
		char name[20]="Prof. Shubha Raj";
		glColor3f(0,0,1);
		glRasterPos3f(0.43,0.58,-0.5);
		for(i=0;i<16;i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,name[i]);
		char prof[20]="Assisant Professor";
		glRasterPos3f(0.43,0.55,-0.5);
		for(i=0;i<18;i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,prof[i]);
		char dept[20]="Department of CSE";
		glRasterPos3f(0.43,0.52,-0.5);
		for(i=0;i<17;i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,dept[i]);
		char start[30]="\"PRESS 'P' TO START\"";
		glColor3f(0,1,0);
		glRasterPos3f(0.41,0.44,-0.5);
		for(i=0;i<20;i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,start[i]);
		glColor3f(1,1,1);
    		char credits[9]={'D','O','N','E',' ','B','Y',' ',':'};
    		glRasterPos3f(0.7,0.1880,0);
    		 for(int i=0;i<9;i++)
    		    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,credits[i]);
    		char credits1[18]={'A','M','I','T','H',' ','-',' ','1','P','E','1','7','C','S','0','3','3'};
    		glRasterPos3f(0.7,0.16,0);
     		for(int i=0;i<18;i++)
     		   glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,credits1[i]);
    		char credits2[21]={'S','U','P','R','E','E','T','H',' ','-',' ','1','P','E','1','7','C','S','0','5','6'};
   		 glRasterPos3f(0.7,0.14,0);
   		  for(int i=0;i<21;i++)
   		     glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,credits2[i]);
   		 char credits3[18]={'H','A','R','S','H',' ','-',' ','1','P','E','1','7','C','S','0','5','7'};
   		 glRasterPos3f(0.7,0.12,0);
   		  for(int i=0;i<18;i++)
        		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,credits3[i]);
		glutSwapBuffers();
		glFlush();
		glutPostRedisplay();

	   }
	    else{
		if(play&&!gameover) {
	    glEnable(GL_DEPTH_TEST);
	    background();
	    if(night==false)
		glClearColor(0,1,1,1);
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	    if(night)
	    {
		glColor3ub(220,220,220);
	    }
	    else
		glColor3ub(255,165,0);
	    float theta;
	    GLfloat angle;
	    glLineWidth(1.5);
	    glBegin(GL_POLYGON);
		for (int i = 0; i <360 ; i++)
		{
		    theta  = i*Pi*i/180;
		    glVertex3f(0.100+0.080*cos(theta)/2, 0.800+0.080*sin(theta)/2,-0.5);
		}
	    glEnd();
	    glColor3ub(165,42,42);
	    glBegin(GL_POLYGON);
		glVertex3f(0,1.000,-0.9);
		glVertex3f(0,0.900,-0.9);
		glVertex3f(1.000,0.900,-0.9);
		glVertex3f(1.000,1.000,-0.9);
	    glEnd();
	    if((0.07+basket1x>=0.99&&speed1>0) || (basket1x<=0.01&&speed1<0))
	    {
		speed1=-speed1;
	    }
	    basket1x+=speed1;
	    eggx+=speed1;
	    if((0.07+basket2x>=0.99&&speed2>0) || (basket2x<=0.01&&speed2<0))
	    {
		speed2=-speed2;
	    }
	    basket2x+=speed2;
	    if((0.07+basket3x>=0.99&&speed3>0) || (basket3x<=0.01 && speed3<0))
	    {
		speed3=-speed3;
	    }
	    basket3x+=speed3;
	    drawbasket(basket1x,basket1y);
	    drawbasket(basket2x,basket2y);
	    drawbasket(basket3x,basket3y);
	    if(movedown)
		decrement();
	    if(currentbasket==1)
	    {
		eggx=basket1x+0.035;
		if(flag)
		{
		    eggy+=velocity;
		    velocity-=g;
		}
	    }
	    else if(currentbasket==2)
	    {
		eggx=basket2x+0.035;
		if(flag)
		{
		    eggy+=velocity;
		    velocity-=g;
		}
	    }
	    else
	    {
		eggx=basket3x+0.035;
		if(flag)
		{
		    eggy+=velocity;
		    velocity-=g;
		}
	    }
	    if(flag)
	    {
		if(velocity<0&&(eggx>=(basket1x+0.01))&&eggx<=(basket1x+0.05)&&eggy>=(basket1y+0.01)&&eggy<=(basket1y+0.04))
		{
		    prevlife=life;
		    if(currentbasket==1)
		        life--;
		    else
			points++;
		    flag=false;
		    currentbasket=1;
		    velocity=vel;
		    eggx=basket1x+0.035;
		    eggy=basket1y+0.015;

		}
		if(velocity<0&&(eggx>=(basket2x+0.01))&&eggx<=(basket2x+0.05)&&eggy>=(basket2y+0.03)&&eggy<=(basket2y+0.05))
		{
		    prevlife=life;
		    if(currentbasket==2)
		        life--;
		    else
			points++;
		    flag=false;
		    currentbasket=2;
		    velocity=vel;
		    eggx=basket2x+0.035;
		    eggy=basket2y+0.015;

		}
		if(velocity<0&&(eggx>=(basket3x+0.01))&&eggx<=(basket3x+0.05)&&eggy>=(basket3y+0.03)&&eggy<=(basket3y+0.05))
		{
			    prevlife=life;
			    if(currentbasket==3)
				life--;
			    else
				points++;
			    flag=false;
			    currentbasket=3;
			    velocity=vel;
			    eggx=basket3x+0.035;
			    eggy=basket3y+0.015;

		}
		if(eggy<=0.115)
		{
			flag=false;
			velocity=vel;
			addtobasket(below);
		}
	    }
	    ellipse(eggx,eggy,eggrx,eggry);
	    displaylife();
	    displayscore();
	    displaymenu();
	    if(life==0)
		gameover=true;
	    if(currentbasket==above)
		movedown=true;
	    glutSwapBuffers();
	    glutPostRedisplay();
	}
    }
if(gameover)
{
    glClearColor(0,0,0,1);
    play=false;
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    char msg1[9]={'G','A','M','E',' ','O','V','E','R'};
    glRasterPos3f(0.4,0.6,0);
    for(int i=0;i<9;i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,msg1[i]);
    int s=points;
    char l=48+s%10;
    s=s/10;
    char f=48+s;
    char rep[15]={'Y','O','U','R',' ','S','C','O','R','E',' ',':',' ',' ',' '};
    rep[13]=f;
    rep[14]=l;
    glRasterPos3f(0.4,0.5,0);
    for(int i=0;i<15;i++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15,rep[i]);
    glRasterPos3f(0.4,0.47,-0.7);
    char data1[18]={'P','R','E','S','S',' ','P',' ','T','O',' ','R','E','S','T','A','R','T'};
    for(int i=0;i<18;i++)
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,data1[i]);
    glRasterPos3f(0.4,0.44,-0.7);
    char data2[15]={'P','R','E','S','S',' ','Q',' ','T','O',' ','Q','U','I','T'};
    for(int i=0;i<15;i++)
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,data2[i]);
    glRasterPos3f(0.4,0.41,-0.7);
    char data3[20]={'R','I','G','H','T',' ','C','L','I','C','K',' ','F','O','R',' ','M','E','N','U'};
     for(int i=0;i<20;i++)
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,data3[i]);
    glutSwapBuffers();
    glutPostRedisplay();

}

}
void idle()
{
   glutPostRedisplay();
}

void menu(int opt)
{
    switch(opt) {
	case 1: play=!play;
		start_game=1;
		if(gameover) {
		    life=max;
		    points=0;
		    gameover=false;
		    flag=false;movedown=false;night=false;play=false;
		    start_game=0;
		    basket1x=0.01;basket1y=0.100;basket2x=0.5;basket2y=0.450;basket3x=0.91;basket3y=0.800;
		    eggx=basket1x+0.035;eggy=basket1y+0.015;eggrx=0.015;eggry=0.025;
		    currentbasket=1;
		    velocity=vel;g=0.0018;
		    prevlife=max;below=1;above=3;
		    dn=0;
		}
		break;
	case 2: exit(0);
		break;
    }
    glutPostRedisplay();
}

int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(width,height);
    glutCreateWindow("GAME");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(key);
    glutReshapeFunc(reshape);
    glutCreateMenu(menu);
	glutAddMenuEntry("Play / Pause",1);
	glutAddMenuEntry("Quit",2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
    return 0;
}
