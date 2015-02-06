#include <GL/glfw.h>
#include <GL/freeglut.h>
#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <cstring>
#include "vmath.h"
#include "main.h"

void renderBitmapString(float x, float y, float z, char *string) {
    char *c;
    glMatrixMode(GL_PROJECTION);
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glLoadIdentity();

    gluOrtho2D(0, 400, 0, 300);
    glScalef(1, -1, 1);
    glTranslatef(200, -150, 0);
    glRasterPos3f(x, y,z);

    glMatrixMode(GL_MODELVIEW);
	for (c=string; *c != '\0'; c++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
	
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

double distance(double x1, double y1, double x2, double y2)
{
    return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

void collision2Ds(double& xx1, double& yy1, double& xx2, double& yy2,
                 double& vxx1, double& vyy1, double& vxx2, double& vyy2,double& sxx1, double& syy1, double& sxx2, double& syy2)     {

       Vector2<double> p1(xx1,yy1);//centre of ball 1
       Vector2<double> p2(xx2,yy2);//circle of ball 2
       Vector2<double> v1(sxx1*vxx1,syy1*vyy1);//velocity of ball 1
       Vector2<double> v2(sxx2*vxx2,syy2*vyy2);//velocity of ball 2
        Vector2<double> posDiff = (p2-p1);//collision line vector

        Vector2<double> posDiffNorm=posDiff;
        posDiffNorm.normalize();//normalized collision line or unit normal line
        Vector2<double> tangent;//unit tangent between two balls
        tangent.x=-posDiffNorm.y;
        tangent.y=posDiffNorm.x;
        //redundant code for understanding the process
        Vector2<double> v1n=v1*posDiffNorm;//components of velocity of balls along normal
        Vector2<double> v2n=v2*posDiffNorm;
        Vector2<double> v1t=v1*tangent;//components of velocity of balls along tangent
        Vector2<double> v2t=v2*tangent;
        //swapping the normal components and keeping the tangential components same
        Vector2<double> newv1n=v2n*posDiffNorm;
        Vector2<double> newv2n=v1n*posDiffNorm;
        Vector2<double> newv1t=v1t*tangent;
        Vector2<double> newv2t=v2t*tangent;

        //assign new velocities
            v1=newv1n+newv1t;
            v2=newv2n+newv2t;


        //adjust the ball position to avoid sticking of balls in case of intersection of ball boundaries
            Vector2<double> adjust=posDiffNorm*(2*rad-distance(xx1,yy1,xx2,yy2))/2;
            if(newv1n<0)p1+=adjust;
            else p1-=adjust;
            if(newv2n<0)
            p2-=adjust;
            else p2+=adjust;
        //assign the changed positions
        xx1=p1.x;
        xx2=p2.x;
        yy1=p1.y;
        yy2=p2.y;
        //change the sign of velocity accordingly
        if(sxx1*v1.x*vxx1<0)
        sxx1=-sxx1;
        if(syy1*v1.y*vyy1<0)
        syy1=-syy1;
        if(sxx2*v2.x*vxx2<0)
        sxx2=-sxx2;
        if(syy2*v2.y*vyy2<0)
        syy2=-syy2;

        //keep the absolute values in velocities
        vxx1=fabs(v1.x);
        vxx2=fabs(v2.x);
        vyy1=fabs(v1.y);
        vyy2=fabs(v2.y);

       return;
}
//code to maintain velocity above a certain desired value
void checkVel(double &vx,double &vy)
{
        if(checkBound==true)
        {
		srand((unsigned)time(0));
		if(vx<1.5)
		vx=(rand()%2+0.5);
		if(vy<1.5)
		vy=(rand()%2+0.5);
	}
}
//code for checking boundary collisions
void checkBoundary()
{
        if(checkBound==true)
        {
		for(int i=1;i<5;i++)
		{
			if(x[i]>=wWidth/2-rad)
			{
		        x[i]=wWidth/2-rad;
		        hitWall=true;
			}if(x[i]<=rad-wWidth/2)
			{
		        x[i]=rad-wWidth/2;
		        hitWall=true;
			}
			if(y[i]>=wHeight/2-rad)
			{
			    y[i]=wHeight/2-rad;
		        hitWall=true;
			}
			if(y[i]<=rad-wHeight/2)
			{
				y[i]=rad-wHeight/2;
			    hitWall=true;
			}
		}

        }
}


//When game is over drop all the balls
void dropAll()
{
        checkBound=false;
        if(finish==false)
        endTime=glutGet(GLUT_ELAPSED_TIME);
        finish=true;

        for(int i=1;i<5;i++)
        {
            vx[i]=0;vy[i]=-1.5*sy[i];
        }
}

//check the collisions for all combinations of balls
void checkCollision()
{
        for(int i=1;i<=4;i++)
	for(int j=i+1;j<=4;j++)
        {
                if(distance(x[i],y[i],x[j],y[j])<=2*rad)
                {
                        collision2Ds(x[i],y[i],x[j],y[j],vx[i],vy[i],vx[j],vy[j],sx[i],sy[i],sx[j],sy[j]);
                }
	}

	//if collision is with ball controlled by mouse then game is over
	if(distance(x[1],y[1],x[0],-y[0])<=2*rad||
	    distance(x[2],y[2],x[0],-y[0])<=2*rad ||
	    distance(x[3],y[3],x[0],-y[0])<=2*rad ||
	    distance(x[4],y[4],x[0],-y[0])<=2*rad)
	
	{
	        if(start==true)
	        dropAll();	
	}
}

//randomize the initial positions.............
void randomInit()
{
        sx[1]=sy[1]=1;
        sx[2]=sy[2]=-1;
        sy[3]=1;sx[3]=1;
        sy[4]=-1;sx[4]=-1;
        srand((unsigned)time(0));
        for(int i=1;i<=4;i++)
	{
		x[i]=rand()%(int)wWidth-wWidth/2;
        	y[i]=rand()%(int)wHeight-wHeight/2;
    	}
        for(int i=1;i<=4;i++)
        {
		x[i]+= (x[i]<0)?rad:-rad;
	        y[i]+= (y[i]<0)?rad:-rad;
        }
        checkCollision();
        for(int i=1;i<=4;i++)
        {
		vx[i]=(double)(rand()%15)/6;
	        vy[i]=(double)(rand()%15)/6;
	}

}
void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-wWidth/2,wWidth/2, -wHeight/2,wHeight/2, -50.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;


    glColor3d(1,0,0);
    //Your ball...............the one controlled with mouse
    glPushMatrix();
    glTranslated(x[0],-y[0],0.0);
    glutSolidSphere(rad,30,30);
    glPopMatrix();
    //Other balls
    glColor3f(1.0,1.0,0.0);

    for(int i=1;i<5;i++)
    {
		glPushMatrix();
        glTranslated(x[i],y[i],0.0);
        glutSolidSphere(rad,30,30);
    	glPopMatrix();
    }
    //if the game was not started
    if(!start&&!finish)
    {
        glColor3f(0.0,1.0,1.0);
        renderBitmapString(-50,0,0,"Press ENTER or S to start:");
    }
    //if game was started then change the position
    if(start)
	{//if game was finished display the time
    	if(finish)
        {


                int t=(endTime-startTime)/1000;
                char integer_string[32];
                sprintf(integer_string, "%d", t);
                char other_string[64] = "Time: "; // make sure you allocate enough space to append the other string
                strcat(other_string, integer_string);
                strcat(other_string, " seconds");
                char gameover[32] = "Game Over";
                char retry[32]="Press R to retry";
                glColor3f(1.0,1.0,1.0);
                renderBitmapString(-40,00,0,other_string);
                renderBitmapString(-30,10,0,gameover);
                renderBitmapString(-40,20,0,retry);

        }
	    //Move the random balls to next position by checking collisions with other balls and wall
	    checkCollision();
	    checkBoundary();
	    //try to maintain velocity of balls
	    for(int i=1;i<4;i++)
	    checkVel(vx[i],vy[i]);
	
	    //if ball was hit to the boundary...........change the velocity direction of corresponding component
	   if(hitWall==true)
	    {
	    	for(int i = 1; i<=4; i++)
	        {
	        	if(x[i]>=wWidth/2-rad||x[i]<=rad-wWidth/2)
	            sx[i]=-sx[i];
	            if(y[i]>=wHeight/2-rad||y[i]<=rad-wHeight/2)
	            sy[i]=-sy[i];
	            hitWall=false;
	        }
	    }
	    for(int i=1;i<5;i++)
	    {
			x[i]=x[i]+vx[i]*sx[i];y[i]=y[i]+vy[i]*sy[i];
		}
    }

    glFlush();
    glfwSwapBuffers();
    glGetError();
}
int xpos,ypos;

void GLFWCALL getMouse(void *arg)
{
    while(true)
    {
        glfwGetMousePos(&xpos,&ypos);
        //x[0]=xpos-wWidth/2;y[0]=ypos-wHeight/2;
        x[0]=(xpos<rad)?(xpos+rad-wWidth/2):(xpos-(xpos>(wWidth-rad))*rad-wWidth/2);
        y[0]=(ypos<rad)?(ypos+rad-wHeight/2):(ypos-(ypos>(wHeight-rad))*rad-wHeight/2);
    }
}


const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

int main(int argc, char *argv[])
{
    int     width, height;
    int     frame = 0;
    bool    running = true;
    randomInit();
    glfwInit();
    glutInit(&argc,argv);

    if( !glfwOpenWindow( wWidth, wHeight, 0, 0, 0, 0, 0, 0, GLFW_WINDOW ) )
    {
        glfwTerminate();
        return 0;
    }

    glfwSetWindowTitle("Dodge The Balls");

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0,0,0,0);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glDisable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);


    GLFWthread mouse;
    if((mouse=glfwCreateThread(getMouse,NULL)))
    while(running)
    {
        frame++;

        glfwGetWindowSize( &width, &height );
        height = height > 0 ? height : 1;

        glViewport( 0, 0,width, height );

        glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
        glClear( GL_COLOR_BUFFER_BIT );

        if((glfwGetKey(GLFW_KEY_ENTER)||glfwGetKey('S'))&&!start)
        {
            startTime=glutGet(GLUT_ELAPSED_TIME);//note down the initial time
            start=true;
            finish=false;
        }
        if(glfwGetKey('R')&&finish)
        {
            checkBound=true;
            randomInit();
            finish=false;
            start=false;
        }

        display();

        glfwSwapBuffers();

        // exit if ESC was pressed or window was closed
        running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam( GLFW_OPENED);
    }

    glfwDestroyThread(mouse);
    glfwTerminate();

    return 0;
}
