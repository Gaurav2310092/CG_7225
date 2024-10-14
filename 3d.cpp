#include <iostream>
#include <GL/glut.h>
#include <cmath>

using namespace std;

static GLfloat input[8][3] = {
    {40, 40, -50}, {90, 40, -50}, {90, 90, -50}, {40, 90, -50},
    {30, 30, 0}, {80, 30, 0}, {80, 80, 0}, {30, 80, 0}
};

float output[8][3];
float tx, ty, tz; // Translation values
float sx, sy, sz; // Scaling values
float angle; // Rotation angle
int choice; // Transformation choice
int choiceRot; // Rotation choice

void translate(float tx, float ty, float tz) {
    for (int i = 0; i < 8; i++) {
        output[i][0] = input[i][0] + tx;
        output[i][1] = input[i][1] + ty;
        output[i][2] = input[i][2] + tz;
    }
}

void scale(float sx, float sy, float sz) {
    // Calculate the center of the shape
    float centerX = (input[0][0] + input[2][0]) / 2.0;
    float centerY = (input[0][1] + input[4][1]) / 2.0;
    float centerZ = (input[0][2] + input[4][2]) / 2.0;

    for (int i = 0; i < 8; i++) {
        // Translate point to origin
        output[i][0] = (input[i][0] - centerX) * sx + centerX;
        output[i][1] = (input[i][1] - centerY) * sy + centerY;
        output[i][2] = (input[i][2] - centerZ) * sz + centerZ;
    }
}

void rotateX(float angle) {
    angle = angle * M_PI / 180.0; // Convert to radians
    float cosA = cos(angle);
    float sinA = sin(angle);
    for (int i = 0; i < 8; i++) {
        float y = output[i][1];
        float z = output[i][2];
        output[i][1] = y * cosA - z * sinA; // New y
        output[i][2] = y * sinA + z * cosA; // New z
    }
}

void Axes(void) {
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex3f(-1000, 0, 0);
    glVertex3f(1000, 0, 0);
    glVertex3f(0, -1000, 0);
    glVertex3f(0, 1000, 0);
    glEnd();
}

void draw(float a[8][3]) {
    glBegin(GL_QUADS);
    glColor3f(0.7, 0.4, 0.5);
    glVertex3fv(a[0]);
    glVertex3fv(a[1]);
    glVertex3fv(a[2]);
    glVertex3fv(a[3]);

    glColor3f(0.8, 0.2, 0.4);
    glVertex3fv(a[0]);
    glVertex3fv(a[1]);
    glVertex3fv(a[5]);
    glVertex3fv(a[4]);

    glColor3f(0.3, 0.6, 0.7);
    glVertex3fv(a[0]);
    glVertex3fv(a[4]);
    glVertex3fv(a[7]);
    glVertex3fv(a[3]);

    glColor3f(0.2, 0.8, 0.2);
    glVertex3fv(a[1]);
    glVertex3fv(a[2]);
    glVertex3fv(a[6]);
    glVertex3fv(a[5]);

    glColor3f(0.7, 0.7, 0.2);
    glVertex3fv(a[2]);
    glVertex3fv(a[3]);
    glVertex3fv(a[7]);
    glVertex3fv(a[6]);

    glColor3f(1.0, 0.1, 0.1);
    glVertex3fv(a[4]);
    glVertex3fv(a[5]);
    glVertex3fv(a[6]);
    glVertex3fv(a[7]);
    glEnd();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1362.0 / 750.0, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -300.0); // Move the camera back
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -300.0); // Ensure camera position

    Axes();

    // Draw the original shape
    draw(input);

    // Reset output to input for fresh transformations
    for (int i = 0; i < 8; i++) {
        output[i][0] = input[i][0];
        output[i][1] = input[i][1];
        output[i][2] = input[i][2];
    }

    // Apply transformations
    switch (choice) {
        case 1: // Translation
            translate(tx, ty, tz);
            break;
        case 2: // Scaling
            scale(sx, sy, sz);
            break;
        case 3: // Rotation
            if (choiceRot == 1) {
                rotateX(angle);
            }
            break;
    }

    // Draw the transformed shape
    draw(output);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1362, 750);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("3D Transformations");
    init();

    // Taking user input
    cout << "Enter your choice number:\n1. Translation\n2. Scaling\n3. Rotation\n";
    cin >> choice;

    switch (choice) {
        case 1: // Translation
            cout << "\nEnter tx, ty, tz: ";
            cin >> tx >> ty >> tz;
            break;
        case 2: // Scaling
            cout << "\nEnter sx, sy, sz: ";
            cin >> sx >> sy >> sz;
            break;
        case 3: // Rotation
            cout << "Enter your choice for rotation about axis:\n1. Parallel to x-axis.\n";
            cin >> choiceRot;
            if (choiceRot == 1) {
                cout << "Enter rotation angle: ";
                cin >> angle;
            }
            break;
        default:
            cout << "Invalid choice. Exiting." << endl;
            return 0;
    }

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
