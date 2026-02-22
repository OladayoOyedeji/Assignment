#include <GL/freeglut.h>
#include "gl3d.h"
#include "View.h"
#include "SingletonView.h"
//#include "Keyboard.h"
#include "Reshape.h"
#include "Material.h"
#include "Light.h"
#include "vec4f.h"
#include "Body.h"

mygllib::Light light;
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

const double VELOCITY[] = {0,
    47.4E9, 35.0E9, 29.8E9, 1.0E9,
    24.1E9, 13.1E9, 9.7E9, 6.8E9,
    5.4E9, 4.7E9};

mygllib::View view;

int NO = 9;
Body * body;
double dt = 300000000;

void rotate(double & x, double & z, double & t)
{
    return;
}

void init()
{
    view.eyex() = 3;
    view.eyey() = 10;
    view.eyez() = 3;
    
    view.zNear() = 0.01;
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
    body[0].pos() = vec4f(0, 0, 0, 1);
    
    body[0].radius() = DIAMETER[0]/2;

    // Planets
    for (int i = 1; i < NO; ++i)
    {
        // set values of body[i]
        // body[i].name() = NAME[i];
        body[i].mass() = MASS[i];
        float peri = PERIHELION[i]*1e3;
        float angle = double(rand()) / RAND_MAX;
        
        std::cout << angle << std::endl;
        angle *= 2 * M_PI - M_PI;
        std::cout << angle << std::endl;
        
        body[i].pos() = vec4f(peri * cos(angle), 0, peri * sin(angle), 1);
        body[i].vel() = vec4f(-peri * sin(angle), 0, peri * cos(angle), 1);
        body[i].vel() /= body[i].vel().len() * VELOCITY[i];
        std::cout << "velocity: " << body[i].vel() << std::endl;
        
        std::cout << "position: " << body[i].pos() << std::endl;
        body[i].radius() = DIAMETER[i];
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
    //gllib::draw_xz_plane();
    glEnable(GL_LIGHTING);

    glColor3f(0.0f, 0.0f, 0.0f);

    glPushMatrix();
    {
        glScalef(1e-14, 1e-14, 1e-14); // Experiment with some values
        for (int i = 0; i < NO; ++i)
        {
            // Draw body[i] using:
            // push model view matrix stack
            glPushMatrix();
            {
                // translate
                glTranslatef(body[i].pos().x(), body[i].pos().y(), body[i].pos().z());

                // glTranslatef(0,0,0);
                // std::cout << body[i].pos().x() << ' ' << body[i].pos().y() << ' ' <<  body[i].pos().z() << std::endl;
                //glColor4f(1, 1, 1, 1);
                glColor3f(1, 1, 1);
                // std::cout << "radius; " << body[i].radius() << std::endl;
                glutSolidSphere(body[i].radius(), 25, 25);
            }
            glPopMatrix();
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
    for (int i = 0; i < NO; ++i)
    {
// Compute F[i] by computing the sum of forces of body[j] attracting
// body[i]. (You can also just compute the attracting of body[0] (the
// sun) on body[i] since the main force of attraction is from the sun.)
        F[i] = vec4f(0,0,0,1);
        for (int j = 0; j < NO; ++j)
        {
            if (j != i)
            {
                // TODO
                // position vector of m1 and m2 in p
                
                
                vec4f p = body[i].pos() - body[j].pos();
                float r = p.len();
                if (r != 0)
                {
                    //std::cout << "distance: " << r << std::endl;
                    p /= r;
                    //std::cout << "normalized: " << p << std::endl;
                    // p.normalize()
                    float f = G * MASS[i] * MASS[j] / (r * r);
                    p *= f;
                    //std::cout << "forcalized: " << p << std::endl;
                    F[i] += p;
                }
            }
        }
    }
    for (int i = 1; i < NO; ++i) // no update for sun
    {
// Update the velocity and position of body[i]
        //std::cout << "force: " << F[i] << std::endl;
        vec4f a = F[i] / MASS[i];
        //std::cout << MASS[i] << std::endl;
        //std::cout << "acceleration: " << a << std::endl;
        body[i].vel() = body[i].vel() + a * dt;
        //std::cout << "velocity: " << body[i].vel() << std::endl;
        body[i].pos() = body[i].pos() + body[i].vel() * dt;
        std::cout << body[i].pos() << std::endl;
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

    }
    
    view.set_projection();
    view.lookat();    
    glutPostRedisplay();
}

void specialkeyboard(int key, int x, int y)
{
    switch (key)
    {
    }
    //std::cout << t_y << std::endl;
    view.set_projection();
    view.lookat();    
    glutPostRedisplay();
}

int main(int argc, char ** argv)
{
    // mygllib::WIN_W = 600;
    // mygllib::WIN_H = 600;
    // mygllib::init3d();
    // init();    
    // glutDisplayFunc(display);
    // glutReshapeFunc(reshape);
    // glutKeyboardFunc(keyboard);
    // glutSpecialFunc(specialkeyboard);
    // glutMainLoop();

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
    glutTimerFunc(1, animate, 1);
    glutMainLoop();
  
    return 0;
}
