#include "Cube.hpp"

Cube::Cube(Vector* vertexes, const Vector& color, const double& size) :
    Object(color),
    vertexes_(vertexes),
    size_(size)
{}

Vector Cube::norm(const Vector& p  ) {
    return p; //todo
}