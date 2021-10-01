// 3D scene - Camera
// Operates camera functionality
// Gavin Zimmerman


//DEPENDENCIES
#include "camera.h"
#include <math.h>
#include <stdarg.h>

#ifdef USEGLEW
#include <GL/glew.h>
#endif
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
// Supress depreciated warnings
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#else
#include <GL/glut.h>
#endif

#ifndef RES
#define RES 1
#endif

// CONFIGURABLES
double cam_move_speed = 15.0/40.0;
double cam_ang_speed = 1.0/5.0;
double static fov = 60;

// STATE GLOBALS
static int mode = 0;
static int camId = 0;
static double forward=0, right=0;

static int mouse_button_left = 0, mouse_button_middle = 0, mouse_button_right = 0;
static int shift = 0;
static int mouse_xpos=0, mouse_ypos=0;


// Cameras
static double ph[] = {30,20}, th[] = {-30,-90};
static double camPosX[]={-10,-10}, camPosY[]={-10,-5}, camPosZ[]={-10,-13};
static double zoom[] = {30,8};


double static dim = 20;
double static asp = 16/9;


// SOURCE

// Event Callbacks
// mouseButton - For handling inputs on mouse
    // @param button - The key pressed
    // @param state - How the callback was triggered (key down or key up)
    // @param x - Mouse horizontal position in pixels
    // @param y - Mouse vertical position in pixels
void mouseButton(int button, int state, int x, int y) {
    // Set state of relevant button
    if (button == GLUT_LEFT_BUTTON)
        mouse_button_left = (state == GLUT_DOWN);
    else if (button == GLUT_MIDDLE_BUTTON)
        mouse_button_middle = (state == GLUT_DOWN);
    else if (button == GLUT_RIGHT_BUTTON)
        mouse_button_right = (state == GLUT_DOWN);

    // Set state of button inputs
    mouse_xpos = x; 
    mouse_ypos = y;
    shift = glutGetModifiers() & GLUT_ACTIVE_SHIFT;
}



// mouseMove - For handling when cursor is moved
    // @param x - Mouse horizontal position in pixels
    // @param y - Mouse vertical position in pixels
void mouseMove(int x, int y) {
    if (!mouse_button_middle)
        return;

    double dx = (double)(x-mouse_xpos), dy = (double)(y-mouse_ypos);
    // Blender Movement controls
    /*if (shift) {
        glPushMatrix();
        glLoadIdentity();
        
        // Apply rotation to XY inputs to get right vector sum and up vector sum; and add to camera offset
        glRotated(-th[camId],0,1,0);
        glRotated(ph[camId],1,0,0);
        glTranslated((double)dx*cam_move_speed, (double)dy*cam_move_speed, 0);
        
        double m[16];
        glGetDoublev(GL_MODELVIEW_MATRIX, m);
        glPopMatrix();
        camPosX[camId]+=m[12];
        camPosY[camId]-=m[13];
        camPosZ[camId]+=m[14];
    }
    else */{
        th[camId]+=dx*cam_ang_speed;
        ph[camId]+=dy*cam_ang_speed;
    }

    mouse_xpos = x; 
    mouse_ypos = y;
    glutPostRedisplay();
}

// Moves cameras as an idle function reading input state variables accessable globally
void moveCam() {
    if (!((forward==0) && (right==0))) {
        
        glPushMatrix();
        glLoadIdentity();
        
        // Apply rotation to XY inputs to get right vector sum and up vector sum; and add to camera offset
        glRotated(-th[camId],0,1,0);
        if (mode<2)
            glRotated(ph[camId],1,0,0);
        double movemag = sqrt(pow(forward,2)+pow(right,2));
        glTranslated(-right*cam_move_speed*(shift?2:1)/movemag, 0, forward*cam_move_speed*(shift?2:1)/movemag);
        
        double m[16];
        glGetDoublev(GL_MODELVIEW_MATRIX, m);
        glPopMatrix();
        camPosX[camId]+=m[12];
        camPosY[camId]-=m[13];
        camPosZ[camId]+=m[14];
        glutPostRedisplay();
    }
    
}

// Called when a user presses/is pressing a button
int cameraDownButtons(unsigned char key, int x, int y) {
    if ((key>='A') && (key<='Z')) key-='A'-'a';
    if (key=='i') {
        zoom[camId]-=1;
        zoom[camId] =zoom[camId]>5?zoom[camId]:5;
        glutPostRedisplay();
    }
    else if (key=='o') {
        zoom[camId]+=1;
        zoom[camId]= zoom[camId]<300?zoom[camId]:300;
        glutPostRedisplay();
    }
    else if (key=='w') 
        forward=1;
    else if (key=='a') 
        right=-1;
    else if (key=='s') 
        forward=-1;
    else if (key=='d') 
        right=1;
    else if (key=='m') {
        mode=(mode+1)%3;
        project();
        glutPostRedisplay();
    }
    else {
        // Did not register input - pass it to other functions
        return -1;
    }
    shift = glutGetModifiers() & GLUT_ACTIVE_SHIFT;
    return 0;
}


// Called when user releases a button
int cameraUpButtons(unsigned char key, int x, int y) {
    if ((key>='A') && (key<='Z')) key-='A'-'a';
    if (key=='w') 
        forward=0;
    else if (key=='a') 
        right=0;
    else if (key=='s') 
        forward=0;
    else if (key=='d') 
        right=0;
    else {
        // Did not register input - pass it to other functions
        return -1;
    }
    shift = glutGetModifiers() & GLUT_ACTIVE_SHIFT;
    
    return 0;
}


// cameraUpdate - Places camera position
void cameraUpdate() {
    // Apply rotation at distance
    glTranslatef(0,0,-zoom[camId]);
    glRotated(ph[camId],1,0,0);
    glRotated(th[camId],0,1,0);

    // Create Cursor
    {
        glPushMatrix();
        glPointSize(3);
        glColor3f(1,1,1);
        glBegin(GL_POINTS);
        glVertex3d(0,0,0);
        glEnd();
        glPopMatrix();
    }

    // Apply camera Offset
    glTranslated(camPosX[camId],camPosY[camId],camPosZ[camId]);
}



// reshape - Reshapes viewport display
void reshape(int width, int height) {
    asp = (height>0) ? (double)width/height : 1;

    glViewport(0,0, width*RES, height*RES);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(fov, asp, dim/8, 6*dim);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


// Function to update projection and camera state
void project() {
    if (mode<2) {
        camId=0;
        cam_ang_speed = 1.0/5.0;
    }
    else {
        camId=1;
        cam_ang_speed = 1.0/3.0;
    }
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (mode==1) {
        glOrtho(-asp*dim,+asp*dim, -dim,+dim, -6*dim, +6*dim);
    }
    else {
        gluPerspective(fov, asp, dim/8, 6*dim);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}