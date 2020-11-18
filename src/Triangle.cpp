#include "Triangle.h"
#include <limits>
using namespace Raytracer148;
using namespace Eigen;
using namespace std;



HitRecord triangle::intersect(const Ray& ray) {

	HitRecord result;
	result.color = col;
	result.t = -1;

	Vector3d normal = ((v2 - v1).cross(v3 - v1)).normalized();
	double t = -((ray.origin - v1).dot(normal)) / (ray.direction.dot(normal));

	Vector3d position = ray.origin + t * ray.direction;

	double a = ((v2 - v1).cross(position - v1)).dot(normal);
	double b = ((v3 - v2).cross(position - v2)).dot(normal);
	double c = ((v1 - v3).cross(position - v3)).dot(normal);

	if (!(a > 0 && b > 0 && c > 0)) return result;


	result.t = t;
	result.position = ray.origin + result.t * ray.direction;
	result.normal = normal;

	return result;

}