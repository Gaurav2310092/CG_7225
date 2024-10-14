#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int pntx1, pnty1, choice = 0, edges;
vector<int> pntx;
vector<int> pnty;
int tx, ty;
double sx, sy;
double angle, anglerad;

void drawPolygon() {
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    for (int i = 0; i < edges; i++) {
        glVertex2i(pntx[i], pnty[i]);
    }
    glEnd();
}

void drawPolygonTrans(int x, int y) {
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0); // Green
    for (int i = 0; i < edges; i++) {
        glVertex2i(pntx[i] + x, pnty[i] + y);
    }
    glEnd();
}

void drawPolygonScale(double x, double y) {
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 1.0); // Blue
    for (int i = 0; i < edges; i++) {
        glVertex2i(round(pntx[i] * x), round(pnty[i] * y));
    }
    glEnd();
}

void drawPolygonRotation(double anglerad) {
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 1.0); // Blue
    for (int i = 0; i < edges; i++) {
        glVertex2i(round(pntx[i] * cos(anglerad) - pnty[i] * sin(anglerad)),
                   round(pntx[i] * sin(anglerad) + pnty[i] * cos(anglerad)));
    }
    glEnd();
}

void myInit(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-640.0, 640.0, -480.0, 480.0);
}

void myDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    if (choice == 1) {
        drawPolygon();
        drawPolygonTrans(tx, ty);
    }
    else if (choice == 2) {
        drawPolygon();
        drawPolygonScale(sx, sy);
    }
    else if (choice == 3) {
        drawPolygon();
        drawPolygonRotation(anglerad);
    }
    glFlush();
}

int main(int argc, char** argv) {
    cout << "Enter your choice:\n\n" << endl;
    cout << "1. Translation" << endl;
    cout << "2. Scaling" << endl;
    cout << "3. Rotation" << endl;
    cout << "4. Exit" << endl;
    cin >> choice;
    if (choice == 4) {
        return 0;
    }
    cout << "\n\nfor Polygon:\n" << endl;
    cout << "Enter number of edges: ";
    cin >> edges;
    for (int i = 0; i < edges; i++) {
        cout << "Enter coordinates for vertex " << i + 1 << " : ";
        cin >> pntx1 >> pnty1;
        pntx.push_back(pntx1);
        pnty.push_back(pnty1);
    }
    if (choice == 1) {
        cout << "Enter the translation factor for X and Y :";
        cin >> tx >> ty;
    }
    else if (choice == 2) {
        cout << "Enter the scaling factor for X and Y :";
        cin >> sx >> sy;
    }
    else if (choice == 3) {
        cout << "Enter the rotational angle :";
        cin >> angle;
        anglerad = angle * 3.1416/ 180;
    }

    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("2D_Transformation");
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();
}

