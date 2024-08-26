/*
    Copyright 2014 Lumerical Solutions, Inc. All rights reserved.
*/
#ifndef _DRUDEMODIFIED_H
#define _DRUDEMODIFIED_H

#include "imaterialplugin.h"

class DrudeModfiedPlugin : public IMaterialPlugin
{
public:
    DrudeModfiedPlugin(){};
    virtual ~DrudeModfiedPlugin(){};

    const char* name() const {return "Drude Modified";};
    const char* uniqueId() const { return "{568092DE-3D4B-4B40-B13A-8EC1924BD079}";};
    const char** parameterNames() const {return names;};
    float calculateEx( float U, float V, float Ex, float* storage);
    float calculateEy( float U, float V, float Ey, float* storage);
    float calculateEz( float U, float V, float Ez, float* storage);
    void initialize(const double** parameters, double dt);
    void initializeStorageEx(float* storage){};
    void initializeStorageEy(float* storage){};
    void initializeStorageEz(float* storage){};
    size_t storageSizeE() const {return 4;};

private:
    float calculate(int axis, float U, float V, float E, float* storage);

    float a1[3];
    float a2[3];
    float a3[3];
	float delta_wp[3];
    static const char* names[8];
	static const double PI;
    static const double C;
    static const double EPS0;
    static const double HBAR;
};

#endif

