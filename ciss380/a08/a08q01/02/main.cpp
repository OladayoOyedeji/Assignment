#include <GL/freeglut.h>
#include <list>
#include "gl3d.h"
#include "View.h"
#include "SingletonView.h"
//#include "Keyboard.h"
#include "Reshape.h"
#include "Material.h"
#include "Light.h"
#include "Body.h"

mygllib::Light light;
const double G = 6.67408e-14;
const char NAME[10][32] = {"SUN",
    "MECURY", "VENUS", "EARTH", "MARS",
    "JUPITER", "SATURN", "URANUS", "NEPTUNE", "PLUTO"};

const double MASS[] = {1.989E30,
    0.330E24, 4.87E24, 5.97E24, 0.642E24,
    1898E24, 568E24, 86.8E24, 102E24, 0.0146E24};
const double PERIHELION[] = {0,
    46.0E6, 107.5E6, 147.1E6, 206.6E6,
    740.5E6, 1352.6E6, 2741.3E6, 4444.5E6, 4436.8E6};
const double APHELION[] = {0,
    69.8E6, 108.9E6, 152.1E6, 249.2E6,
    816.6E6, 1514.5E6, 3003.6E6, 4545.7E6, 7375.9E6};
const double DIAMETER[] = {0,
    4879, 12104, 12756, 6792,
    142984, 120536, 51118, 49528, 2370};

const double VELOCITY[] = {0,
    47.4, 35.0, 29.8,
    24.1, 13.1, 9.7, 6.8,
    5.4, 4.7};

mygllib::View view;

int NO = 10;
Body * body;
double dt = 500000;

std::list< vec2<float> > trail[10]; // declare trail as an array of 10 linked list

void rotate(double & x, double & z, double & t)
{
    return;
}

void init()
{
    view.eyex() = 3;
    view.eyey() = 300;
    view.eyez() = 3;
    
    view.zNear() = 0.1;
    view.zFar() = 1e9;

    
    view.set_projection();
    view.lookat();

    // Set eye at (3, 300, 3) whit a small zNear and a large zFar, fovy = 90,
    // aspect ratio = 1

    body = new Body[10];

    // SUN
    // set Values of body[0]
    //body[0].name() = NAME[0];
    body[0].mass() = MASS[0];
    
    srand((unsigned int) time(NULL));
    body[0].pos() = vec2<float>(0, 0);
    
    body[0].radius() = DIAMETER[0]/2;

    // Planets
    for (int i = 1; i < NO; ++i)
    {
        // set values of body[i]
        body[i].mass() = MASS[i];
        float peri = PERIHELION[i];
        float angle = double(rand()) / RAND_MAX;
        
        angle *= 2 * M_PI - M_PI;
        
        
        body[i].pos() = vec2<float>(peri * cos(angle), peri * sin(angle));
        body[i].vel() = vec2<float>(-peri * sin(angle), peri * cos(angle));
        body[i].vel() /= body[i].vel().len();
        body[i].vel() *= VELOCITY[i];
        
        body[i].radius() = DIAMETER[i]/2;
    }
}

void draw_cylinder(float radius, float height)
{
    //glPushMatrix();
    GLUquadricObj * p = gluNewQuadric();
    // SECOND RUN
    //gluQuadricDrawStyle(p, GLU_LINE);
    gluQuadricDrawStyle(p, GLU_FILL);
    int slice_per_ring = 20;
    int rings = 20;
    gluCylinder(p, radius, radius, height, slice_per_ring, rings);
    gluDeleteQuadric(p);
    //glPopMatrix();
}


void display()
{    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_LIGHTING);
    mygllib::draw_axes();

    
    glEnable(GL_LIGHTING);

    glColor3f(0.0f, 0.0f, 0.0f);

    glPushMatrix();
    {
        glScalef(1e-6, 1e-6, 1e-6);
        for (int i = 0; i < NO; i++)
        {
            // Draw body[i] using:
            // push model view matrix stack
            glPushMatrix();
            {
                // translate
                glBegin(GL_LINE_STRIP);
                for (std::list< vec2<float> >::iterator p = trail[i].begin();
                     p != trail[i].end();
                     ++p)
                {
                    // *p is a vec4f object in trail[i]
                    float x = p->x()*1e-1;
                    float y = p->y()*1e-1;
                    glVertex3f(x, 0, y);
                }
                glEnd();
                glTranslatef(body[i].pos().x() *1e-1, 0, body[i].pos().y()*1e-1);
            
                glColor3f(1, 1, 1);
                glScalef(1e2, 1e2, 1e2);
                glutSolidSphere(body[i].radius(), 25, 25);
            }
            glPopMatrix();
        }
    }
    glPopMatrix(); 
    glutSwapBuffers();

}

// Timer function for glutTimerFunc().
void animate(int someValue)
{
    vec2<float> F[10]; // F[i] is the gravitional force (vector) acting on body[i]
    for (int i = 0; i < NO; ++i)
    {
        // Compute F[i] by computing the sum of forces of body[j] attracting
        // body[i]. (You can also just compute the attracting of body[0] (the
        // sun) on body[i] since the main force of attraction is from the sun.)
        F[i] = vec2<float>(0,0);
        for (int j = 0; j < NO; ++j)
        {
            if (j != i)
            {
                vec2<float> p = body[j].pos() - body[i].pos();
                
                float r = p.len();
                
                if (r != 0)
                {
                    p /= r;
                    
                    // p.normalize()
                    float f = G * MASS[i] * MASS[j] / (r * r) * 1e-6;
                    
                    p *= f;
                    
                    F[i] += p;
                }
            
            }
        }
    }
    for (int i = 1; i < NO; ++i) // no update for sun
    {
        // Update the velocity and position of body[i]
        
        vec2<float> a = F[i] / MASS[i];
        body[i].vel() += a * dt;
        
        body[i].pos() += body[i].vel() * dt;
        
        // updates trail -- this should be in the timer function that
        // updates the positions of the planets
        trail[i].push_front(body[i].pos()); // insert a vec4f object p as head of list
        if (trail[i].size() > 10000)
        {
            trail[i].pop_back(); // remove tail from list
        }
    }
    glutPostRedisplay();
    glutTimerFunc(1, animate, 1);
}

void reshape(int w, int h)
{
    glViewport(0, 0, 700, 700);
}


void keyboard(unsigned char key, int x, int y)
{
    
    switch(key)
    {
        case 'x': view.eyex() -= 0.1; break;
        case 'X': view.eyex() += 0.1; break;
        case 'y': view.eyey() -= 0.1; break;
        case 'Y': view.eyey() += 0.1; break;
        case 'z': view.eyez() -= 0.1; break;
        case 'Z': view.eyez() += 0.1; break;
            
        case 'v': view.fovy() -= 0.1; break;
        case 'V': view.fovy() += 0.1; break;            
        case 'a': view.aspect() -= 0.1; break;
        case 'A': view.aspect() += 0.1; break;
        case 'n': view.zNear() -= 0.1; break;
        case 'N': view.zNear() += 0.1; break;
        case 'f': view.zFar() -= 0.1; break;
        case 'F': view.zFar() += 0.1; break;

        case 'm': animate(1); break;

        case '+':
            view.eyey() -= 1;
            view.eyex() -= 1;
            view.eyez() -= 1;
            break;

        case '-':
            view.eyey() += 1;
            view.eyex() += 1;
            view.eyez() += 1;
    }
    
    view.set_projection();
    view.lookat();    
    glutPostRedisplay();
}

void specialkeyboard(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_UP:
            view.eyey() += 1;
            view.eyex() -= 1;
            view.eyez() -= 1;
            break;
        case GLUT_KEY_DOWN:
            view.eyey() -= 1;
            view.eyex() += 1;
            view.eyez() += 1;
            break;
        case GLUT_KEY_RIGHT:
            view.eyex() += 1;
            view.eyez() -= 1;
            break;
        case GLUT_KEY_LEFT:
            view.eyex() -= 1;
            view.eyez() += 1;
            break;
    }
    view.set_projection();
    view.lookat();    
    glutPostRedisplay();
}

int main(int argc, char ** argv)
{
    mygllib::WIN_W = 700;
    mygllib::WIN_H = 700;
    mygllib::init3d();
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
    glutSpecialFunc(specialkeyboard);
    glutTimerFunc(1, animate, 1);
    glutMainLoop();
  
    return 0;
}
