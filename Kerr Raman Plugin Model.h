/*
    Copyright 2012 Lumerical Solutions, Inc. All rights reserved.
*/
#ifndef _CHI3RAMANKERRMODIFIED_H
#define _CHI3RAMANKERRMODIFIED_H

#include "imaterialplugin.h"

class Chi3RamanKerrModifiedMaterialPlugin : public IMaterialPlugin
{
public:
    Chi3RamanKerrModifiedMaterialPlugin(){};
    virtual ~Chi3RamanKerrModifiedMaterialPlugin(){};

    const char* name() const {return "Chi3 Raman Kerr Modified";};
    const char* uniqueId() const {return "{3438B94C-E576-4EBA-9F96-6F5B4FC981AF}";};
    const char** parameterNames() const {return names;};
    float calculateEx( float U, float V, float Ex, float* storage);
    float calculateEy( float U, float V, float Ey, float* storage);
    float calculateEz( float U, float V, float Ez, float* storage);
    void initialize(const double** parameters, double dt);
    void initializeStorageEx(float* storage){};
    void initializeStorageEy(float* storage){};
    void initializeStorageEz(float* storage){};
    size_t storageSizeE() const {return 5;};

private:
    float calculate(int axis, float U, float V, float E, float* storage);

    float a1[3];
    float a2[3];
    float a3[3];
    float chi1[3];
    float chi3[3];

    static const char* names[6];
};

#endif


