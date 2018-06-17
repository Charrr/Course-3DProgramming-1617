//
//  THIS IS LAB7.
//  Created by 陈子谦 on 10/05/2017.
//  Copyright © 2017 Charrr. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#include <math.h>
#include <time.h>


#define WINDOW_SIZE 15

#define BODY_RADIUS 1.0
#define HEAD_RADIUS 1.2
#define ABDOMEN_RADIUS 1.5
#define ABDOMEN_SCALE 1.3
#define STING_RADIUS 0.4
#define STING_LENGTH 0.8
#define ATENNA_RADIUS 0.1
#define ATENNA_LENGTH 1.8
#define ATENNA_ANGLE 15.0   // with respect to y-axis
#define UPPERLEG_RADIUS 0.2
#define UPPERLEG_LENGTH 0.3
#define LOWERLEG_RADIUS 0.1
#define LOWERLEG_LENGTH 0.5
#define LEG_ANGLE 40.0      // with respect to y-axis
#define LEG_GAPANGLE 60.0
#define LEG_GAP 0.4
#define WING_WIDTH 1.0
#define WING_LENGTH 2.5
#define WING_GAPANGLE 45.0      // how distant for two wings of a pair (the angle with respect to y-axis)
#define FOREWING_ANGLE 20.0     // the angle at which the forewings tilt forwards
#define BACKWING_ANGLE -30.0    // the angle at which the backwings tilt backwards
#define FLIP 20.0               // the frequency of flipping wings
#define SPIN 0.8                // the speed of self-spinning
#define CIRCLE_RADIUS 10.0      // the radius of circulation motion
#define FLUC 0.5                // fluctuation, the height at which she moves up and down





/* >>>>>>>>>>   MATERIAL   <<<<<<<<<< */
/* >>>>>>>>>>   MATERIAL   <<<<<<<<<< */
/* >>>>>>>>>>   MATERIAL   <<<<<<<<<< */

// set material structure
typedef struct materialStruct{
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat shininess;
} materialStruct;

/* Default Material: white rubber */
materialStruct materialDefault = {
    {0.05f, 0.05f, 0.05f, 1.0f},
    {0.5f ,0.5f, 0.5f, 1.0f},
    {0.7f, 0.7f, 0.7f, 1.0f},
    10.0f
};

/* Material Set 1: METAL BEE */
materialStruct metalAluminum = {
    {0.05f, 0.05f, 0.05f, 1.0f},
    {0.5f ,0.5f, 0.5f, 1.0f},
    {0.7f, 0.7f, 0.7f, 1.0f},
    10.0f
};
materialStruct metalBronze = {
    {0.2125f, 0.1275f, 0.054f, 1.0f},
    {0.914f, 0.8284f, 0.78144f, 1.0f},
    {0.993548f, 0.871906f, 0.766721f, 1.0f},
    25.6f
};
materialStruct metalPolishedBronze = {
    {0.25f, 0.148f, 0.06475f, 1.0f},
    {0.4f, 0.2368f, 0.1036f, 1.0f},
    {0.774597f, 0.458561f, 0.200621f, 1.0f},
    10.0f
};
materialStruct metalPolishedCopper = {
    {0.2295f, 0.08825f, 0.0275f, 1.0f},
    {0.5508f, 0.2118f, 0.066f, 1.0f},
    {0.580594f, 0.223257f, 0.0695701f, 1.0f},
    10.0f
};
materialStruct metalSilver = {
    {0.19225f, 0.19225f, 0.19225f, 1.0f},
    {0.80754f, 0.80754f, 0.80754f, 1.0f},
    {0.508273f, 0.508273f, 0.508273f, 1.0f},
    10.0f
};
materialStruct metalChrome = {
    {0.19225f, 0.19225f, 0.19225f, 1.0f},
    {0.0754f, 0.0754f, 0.0754f, 1.0f},
    {0.774597f, 0.774597f, 0.774597f, 1.0f},
    12.2f
};
materialStruct metalGold = {
    {0.26725f, 0.1995f, 0.0745f, 1.0f},
    {0.75164f, 0.60648f, 0.22648f, 1.0f},
    {0.628281f, 0.555802f, 0.366065f, 1.0f},
    10.0f
};
materialStruct metalGoldLeaf = {
    {0.26725f, 0.1995f, 0.0745f, 0.2f},
    {0.75164f, 0.60648f, 0.22648f, 0.2f},
    {0.928281f, 0.855802f, 0.366065f, 0.2f},
    10.0f
};
materialStruct metalPolishedGold = {
    {0.74725f, 0.7245f, 0.0645f, 1.0f},
    {0.64615f, 0.6143f, 0.0903f, 1.0f},
    {0.797357f, 0.723991f, 0.208006f, 1.0f},
    12.2f
};


/* Material Set 2: BLOODY BEE */
materialStruct bloodyBlack = {
    {0.55375f, 0.05f, 0.06625f, 0.82f},
    {0.68275f, 0.17f, 0.22525f, 0.82f},
    {0.332741f, 0.328634f, 0.346435f, 0.82f},
    100.0f
};
materialStruct bloodyRuby = {
    {0.1745f, 0.01175f, 0.01175f, 0.55f},
    {0.61424f, 0.04136f, 0.04136f, 0.55f},
    {0.727f, 0.626f, 0.626f, 0.55f},
    100.0f
};
materialStruct bloodyRed = {
    {0.9745f, 0.01175f, 0.01175f, 1.0f},
    {0.91424f, 0.04136f, 0.04136f, 1.0f},
    {0.927f, 0.926f, 0.626f, 1.0f},
    120.0f
};
materialStruct bloodyRed2 = {
    {0.9745f, 0.01175f, 0.01175f, 1.0f},
    {1.0f, 0.829f, 0.829f, 1.0f},
    {0.296648f, 0.296648f, 0.296648f, 1.0f},
    100.0f
};
materialStruct bloodyOrange = {
    {0.55f, 0.20725f, 0.20725f, 1.0f},
    {1.0f, 0.929f, 0.929f, 1.0f},
    {0.796648f, 0.696648f, 0.696648f, 1.0f},
    120.0f
};
materialStruct bloodyBrown = {
    {0.1f, 0.1725f, 0.0725f, 1.0f},
    {0.2f, 0.229f, 0.129f, 1.0f},
    {0.296648f, 0.296648f, 0.296648f, 1.0f},
    100.0f
};
materialStruct bloodyPearl = {
    {0.25f, 0.20725f, 0.20725f, 1.0f},
    {1.0f, 0.829f, 0.829f, 1.0f},
    {0.296648f, 0.296648f, 0.296648f, 1.0f},
    100.0f
};


/* Material Set 3: GHOST BEE */
materialStruct ghostGreen = {
    {0.2f, 0.9f, 0.3f, 0.3f},
    {0.2f, 0.9f, 0.3f, 0.3f},
    {0.2f, 0.9f, 0.3f, 0.3f},
    10.0f
};
materialStruct ghostGreen2 = {
    {0.2f, 0.9f, 0.3f, 0.3f},
    {0.9f, 0.95f, 0.95f, 0.5f},
    {0.9f, 0.95f, 0.95f, 0.5f},
    10.0f
};
materialStruct ghostBlue = {
    {0.2f, 0.3f, 0.9f, 0.5f},
    {0.2f, 0.3f, 0.9f, 0.5f},
    {0.2f, 0.3f, 0.9f, 0.5f},
    10.0f
};
materialStruct ghostBlue2 = {
    {0.2f, 0.3f, 0.9f, 0.5f},
    {0.2f, 0.3f, 0.9f, 0.5f},
    {0.2f, 0.3f, 0.9f, 0.5f},
    10.0f
};
materialStruct ghostWhite = {
    {0.9f, 0.95f, 0.95f, 0.5f},
    {0.9f, 0.95f, 0.95f, 0.5f},
    {0.9f, 0.95f, 0.95f, 0.5f},
    10.0f
};
materialStruct ghostGrey = {
    {0.56, 0.70f, 0.70f, 0.5f},
    {0.56, 0.70f, 0.70f, 0.5f},
    {0.56, 0.70f, 0.70f, 0.5f},
    10.0f
};
materialStruct ghostBlack = {
    {0.05f, 0.05f, 0.05f, 0.5f},
    {0.05f, 0.05f, 0.05f, 0.5f},
    {0.05f, 0.05f, 0.05f, 0.5f},
    10.0f
};


// material of each part
materialStruct *material_body;
materialStruct *material_head;
materialStruct *material_abdomen;
materialStruct *material_sting;
materialStruct *material_antenna;
materialStruct *material_antennatop;
materialStruct *material_leg;
materialStruct *material_wing;

// to choose from the materials that have been defined
void chooseMaterial(materialStruct *material){
    glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, &material->shininess);
    return;
}



/* >>>>>>>>>>   LIGHTING   <<<<<<<<<< */
/* >>>>>>>>>>   LIGHTING   <<<<<<<<<< */
/* >>>>>>>>>>   LIGHTING   <<<<<<<<<< */

typedef struct lightingStruct {
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
} lightingStruct;

// set the colours of lights
lightingStruct whiteLighting = {        // Default light: white light.
    {0.0, 0.0, 0.0, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0, 1.0}
};
lightingStruct noonLighting = {
    {0.3, 0.2, 0.1, 1.0},
    {1.0, 0.95, 0.90, 1.0},
    {1.0, 0.95, 0.90, 1.0}
};
lightingStruct earlyEveningLighting = {
    {0.2, 0.1, 0.0, 1.0},
    {1.0, 0.7, 0.5, 1.0},
    {1.0, 0.7, 0.5, 1.0}
};
lightingStruct lateEveningLighting = {
    {0.0, 0.2, 0.3, 1.0},
    {0.0, 0.3, 0.5, 1.0},
    {0.0, 0.5, 0.8, 1.0}
};

// set the positions of lights
lightingStruct *currentLighting;
static GLfloat *currentPosition;
GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};    // default position
GLfloat noonPosition[] = {0.0, 100.0, 0.0, 0.0};              // sunshine from above
GLfloat earlyEveningPosition[] = {-20.0, 5.0, 0.0, 0.0};      // sunset from the west
GLfloat lateEveningPosition[] = {10.0, 10.0, 10.0, 0.0};       // moonlight from a certain position


/* >>>>>>>>>>   MODELLING   <<<<<<<<<< */
/* >>>>>>>>>>   MODELLING   <<<<<<<<<< */
/* >>>>>>>>>>   MODELLING   <<<<<<<<<< */

GLUquadricObj *p;

static GLfloat theta[] = {0, 0, 0};         // for rotation
static GLint axis = 1;                      // for rotation, the initial axis is y
static GLboolean rotate_state = GL_TRUE;   // for rotation
static GLboolean fly_state = GL_TRUE;      // for flying
static GLfloat theta_wing = 0.0;            // for flying
static GLint flip_direction = 1;            // for flying

void body(){
    glColor3f(1.0, 0.9, 0.0); // yellow-ish
    chooseMaterial(material_body);
    glPushMatrix();
    gluSphere(p, BODY_RADIUS, 50, 50);
    glPopMatrix();
}

void head(){
    glColor3f(0.1, 0.1, 0.0); // dark dark brown
    chooseMaterial(material_head);
    glPushMatrix();
    gluSphere(p, HEAD_RADIUS, 50, 50);
    glPopMatrix();
}

void abdomen(){
    glColor3f(0.1, 0.1, 0.0); // dark dark brown
    chooseMaterial(material_abdomen);
    glPushMatrix();
    glScalef(ABDOMEN_SCALE, 1.0, 1.0);
    gluSphere(p, ABDOMEN_RADIUS, 50, 50);
    glPopMatrix();
}

void sting(){
    glColor3f(0.9, 0.3, 0.6); // hot pink
    chooseMaterial(material_sting);
    glPushMatrix();
    gluCylinder(p, STING_RADIUS, 0.0, HEAD_RADIUS+STING_LENGTH, 15, 15);
    glPopMatrix();
}

void atenna(){
    glPushMatrix();
    chooseMaterial(material_antenna);
    glColor3f(0.9, 0.3, 0.6); // hot pink
    gluCylinder(p, ATENNA_RADIUS, ATENNA_RADIUS*0.5, ATENNA_LENGTH+HEAD_RADIUS, 15, 15);
    chooseMaterial(material_antennatop);
    glColor3f(0.3, 0.8, 0.8); // weird cyan
    glTranslatef(0.0, 0.0, ATENNA_LENGTH+HEAD_RADIUS);
    gluSphere(p, ATENNA_RADIUS*1.2, 50, 50);
    glPopMatrix();
}

void leg(GLfloat upper_leng, GLfloat lower_leng){
    glPushMatrix();
    chooseMaterial(material_leg);
    glColor3f(0.7, 0.2, 0.9); // purple-ish
    gluCylinder(p, UPPERLEG_RADIUS, LOWERLEG_RADIUS, HEAD_RADIUS+upper_leng, 15, 15);  // the upper leg
    glColor3f(0.9, 0.5, 1.0); // lighter purple
    glTranslatef(0.0, 0.0, HEAD_RADIUS+upper_leng);
    glRotatef(LEG_GAPANGLE, 1.0, 0.0, 0.0);
    gluCylinder(p, LOWERLEG_RADIUS, 0.0, lower_leng, 15, 15);
    glPopMatrix();
}

void wing(){
    glColor4f(0.2, 0.8, 1.0, 0.2);
    chooseMaterial(material_wing);
    glPushMatrix();
    glScalef(1.0, WING_LENGTH/WING_WIDTH, 1.0);
    gluDisk(p, 0.0, WING_WIDTH, 30, 30);
    glPopMatrix();
}

void animal(){
    // Draw the body.
    glPushMatrix();
    body();
    glPopMatrix();
    
    // Draw the head.
    glPushMatrix();
    glTranslatef(-HEAD_RADIUS-BODY_RADIUS+0.1, 0.0, 0.0);
    head();
    glPopMatrix();
    
    // Draw the abdomen.
    glPushMatrix();
    glColor3f(0.1,0.1,0.0); // dark abdomen
    glTranslatef(BODY_RADIUS+ABDOMEN_RADIUS*ABDOMEN_SCALE-0.1, 0.0, 0.0);
    abdomen();
    glPopMatrix();
    
    // Draw the sting.
    glPushMatrix();
    glTranslatef(BODY_RADIUS+ABDOMEN_RADIUS*ABDOMEN_SCALE*2-0.5, 0.0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    sting();
    glPopMatrix();
    
    // Draw the left atenna.
    glPushMatrix();
    glTranslatef(-HEAD_RADIUS-BODY_RADIUS-0.2, 0.0, 0.0);
    glRotatef(ATENNA_ANGLE, 0.0, 0.0, 1.0);
    glRotatef(-75.0, 1.0, 0.0, 0.0);
    atenna();
    glPopMatrix();
    
    // Draw the right atenna.
    glPushMatrix();
    glTranslatef(-HEAD_RADIUS-BODY_RADIUS-0.2, 0.0, 0.0);
    glRotatef(ATENNA_ANGLE, 0.0, 0.0, 1.0);
    glRotatef(-105.0, 1.0, 0.0, 0.0);
    atenna();
    glPopMatrix();
    
    // Draw the legs on the left.
    for (int i=-1; i<=1; i++){
        glPushMatrix();
        glTranslatef(i*LEG_GAP, 0.0, 0.0);
        glRotatef(5.0, 0.0, 0.0, 1.0);          // additional flying angle
        glRotatef(90.0-LEG_ANGLE, 1.0, 0.0, 0.0);
        leg(UPPERLEG_LENGTH*(1+i*0.1), LOWERLEG_LENGTH*(1+i*0.1));
        glPopMatrix();
    }
    
    // Draw the legs on the right.
    for (int i=-1; i<=1; i++){
        glPushMatrix();
        glTranslatef(i*LEG_GAP, 0.0, 0.0);
        glRotatef(5.0, 0.0, 0.0, 1.0);          // additional flying angle
        glRotatef(90.0+LEG_ANGLE, 1.0, 0.0, 0.0);
        glRotatef(180, 0.0, 0.0, 1.0);
        leg(UPPERLEG_LENGTH*(1+i*0.1), LOWERLEG_LENGTH*(1+i*0.1));
        glPopMatrix();
    }
    
    // Draw the forewings.
    for(int i=-1; i<=1; i+=2){
        glPushMatrix();
        glTranslatef(0.0, cos(WING_GAPANGLE)-0.2, (sin(WING_GAPANGLE)-0.2)*i);
        glRotatef(i*theta_wing, 1.0, 0.0, 0.0);
        glTranslatef(0.0, -cos(WING_GAPANGLE)+0.2, -(sin(WING_GAPANGLE)-0.2)*i);
        glRotatef(FOREWING_ANGLE, 0.0, -i*sin(WING_GAPANGLE), cos(WING_GAPANGLE));
        glRotatef(i*WING_GAPANGLE, 1.0, 0.0, 0.0);
        glTranslatef(0.0, BODY_RADIUS+WING_LENGTH-0.2, 0.0);
        wing();
        glPopMatrix();
    }
    
    // Draw the backwings.
    for(int i=-1; i<=1; i+=2){
        glPushMatrix();
        glTranslatef(0.0, cos(WING_GAPANGLE)-0.2, (sin(WING_GAPANGLE)-0.2)*i);
        glRotatef(i*theta_wing, 1.0, 0.0, 0.0);
        glTranslatef(0.0, -cos(WING_GAPANGLE)+0.2, -(sin(WING_GAPANGLE)-0.2)*i);
        glRotatef(BACKWING_ANGLE, 0.0, -i*sin(WING_GAPANGLE), cos(WING_GAPANGLE));
        glRotatef(i*WING_GAPANGLE, 1.0, 0.0, 0.0);
        glTranslatef(0.0, BODY_RADIUS+WING_LENGTH*0.7-0.2, 0.0);
        glScalef(0.7, 0.7, 0.7);                // make backwings smaller than forewings
        wing();
        glPopMatrix();
    }
}



/* >>>>>>>>>>   INTERACTIONS   <<<<<<<<<< */
/* >>>>>>>>>>   INTERACTIONS   <<<<<<<<<< */
/* >>>>>>>>>>   INTERACTIONS   <<<<<<<<<< */

void display(){
    // clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // set the camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(0.0, 0.5, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // isometric view
    glLightfv(GL_LIGHT0, GL_POSITION, currentPosition);
    
    /* ROTATION */
    glRotatef(theta[0], 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);
    
    /* MOVING IN A CIRCLE */
    glTranslatef(-CIRCLE_RADIUS, FLUC*sin(0.25*theta[1]), 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    
    animal();
    glutSwapBuffers();
    glFlush();
}


// left click to open the menu for different material options
void mymouse(GLint button, GLint state, GLint x, GLint y)
{
    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if (fly_state==GL_FALSE && rotate_state==GL_FALSE) {
            fly_state = GL_TRUE;
            rotate_state = GL_TRUE;
        }
        else{
            fly_state = GL_FALSE;
            rotate_state = GL_FALSE;
        }
    }
    return;
}

void idle(){
    /* FLYING */
    if (fly_state == GL_TRUE){
        if (flip_direction == 1) {      // flip downwards
            theta_wing += FLIP;
            if (theta_wing >= 90.0) {
                flip_direction = -1;    // then flip upwards
            }
        }
        if (flip_direction == -1) {     // flip upwards
            theta_wing -= FLIP;
            if (theta_wing <= -10.0) {
                flip_direction = 1;     // then flip downwards
            }
        }
    }
    /* ROTATION */
    if (rotate_state == GL_TRUE){
        theta[axis] += SPIN;
        if( theta[axis] > 360.0 ) theta[axis] -= 360.0;
    }
    
    glutPostRedisplay();
}


// MENU SETTINGS

void mymenu_material(int id){
    if (id==1){
        material_body=&metalBronze;
        material_head=&metalAluminum;
        material_abdomen=&metalChrome;
        material_antenna=&metalSilver;
        material_antennatop=&metalPolishedGold;
        material_sting=&metalSilver;
        material_leg=&metalPolishedBronze;
        material_wing=&metalGoldLeaf;
    }
    if (id==2){
        material_body=&bloodyBlack;
        material_head=&bloodyOrange;
        material_abdomen=&bloodyRed;
        material_antenna=&bloodyRed2;
        material_antennatop=&bloodyPearl;
        material_sting=&bloodyOrange;
        material_leg=&bloodyBrown;
        material_wing=&bloodyRuby;
    }
    if (id==3){
        material_body=&ghostGrey;
        material_head=&ghostGreen;
        material_abdomen=&ghostGreen2;
        material_antenna=&ghostWhite;
        material_antennatop=&ghostBlack;
        material_sting=&ghostBlue;
        material_leg=&ghostBlue2;
        material_wing=&ghostWhite;
    }
    else return;
}

void mymenu_time(int id){
    if (id==1){
        currentLighting=&noonLighting;
        currentPosition=noonPosition;
        glLightfv(GL_LIGHT0, GL_AMBIENT, currentLighting -> ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLighting -> diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, currentLighting -> specular);
    }
    if (id==2){
        currentLighting=&earlyEveningLighting;
        currentPosition=earlyEveningPosition;
        glLightfv(GL_LIGHT0, GL_AMBIENT, currentLighting -> ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLighting -> diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, currentLighting -> specular);
    }
    if (id==3){
        currentLighting=&lateEveningLighting;
        currentPosition=lateEveningPosition;
        glLightfv(GL_LIGHT0, GL_AMBIENT, currentLighting -> ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLighting -> diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, currentLighting -> specular);
    }
    else return;
}

//create menu
void createMenu(){
    int id_material;
    id_material=glutCreateMenu(mymenu_material);
    glutAddMenuEntry("METAL BEE", 1);
    glutAddMenuEntry("BLOODY BEE", 2);
    glutAddMenuEntry("GHOST BEE", 3);
    glutAttachMenu(GLUT_LEFT_BUTTON);
    int id_time;
    id_time=glutCreateMenu(mymenu_time);
    glutAddMenuEntry("NOON", 1);
    glutAddMenuEntry("EARLY EVENING", 2);
    glutAddMenuEntry("LATE EVENING", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void init(){
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.8, 0.8, 0.8, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    p = gluNewQuadric();
    
    /* lighting settings */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    currentLighting = &whiteLighting;   // set current lighting as the defined white light
    glLightfv(GL_LIGHT0, GL_AMBIENT, currentLighting -> ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLighting -> diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, currentLighting -> specular);
    currentPosition = light_position;
    glLightfv(GL_LIGHT0, GL_POSITION, currentPosition);
    
    // initialise with Material of White Rubber, in order to observe the lighting effects
    material_body=&materialDefault;
    material_head=&materialDefault;
    material_abdomen=&materialDefault;
    material_antenna=&materialDefault;
    material_antennatop=&materialDefault;
    material_sting=&materialDefault;
    material_leg=&materialDefault;
    material_wing=&materialDefault;
}

void reshape(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w<=h)
        glOrtho(-WINDOW_SIZE, WINDOW_SIZE, -WINDOW_SIZE*(GLfloat)h/(GLfloat)w, WINDOW_SIZE*(GLfloat)h/(GLfloat)w, -WINDOW_SIZE, WINDOW_SIZE);
    else
        glOrtho(-WINDOW_SIZE*(GLfloat)w/(GLfloat)h, WINDOW_SIZE*(GLfloat)w/(GLfloat)h, -WINDOW_SIZE, WINDOW_SIZE, -WINDOW_SIZE, WINDOW_SIZE);
}



/* >>>>>>>>>>   MAIN   <<<<<<<<<< */
/* >>>>>>>>>>   MAIN   <<<<<<<<<< */
/* >>>>>>>>>>   MAIN   <<<<<<<<<< */

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("QueenBee");
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutMouseFunc(mymouse);
    glEnable(GL_DEPTH_TEST);
    init();
    createMenu();
    glutMainLoop();
}
