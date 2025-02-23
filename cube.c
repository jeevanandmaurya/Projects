#include <stdio.h>
#include <math.h>
#include <windows.h>

#define PI 3.14159265
#define WIDTH 80
#define HEIGHT 40

typedef struct { float x, y, z; } Point3D;

// Cube vertices
Point3D cube[] = {
    {-1, -1, -1}, {1, -1, -1}, {1, 1, -1}, {-1, 1, -1},
    {-1, -1, 1}, {1, -1, 1}, {1, 1, 1}, {-1, 1, 1}
};

// Edges connecting vertices
int edges[][2] = {
    {0,1}, {1,2}, {2,3}, {3,0}, // Front face
    {4,5}, {5,6}, {6,7}, {7,4}, // Back face
    {0,4}, {1,5}, {2,6}, {3,7}  // Connecting edges
};

void rotateX(Point3D *p, float angle) {
    float rad = angle * PI / 180.0f;
    float y = p->y * cos(rad) - p->z * sin(rad);
    float z = p->y * sin(rad) + p->z * cos(rad);
    p->y = y; p->z = z;
}

void rotateY(Point3D *p, float angle) {
    float rad = angle * PI / 180.0f;
    float x = p->x * cos(rad) + p->z * sin(rad);
    float z = -p->x * sin(rad) + p->z * cos(rad);
    p->x = x; p->z = z;
}

void drawWireframeCube(Point3D rotatedCube[]) {
    char buffer[HEIGHT][WIDTH];
    
    // Initialize buffer
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            buffer[y][x] = ' ';

    // Draw all edges
    for (int i = 0; i < 12; i++) {
        Point3D p1 = rotatedCube[edges[i][0]];
        Point3D p2 = rotatedCube[edges[i][1]];

        // Project to 2D with perspective
        float scale1 = 15.0f / (3.0f - p1.z);
        float scale2 = 15.0f / (3.0f - p2.z);
        
        int x1 = (int)(p1.x * scale1 * 2.0f + WIDTH/2);
        int y1 = (int)(p1.y * scale1 + HEIGHT/2);
        int x2 = (int)(p2.x * scale2 * 2.0f + WIDTH/2);
        int y2 = (int)(p2.y * scale2 + HEIGHT/2);

        // Bresenham's line algorithm
        int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
        int dy = -abs(y2 - y1), sy = y1 < y2 ? 1 : -1; 
        int err = dx + dy, e2;

        while (1) {
            if (x1 >= 0 && x1 < WIDTH && y1 >= 0 && y1 < HEIGHT)
                buffer[y1][x1] = '#';
            
            if (x1 == x2 && y1 == y2) break;
            e2 = 2 * err;
            
            if (e2 >= dy) { err += dy; x1 += sx; }
            if (e2 <= dx) { err += dx; y1 += sy; }
        }
    }

    // Draw buffer
    system("cls");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++)
            putchar(buffer[y][x]);
        putchar('\n');
    }
}

int main() {
    float angleX = 0, angleY = 0;
    while (1) {
        Point3D rotatedCube[8];
        for (int i = 0; i < 8; i++) {
            rotatedCube[i] = cube[i];
            rotateX(&rotatedCube[i], angleX);
            rotateY(&rotatedCube[i], angleY);
        }

        drawWireframeCube(rotatedCube);
        angleX += 0.5f;
        angleY += 0.5f;
        Sleep(50);
    }
    return 0;
}