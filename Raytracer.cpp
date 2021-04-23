#include "Raytracer.hpp"

Raytracer::Raytracer(int object_count, Object** objects, Properties* prop) :
    object_count_ (object_count),
    objects_      (objects),
    prop_         (prop)
{}

Vector Raytracer::trace(const Ray& ray, int* object, Vector* norm) {
    Vector hit_near = NULLVEC, hit, n = NULLVEC;
    double min_length = 10000;

    for (int obj = 0; obj < object_count_; ++obj) {
        hit = objects_[obj]->trace(ray, &n);
        if (hit == NULLVEC) {
            continue;
        }

        double length = (hit - ray.start_).length();

        if (length <= min_length) {
            min_length = length;
            hit_near = hit;

            if (object != nullptr) *object = obj;
            if (norm   != nullptr) *norm   = n;
        }
    }

    return hit_near;
}

Vector Raytracer::color(const Ray& ray) {
    int obj;
    Vector norm = NULLVEC;
    Vector hit = trace(ray, &obj, &norm);

    if (hit == NULLVEC)                       return prop_->BACKGROUNDCOLOR;//луч не пересекает объекты
    if (objects_[obj]->mat_.transparency < 0) return objects_[obj]->color_; //объект - источник 
    if (ray.generation_ > MAXGEN)             return NULLVEC;               //достигнут лимит

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