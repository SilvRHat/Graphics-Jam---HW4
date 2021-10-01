
// DEPENDENCIES
#include "objects.h"



// SOURCE
// Cube function credit to: Vlakkies Schreuder
void cube(
        double px, double py,double pz, // Position
        double sx,double sy,double sz, // Scale
        double rx, double ry, double rz, // Rotation
        GLubyte color[]  // Color
    ) {

    //  Save transformation
    glPushMatrix();
    //  Offset
    glTranslated(px,py,pz);
    glRotated(rx,1,0,0);
    glRotated(ry,0,1,0);
    glRotated(rz,0,0,1);
    glScaled(sx,sy,sz);
    glColor3ub(color[0], color[1], color[2]);
    //  Cube
    glBegin(GL_QUADS);
    //  Front
    glVertex3f(-1,-1, 1);
    glVertex3f(+1,-1, 1);
    glVertex3f(+1,+1, 1);
    glVertex3f(-1,+1, 1);
    //  Back
    glVertex3f(+1,-1,-1);
    glVertex3f(-1,-1,-1);
    glVertex3f(-1,+1,-1);
    glVertex3f(+1,+1,-1);
    //  Right
    glVertex3f(+1,-1,+1);
    glVertex3f(+1,-1,-1);
    glVertex3f(+1,+1,-1);
    glVertex3f(+1,+1,+1);
    //  Left
    glVertex3f(-1,-1,-1);
    glVertex3f(-1,-1,+1);
    glVertex3f(-1,+1,+1);
    glVertex3f(-1,+1,-1);
    //  Top
    glVertex3f(-1,+1,+1);
    glVertex3f(+1,+1,+1);
    glVertex3f(+1,+1,-1);
    glVertex3f(-1,+1,-1);
    //  Bottom
    glVertex3f(-1,-1,-1);
    glVertex3f(+1,-1,-1);
    glVertex3f(+1,-1,+1);
    glVertex3f(-1,-1,+1);
    //  End
    glEnd();
    //  Undo transofrmations
    glPopMatrix();
}

void arc(
        double px, double py,double pz, // Position
        double sx,double sy,double sz, // Scale
        double bx, double by, double bz, // Cube Size
        GLubyte color[], double a, double width, int pieces  // Color, angle, width, pieces
    ) {
    glPushMatrix();
    glTranslated(px, py, pz);
    glScaled(sx, sy, sz);

    double dp = (width/2) / tan(a/2* M_PI / 180);
    double r = sqrt(pow(dp,2)+pow(width/2,2));
    for (int i=0; i<pieces; i++) {
        double ang = -(a/2) + (i*(a/(pieces-1+1e-5)));
        double x = r * sin(ang * M_PI / 180);
        double y = r * cos(ang * M_PI / 180) -dp;

        cube(x,y,0,  bx,by,bz,  0,0,-ang,  color);
    }
    glPopMatrix();
}