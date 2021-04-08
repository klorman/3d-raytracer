#include "Raytracer.hpp"

Raytracer::Raytracer(int object_count, Object** objects, int light_count, Light* lights) :
    object_count_(object_count),
    light_count_(light_count),
    objects_(objects),
    lights_(lights)
{}

Vector Raytracer::trace(const Ray& ray, int* object) {
    Vector hit_near = NULL, hit;
    double min_length = 99999;

    for (int obj = 0; obj < object_count_; ++obj) {
        hit = objects_[obj]->trace(ray);
        if (hit == NULL) {
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

bool Raytracer::inshadow(const Vector& p, const Vector& lightpos) {
    Vector hit = trace({ lightpos, (p - lightpos).norm() });

    if (hit == NULL) {
        return false;
    }

    return ((hit - lightpos).length() + 0.1 <= (p - lightpos).length() - 0.1);
}

Vector Raytracer::color(const Ray& ray) {
    int obj;
    Vector hit = trace(ray, &obj);

    if (hit == NULL) {
        return background_color;
    }

    Vector norm = objects_[obj]->norm(hit);

    return ((reflection(objects_[obj], hit, norm, ray) * objects_[obj]->mat_.reflection  ) +
            (refraction(objects_[obj], hit, norm, ray) * objects_[obj]->mat_.transparency) +
            (diffuse   (objects_[obj], hit, norm     ) * objects_[obj]->mat_.surface     )).limit(255);
}

Vector Raytracer::diffuse(Object* obj, const Vector& hit, const Vector& norm) {
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

    return obj->color(hit) * sumlight * k;
}

Vector Raytracer::reflection(Object* obj, const Vector& hit, const Vector& norm, const Ray& ray) {
    if (obj->mat_.reflection * ray.power_ < 0.2) {
        return { 0, 0, 0 };
    }

    Ray reflected = ray.reflect(norm, hit, obj->mat_.reflection);

    return color(reflected);
}

Vector Raytracer::refraction(Object* obj, const Vector& hit, const Vector& norm, const Ray& ray) {
    //return {0,0,0};
    if (obj->mat_.transparency * ray.power_ <= 0) {
        return NULL;
    }

    Ray refracted = ray.refract(norm, hit, obj->mat_.refraction, obj->mat_.transparency);
    
    if (refracted.dir_ == NULL) {
        return NULL;
    }

    return color(refracted);
}