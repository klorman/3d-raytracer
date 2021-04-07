#include "Raytracer.hpp"

Raytracer::Raytracer(int object_count, Sphere* objects, int light_count, Light* lights) :
    object_count_(object_count),
    light_count_(light_count),
    objects_(objects),
    lights_(lights)
{}

Vector Raytracer::trace(Ray ray, Sphere* object) {
    Vector hit_near = NULL, hit;
    double min_length = 99999;

    for (int obj = 0; obj < object_count_; ++obj) {
        hit = objects_[obj].trace(ray);
        if (hit == NULL) {
            continue;
        } 

        double length = (hit - ray.start_).length();

        if (length <= min_length) {
            min_length = length;
            hit_near = hit;
            if (object != nullptr) {
                *object = objects_[obj];
            }
        }
    }

    return hit_near;
}

bool Raytracer::inshadow(Vector p, Vector lightpos) {
    Vector hit = trace({ lightpos, (p - lightpos).norm() });

    if (hit == NULL) {
        return false;
    }

    return ((hit - lightpos).length() + 0.1 <= (p - lightpos).length() - 0.1);
}

Vector Raytracer::color(Ray ray) {
    Sphere obj;
    Vector hit = trace(ray, &obj);

    if (hit == NULL) {
        return background_color;
    }

    Vector norm = obj.norm(hit);

    return  (reflection(obj, hit, norm, ray) * obj.mat_.reflection  ) +
            (refraction(obj, hit, norm)      * obj.mat_.transparency) +
            (diffuse   (obj, hit, norm)      * obj.mat_.surface     );
}

Vector Raytracer::diffuse   (Sphere obj, Vector hit, Vector norm) {
    double k = 1, sumlight = 0;

    for (int light = 0; light < light_count_; ++light) {
        if (inshadow(hit, lights_[light].pos_)) {
            //continue;
            k = 0.3;
        }

        Vector dir = (hit - lights_[light].pos_).norm();
        double cos = -(dir ^ norm);
        if (cos < 0) cos = 0;

        sumlight += lights_[light].power_ * cos;
    }

    return obj.color_ * sumlight * k;
}

Vector Raytracer::reflection(Sphere obj, Vector hit, Vector norm, Ray ray) {
    //return background_color;

    if (obj.mat_.reflection * ray.power_ < 0.2) {
        return { 0, 0, 0 };
    }

    Ray reflected = ray.reflect(norm, hit, obj.mat_.reflection);

    return color(reflected);
}

Vector Raytracer::refraction(Sphere obj, Vector hit, Vector norm) {
    (void)obj;
    (void)hit;
    (void)norm;
    return { 0, 0, 0 };
}