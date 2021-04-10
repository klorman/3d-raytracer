#include "Raytracer.hpp"
#include <random>


Raytracer::Raytracer(int object_count, Object** objects, int light_count, Light* lights) :
    object_count_(object_count),
    light_count_(light_count),
    objects_(objects),
    lights_(lights)
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

std::default_random_engine re;

double Raytracer::shading(const Vector& p, const Light& light) {

    std::uniform_real_distribution<double> unif(0, 1);
    Vector rnd;// = { unif(re), unif(re), unif(re) };
    //double theta = rnd.x_ * 2 * txPI; //рандомная точка на фере
    //double phi = acos(2 * rnd.y_ - 1);
    //double r = pow(rnd.z_, 1.0 / 3.0);

    //rnd = Vector {
    //    r * sin(phi) * cos(theta),
    //    r * sin(phi) * sin(theta),
    //    r * cos(phi)
    //} * light.radius_;

    while(true) { //рандомная точка в кубе, работает быстрее, чем поиск ранд точки на сфере
        rnd = Vector { unif(re), unif(re), unif(re) } * light.radius_;
    
        if (rnd.length() <= light.radius_) break;
    }

    Vector dir = (light.center_ + rnd - p).norm();

    int obj;
    Vector hit = trace({ p + dir * 0.01, dir }, &obj);

    if (objects_[obj]->mat_.transparency > 0) {
        Ray ray = { hit, dir };
        ray.refract(objects_[obj]->norm(hit), hit, objects_[obj]->mat_.refraction, objects_[obj]->mat_.transparency);

        hit = trace(ray, &obj);
        ray.refract(objects_[obj]->norm(hit), hit, objects_[obj]->mat_.refraction, objects_[obj]->mat_.transparency);

        if (obj >= object_count_ - light_count_) return objects_[obj]->mat_.transparency; //тут должна быть рекурсия, но и без нее всё не работает
    }

    if (obj >= object_count_ - light_count_) return 1;
    else                                     return 0;


    //if (hit == NULLVEC) {
    //    return false;
    //}
    //return ((hit - light.center_).length() <= (p - light.center_).length() - 0.01);
}

Vector Raytracer::color(const Ray& ray) {
    int obj;
    Vector hit = trace(ray, &obj);

    if (hit == NULLVEC) {
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
        if ((lights_[light].center_ - hit).length() <= lights_[light].radius_ + 0.01) {
            return lights_[light].color_;
        }

        k += shading(hit, lights_[light]);

        Vector dir = (hit - lights_[light].center_).norm();
        double cos = -(dir ^ norm);
        if (cos < 0) cos = 0;

        sumlight += lights_[light].power_ * cos;
    }

    return obj->color(hit) * sumlight * k;
}

Vector Raytracer::reflection(Object* obj, const Vector& hit, const Vector& norm, const Ray& ray) {
    if (obj->mat_.reflection * ray.power_ < 0.1) {
        return { 0, 0, 0 };
    }

    Ray reflected = ray.reflect(norm, hit, obj->mat_.reflection);

    return color(reflected);
}

Vector Raytracer::refraction(Object* obj, const Vector& hit, const Vector& norm, const Ray& ray) {
    //return {0,0,0};
    if (obj->mat_.transparency * ray.power_ <= 0) {
        return NULLVEC;
    }

    Ray refracted = ray.refract(norm, hit, obj->mat_.refraction, obj->mat_.transparency);
    
    if (refracted.dir_ == NULLVEC) {
        return NULLVEC;
    }

    return color(refracted);
}