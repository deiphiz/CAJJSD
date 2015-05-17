#include <GL/freeglut.h>
#include <math.h>

#define PI 3.1415926535898
#define Cos(th) cos(PI/180*(th))
#define Sin(th) sin(PI/180*(th))

static GLboolean keys[256];
double dim = 3.0;
static GLboolean grid = false;
static GLboolean axes = false; //I am your master
static GLboolean wireframe = false;
static GLboolean shading = false;
static GLboolean showLightPos = false;
static GLboolean skeys[4];
static GLfloat track[2] = {0.0,0.0};
static GLint toggleMode = 0;
static GLfloat th = 0;
static GLfloat ph = 0;
static GLfloat dolly = 2.5;
int fov = 55;
int asp = 1;
void glLoadRotations(void);
//lightPositions
static GLfloat lightX = 2;
static GLfloat lightY = 3;
static GLfloat lightZ = 5;
//rotation speed
static GLfloat rotateSpeed = 2;
//track speed
static GLfloat trackSpeed = 0.1;
//zoom speed
static GLfloat zoomSpeed = 0.1;

//code inside this function only
void drawPrimitives()
{

//grounda
glPushMatrix();
glBegin(GL_QUADS);
    glColor3f(0,1,0);
    glVertex3f(-1,-0.0001,0);
    glVertex3f(1,-0.0001,0);
    glVertex3f(1,-0.0001,1);
    glVertex3f(-1,-0.0001,1);

    glColor4f(0,0.8,0,0.5);
    for(GLfloat i=0; i<1; i+=0.1)
    {
        glVertex3f(-1,-0.00009,i);
        glVertex3f(1,-0.00009,i);
        glVertex3f(1,-0.00009,i+0.05);
        glVertex3f(-1,-0.00009,i+0.05);
    }
    glColor4f(0,0.7,0,0.5);
    for(GLfloat i=-1; i<1; i+=0.1)
    {
        glVertex3f(i,-0.00008,0);
        glVertex3f(i+0.05,-0.00008,0);
        glVertex3f(i+0.05,-0.00008,1);
        glVertex3f(i,-0.00008,1);
    }
glEnd();
glLoadIdentity();
glPopMatrix();

//groundb
glPushMatrix();
glBegin(GL_QUADS);
    glColor3ub(102, 102, 61);
    glVertex3f(-1,-0.0001,-1);//1a
    glVertex3f(1,-0.0001,-1);//2a
    glVertex3f(1,-0.0001,0);//3a
    glVertex3f(-1,-0.0001,0);//4a
    glEnd();
glLoadIdentity();
glPopMatrix();

//platform
glPushMatrix();
glColor3ub(102, 51, 0);
glScalef(2.5, 0.125, 2.5);
glTranslatef(0, -0.5127, 0);
glutSolidCube(1);
glLoadIdentity();
glPopMatrix();

//Underneath
glPushMatrix();
glBegin(GL_TRIANGLE_FAN);
    glColor3ub(75, 37, 0);
    glVertex3f(0, -1, 0);
    glColor3ub(92, 46, 0);
    glVertex3f(-1.25,-0.125,-1.25);
    glVertex3f(-1.25,-0.125,1.25);
    glVertex3f(1.25,-0.125,1.25);
    glVertex3f(1.25,-0.125,-1.25);
    glVertex3f(-1.25,-0.125,-1.25);
glEnd();
glLoadIdentity();
glPopMatrix();

//path
glPushMatrix();
glBegin(GL_QUAD_STRIP);
    glColor3ub(138, 92, 46);
    glVertex3f(0.1, 0, -0.15);
    glVertex3f(-0.1, 0, -0.15);
    glVertex3f(0.1, 0, 0.3);
    glVertex3f(-0.1, 0, 0.3);
    glVertex3f(0.2, 0, 0.5);
    glVertex3f(0.0, 0, 0.5);
    glVertex3f(0.2, 0, 1);
    glVertex3f(0.0, 0, 1);
glEnd();
glLoadIdentity();
glPopMatrix();

//pillars
for(GLfloat x=-0.8; x<0.81; x+=1.6)
{
    for(GLfloat z=-0.8; z<=-0.2; z+=0.2)
    {
        glPushMatrix();
        glTranslatef(x, 0.3, z);
        glRotatef(90, 1, 0, 0);
        glColor3ub(102, 153, 153);
        glutSolidCylinder(0.05, 0.3, 8, 1);
        glLoadIdentity();
        glPopMatrix();
    }
}

//umbrella
glPushMatrix();
glTranslatef(.5,0,.5);
glBegin(GL_TRIANGLE_FAN);
    glColor3ub(184, 92, 0);
    glVertex3f(0,.5,0);//0
    glColor3ub(147, 74, 0);
    glVertex3f(.15,.3,.15);//1
    glVertex3f(.15,.3,-.15);//2
    glVertex3f(-.15,.3,-.15);//3
    glVertex3f(-.15,.3,.15);//4
    glVertex3f(.15,.3,.15);//5`
glEnd();
glLoadIdentity();
glPopMatrix();

//umbrela stand-ish
glPushMatrix();
glTranslatef(.5,0,.5);
glBegin(GL_QUAD_STRIP);
    glColor3ub(102, 61, 0);
    glVertex3f(.01,0,.01);//1
    glVertex3f(.01,.4,.01);//2
    glVertex3f(.01,0,-.01);//3
    glVertex3f(.01,.4,-.01);//4
    glVertex3f(-.01,0,-.01);//5
    glVertex3f(-.01,.4,-.01);//6
    glVertex3f(-.01,0,.01);//7
    glVertex3f(-.01,.4,.01);//8`
    glVertex3f(.01,0,.01);//1
    glVertex3f(.01,.4,.01);//2
glEnd();
glLoadIdentity();
glPopMatrix();

//umbrela table
glPushMatrix();
glTranslatef(.5,0,.5);
glBegin(GL_QUAD_STRIP);
    glColor3ub(102, 61, 0);
    glVertex3f(.19,.15,.19);//1
    glVertex3f(.19,.19,.19);//2
    glVertex3f(.19,.15,-.19);//3
    glVertex3f(.19,.19,-.19);//4
    glVertex3f(-.19,.15,-.19);//5
    glVertex3f(-.19,.19,-.19);//6
    glVertex3f(-.19,.15,.19);//7
    glVertex3f(-.19,.19,.19);//8`
    glVertex3f(.19,.15,.19);//1
    glVertex3f(.19,.19,.19);//2
glEnd();
glLoadIdentity();
glPopMatrix();

//umbrela table quad top
glPushMatrix();
glTranslatef(.5,0,.5);
glBegin(GL_QUADS);
    glColor3f(.5,.3,0);
    glVertex3f(.19,.19,.19);//2
    glVertex3f(.19,.19,-.19);//4
    glVertex3f(-.19,.19,-.19);//6
    glVertex3f(-.19,.19,.19);//8`
glEnd();
glLoadIdentity();
glPopMatrix();

//umbrela table foot bottom lefft
glPushMatrix();
glTranslatef(.36,0,.65);
glBegin(GL_QUAD_STRIP);
    glColor3ub(102, 61, 0);
    glVertex3f(.01,0,.01);//1
    glVertex3f(.01,.15,.01);//2
    glVertex3f(.01,0,-.01);//3
    glVertex3f(.01,.15,-.01);//4
    glVertex3f(-.01,0,-.01);//5
    glVertex3f(-.01,.15,-.01);//6
    glVertex3f(-.01,0,.01);//7
    glVertex3f(-.01,.15,.01);//8`
    glVertex3f(.01,0,.01);//1
    glVertex3f(.01,.15,.01);//2
glEnd();
glLoadIdentity();
glPopMatrix();

//umbrela table foot bottom right
glPushMatrix();
glTranslatef(.65,0,.65);
glBegin(GL_QUAD_STRIP);
    glVertex3f(.01,0,.01);//1
    glVertex3f(.01,.15,.01);//2
    glVertex3f(.01,0,-.01);//3
    glVertex3f(.01,.15,-.01);//4
    glVertex3f(-.01,0,-.01);//5
    glVertex3f(-.01,.15,-.01);//6
    glVertex3f(-.01,0,.01);//7
    glVertex3f(-.01,.15,.01);//8`
    glVertex3f(.01,0,.01);//1
    glVertex3f(.01,.15,.01);//2
glEnd();
glLoadIdentity();
glPopMatrix();

//umbrela table foot top right
glPushMatrix();
glTranslatef(.65,0,.35);
glBegin(GL_QUAD_STRIP);
    glVertex3f(.01,0,.01);//1
    glVertex3f(.01,.15,.01);//2
    glVertex3f(.01,0,-.01);//3
    glVertex3f(.01,.15,-.01);//4
    glVertex3f(-.01,0,-.01);//5
    glVertex3f(-.01,.15,-.01);//6
    glVertex3f(-.01,0,.01);//7
    glVertex3f(-.01,.15,.01);//8`
    glVertex3f(.01,0,.01);//1
    glVertex3f(.01,.15,.01);//2
glEnd();
glLoadIdentity();
glPopMatrix();

//umbrela table foot top left
glPushMatrix();
glTranslatef(.35,0,.35);
glBegin(GL_QUAD_STRIP);
    glVertex3f(.01,0,.01);//1
    glVertex3f(.01,.15,.01);//2
    glVertex3f(.01,0,-.01);//3
    glVertex3f(.01,.15,-.01);//4
    glVertex3f(-.01,0,-.01);//5
    glVertex3f(-.01,.15,-.01);//6
    glVertex3f(-.01,0,.01);//7
    glVertex3f(-.01,.15,.01);//8`
    glVertex3f(.01,0,.01);//1
    glVertex3f(.01,.15,.01);//2
glEnd();
glLoadIdentity();
glPopMatrix();

//chair 1
glPushMatrix();
glTranslatef(.5,.05,.8);
glutSolidCube(.1);
glLoadIdentity();
glPopMatrix();

//chair 2
glPushMatrix();
glTranslatef(.5,.05,.2);
glutSolidCube(.1);
glLoadIdentity();
glPopMatrix();

//chair 3
glPushMatrix();
glTranslatef(.8,.05,.5);
glutSolidCube(.1);
glLoadIdentity();
glPopMatrix();

//ERMAHGERD SWERMMERNG PUURL
glPushMatrix();
glBegin(GL_TRIANGLE_FAN);
    glColor4ub(0, 51, 204, 128);
    glVertex3f(-.5,.001,.5);
    glVertex3f(-.3,.001,.2);
    glVertex3f(-.15,.001,.5);
    glVertex3f(-.15,.001,.6);
    glVertex3f(-.3,.001,.85);
    glVertex3f(-.7,.001,.8);
    glVertex3f(-.85,.001,.6);
    glVertex3f(-.85,.001,.4);
    glVertex3f(-.7,.001,.2);
    glVertex3f(-.3,.001,.2);
glEnd();
glLoadIdentity();
glPopMatrix();

//ERMAHGERD IT'S A ROCK
glPushMatrix();
glTranslatef(-.8,.02,.15);
glScalef(.06,.06,.06);
glColor3f(.6,.6,.7);
glutSolidIcosahedron();
glLoadIdentity();
glPopMatrix();
glPushMatrix();

//ERMAHGERD ANOTHER ROCK >>
glPushMatrix();
glTranslatef(-.77,.02,.86);
glScalef(.02,.02,.02);
glColor3f(.6,.6,.7);
glutSolidDodecahedron();
glLoadIdentity();
glPopMatrix();
glPushMatrix();

//ERMAHGERD ANOTHER ROCK
glPushMatrix();
glTranslatef(-.55,.04,.61);
glScalef(.06,.06,.06);
glColor3f(.6,.6,.7);
glutSolidIcosahedron();
glLoadIdentity();
glPopMatrix();
glPushMatrix();

//ERMAHGERD A ROCK FELL IN THE POND >>
glPushMatrix();
glTranslatef(-.67,.03,.49);
glScalef(.07,.07,.07);
glColor3f(.6,.6,.7);
glutSolidDodecahedron();
glLoadIdentity();
glPopMatrix();
glPushMatrix();

//ERMAHGERD ANOTHER ROCK >>
glPushMatrix();
glTranslatef(-.9,.02,.29);
glScalef(.04,.04,.04);
glColor3f(.6,.6,.7);
glutSolidIcosahedron();
glLoadIdentity();
glPopMatrix();
glPushMatrix();

//ERMAHGERD LIRLY PURDS
glPushMatrix();
glTranslatef(-.4,.02,.2);
glScalef(.2,0,.2);
glBegin(GL_TRIANGLE_FAN);
    glColor3f(0,.8,0);
    glVertex3f(-.5,.01,.5);
    glVertex3f(-.3,.01,.2);
    glVertex3f(-.15,.01,.4);
    glVertex3f(-.15,.01,.6);
    glVertex3f(-.3,.01,.8);
    glVertex3f(-.7,.01,.8);
    glVertex3f(-.85,.01,.6);
    glVertex3f(-.85,.01,.4);
    glVertex3f(-.7,.01,.2);
    glVertex3f(-.3,.01,.2);
glEnd();
glLoadIdentity();
glPopMatrix();

//ERMAHGERD LIRLY PURDS
glPushMatrix();
glTranslatef(-.3,.02,.6);
glScalef(.2,0,.2);
glBegin(GL_TRIANGLE_FAN);
    glColor3f(0,.8,0);
    glVertex3f(-.5,.01,.5);
    glVertex3f(-.3,.01,.2);
    glVertex3f(-.15,.01,.4);
    glVertex3f(-.15,.01,.6);
    glVertex3f(-.3,.01,.8);
    glVertex3f(-.7,.01,.8);
    glVertex3f(-.85,.01,.6);
    glVertex3f(-.85,.01,.4);
    glVertex3f(-.7,.01,.2);
    glVertex3f(-.3,.01,.2);
glEnd();
glLoadIdentity();
glPopMatrix();

//ERMAHGERD LIRLY PURDS
glPushMatrix();
glTranslatef(-.2,.02,.3);
glScalef(.25,0,.25);
glBegin(GL_TRIANGLE_FAN);
    glColor3f(0,.8,0);
    glVertex3f(-.5,.01,.5);
    glVertex3f(-.3,.01,.2);
    glVertex3f(-.15,.01,.4);
    glVertex3f(-.15,.01,.6);
    glVertex3f(-.3,.01,.8);
    glVertex3f(-.7,.01,.8);
    glVertex3f(-.85,.01,.6);
    glVertex3f(-.85,.01,.4);
    glVertex3f(-.7,.01,.2);
    glVertex3f(-.3,.01,.2);
glEnd();
glLoadIdentity();
glPopMatrix();

//ERMAHGERD LIRLY PURDS
glPushMatrix();
glTranslatef(-.6,.02,.65);
glScalef(.1,0,.1);
glBegin(GL_TRIANGLE_FAN);
    glColor3f(0,.8,0);
    glVertex3f(-.5,.01,.5);
    glVertex3f(-.3,.01,.2);
    glVertex3f(-.15,.01,.4);
    glVertex3f(-.15,.01,.6);
    glVertex3f(-.3,.01,.8);
    glVertex3f(-.7,.01,.8);
    glVertex3f(-.85,.01,.6);
    glVertex3f(-.85,.01,.4);
    glVertex3f(-.7,.01,.2);
    glVertex3f(-.3,.01,.2);
glEnd();
glLoadIdentity();
glPopMatrix();

//ERMAHGERD LIRLY PURDS
glPushMatrix();
glTranslatef(-.2,.02,.55);
glScalef(.1,0,.1);
glBegin(GL_TRIANGLE_FAN);
    glColor3f(0,.8,0);
    glVertex3f(-.5,.01,.5);
    glVertex3f(-.3,.01,.2);
    glVertex3f(-.15,.01,.4);
    glVertex3f(-.15,.01,.6);
    glVertex3f(-.3,.01,.8);
    glVertex3f(-.7,.01,.8);
    glVertex3f(-.85,.01,.6);
    glVertex3f(-.85,.01,.4);
    glVertex3f(-.7,.01,.2);
    glVertex3f(-.3,.01,.2);
glEnd();
glLoadIdentity();
glPopMatrix();

//pagoda base
glPushMatrix();
glBegin(GL_QUAD_STRIP);
    glColor3ub(160, 160, 160);
    glVertex3f(0.7, 0, -1);
    glVertex3f(0.55, 0.07, -1);
    glVertex3f(0.7, 0, 0);
    glVertex3f(0.55, 0.07, 0);
    glVertex3f(0.1, 0, 0);
    glVertex3f(0.1, 0.07, 0);
    glVertex3f(0.1, 0, -0.15);
    glVertex3f(0.1, 0.07, -0.15);
    glVertex3f(-0.1, 0, -0.15);
    glVertex3f(-0.1, 0.07, -0.15);
    glVertex3f(-0.1, 0, 0);
    glVertex3f(-0.1, 0.07, 0);
    glVertex3f(-0.7, 0, 0);
    glVertex3f(-0.55, 0.07, 0);
    glVertex3f(-0.7, 0, -1);
    glVertex3f(-0.55, 0.07, -1);
    glVertex3f(0.7, 0, -1);
    glVertex3f(0.55, 0.07, -1);
glEnd();
glLoadIdentity();
glPopMatrix();

//pagoda porch left
glPushMatrix();
glColor3ub(178, 178, 178);
glBegin(GL_QUADS);
    glVertex3f(-0.55, 0.07, 0);
    glVertex3f(-0.55, 0.07, -0.15);
    glVertex3f(-0.1, 0.07, -0.15);
    glVertex3f(-0.1, 0.07, 0);
glEnd();
glLoadIdentity();
glPopMatrix();

//pagoda porch right
glPushMatrix();
glColor3ub(178, 178, 178);
glBegin(GL_QUADS);
    glVertex3f(0.1, 0.07, 0);
    glVertex3f(0.1, 0.07, -0.15);
    glVertex3f(0.55, 0.07, -0.15);
    glVertex3f(0.55, 0.07, 0);
glEnd();
glLoadIdentity();
glPopMatrix();

//pagoda ramp
glPushMatrix();
glBegin(GL_QUADS);
    glColor3ub(122, 122, 82);
    glVertex3f(0.1, 0.07, -0.15);
    glVertex3f(-0.1, 0.07, -0.15);
    glVertex3f(-0.1, 0, 0);
    glVertex3f(0.1, 0, 0);
glEnd();
glLoadIdentity();
glPopMatrix();

//pagoda floor
glPushMatrix();
glBegin(GL_QUADS);
    glColor3ub(255, 204, 128);
    glVertex3f(-0.55, 0.07, -1);
    glVertex3f(0.55, 0.07, -1);
    glVertex3f(0.55, 0.07, -0.15);
    glVertex3f(-0.55, 0.07, -0.15);

    glColor3ub(230, 184, 115);
    for(GLfloat i=-0.55; i<0.54; i+=0.1)
    {
        glVertex3f(i, 0.0701, -1);
        glVertex3f(i+0.05, 0.0701, -1);
        glVertex3f(i+0.05, 0.0701, -0.15);
        glVertex3f(i, 0.0701, -0.15);
    }
glEnd();
glLoadIdentity();
glPopMatrix();

//pagoda bottom wall
glPushMatrix();
glBegin(GL_QUAD_STRIP);
    glColor3ub(102, 51, 0);
    glVertex3f(-0.1, 0.07, -0.15);
    glVertex3f(-0.1, 0.17, -0.15);
    glVertex3f(-0.55, 0.07, -0.15);
    glVertex3f(-0.55, 0.17, -0.15);
    glVertex3f(-0.55, 0.07, -1);
    glVertex3f(-0.55, 0.17, -1);
    glVertex3f(0.55, 0.07, -1);
    glVertex3f(0.55, 0.17, -1);
    glVertex3f(0.55, 0.07, -0.15);
    glVertex3f(0.55, 0.17, -0.15);
    glVertex3f(0.1, 0.07, -0.15);
    glVertex3f(0.1, 0.17, -0.15);
glEnd();
glLoadIdentity();
glPopMatrix();

//pagoda top wall
glPushMatrix();
glTranslatef(0, 0.43, 0);
glBegin(GL_QUAD_STRIP);
    glColor3ub(102, 51, 0);
    glVertex3f(-0.55, 0.07, -0.15);
    glVertex3f(-0.55, 0.17, -0.15);
    glVertex3f(-0.55, 0.07, -1);
    glVertex3f(-0.55, 0.17, -1);
    glVertex3f(0.55, 0.07, -1);
    glVertex3f(0.55, 0.17, -1);
    glVertex3f(0.55, 0.07, -0.15);
    glVertex3f(0.55, 0.17, -0.15);
    glVertex3f(-0.55, 0.07, -0.15);
    glVertex3f(-0.55, 0.17, -0.15);
glEnd();
glLoadIdentity();
glPopMatrix();

//front left window
glPushMatrix();
glBegin(GL_QUAD_STRIP);
    glColor3ub(204, 204, 163);
    glVertex3f(-0.1, 0.17, -0.15);
    glVertex3f(-0.15, 0.21, -0.15);
    glVertex3f(-0.55, 0.17, -0.15);
    glVertex3f(-0.4, 0.21, -0.15);
    glVertex3f(-0.55, 0.5, -0.15);
    glVertex3f(-0.4, 0.46, -0.15);
    glVertex3f(-0.1, 0.5, -0.15);
    glVertex3f(-0.15, 0.46, -0.15);
    glVertex3f(-0.1, 0.17, -0.15);
    glVertex3f(-0.15, 0.21, -0.15);
glEnd();
glLoadIdentity();
glPopMatrix();

//front right window
glPushMatrix();
glBegin(GL_QUAD_STRIP);
    glColor3ub(204, 204, 163);
    glVertex3f(0.1, 0.17, -0.15);
    glVertex3f(0.15, 0.21, -0.15);
    glVertex3f(0.55, 0.17, -0.15);
    glVertex3f(0.4, 0.21, -0.15);
    glVertex3f(0.55, 0.5, -0.15);
    glVertex3f(0.4, 0.46, -0.15);
    glVertex3f(0.1, 0.5, -0.15);
    glVertex3f(0.15, 0.46, -0.15);
    glVertex3f(0.1, 0.17, -0.15);
    glVertex3f(0.15, 0.21, -0.15);
glEnd();
glLoadIdentity();
glPopMatrix();

//front left windowsill
glPushMatrix();
glBegin(GL_QUADS);
    glColor3ub(102, 51, 0);
    glVertex3f(-0.4, 0.21, -0.15);
    glVertex3f(-0.15, 0.21, -0.15);
    glVertex3f(-0.15, 0.21, -0.05);
    glVertex3f(-0.4, 0.21, -0.05);
glEnd();
glLoadIdentity();
glPopMatrix();

//front right windowsill
glPushMatrix();
glTranslatef(0.55, 0, 0);
glBegin(GL_QUADS);
    glColor3ub(102, 51, 0);
    glVertex3f(-0.4, 0.21, -0.15);
    glVertex3f(-0.15, 0.21, -0.15);
    glVertex3f(-0.15, 0.21, -0.05);
    glVertex3f(-0.4, 0.21, -0.05);
glEnd();
glLoadIdentity();
glPopMatrix();

//front left window doors
glPushMatrix();
glBegin(GL_QUADS);
    glColor3ub(102, 26, 0);
    glVertex3f(-0.4, 0.21, -0.15);
    glVertex3f(-0.4, 0.46, -0.15);
    glVertex3f(-0.356, 0.46, -0.05);
    glVertex3f(-0.356, 0.21, -0.05);

    glVertex3f(-0.15, 0.21, -0.15);
    glVertex3f(-0.15, 0.46, -0.15);
    glVertex3f(-0.194, 0.46, -0.05);
    glVertex3f(-0.194, 0.21, -0.05);
glEnd();
glLoadIdentity();
glPopMatrix();

//front right window doors
glPushMatrix();
glTranslatef(0.55, 0, 0);
glBegin(GL_QUADS);
    glColor3ub(102, 26, 0);
    glVertex3f(-0.4, 0.21, -0.15);
    glVertex3f(-0.4, 0.46, -0.15);
    glVertex3f(-0.356, 0.46, -0.05);
    glVertex3f(-0.356, 0.21, -0.05);

    glVertex3f(-0.15, 0.21, -0.15);
    glVertex3f(-0.15, 0.46, -0.15);
    glVertex3f(-0.194, 0.46, -0.05);
    glVertex3f(-0.194, 0.21, -0.05);
glEnd();
glLoadIdentity();
glPopMatrix();

//pagoda middle wall
glPushMatrix();
glBegin(GL_QUAD_STRIP);
    glColor3ub(204, 204, 163);
    glVertex3f(-0.55, 0.17, -0.15);
    glVertex3f(-0.55, 0.5, -0.15);
    glColor3ub(184, 184, 147);
    glVertex3f(-0.55, 0.17, -1);
    glVertex3f(-0.55, 0.5, -1);
    glVertex3f(0.55, 0.17, -1);
    glVertex3f(0.55, 0.5, -1);
glEnd();
glLoadIdentity();
glPopMatrix();

//pagoda side window
glPushMatrix();
glBegin(GL_QUAD_STRIP);
    glColor3ub(184, 184, 147);
    glVertex3f(0.55, 0.17, -1);
    glVertex3f(0.55, 0.21, -0.9);
    glVertex3f(0.55, 0.5, -1);
    glVertex3f(0.55, 0.46, -0.9);
    glColor3ub(204, 204, 163);
    glVertex3f(0.55, 0.5, -0.15);
    glVertex3f(0.55, 0.46, -0.25);
    glVertex3f(0.55, 0.17, -0.15);
    glVertex3f(0.55, 0.21, -0.25);
    glColor3ub(184, 184, 147);
    glVertex3f(0.55, 0.17, -1);
    glVertex3f(0.55, 0.21, -0.9);
glEnd();
glLoadIdentity();
glPopMatrix();

//side window grid
glPushMatrix();
glBegin(GL_QUADS);
    glColor3ub(102, 26, 0);
    for(GLfloat i=-0.25; i>-0.9; i-=.1)
    {
        glVertex3f(0.55, 0.21, i);
        glVertex3f(0.55, 0.46, i);
        glVertex3f(0.55, 0.46, i-0.05);
        glVertex3f(0.55, 0.21, i-0.05);
    }
glEnd();
glLoadIdentity();
glPopMatrix();

//roof beams
glPushMatrix();
glBegin(GL_QUADS);
    glColor3ub(102, 51, 0);
    for(GLfloat i=-1; i<-0.15; i+=0.1)
    {
        glVertex3f(-0.55, 0.5, i);
        glVertex3f(0.55, 0.5, i);
        glVertex3f(0.55, 0.5, i+0.05);
        glVertex3f(-0.55, 0.5, i+0.05);
    }
glEnd();
glLoadIdentity();
glPopMatrix();

//Roof Base
glPushMatrix();
glBegin(GL_QUAD_STRIP);
    glColor3ub(166, 83, 0);
    glVertex3f(-0.5, 0.7, -0.95);
    glVertex3f(-0.75, 0.5, -1.2);
    glVertex3f(0.5, 0.7, -0.95);
    glVertex3f(0.75, 0.5, -1.2);
    glVertex3f(0.5, 0.7, -0.2);
    glVertex3f(0.75, 0.5, 0.05);
    glVertex3f(-0.5, 0.7, -0.2);
    glVertex3f(-0.75, 0.5, 0.05);
    glVertex3f(-0.5, 0.7, -0.95);
    glVertex3f(-0.75, 0.5, -1.2);
glEnd();
glLoadIdentity();
glPopMatrix();

//Roof Sides
glPushMatrix();
glBegin(GL_TRIANGLES);
    glColor3ub(102, 26, 0);
    glVertex3f(0.5, 1, -0.575);
    glVertex3f(0.5, 0.7, -0.95);
    glVertex3f(0.5, 0.7, -0.2);

    glVertex3f(-0.5, 1, -0.575);
    glVertex3f(-0.5, 0.7, -0.95);
    glVertex3f(-0.5, 0.7, -0.2);
glEnd();
glLoadIdentity();
glPopMatrix();

//Roof top
glPushMatrix();
glBegin(GL_QUAD_STRIP);
    glColor3ub(184, 92, 0);
    glVertex3f(-0.5, 0.7, -0.2);
    glVertex3f(0.5, 0.7, -0.2);
    glColor3ub(166, 83, 0);
    glVertex3f(-0.7, 1, -0.575);
    glVertex3f(0.7, 1, -0.575);
    glColor3ub(184, 92, 0);
    glVertex3f(-0.5, 0.7, -0.95);
    glVertex3f(0.5, 0.7, -0.95);
glEnd();
glLoadIdentity();
glPopMatrix();

//Beam at the top
glPushMatrix();
glTranslatef(-0.7,1,-0.575);
glRotatef(90, 0, 1, 0);
glColor3ub(102, 26, 0);
glutSolidCylinder(0.03, 1.4, 8, 1);
glLoadIdentity();
glPopMatrix();
}

void switchProjection()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (toggleMode) {
    gluPerspective(fov,asp,dim/4,4*dim);
  }
  else {
    glOrtho(-dim*asp,+dim*asp, -dim,+dim, -dim,+dim);
  }

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}



void draw_axes(void)
{
    glLineWidth(3);
    glBegin(GL_LINES);
       glColor3f(1.0, 0.0, 0.0);    // x-axis
       glVertex3f(0.0, 0.0, 0.0);
       glVertex3f(1.0, 0.0, 0.0);

       glColor3f(0.0, 1.0, 0.0);    // y-axis
       glVertex3f(0.0, 0.0, 0.0);
       glVertex3f(0.0, 1.0, 0.0);

       glColor3f(0.0, 0.0, 1.0);    // z-axis
       glVertex3f(0.0, 0.0, 0.0);
       glVertex3f(0.0, 0.0, 1.0);
    glEnd();
    glLineWidth(1);
}

void draw_grid(void)
{
    glBegin(GL_LINES);
    for(GLfloat a =-1; a < 1;){
        glColor3f(.2, .2, .2);
        glVertex3f(-1,0,a);
        glVertex3f(1,0,a);
        a = a+0.2;
    }
    glEnd();

    glBegin(GL_LINES);
    for(GLfloat b =-1; b < 1;){
        glColor3f(.2, .2, .2);
        glVertex3f(b,0,-1);
        glVertex3f(b,0,1);
        b = b+0.2;
    }
    glEnd();
}

void drawLightPos(void)
{
    glColor3f(1,1,0);
    glLineWidth(20);
    glBegin(GL_LINES);
    glVertex3f(lightX,lightY,lightZ);
    glVertex3f(0,0,0);
    glEnd();
    glLineWidth(1);

}

void display()
{
  if(wireframe)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  glLoadIdentity();
  if(showLightPos)
  drawLightPos();
  glLoadRotations();

  if(shading)
  {
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  }

  drawPrimitives();
  glLoadIdentity();
  glLoadRotations();

  if(shading)
  {
  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);
  glDisable(GL_COLOR_MATERIAL);
  }
  if(axes)
  draw_axes();
  if(grid)
  draw_grid();

  glFlush();
  glutSwapBuffers();
}

void glLoadRotations()
{
  glTranslatef(track[0], track[1], 0);
  if (toggleMode) {
    double Ex = -2*dim*Sin(th)*Cos(ph);
    double Ey = +2*dim        *Sin(ph);
    double Ez = +2*dim*Cos(th)*Cos(ph);
    gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
  }
  else {
    glRotatef(ph,1,0,0);
    glRotatef(th,0,1,0);
  }
  glScalef(dolly,dolly,dolly);
}


void reshape(int width,int height)
{
  glutReshapeWindow(600,600);
  glViewport(0,0, width,height);
  switchProjection();
}


void event_keyboard(unsigned char key, int x, int y)
{
        keys[key] = true;
        switch(key)
        {
        case 'r':  if(wireframe)
                   wireframe=false;
                   else
                   {
                       wireframe = true;
                       shading = false;
                   }

                   glutPostRedisplay();
                   break;
        case 'p':  toggleMode = 1-toggleMode;
                   switchProjection();
                   glutPostRedisplay();
                   break;
        case 'x':  if(axes)axes=false;
                   else axes = true;
                   glutPostRedisplay();
                   break;
        case 'g':  if(grid)grid=false;
                   else grid = true;
                   glutPostRedisplay();
                   break;
        case 'l':  if(showLightPos)showLightPos=false;
                   else showLightPos = true;
                   glutPostRedisplay();
                   break;
        case 't':  if(shading)shading=false;
                   else
                   {
                        wireframe = false;
                        shading = true;
                   }

                   glutPostRedisplay();
                   break;
        default :  break;
        }
}

void event_keyboardUp(unsigned char key, int x, int y)
{
        keys[key] = false;
}

void idle()
{
    //w
    if (keys[119]==true || keys[87]==true)
    {
        ph += rotateSpeed;
        glutPostRedisplay();
    }
    //a
    if (keys[97]==true || keys[65]==true)
    {
        th -= rotateSpeed;
        glutPostRedisplay();
    }
    //s
   if (keys[115]==true || keys[83]==true)
   {
       ph -= rotateSpeed;
       glutPostRedisplay();
   }
    //d
   if (keys[100]==true || keys[68]==true)
   {
       th += rotateSpeed;
       glutPostRedisplay();
   }
    //1
    if (keys[49]==true)
    {
        dolly = 2.5;
        th = 0;
        ph = 0;
        track[0] = 0;
        track[1] = 0;
        glutPostRedisplay();
    }
    //2
    if (keys[50]==true)
    {
        dolly = 2.5;
        track[0] = 0;
        track[1] = 0;
        th = 0;
        ph = 90;
        glutPostRedisplay();
    }
    //3
    if (keys[51]==true)
    {
        dolly = 2.5;
        th = -90;
        ph = 0;
        track[0] = 0;
        track[1] = 0;
        glutPostRedisplay();
    }
    if (keys[61] || keys[43])
    {
        dolly += zoomSpeed;
        glutPostRedisplay();
    }

    if (keys[45] || keys[95])
    {
        dolly -= zoomSpeed;
        glutPostRedisplay();
    }

    if (skeys[0])
    {
        track[0] += trackSpeed;
        glutPostRedisplay();
    }

    if (skeys[3])
    {
        track[0] -= trackSpeed;
        glutPostRedisplay();
    }
    if (skeys[1])
    {
        track[1] -= trackSpeed;
        glutPostRedisplay();
    }
    if (skeys[2])
    {
        track[1] += trackSpeed;
        glutPostRedisplay();
    }


   if(ph > 360.0) ph -= 360.0;
   if(th > 360.0) th -= 360.0;

   Sleep(33.3333); //30 Frames Per Second
}

void event_keyboardSpec(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_LEFT: skeys[0] = true; break;
        case GLUT_KEY_RIGHT: skeys[3] = true; break;
        case GLUT_KEY_UP: skeys[1] = true; break;
        case GLUT_KEY_DOWN: skeys[2] = true; break;
        default: break;
    }
}

void event_keyboardUpSpec(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_LEFT: skeys[0] = false; break;
        case GLUT_KEY_RIGHT: skeys[3] = false; break;
        case GLUT_KEY_UP: skeys[1] = false; break;
        case GLUT_KEY_DOWN: skeys[2] = false; break;
        default: break;
    }
}


void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //set lighting intensity and color
    glEnable(GL_NORMALIZE);
    GLfloat light_ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat light_diffuse[] = {.8, .8, .8, 1.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[] = {lightX, lightY, lightZ, 0.0};

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2.0);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.5);

    //material properties
    GLfloat mat_ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat mat_diffuse[] = {.8, .8, .8, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {70.0};
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

    glShadeModel(GL_SMOOTH);
}

int main(int argc,char* argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(600, 600);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("JJSD_mp3");
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(event_keyboard);
  glutKeyboardUpFunc(event_keyboardUp);
  glutSpecialFunc(event_keyboardSpec);
  glutSpecialUpFunc(event_keyboardUpSpec);


  glutIdleFunc(idle);
  glutMainLoop();
  return 0;
}

