//
// Created by Göksu Güvendiren on 2019-05-14.
//

#include "Scene.hpp"

void Scene::buildBVH() {
    printf(" - Generating BVH...\n\n");
    this->bvh = new BVHAccel(objects, 1, BVHAccel::SplitMethod::NAIVE);
}

Intersection Scene::obj_intert(const Ray &ray) const {
    return this->bvh->Intersect(ray);
}

void Scene::sampleLight(Intersection &pos, float &pdf) const {
    float emit_area_sum = 0;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()) {
            emit_area_sum += objects[k]->getArea();
        }
    }
    float p = get_random_float() * emit_area_sum;
    emit_area_sum = 0;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()) {
            emit_area_sum += objects[k]->getArea();
            if (p <= emit_area_sum) {
                objects[k]->Sample(pos, pdf);
                break;
            }
        }
    }
}

bool Scene::trace(
    const Ray &ray,
    const std::vector<Object *> &objects,
    float &tNear, uint32_t &index, Object **hitObject) {
    *hitObject = nullptr;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        float tNearK = kInfinity;
        uint32_t indexK;
        Vector2f uvK;
        if (objects[k]->obj_intert(ray, tNearK, indexK) && tNearK < tNear) {
            *hitObject = objects[k];
            tNear = tNearK;
            index = indexK;
        }
    }

    return (*hitObject != nullptr);
}

// Implementation of Path Tracing
Vector3f Scene::castRay(const Ray &ray, int depth) const {
    // TO DO Implement Path Tracing Algorithm here
    Intersection obj_inter = obj_intert(ray);
    if (!obj_inter.happened) {
        return Vector3f();
    }

    // 打到光源
    if (obj_inter.m->hasEmission()) {
        return obj_inter.m->getEmission();
    }

    Vector3f l_dir;
    Vector3f l_indir;

    // 对光源积分
    Intersection light_inter;
    float lightPdf = 0.0f;
    sampleLight(light_inter, lightPdf);

    Vector3f obj2light = light_inter.coords - obj_inter.coords;
    Vector3f obj2lightDir = obj2light.normalized();
    float obj2lightPow = obj2light.x * obj2light.x + obj2light.y * obj2light.y + obj2light.z * obj2light.z;

    Ray obj2lightRay(obj_inter.coords, obj2lightDir);
    Intersection block_inter1 = obj_intert(obj2lightRay);
    if (block_inter1.distance - obj2light.norm() > -EPSILON) {
        l_dir = light_inter.emit * obj_inter.m->eval(ray.direction, obj2lightDir, obj_inter.normal) * dotProduct(obj2lightDir, obj_inter.normal) * dotProduct(-obj2lightDir, light_inter.normal) / obj2lightPow / lightPdf;
    }

    if (get_random_float() > RussianRoulette) {
        return l_dir;
    }

    // 对其他方向积分
    Vector3f obj2otherDir = obj_inter.m->sample(ray.direction, obj_inter.normal).normalized();
    Ray obj2nextobjray(obj_inter.coords, obj2otherDir);
    Intersection other_inter = obj_intert(obj2nextobjray);
    
    if (other_inter.happened && !other_inter.m->hasEmission()) {
        float pdf = obj_inter.m->pdf(ray.direction, obj2otherDir, obj_inter.normal);
        l_indir = castRay(obj2nextobjray, depth + 1) * obj_inter.m->eval(ray.direction, obj2otherDir, obj_inter.normal) * dotProduct(obj2otherDir, obj_inter.normal) / pdf / RussianRoulette;
    }

    return l_dir + l_indir;
}