#include "Object.hpp"

Lens::Lens(const Material& mat, const Vector& size1, const Vector& size2, const Vector& center1, const Vector& center2, const Vector& color, const Vector& rotation) :
    Object(mat, NULLVEC, (center2 + center1) / 2, color, rotation),
    sphere1_ ({mat, size1, center1, color, rotation}),
    sphere2_ ({mat, size2, center2, color, rotation})
{}

Vector Lens::color(const Vector& hit) const {
    (void) hit;
    return color_;
}

VectorPair Lens::trace(const Ray& ray, Vector* norm) const {
    Vector N1 = NULLVEC, N2 = NULLVEC;
    VectorPair intersections1 = sphere1_.trace(ray, &N1);

    if (intersections1.first == NULLVEC && intersections1.second == NULLVEC) return {NULLVEC, NULLVEC};

    VectorPair intersections2 = sphere2_.trace(ray, &N2);

    if (intersections2.first == NULLVEC && intersections2.second == NULLVEC) return {NULLVEC, NULLVEC};

    Vector vec1 = intersections1.first  - ray.start_,
           vec2 = intersections1.second - ray.start_,
           vec3 = intersections2.first  - ray.start_,
           vec4 = intersections2.second - ray.start_;

    double dist1 = (vec1 ^ vec1) * (vec1 ^ ray.dir_),
           dist2 = (vec2 ^ vec2) * (vec2 ^ ray.dir_),
           dist3 = (vec3 ^ vec3) * (vec3 ^ ray.dir_),
           dist4 = (vec4 ^ vec4) * (vec4 ^ ray.dir_);

    std::vector<double> sorted = sortFour(dist1, dist2, dist3, dist4);

    VectorPair intersections = { ray.start_ + ray.dir_ * (sorted[1] > 0 ? sqrt(sorted[1]) : -sqrt(-sorted[1])), ray.start_ + ray.dir_ * (sorted[2] > 0 ? sqrt(sorted[2]) : -sqrt(-sorted[2]))}; //можно не считать заново вектор пересечения

    *norm =  (((sorted[1] >= 0 ? intersections.first : intersections.second)  - center_) / size_ / size_ * 2).norm();

    return intersections;
}
