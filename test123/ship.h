// cars.h
#ifndef CARS_H
#define CARS_H




struct BoundingBox {
    float minX, maxX;
    float minY, maxY;
    float minZ, maxZ;
};

bool checkAllCollisions();
BoundingBox ship_controller(int n);
BoundingBox ship_controller_t(int n);
bool checkCollision(const BoundingBox& box1, const BoundingBox& box2);
BoundingBox  cars_midg(float noc, float lrindex, float car);

#endif // CARS_H