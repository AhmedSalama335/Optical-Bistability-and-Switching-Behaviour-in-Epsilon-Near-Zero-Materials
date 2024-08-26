/*
    Copyright 2014 Lumerical Solutions, Inc. All rights reserved.
*/
#ifndef _DRUDEEXAMPLE_H
#define _DRUDEEXAMPLE_H

#include "imaterialplugin.h"

class DrudeExamplePlugin : public IMaterialPlugin
{
public:
    DrudeExamplePlugin(){};
    virtual ~DrudeExamplePlugin(){};

    const char* name() const {return "Drude Example";};
    const char* uniqueId() const { return "{68C6641E-D32C-4F17-87D5-6A61D2280158}";};
    const char** parameterNames() const {return names;};
    float calculateEx( float U, float V, float Ex, float* storage);
    float calculateEy( float U, float V, float Ey, float* storage);
    float calculateEz( float U, float V, float Ez, float* storage);
    void initialize(const double** parameters, double dt);
    void initializeStorageEx(float* storage){};
    void initializeStorageEy(float* storage){};
    void initializeStorageEz(float* storage){};
    size_t storageSizeE() const {return 8;};

private:
    float calculate(int axis, float U, float V, float E, float* storage);

    float a1[3];
    float a2[3];
    float a3[3];

    static const char* names[3];
	
};

#endif


