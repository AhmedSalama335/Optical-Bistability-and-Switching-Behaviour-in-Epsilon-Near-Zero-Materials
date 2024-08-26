/*
    Copyright 2012 Lumerical Solutions, Inc. All rights reserved.
*/
#include "chi3ramankerrmodified.h"

/*!
    \class Chi3RamanKerrMaterialPlugin

    \brief 
*/

const char* Chi3RamanKerrModifiedMaterialPlugin::names[6] = {"chi1", "chi3", "alpha", "wraman","delta raman",0};

void Chi3RamanKerrModifiedMaterialPlugin::initialize(const double** parameters, double dt)
{
    for(int i=0; i<3; i++){
        double alpha  = float(parameters[2][i]);
        double wraman2 = (parameters[3][i]*dt)*(parameters[3][i]*dt);
        double draman  = parameters[4][i]*dt;

        a1[i] = float((2.-wraman2)/(draman + 1.));
        a2[i] = float((draman-1.)/(draman + 1.));
        a3[i] = float((1.-alpha)*parameters[1][i]*wraman2/(draman + 1.));

        chi1[i]   = float(parameters[0][i]);
        chi3[i]   = float(parameters[1][i] * alpha);

    }
}

float Chi3RamanKerrModifiedMaterialPlugin::calculate(int axis, float U, float V, float E, float* storage)
{
    float Snm1 = storage[0];
    float Sn   = storage[1];

    float E2 = E*E;
    float Snp1 = a1[axis]*Sn + a2[axis]*Snm1 + a3[axis]*E2;

    float Enp1 = V/(U+chi1[axis]+chi3[axis]*E2+Snp1);
	
    storage[0] = Sn;
    storage[1] = Snp1;
	storage[2] = U;
	storage[3] = chi1[axis]+chi3[axis]*E2+Snp1;
	storage[4] = U+chi1[axis]+chi3[axis]*E2+Snp1;

    return Enp1;
}

float Chi3RamanKerrModifiedMaterialPlugin::calculateEx( float U, float V, float Ex, float* storage )
{
    return calculate(0, U, V, Ex, storage);
}

float Chi3RamanKerrModifiedMaterialPlugin::calculateEy( float U, float V, float Ey, float* storage )
{
    return calculate(1, U, V, Ey, storage);
}

float Chi3RamanKerrModifiedMaterialPlugin::calculateEz( float U, float V, float Ez, float* storage )
{
    return calculate(2, U, V, Ez, storage);
}

MATERIAL_PLUGIN(Chi3RamanKerrModifiedMaterialPlugin);

