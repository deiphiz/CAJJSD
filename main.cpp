#include <GL/freeglut.h>
#include <math.h>

#define PI 3.1415926535898
#define Cos(th) cos(PI/180*(th))
#define Sin(th) sin(PI/180*(th))

static GLboolean keys[256];
double dim = 3.0;
static GLboolean grid = true;
static GLboolean axes = true; //I am your master
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
static GLfloat lightX = 3;
static GLfloat lightY = 3;
static GLfloat lightZ = 5;

//code inside this function only
void drawPrimitives()
{
    //grounda
    glPushMatrix();
glBegin(GL_QUADS);
glColor3f(0,1,0);
glVertex3f(-1,-0.1,-1);//1b
glVertex3f(1,-0.1,-1);//2b
glVertex3f(1,-0.1,1);//3b
glVertex3f(-1,-0.1,1);//4b
glEnd();
glLoadIdentity();
glPopMatrix();

glPushMatrix();
//groundb
glBegin(GL_QUADS);
glColor3f(0,1,0);
glVertex3f(-1,0,-1);//1a
glVertex3f(1,0,-1);//2a
glVertex3f(1,0,1);//3a
glVertex3f(-1,0,1);//4a
glEnd();
glLoadIdentity();
glPopMatrix();
// side matrix
glPushMatrix();
glBegin(GL_QUAD_STRIP);
glColor3f(0.6,.3,0);
glVertex3f(-1,0,-1);//1b
glVertex3f(-1,.1,-1);//1a
glVertex3f(1,0,-1);//2b
glVertex3f(1,.1,-1);//2a
glVertex3f(1,0,1);//3b
glVertex3f(1,.1,1);//3a
glVertex3f(-1,0,1);//4b
glVertex3f(-1,.1,1);//4a
glVertex3f(-1,0,-1);//1b
glVertex3f(-1,.1,-1);//1a
glEnd();
glLoadIdentity();
glPopMatrix();

//house floor
glPushMatrix();
glTranslatef(-.5,.5,-.5);
glColor3f(1,1,1);
glutSolidCube(.8);
glLoadIdentity();
glPopMatrix();

//mini pool thingy
glPushMatrix();
glBegin(GL_TRIANGLE_FAN);
glColor4f(.5,72, 118, 255);
glVertex3f(.5,.01,.5);
glVertex3f(.5,.01,.1);
glVertex3f(.450,.01,.150);
glVertex3f(.4,.01,.2);
glVertex3f(.350,.01,.250);
glVertex3f(.3,.01,.3);
glVertex3f(.250,.01,.350);
glVertex3f(.2,.01,.4);
glVertex3f(.150,.01,.450);
glVertex3f(.1,.01,.5);
glVertex3f(.150,.01,.550);
glVertex3f(.2,.01,.6);
glVertex3f(.250,.01,.650);
glVertex3f(.3,.01,.7);
glVertex3f(.350,.01,.750);
glVertex3f(.4,.01,.8);
glVertex3f(.450,.01,.850);
glVertex3f(.5,.01,.9);
glVertex3f(.550,.01,.850);
glVertex3f(.6,.01,.8);
glVertex3f(.650,.01,.750);
glVertex3f(.7,.01,.7);
glVertex3f(.750,.01,.650);
glVertex3f(.8,.01,.6);
glVertex3f(.850,.01,.550);
glVertex3f(.9,.01,.5);
glVertex3f(.850,.01,.450);
glVertex3f(.8,.01,.4);
glVertex3f(.750,.01,.350);
glVertex3f(.7,.01,.3);
glVertex3f(.650,.01,.250);
glVertex3f(.6,.01,.2);
glVertex3f(.550,.01,.150);
glVertex3f(.5,.01,.1);

glEnd();
glLoadIdentity();
glPopMatrix();

//uuper cubes
glPushMatrix();
glTranslatef(-.5,1,-.5);
glColor3f(1,1,1);
glutSolidCube(.5);
glLoadIdentity();
glPopMatrix();
//umbrella
glPushMatrix();
glTranslatef(.5,0,.5);
glBegin(GL_TRIANGLE_FAN);
glColor3f(.6,.6,.7);
glVertex3f(0,.5,0);//0
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
glColor3f(.5,.3,0);
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
glColor3f(.5,.3,0);
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
glColor3f(.5,.3,0);
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
glColor3f(.5,.3,0);
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
glColor3f(.5,.3,0);
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
glColor3f(.5,.3,0);
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
//chair 1 bot mid
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
glTranslatef(.19,.05,.5);
glutSolidCube(.1);
glLoadIdentity();
glPopMatrix();
//chair 4
glPushMatrix();
glTranslatef(.8,.05,.5);
glutSolidCube(.1);
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
  glTranslatef(track[0], track[1], 0);
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
    if (keys[119]==true)
    {
        ph += 0.2;
        glutPostRedisplay();
    }
    //a
    if (keys[97]==true)
    {
        th -= 0.2;
        glutPostRedisplay();
    }
    //s
   if (keys[115]==true)
   {
       ph -= 0.2;
       glutPostRedisplay();
   }
    //d
   if (keys[100]==true)
   {
       th += 0.2;
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
        dolly += 0.05;
        glutPostRedisplay();
    }

    if (keys[45] || keys[95])
    {
        dolly -= 0.05;
        glutPostRedisplay();
    }

    if (skeys[0])
    {
        track[0] -= 0.05;
        glutPostRedisplay();
    }

    if (skeys[3])
    {
        track[0] += 0.05;
        glutPostRedisplay();
    }
    if (skeys[1])
    {
        track[1] += 0.05;
        glutPostRedisplay();
    }
    if (skeys[2])
    {
        track[1] -= 0.05;
        glutPostRedisplay();
    }


   if(ph > 360.0) ph -= 360.0;
   if(th > 360.0) th -= 360.0;


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
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glClearColor(0.0, 0.0, 0.0, 0.0);

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
    GLfloat mat_shininess[] = {60.0};
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
  glutInitWindowSize(900, 900);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("OpenGL");
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

