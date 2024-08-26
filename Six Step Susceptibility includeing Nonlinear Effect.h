/*
    Copyright 2013 Lumerical Solutions, Inc. All rights reserved.
*/
#ifndef _THREESTEPINDEXWITHELECTRICFIELD_H
#define _THREESTEPINDEXWITHELECTRICFIELD_H

#include "imaterialplugin.h"

class ThreeStepIndexwithelecricfieldPlugin: public IMaterialPlugin
{
public:
    ThreeStepIndexwithelecricfieldPlugin(){};
    virtual ~ThreeStepIndexwithelecricfieldPlugin(){};

    const char* name() const {return "Three Step Index with Linear ELectric";};
    const char* uniqueId() const {return "{D0C029BD-A4AA-432C-AAE9-95C05D8D148D}";};
    const char** parameterNames() const {return names;};
    float calculateEx( float U, float V, float Ex, float* storage);
    float calculateEy( float U, float V, float Ey, float* storage);
    float calculateEz( float U, float V, float Ez, float* storage);
    void initialize(const double** parameters, double dt);
    void initializeStorageEx(float* storage){};
    void initializeStorageEy(float* storage){};
    void initializeStorageEz(float* storage){};
    size_t storageSizeE() const {return 14;};

private:
    float calculate(int axis, float U, float V, float E, float* storage);

    float delta_eps1[3];
	float delta_eps2[3];
	float delta_eps3[3];
	float delta_eps4[3];
	float delta_eps5[3];
	float delta_eps6[3];
    double time_start;
    double time_stop;
	double time_start2;
	double time_stop2;
	double time_start3;
	double time_stop3;
	double time_start4;
	double time_stop4;
	double time_start5;
	double time_stop5;
	double time_start6;
	double time_stop6;
    double time_dt;
    static const char* names[19];
};

#endif

