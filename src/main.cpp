#include <iostream>
#include "Image.h"
#include "Scene.h"
#include "Sphere.h"
#include "Triangle.h"
#include <cmath>
using namespace std;
using namespace Raytracer148;
using namespace Eigen;

int main() {
    Image im(400, 400);

    Scene scene;
    Vector3d color;

    Vector3d center, center1;
    center1[0] = -0.5;
    center1[1] = 1;
    center1[2] = 2.5;

    scene.addShape(new Sphere(center1, 0.75, 0.5, 0.2, 0.6));
    
    //triangle 
    Vector3d Vertex1, Vertex2, Vertex3;

    color[0] = 0.5 ;
    color[1] = 0;
    color[2] = 0;

    Vertex1[0] = 3.5;
    Vertex1[1] = -0.5;
    Vertex1[2] = 3.5 - 0.4;

    Vertex2[0] = 0.75;
    Vertex2[1] = 1;
    Vertex2[2] = 2 - 0.4;

    Vertex3[0] = 0;
    Vertex3[1] = -0.75;
    Vertex3[2] = 5 - 0.4;

    scene.addShape(new triangle(Vertex1, Vertex2, Vertex3, color));


    scene.render(im);

    im.writePNG("test.png");

    return 0;
}
