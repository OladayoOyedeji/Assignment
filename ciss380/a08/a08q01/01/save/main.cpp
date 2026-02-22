#include "vec4f.h"


const double G = 6.67408e-11;
const char NAME[10][32] = {"SUN",
    "MECURY", "VENUS", "EARTH", "MARS",
    "JUPITER", "SATURN", "URANUS", "NEPTUNE", "PLUTO"};

const double MASS[] = {1.989E30,
    0.330E24, 4.87E24, 5.97E24, 0.642E24,
    1898E24, 568E24, 86.8E24, 102E24, 0.0146E24};
const double PERIHELION[] = {0,
    46.0E9, 107.5E9, 147.1E9, 206.6E9,
    740.5E9, 1352.6E9, 2741.3E9, 4444.5E9, 4436.8E9};
const double APHELION[] = {0,
    69.8E9, 108.9E9, 152.1E9, 249.2E9,
    816.6E9, 1514.5E9, 3003.6E9, 4545.7E9, 7375.9E9};
const double DIAMETER[] = {0,
    4879E9, 12104E9, 12756E9, 6792E9,
    142984E9, 120536E9, 51118E9, 49528E9, 2370E9};


mygllib::View view;

int NO 4;
Body * body;
double dt 300000;

void rotate(double & x, double & z, double & t)
{
    return;
}

void init(void)
{
    // Set eye at (3, 300, 3) whit a small zNear and a large zFar, fovy = 90,
    // aspect ratio = 1

    body = new Body[10];

    // SUN
    // set Values of body[0]

    // Planets
    for (int i = 1; i < NO; ++i)
    {
        // set values of body[i]
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_LIGHTING);
// Draw axes
    glEnable(GL_LIGHTING);
    glPushMatrix();
    {
        glScalef(1e-10, 1e-10, 1e-10); // Experiment with some values
        for (int i = 0; i < N0; ++i)
        {
// Draw body[i] using:
// push model view matrix stack
            // translate
// glColor4f(1, 1, 1, 1);
// glutSolidSphere(radius of body[i], 25, 25);
// pop model view matrix stack
        }
    }
    glPopMatrix();
    glutSwapBuffers();
}

// Timer function for glutTimerFunc().
void animate(int someValue)
{
    vec4f F[10]; // F[i] is the gravitional force (vector) acting on body[i]
    for (int i = 0; i < N0; ++i)
    {
// Compute F[i] by computing the sum of forces of body[j] attracting
// body[i]. (You can also just compute the attracting of body[0] (the
// sun) on body[i] since the main force of attraction is from the sun.)
        F[i] = vec4f(0,0,0,1);
        for (int j = 0; j < N0; ++j)
        {
            if (j != i)
            {
// TODO
            }
        }
    }
    for (int i = 1; i < N0; ++i) // no update for sun
    {
// Update the velocity and position of body[i]
    }
    glutPostRedisplay();
    glutTimerFunc(1, animate, 1);
}
void reshape(int w, int h)
{
// TODO
}

void keyboard(unsigned char key, int x, int y)
{
// TODO
}

int main()
{
    // Initialize with a window of size 700-by-700
    init();
    glClearColor(0, 0, 0, 0);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(1, animate, 1);
    glutMainLoop();
    
    return 0;
}
