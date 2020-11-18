#include "Scene.h"
#include <cmath>
using namespace Raytracer148;
using namespace std;
using namespace Eigen;

HitRecord Scene::closestHit(const Ray &ray) {
    HitRecord result;
    result.t = -1;
    bool foundSomething = false;

    for (unsigned int i = 0; i < shapes.size(); i++) {
        HitRecord r = shapes[i]->intersect(ray);
        if (r.t > std::numeric_limits<double>::epsilon() && (!foundSomething || r.t < result.t)) {
            result = r;
            foundSomething = true;
        }
    }

    return result;
}



// Returns an RGB color, where R/G/B are each in the range [0,1]
Vector3d Scene::trace(const Ray &ray) {
    // For now we'll have diffuse shading with no shadows, so it's easy!
    HitRecord r = closestHit(ray);
	Vector3d Viewpos;
	Viewpos[0] = 3;
	Viewpos[1] = 0;
	Viewpos[2] = 0;

    Vector3d result;
    result[0] = result[1] = result[2] = 0;

    if (r.t < numeric_limits<double>::epsilon()) return result;
	//ambient
	double ambient = 0.4;
	
	//diffuse
    Vector3d lightDir = (lightPos - r.position).normalized();
    double dot = lightDir.dot(r.normal);
    if (dot < 0) dot = 0;
	
	//specular
	double specular = 0.5;
	Vector3d viewDir = (Viewpos - r.position).normalized();
	Vector3d reflectDir = -lightDir - 2 * -lightDir.dot(r.normal)*r.normal;
	double spec = viewDir.dot(reflectDir)*specular;
    //phong shading
	double phong = spec + ambient + dot;  

	//shadow
     Ray reflactiveray;
     reflactiveray.origin = r.position;
     reflactiveray.direction = lightDir; 
     for (int i = 0; i < shapes.size(); i++) {
	     HitRecord r = shapes[i]->intersect(reflactiveray);
	     if (r.t > 0.00001) return result;
     } 
	     result[0] = r.color[0] * phong;
	     result[1] = r.color[1] * phong;
	     result[2] = r.color[2] * phong; 

	     return result;
     
}

void Scene::render(Image &image) {
    // We make the assumption that the camera is located at (0,0,0)
    // and that the image plane happens in the square from (-1,-1,1)
    // to (1,1,1).

    assert(image.getWidth() == image.getHeight());

    int size = image.getWidth();
    double pixelSize = 2. / size;
    for (int x = 0; x < size; x++)
        for (int y = 0; y < size; y++) {
            Ray curRay;
            curRay.origin[0] = curRay.origin[1] = curRay.origin[2] = 0;

            curRay.direction[0] = (x + 0.5) * pixelSize - 1;
            curRay.direction[1] = 1 - (y + 0.5) * pixelSize;
            curRay.direction[2] = 1;

            Vector3d color = trace(curRay);
            image.setColor(x, y, color[2], color[0], color[1]);
        }
}