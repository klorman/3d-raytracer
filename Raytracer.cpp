#include "Raytracer.hpp"

Raytracer::Raytracer() :
    object_count_ (0),
    objects_      (std::vector<Object*>())
{}

Raytracer::Raytracer(int object_count, std::vector<Object*> objects) :
    object_count_ (object_count),
    objects_      (objects)
{}

VectorPair Raytracer::trace(const Ray& ray, int* object, Vector* norm) {
    Vector     n             = NULLVEC;
    VectorPair intersections = {NULLVEC, NULLVEC},
               hit_near      = {NULLVEC, NULLVEC};
    double     min_length    = INF;

    for (int obj = 0; obj < object_count_; ++obj) {
        intersections = objects_[obj]->trace(ray, &n);

        if (intersections.first == NULLVEC && intersections.second == NULLVEC) continue;

        //Vector hit = (((intersections.first - ray.start_) ^ (intersections.second - ray.start_)) > 0) ? intersections.first : intersections.second;
        if (((intersections.first - ray.start_) ^ (intersections.second - ray.start_)) < 0) std::swap(intersections.first, intersections.second);

        double length = (intersections.first - ray.start_).length();

        if (length <= min_length) {
            min_length = length;
            hit_near = intersections;

            if (object != nullptr) *object = obj;
            if (norm   != nullptr) *norm   = n;
        }
    }

    return hit_near;
}

Vector Raytracer::color(const Ray& ray) {
    int        obj           = 0;
    Vector     norm          = NULLVEC;
    VectorPair intersections = trace(ray, &obj, &norm);
    Vector     hit           = intersections.first;

    if (hit == NULLVEC)                       return prop.BACKGROUNDCOLOR;                         //луч не пересекает объекты
    if (objects_[obj]->status_ && abs(intersections.second - intersections.first) < objects_[obj]->size_ * 0.2) return objects_[obj]->color(hit).getContrastColor(); //объект выделен
    if (objects_[obj]->mat_.transparency < 0) return objects_[obj]->color_;                        //объект - источник 
    if (ray.generation_ > prop.MAXGEN)        return NULLVEC;                                      //достигнут лимит

    return ((reflection(objects_[obj], hit, norm, ray) * objects_[obj]->mat_.reflection   ) +
            (refraction(objects_[obj], hit, norm, ray) * objects_[obj]->mat_.transparency)) * objects_[obj]->color(hit);
}

Vector Raytracer::reflection(Object* obj, const Vector& hit, const Vector& norm, const Ray& ray) {
    if (obj->mat_.reflection < EPS) {
        return NULLVEC;
    }

    Ray reflected = ray.reflect(norm, hit, obj->mat_.roughness);

    return color(reflected);
}

Vector Raytracer::refraction(Object* obj, const Vector& hit, const Vector& norm, const Ray& ray) {
    if (obj->mat_.transparency < EPS) {
        return NULLVEC;
    }

    Ray refracted = ray.refract(norm, hit, obj->mat_.n);
    
    if (refracted.dir_ == NULLVEC) {
        return NULLVEC;
    }

    return color(refracted);
}

void Raytracer::addObject(Object* object) {
    object_count_++;

    objects_.push_back(object);
}