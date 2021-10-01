// 3D Scene - scene source
// Constructs the 3D scene
// Gavin Zimmerman

// DEPENDENCIES
#include "bridge.h"
#include "objects.h"

#include <stdio.h>
#include <stdlib.h>

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


// SOURCE

// renderUpdate - renders a scene frame
static void renderUpdate() {
    // Start Render / Cleanup
    {
        glClearColor((float)0/255, (float)45/255, (float)50/255, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glBlendFunc(GL_SRC0_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        glEnable(GL_DEPTH_TEST /*| GL_BLEND*/);
        glLoadIdentity();
    }
    // Set Camera
    cameraUpdate();
    
    // Render scnee
    bridge(); 
   
    // End Render / Display
    {
        glFlush();
        glutSwapBuffers();
    }
}

void keyDown(unsigned char key, int x, int y) {
    if (cameraDownButtons(key, x, y)>=0)
        return;
    if (key=='q')
        exit(0);
}

void keyUp(unsigned char key, int x, int y) {
    if (cameraUpButtons(key, x, y)>=0)
        return;
    if (key=='q')
        exit(0);
}



// Main Program
int main(int argc, char* argv[]) {
    // Init

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    
    glutInitWindowSize(1080, 720);
    glutCreateWindow("// Gavin Zimmerman //\n");

#ifdef USEGLEW
    if (glewInit()!=GLEW_OK) exit(-1);
#endif

    // Connect callbacks
    glutDisplayFunc(renderUpdate);

    // Inputs
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);
    glutIdleFunc(moveCam);
    

    glutMainLoop();
    
    return 0;
}