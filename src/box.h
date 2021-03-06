//
//  box.h
//  c3p0
//
//  Created by Adam Fish on 11/9/17.
//  Copyright © 2017 Adam Fish. All rights reserved.
//

#ifndef box_h
#define box_h

#include "rectangle.h"
#include "bvh.h"

class Box: public Hitable {
public:
    Vec3f PMin, PMax;
    Hitable* bvh_ptr;
    
    Box() {}
    Box(const Vec3f& p0, const Vec3f& p1, Material* mat_ptr);
    
    virtual bool Hit(const Ray& R, double t_min, double t_max, HitRecord& rec) const;
    virtual bool BoundingBox(double t0, double t1, AABB& box) const;
};

Box::Box(const Vec3f& P0, const Vec3f& P1, Material* mat_ptr) {
    PMin = P0;
    PMax = P1;
    Hitable** list = new Hitable*[6];
    list[0] = new RectXY(P0.x, P1.x, P0.y, P1.y, P1.z, mat_ptr);
    list[1] = new FlippedNormals(new RectXY(P0.x, P1.x, P0.y, P1.y, P0.z, mat_ptr));
    list[2] = new RectXZ(P0.x, P1.x, P0.z, P1.z, P1.y, mat_ptr);
    list[3] = new FlippedNormals(new RectXZ(P0.x, P1.x, P0.z, P1.z, P0.y, mat_ptr));
    list[4] = new RectYZ(P0.y, P1.y, P0.z, P1.z, P1.x, mat_ptr);
    list[5] = new FlippedNormals(new RectYZ(P0.y, P1.y, P0.z, P1.z, P0.x, mat_ptr));
    
    bvh_ptr = new BVHNode(list, 6, 0, 0);
}

bool Box::Hit(const Ray& R, double t_min, double t_max, HitRecord& rec) const {
    return bvh_ptr->Hit(R, t_min, t_max, rec);
}

bool Box::BoundingBox(double t0, double t1, AABB& box) const {
    box = AABB(PMin, PMax);
    return true;
}

#endif /* box_h */
