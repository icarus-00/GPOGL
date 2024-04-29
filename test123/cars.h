// cars.h
#ifndef CARS_H
#define CARS_H




struct BoundingBox {
    float minX, maxX;
    float minY, maxY;
    float minZ, maxZ;
};

bool checkAllCollisions();
BoundingBox cars(int n);
bool checkCollision(const BoundingBox& box1, const BoundingBox& box2);
#endif // CARS_H