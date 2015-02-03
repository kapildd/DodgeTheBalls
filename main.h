#define MAX_N 14

const double wWidth=800,wHeight=600;

//Radii of balls
double rad=18.0;
//Centers of balls
double x[MAX_N],y[MAX_N];
//direction (sign) of velocity and magnitude of velocity
double sx[MAX_N],sy[MAX_N],vx[MAX_N],vy[MAX_N];

int startTime,endTime;  //calculating the time

bool start=false,finish=false;   //true when game starts

bool hitWall=false,checkBound=true; //hitWall for boundary checking and reflection along wall.............and checkBound becomes false when game is over

