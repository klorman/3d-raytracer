#include "Raytracer.hpp"

Raytracer::Raytracer(int object_count, Object** objects) :
    object_count_(object_count),
    objects_(objects)
{}

Vector Raytracer::trace(const Ray& ray, int* object) {
    Vector hit_near = NULLVEC, hit;
    double min_length = 10000;

    for (int obj = 0; obj < object_count_; ++obj) {
        hit = objects_[obj]->trace(ray);
        if (hit == NULLVEC) {
            continue;
        }

        double length = (hit - ray.start_).length();

        if (length <= min_length) {
            min_length = length;
            hit_near = hit;
            if (object != nullptr) {
                *object = obj;
            }
        }
    }

    return hit_near;
}

Vector Raytracer::color(Ray* ray) {
    
    int obj;
    Vector hit = trace(*ray, &obj);

    if (hit == NULLVEC)                       { ray->generation_ = MAXGEN + 1; return background_color;      };
    if (objects_[obj]->mat_.transparency < 0) { ray->generation_ = MAXGEN + 1; return objects_[obj]->color_; };

    Vector norm = objects_[obj]->norm(hit);

    ray->reflect(norm, hit, objects_[obj]->mat_.roughness);

    return objects_[obj]->color(hit) * objects_[obj]->mat_.reflection;
}

//Vector Raytracer::refraction(Object* obj, const Vector& hit, const Vector& norm, const Ray& ray) {
//    if (ray.generation_ > MAXGEN || obj->mat_.transparency <= EPS) {
//        return NULLVEC;
//    }
//
//    Ray refracted = ray.refract(norm, hit, obj->mat_.refraction, obj->mat_.transparency);
//    
//    if (refracted.dir_ == NULLVEC) {
//        return NULLVEC;
//    }
//
//    return color(refracted);
//}