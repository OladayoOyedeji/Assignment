#include <cmath>
#include <iostream>
#include <GL/freeglut.h>
#include "gl3d.h"
#include "View.h"
#include "SingletonView.h"
#include "Keyboard.h"
#include "Reshape.h"
#include "Material.h"
#include "Light.h"

mygllib::Light light;
GLfloat light_model_ambient[] = {1.0, 1.0, 1.0, 1.0};
int y_axis_angle = 0;

const int n = 8;
const int N = pow(2, n) + 1;
const float roughness = 0.003;
const float M = 2 * N;
const float scaley = 0.004;
const float scalex = 0.75;
const float scalez = 0.75;
float heightmap[N][N] = {};

void diamond_average(float heightmap[N][N], int midy, int midx, int w, int start, int end)
{
    float sum = 0;
    int n = 0;

    if (midx - w/2 >= start && midy >= start &&
        midx - w/2 < end    && midy < end)
    {
        sum += heightmap[midx-w/2][midy];
        n += 1;
    }
    if (midx + w/2 >= start && midy >= start &&
        midx + w/2 < end    && midy < end)
    {
        sum += heightmap[midx+w/2][midy];
        n += 1;
    }
    if (midx >= start && midy + w/2 >= start &&
        midx < end    && midy + w/2 < end)
    {
        sum += heightmap[midx][midy+w/2];
        n += 1;
    }
    if (midx >= start && midy - w/2 >= start &&
        midx < end    && midy - w/2 < end)
    {
        sum += heightmap[midx][midy-w/2];
        n += 1;
    }
    //std::cout << "n: " << n << std::endl;
    if (n == 0) return;

    heightmap[midx][midy] = sum / n + double(rand()) / RAND_MAX * 2 * M - M;
}

void DIAMOND_SQAURE_algorithm(float heightmap[N][N], float M, float roughness, int N)
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            heightmap[i][j] = 0;
        }
    }
    heightmap[0][0] = double(rand()) / RAND_MAX * 2 * M - M ;
    heightmap[0][N-1] = double(rand()) / RAND_MAX * 2 * M - M ;
    heightmap[N-1][0] = double(rand()) / RAND_MAX * 2 * M - M ;
    heightmap[N-1][N-1] = double(rand()) / RAND_MAX * 2 * M - M  ;

    for (int width = N-1; width != 1; width/=2)
    {
        // for (int r = 0; r < N; ++r)
        // {
        //     for (int c = 0; c < N; ++c)
        //     {
        //         std::cout << heightmap[r][c] << ' ';
        //     }
        //     std::cout << '\n';
        // }
        // std::cout << std::endl;
        // diamond step
        for (int h = 0; h < N-1; h += width)
        {
            for (int w = 0; w < N-1; w += width)
            {
                // std::cout << ;
                heightmap[h + width / 2][w + width /2] = (heightmap[h][w] + heightmap[h + width][w] +
                                                          heightmap[h][w + width] + heightmap[h + width][w + width]) / 4 + 
                    double(rand()) / RAND_MAX * 2 * M - M;
            }
        }

        // for (int r = 0; r < N; ++r)
        // {
        //     for (int c = 0; c < N; ++c)
        //     {
        //         std::cout << heightmap[r][c] << ' ';
        //     }
        //     std::cout << '\n';
        // }
        // std::cout << std::endl;
        for (int h = 0; h < N-1; h += width)
        {
            for (int w = 0; w < N-1; w += width)
            {
                diamond_average(heightmap, h + width/2, w, width, 0, N);
                // for (int r = 0; r < N; ++r)
                // {
                //     for (int c = 0; c < N; ++c)
                //     {
                //         std::cout << heightmap[r][c] << ' ';
                //     }
                //     std::cout << '\n';
                // }
                // std::cout << std::endl;
                diamond_average(heightmap, h, w + width/2, width, 0, N);
                // for (int r = 0; r < N; ++r)
                // {
                //     for (int c = 0; c < N; ++c)
                //     {
                //         std::cout << heightmap[r][c] << ' ';
                //     }
                //     std::cout << '\n';
                // }
                // std::cout << std::endl;
                diamond_average(heightmap, h + width, w + width/2, width, 0, N);
                // for (int r = 0; r < N; ++r)
                // {
                //     for (int c = 0; c < N; ++c)
                //     {
                //         std::cout << heightmap[r][c] << ' ';
                //     }
                //     std::cout << '\n';
                // }
                // std::cout << std::endl;
                diamond_average(heightmap, h + width / 2, w + width, width, 0, N);
            }
        }

        M *= pow(2, -roughness);
        std::cout << M << std::endl;
    }
    // for (int r = 0; r < N; ++r)
    // {
    //     for (int c = 0; c < N; ++c)
    //     {
    //         std::cout << heightmap[r][c] << ' ';
    //     }
    //     std::cout << '\n';
    // }
    // std::cout << std::endl;
}

void init()
{
    mygllib::View & view = *(mygllib::SingletonView::getInstance());
    view.eyex() = 200.0f;
    view.eyey() = 100.5f;
    view.eyez() = 200.0f;
    view.zNear() = 0.1f;
    view.lookat();    

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClearDepth(1.0f);

    srand((unsigned int) time(NULL));
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            heightmap[i][j] = 0;
        }
    }
    
    
    // glEnable(GL_DEPTH_TEST);
    // glShadeModel(GL_SMOOTH);
    // glEnable(GL_NORMALIZE);
    // mygllib::Light::all_on();
    // light.on();
    // glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    // glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_LIGHTING);
    mygllib::draw_axes();

    mygllib::draw_xz_plane(-500, 500, -500, 500, 10, 10);
    
    //glEnable(GL_LIGHTING);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE );
    // glEnable(GL_COLOR_MATERIAL);
    // glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    // glFrontFace(GL_CCW);
    
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
    {
        glScalef(scalex, scaley, scalez);
        for (int j = 0; j < N-1; ++j)
        {
        
            glBegin(GL_TRIANGLE_STRIP);
            {
                for (int i = 0; i < N-1; ++i)
                {
                
                    //glColor3f(1.0f, 1.0f, 1.0f);
                    glVertex3f(i, heightmap[i][j], j);
                    glVertex3f(i, heightmap[i][j+1], j+1);
                    glVertex3f(i+1, heightmap[i+1][j], j);
                
                    //glColor3f(1.0f, 1.0f, 1.0f);
                    glVertex3f(i+1, heightmap[i+1][j], j);
                    glVertex3f(i+1, heightmap[i+1][j+1], j+1);
                    glVertex3f(i, heightmap[i][j+1], j+1);
                }
            }
            glEnd();
        }
    }
    glPopMatrix();
    
    glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y)
{
    mygllib::View & view = *(mygllib::SingletonView::getInstance());
    bool reset = false;
    switch (key)
    {
        case 'x': view.eyex() -= 0.1; reset = true; break;
        case 'X': view.eyex() += 0.1; reset = true; break;
        case 'y': view.eyey() += 0.1; reset = true; break;
        case 'Y': view.eyey() -= 0.1; reset = true; break;
        case 'z': view.eyez() += 0.1; reset = true; break;
        case 'Z': view.eyez() -= 0.1; reset = true; break;
            
        case 'r': y_axis_angle += 1; reset = true; break;
        case 'R': y_axis_angle -= 1; reset = true; break;
        case 'G': DIAMOND_SQAURE_algorithm(heightmap, M, roughness, N); reset = true; break;
        
        case '1': light.x() += 0.1; reset = true; break;
        case '2': light.x() -= 0.1; reset = true; break;
        case '3': light.y() += 0.1; reset = true; break;
        case '4': light.y() -= 0.1; reset = true; break;
        case '5': light.z() += 0.1; reset = true; break;
        case '6': light.z() -= 0.1; reset = true; break;
    }
    if (reset)
    {
        glLoadIdentity();
        view.lookat();
        light.set();
        glutPostRedisplay();
    }
}

void specialkeyboard(int key, int x, int y)
{
    mygllib::View & view = *(mygllib::SingletonView::getInstance());
    switch (key)
    {
        case GLUT_KEY_UP:
            view.eyey() += 0.1;
            view.eyex() -= 0.1;
            view.eyez() -= 0.1;
            break;
        case GLUT_KEY_DOWN:
            view.eyey() -= 0.1;
            view.eyex() += 0.1;
            view.eyez() += 0.1;
            break;
        case GLUT_KEY_RIGHT:
            view.eyex() += 0.1;
            view.eyez() -= 0.1;
            break;
        case GLUT_KEY_LEFT:
            view.eyex() -= 0.1;
            view.eyez() += 0.1;
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
    
    glClearColor(1, 1, 1, 1);
    glClearDepth(1.0f);
    glutDisplayFunc(display);
    glutReshapeFunc(mygllib::Reshape::reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialkeyboard);
    glutMainLoop();
    
    return 0;
}
