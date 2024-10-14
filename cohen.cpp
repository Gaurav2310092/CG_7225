#include <GL/glut.h>
#include <cmath>
#include <iostream>

using namespace std;

float xmin = -100, ymin = -100, xmax = 100, ymax = 100;
float xd1, yd1, xd2, yd2;
bool mousePressed = false;
int startX, startY;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-300, 300, -300, 300);
}

int code(float x, float y) {
    int c = 0;
    if (y > ymax) c |= 8;  // Top
    if (y < ymin) c |= 4;  // Bottom
    if (x > xmax) c |= 2;  // Right
    if (x < xmin) c |= 1;  // Left
    return c;
}

void cohen_Line(float x1, float y1, float x2, float y2) {
    int c1 = code(x1, y1);
    int c2 = code(x2, y2);
    float m = (x2 != x1) ? (y2 - y1) / (x2 - x1) : 0.0f;

    while ((c1 | c2) != 0) {
        if ((c1 & c2) != 0) {
            xd1 = xd2 = yd1 = yd2 = 0;
            return;
        }

        float x, y;
        int c = (c1 != 0) ? c1 : c2;

        if ((c & 8) != 0) {
            y = ymax;
            x = x1 + (y - y1) / m;
        } else if ((c & 4) != 0) {
            y = ymin;
            x = x1 + (y - y1) / m;
        } else if ((c & 2) != 0) {
            x = xmax;
            y = y1 + m * (x - x1);
        } else if ((c & 1) != 0) {
            x = xmin;
            y = y1 + m * (x - x1);
        }

        if (c == c1) {
            x1 = x;
            y1 = y;
            c1 = code(x1, y1);
        } else {
            x2 = x;
            y2 = y;
            c2 = code(x2, y2);
        }
    }
    xd1 = x1;
    yd1 = y1;
    xd2 = x2;
    yd2 = y2;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmin, ymax);
    glVertex2f(xmax, ymax);
    glVertex2f(xmax, ymin);
    glEnd();

    // Draw the clipped line if coordinates are set
    if (xd1 != xd2 || yd1 != yd2) {
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex2f(xd1, yd1);
        glVertex2f(xd2, yd2);
        glEnd();
    }

    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            startX = x;
            startY = glutGet(GLUT_WINDOW_HEIGHT) - y;  // Convert window y to OpenGL y
            mousePressed = true;
        } else if (state == GLUT_UP) {
            if (mousePressed) {
                float endX = x;
                float endY = glutGet(GLUT_WINDOW_HEIGHT) - y;  // Convert window y to OpenGL y

                // Convert to OpenGL coordinates
                float x1 = startX - 300;
                float y1 = 300 - startY;
                float x2 = endX - 300;
                float y2 = 300 - endY;

                // Debug output
                cout << "Start: (" << x1 << ", " << y1 << ") End: (" << x2 << ", " << y2 << ")" << endl;

                cohen_Line(x1, y1, x2, y2); // Perform clipping

                glutPostRedisplay();
                mousePressed = false;
            }
        }
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 600);  // Set window size to 600x600
    glutCreateWindow("Cohen-Sutherland Line Clipping");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    init();
    glutMainLoop();
    return 0;
}
