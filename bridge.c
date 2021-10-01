// Bridge Scene
// A source file to build the scene called 'bridge' because it contains a bridge
// Gavin Zimmerman


// DEPENDENCIES
#include "objects.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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


// CONSTANTS
#define SCENE_NAME "Cube Trees"





// SOURCE
// Import Scene
void bridge() {
    GLubyte c[] = {255,255,255};
    glTranslated(0,-14,0);
    glScaled(3,3,3);
    
    // Backwall
    c[0] = 100; c[1]=100; c[2]=100;
    cube(-5,9,-2,  3,4,2,  0,0,0,  c);
    c[0] = 95; c[1]=90; c[2]=100;
    cube(4,8.6,-2,  2,3.6,2,  0,0,0,  c);

    // Base
    c[0] = 120; c[1]=120; c[2]=120;
    cube(-6,0,2.4,  4,5,6.4,  0,0,0,  c);
    c[0] = 105; c[1]=100; c[2]=110;
    cube(6,0,2.4,  4,5,6.4,  0,0,0,  c);

    // Water
    c[0] = 0x25; c[1]=0xb9; c[2]=0xe1;
    cube(0,7,-2,  4,4.9,1.9,  0,0,0,  c);
    cube(0,0,2.15,  4,4.9,6.3,  0,0,0,  c);
    c[0] = 0x10; c[1]=0xa4; c[2]=0xcc;
    cube(0,-5,5,  20,1,10,  0,0,0,  c);

    // Water foam
    c[0] = 250; c[1]=252; c[2]=255;
    cube(.9,5,-.6,  1.5,1,1.2,  0,25,0,  c);
    cube(-.3,5,-.7,  1.6,.6,1.5,  0,-10,0,  c);
    cube(0,5,-.7,  1.8,.4,1.5,  0,10,0,  c);

    cube(1.4,-4,9,  1.5,1,1.2,  0,25,0,  c);
    cube(-.8,-4,9,  1.6,.6,1.5,  0,-10,0,  c);
    cube(0,-4,9,  1.8,.4,1.5,  0,10,0,  c);

    // Rocks
    c[0] = 80; c[1]=90; c[2]=90;
    cube(.4,8,-.65,  .4,1.2,1,  0,0,0,  c);
    c[0] = 70; c[1]=60; c[2]=70;
    cube(-4,7,-.8,  1.2,.4,1,  0,0,0,  c);
    cube(-3,10,-.7,  .8,.4,1,  0,0,0,  c);
    cube(-6,12,-.7,  .8,.4,.8,  0,0,0,  c);
    cube(-7.4,8.2,-.8,  .8,.4,1,  0,0,0,  c);
    cube(-7.4,9.6,-2,  .8,.4,.8,  0,0,0,  c);
    cube(5.4,9.6,-2,  .8,.4,1.2,  0,0,0,  c);
    cube(5.4,7,-1.5,  .8,.4,.6,  0,0,0,  c);
    cube(4,6,-.8,  1.1,.4,1,  0,0,0,  c);
    cube(5,8.2,-.8,  .5,.4,1,  0,0,0,  c);
    cube(4.3,10.4,-.8,  .8,.4,1,  0,0,0,  c);

    c[0] = 90; c[1]=90; c[2]=105;
    cube(-8.6,2.3,2,  3,4.2,2.3,  0,0,0,  c);
    c[0] = 120; c[1]=120; c[2]=125;
    cube(-8.4,4.1,-1,  2.4,3,2.7,  0,0,0,  c);

    c[0] = 80; c[1]=80; c[2]=85;
    cube(6.2,2.4,8.4,  2.4,3,1.2,  0,0,0,  c);
    cube(7.2,5,3.3,  1.4,1,1.2,  0,30,0,  c);
    c[0] = 70; c[1]=70; c[2]=75;
    cube(9.6,-1,1,  1.4,2.8,2.5,  0,00,0,  c);

    // Bushes
    c[0] = 30; c[1]=190; c[2]=105;
    cube(-5,5,1.3,  1.4,1,1.2,  0,30,0,  c);
    c[0] = 20; c[1]=150; c[2]=80;
    cube(-5,4.6,1.3,  2,1,1.5,  0,-10,0,  c);

    c[0] = 30; c[1]=190; c[2]=105;
    cube(7,5,-2,  1.4,2,1.2,  0,40,0,  c);
    c[0] = 20; c[1]=150; c[2]=80;
    cube(7,5,-2,  2,1,1.5,  0,-20,0,  c);
    
    // Bridge
    {
        c[0] = 140; c[1]=100; c[2]=85;
        glPushMatrix();
        glTranslated(0,0.1,-1.5);
        glScaled(1,1,1.5);
        arc(
            0,5,4, // Position
            1,1,1,  // Scale
            .2,.05,.8, // Block size
            c, 40, 4, 10  // Color, angle, width, pieces
        );
        c[0] = 120; c[1]=90; c[2]=70;
        arc(
            0,5,3.4, // Position
            1,1,1,  // Scale
            .25,.1,.1, // Block size
            c, 40, 4, 10  // Color, angle, width, pieces
        );
        arc(
            0,5,4.6, // Position
            1,1,1,  // Scale
            .25,.1,.1, // Block size
            c, 40, 4, 10  // Color, angle, width, pieces
        );
        arc(
            0,6,3.4, // Position
            1,1,1,  // Scale
            .3,.1,.15, // Block size
            c, 40, 4, 10  // Color, angle, width, pieces
        );
        arc(
            0,6,4.6, // Position
            1,1,1,  // Scale
            .3,.1,.15, // Block size
            c, 40, 4, 10  // Color, angle, width, pieces
        );
        c[0] = 110; c[1]=80; c[2]=60;
        arc(
            0,5.5,4.6, // Position
            1,1,1,  // Scale
            .1,.5,.1, // Block size
            c, 40, 4, 5  // Color, angle, width, pieces
        );
        arc(
            0,5.5,3.4, // Position
            1,1,1,  // Scale
            .1,.5,.1, // Block size
            c, 40, 4, 5  // Color, angle, width, pieces
        );
        glPopMatrix();
    }

    // Torii Gate
    {   
        c[0] = 200; c[1]=40; c[2]=85;
        glPushMatrix();
        glTranslated(0,6,4.4);
        glScaled(1,1,1.5);
        glRotated(80,0,1,0);
        arc(
            0,3,0, // Position
            1,-1,1,  // Scale
            .2,.25,.25, // Block size
            c, 30, 3.8, 12  // Color, angle, width, pieces
        );
        cube(0,1.95,0, 1.8,.12,.25, 0,0,0, c);
        c[0] = 180; c[1]=30; c[2]=85;
        cube(-1.3,.5,0, .2,2.25,.18, 0,0,0, c);
        cube(1.3,.5,0, .2,2.25,.18, 0,0,0, c);

        glPopMatrix();
    }

    // Random Lights
    c[0] = 255; c[1]=240; c[2]=150;
    cube(-2,10,6, .3,.3,.3, 50,20,-20, c);
    c[0] = 255; c[1]=160; c[2]=250;
    cube(5,12,7, .3,.3,.3, 40,80,-60, c);
    c[0] = 100; c[1]=255; c[2]=150;
    cube(-4,11,3, .3,.3,.3, 10,50,-30, c);
    c[0] = 60; c[1]=240; c[2]=250;
    cube(8,8,3, .3,.3,.3, -30,20,30, c);
}