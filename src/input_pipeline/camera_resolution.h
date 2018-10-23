#ifndef FACERIG_CAMERA_RESOLUTION_H
#define FACERIG_CAMERA_RESOLUTION_H

struct CamResolution {
    CamResolution(int width, int height) : width(width), height(height) {};
    int width;
    int height;
};

#endif //FACERIG_CAMERA_RESOLUTION_H
