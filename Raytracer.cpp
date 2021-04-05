#include "Raytracer.hpp"

Raytracer::Raytracer(int object_count, Sphere* objects, int light_count, Light* lights) :
    object_count_(object_count),
    light_count_(light_count),
    objects_(objects),
    lights_(lights)
{}

Vector Raytracer::trace(Ray ray, Sphere* object) {
    Vector p_near, p;
    double min_length = 9999;

    for (int obj = 0; obj < object_count_; ++obj) {
        p = objects_[obj].trace(ray);
        double length = p.length();

        if (length < min_length) {
            min_length = length;
            p_near = p;
            *object = objects_[obj];
        }
    }

    return p_near;
}

bool Raytracer::inshadow(Vector p, Vector lightpos) {
    Vector q = trace({ lightpos, p - lightpos });
    if (q.length() == 0) {
        return true;
    }

    return (q - lightpos).length() < (p - lightpos).length();
}

Vector Raytracer::color(Ray ray) {
    return background_color;
    Sphere obj = objects_[0];
    Vector hit = obj.trace(ray);

    if (hit == NULL) {
        return background_color;
    }
    //Vector hit = trace(ray, &obj);
    

    if (hit.length() == 0) {
        return { 0, 0, 0 };
    }

    Vector norm = obj.norm(hit);

    return  (obj.mat_.reflection   * reflection(obj, hit, norm)) +
            (obj.mat_.transparency * refraction(obj, hit, norm)) +
            (obj.mat_.surface      * diffuse   (obj, hit, norm));
}

Vector Raytracer::diffuse   (Sphere obj, Vector hit, Vector norm) {
    double sumlight = 0;

    for (int light = 0; light < light_count_; ++light) {
        //if (inshadow(hit, lights_[light].pos_)) {
        //    continue;
        //}

        Vector dir = (hit - lights_[light].pos_).norm();
        double cos = -(dir ^ norm);

        sumlight += lights_[light].power_ * cos;
    }

    return obj.color_ * sumlight;
}

Vector Raytracer::reflection(Sphere obj, Vector hit, Vector norm) {
    (void)obj;
    (void)hit;
    (void)norm;
    return { 0, 0, 0 };
}

Vector Raytracer::refraction(Sphere obj, Vector hit, Vector norm) {
    (void)obj;
    (void)hit;
    (void)norm;
    return { 0, 0, 0 };
}