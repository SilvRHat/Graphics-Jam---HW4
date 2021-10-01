#ifndef CAMERA_H
#define CAMERA_H

// Functions
// #include <stdio.h> //(Enable for testing purposes)

// Public Functions
void mouseButton(int button, int state, int x, int y);
void mouseMove(int x, int y);
void cameraUpdate();
void reshape();
int cameraDownButtons(unsigned char key, int x, int y); 
int cameraUpButtons(unsigned char key, int x, int y);
void moveCam();
void project();

#endif