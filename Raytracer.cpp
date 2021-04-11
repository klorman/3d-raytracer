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

Vector Raytracer::color(const Ray& ray) {
    int obj;
    Vector hit = trace(ray, &obj);

    if (hit == NULLVEC) {
        return background_color;
    }

    if (objects_[obj]->mat_.transparency < 0) return objects_[obj]->color_;

    Vector norm = objects_[obj]->norm(hit);

    return ((reflection(objects_[obj], hit, norm, ray) * objects_[obj]->mat_.reflection  )  +
            (refraction(objects_[obj], hit, norm, ray) * objects_[obj]->mat_.transparency)) * objects_[obj]->color(hit);
}

Vector Raytracer::reflection(Object* obj, const Vector& hit, const Vector& norm, const Ray& ray) {
    if (ray.generation_ > 10 || obj->mat_.reflection < EPS) {
        return NULLVEC;
    }

    Ray reflected = ray.reflect(norm, hit, obj->mat_.reflection);

    Vector diffuse = random_on_sphere();
    diffuse = (diffuse * (diffuse ^ norm)).norm();

    reflected.dir_ = mix(diffuse, reflected.dir_, obj->mat_.roughness);

    //reflected.dir_ = reflected.dir_ * 1000 * obj->mat_.roughness + random_on_sphere();
    //reflected.dir_ = (reflected.dir_ * (reflected.dir_ ^ norm)).norm();

    return color(reflected);
}

Vector Raytracer::refraction(Object* obj, const Vector& hit, const Vector& norm, const Ray& ray) {
    if (obj->mat_.transparency <= EPS) {
        return NULLVEC;
    }

    Ray refracted = ray.refract(norm, hit, obj->mat_.refraction, obj->mat_.transparency);
    
    if (refracted.dir_ == NULLVEC) {
        return NULLVEC;
    }

    return color(refracted);
}

std::default_random_engine re;

Vector random_on_sphere() {
    std::uniform_real_distribution<double> unif(-1, 1);
    Vector rnd;

    while(true) {
        rnd = Vector { unif(re), unif(re), unif(re) };
    
        if (rnd.length() <= 1) break;
    }

    return rnd;
}