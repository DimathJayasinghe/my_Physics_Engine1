#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define GRID_WIDTH 100
#define GRID_HEIGHT 100
#define TIME_STEP 0.0016f   //Simiulate 60 FPS

// Boundaries
#define X_left 0
#define X_right GRID_WIDTH
#define Y_up 0
#define Y_down GRID_HEIGHT

//Physics
#define GRAVITY 9.8f
#define PI 3.14

////////////////////////////////////////////////////////////////////////////////////

//BULLET PROPERTIES
#define BULLET_SPEED 10
#define BULLET_MASS 0.5 // Kilograms

//TARGET
#define TARGET_X 27.42
#define TARGET_Y -0.52 //-0.1//-90.0 
#define ANGLE 45.00
#define HIT_TOLERANCE 0.1

//GUN PROPERTIES
#define GUN_X 10
#define GUN_Y 10
#define GUN_FORCE 100 //Newtons


/////////////////////////////////////////////////////////////////////////////////

char x_coords[100000] = "x_coords = [";
char y_coords[100000] = "y_coords = [";

/////////////////////////////////////////////////////////////////////////////////

typedef struct {
    double x,y;
} Vector2D;

typedef struct {
    Vector2D position;
    Vector2D velocity;
    float mass;
    Vector2D acceleration;
} PhysicsObject;

////////////////////////////////////////////////////////////////////////////////
void deleteFile(const char *filename) {
    if (remove(filename) == 0) {
        printf("History Cleared\n\n");
    }
    return;
}
void writeCoordinatesToFile(const char *filename) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    fprintf(file, "%s]\n", x_coords);
    fprintf(file, "%s]\n", y_coords);
    fprintf(file, "Landing Location: (%.2f, %.2f)\n", TARGET_X, TARGET_Y);
    fclose(file);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void displayObjectInfo(PhysicsObject *obj, Vector2D *force, Vector2D *target) {
    if (obj == NULL || force == NULL) {
        printf("Invalid object or force.\n");
        return;
    }

    printf("Physics Object Info:\n");
    printf("Position: (%.2f, %.2f)\n", obj->position.x, obj->position.y);
    printf("Velocity: (%.2f, %.2f)\n", obj->velocity.x, obj->velocity.y);
    printf("Mass: %.2f kg\n", obj->mass);

    printf("Force Info:\n");
    printf("Force: (%.2f, %.2f)\n", force->x, force->y);

    printf("Target Info:\n");
    printf("Target: (%0.2f,%0.2f)\n",target->x,target->y);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Creates object

double degToRad(int angle) {
    return angle * (PI/180);
}

PhysicsObject *createObject (float x, float y, int v, double a, float m) {
    PhysicsObject *newObject = (PhysicsObject*)malloc(sizeof(PhysicsObject));
    if (newObject == NULL) {
        printf("Memory Allocation failed.\n");
        exit(1);
    }
    newObject->mass = m;
    newObject->position.x = x;
    newObject->position.y = y;

    newObject->velocity.x = v * cos(degToRad(a));
    newObject->velocity.y = v * sin(degToRad(a));

    return newObject;
}

void deleteObject (PhysicsObject *obj) {
    free(obj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Vector2D *addForce (double totalForce,double angle) {
    Vector2D *force = (Vector2D*)malloc (sizeof(Vector2D));
    if (force == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    force->x = totalForce * cos(degToRad(angle));
    force->y = totalForce * sin(degToRad(angle));
    return force;
}

void applyForce (PhysicsObject *obj, Vector2D *force) {
   float deltaTime = TIME_STEP;
   obj->acceleration.x = force->x / obj->mass;
   obj->acceleration.y = (force->y - (obj->mass * GRAVITY)) / obj->mass;
   obj->velocity.x += obj->acceleration.x * deltaTime;
   obj->velocity.y += obj->acceleration.y * deltaTime;
   obj->position.x += obj->velocity.x * deltaTime + (0.5) * obj->acceleration.x * deltaTime * deltaTime;
   obj->position.y += obj->velocity.y * deltaTime + (0.5) * obj->acceleration.y * deltaTime * deltaTime;
   // Ensure x-coordinate does not change when angle is 90 degrees
   if ( ANGLE == 90.00) {
        obj->velocity.x == 0;
        obj->position.x = GUN_X;
   }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void shoot (Vector2D target ,double angle) {
    PhysicsObject *bullet = createObject(GUN_X,GUN_Y,BULLET_SPEED,angle,BULLET_MASS);
    Vector2D *force = addForce(GUN_FORCE,angle);
    displayObjectInfo(bullet,force,&target);
    applyForce(bullet,force);
    float deltaTime = TIME_STEP;
    deleteFile("coordinates.txt"); // Clear previous coordinates

    while(bullet->position.x <= X_right) {
        bullet->acceleration.x = 0;
        bullet->acceleration.y = -GRAVITY;
        if ( ANGLE == 90.00) {
            bullet->velocity.x == 0;
            bullet->position.x = GUN_X;
        }else{
            bullet->velocity.x += bullet->acceleration.x * deltaTime;
        }       
        bullet->velocity.y += bullet->acceleration.y * deltaTime;
        bullet->position.x += bullet->velocity.x * deltaTime + (0.5) * bullet->acceleration.x * deltaTime * deltaTime;
        bullet->position.y += bullet->velocity.y * deltaTime + (0.5) * bullet->acceleration.y * deltaTime * deltaTime;

        printf("X : %0.2lf , Y : %0.2lf\n",bullet->position.x,bullet->position.y);
        
        // Append coordinates to global strings
        char buffer[50];
        snprintf(buffer, sizeof(buffer), "%.2lf,", bullet->position.x);
        strcat(x_coords, buffer);
        snprintf(buffer, sizeof(buffer), "%.2lf,", bullet->position.y);
        strcat(y_coords, buffer);

        if (fabs(bullet->position.x - target.x) <= HIT_TOLERANCE && fabs(bullet->position.y - target.y) <= HIT_TOLERANCE) {
            printf("HIT!\n");
            writeCoordinatesToFile("coordinates.txt");
            free(force);
            free(bullet);
            system("python chartGenarator.py");
            return;
        }
        // getchar();
    }
    printf("MIS!\n");
    writeCoordinatesToFile("coordinates.txt");
    system("python chartGenarator.py");
    free(force);
    free(bullet);
    return;
}



///////////////////////////////////////////////////////////////////////////////////////
int main() {
    Vector2D target = {TARGET_X,TARGET_Y};
    shoot(target,ANGLE);
    return 0;
}