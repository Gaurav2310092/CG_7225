#include <GL/glut.h>
#include <cmath>

// Constants for the circle
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int RADIUS = 200;
const int CENTER_X = SCREEN_WIDTH / 2;
const int CENTER_Y = SCREEN_HEIGHT / 2;

void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void drawCircle(int x_center, int y_center, int radius) {
    int x = radius, y = 0;
    setPixel(x + x_center, y + y_center);

    if (radius > 0) {
        setPixel(x + x_center, -y + y_center);
        setPixel(y + x_center, x + y_center);
        setPixel(-y + x_center, x + y_center);
    }

    int P = 1 - radius;
    while (x > y) {
        y++;

        if (P <= 0)
            P = P + 2*y + 1;
        else {
            x--;
            P = P + 2*y - 2*x + 1;
        }

        if (x < y)
            break;

        setPixel(x + x_center, y + y_center);
        setPixel(-x + x_center, y + y_center);
        setPixel(x + x_center, -y + y_center);
        setPixel(-x + x_center, -y + y_center);

        if (x != y) {
            setPixel(y + x_center, x + y_center);
            setPixel(-y + x_center, x + y_center);
            setPixel(y + x_center, -x + y_center);
            setPixel(-y + x_center, -x + y_center);
        }
    }
}

void drawTriangleInsideCircle(int x_center, int y_center, int radius) {
    // Calculate the vertices of the equilateral triangle
    float angle = 2.0f * M_PI / 3.0f; // 120 degrees in radians
    float x1 = x_center + radius * cos(0);
    float y1 = y_center + radius * sin(0);
    float x2 = x_center + radius * cos(angle);
    float y2 = y_center + radius * sin(angle);
    float x3 = x_center + radius * cos(2 * angle);
    float y3 = y_center + radius * sin(2 * angle);

    // Draw the triangle
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the circle using the midpoint algorithm
    drawCircle(CENTER_X, CENTER_Y, RADIUS);

    // Draw the triangle inside the circle
    drawTriangleInsideCircle(CENTER_X, CENTER_Y, RADIUS);

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(2.0);
    gluOrtho2D(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("Triangle Inside Circle");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
