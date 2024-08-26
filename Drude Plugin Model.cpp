/*
    Copyright 2014 Lumerical Solutions, Inc. All rights reserved.
*/
#include "drudeexample.h"
#include <cmath>
#include <algorithm>
/*!
    \class LorentzExample

    \brief This is a simple linear Drude material purely for the purpose of
    demonstrating how Lumerical Material Plugins work.
*/


const char* DrudeExamplePlugin::names[3] = {"wp0","gamma", 0};

void DrudeExamplePlugin::initialize(const double** parameters, double dt)
{
    for(int i=0; i<3; i++){
        double wp0 = parameters[0][i];
        double gamma = parameters[1][i];
        a1[i] = float( (2)/(gamma*dt+1.) );
        a2[i] = float( (gamma*dt-1.)/(gamma*dt+1.) );
        a3[i] = float( wp0*wp0*dt*dt/(gamma*dt+1.) );
    }
}

float DrudeExamplePlugin::calculate(int axis, float U, float V, float E, float* storage)
{
    float Pn = storage[0];
    float Pnm1 = storage[1];

    float Pnp1 = a1[axis]*Pn + a2[axis]*Pnm1 + a3[axis]*E;

    storage[0] = Pnp1;
    storage[1] = Pn;

    storage[2] = a1[axis];
	storage[3] = a2[axis];
	storage[4] = a3[axis];
	storage[5] = U;
	storage[6] = V;
	
    return (V-Pnp1)/U;

}

float DrudeExamplePlugin::calculateEx( float U, float V, float Ex, float* storage )
{
    return calculate(0, U, V, Ex, storage);
}

float DrudeExamplePlugin::calculateEy( float U, float V, float Ey, float* storage )
{
    return calculate(1, U, V, Ey, storage);
}

float DrudeExamplePlugin::calculateEz( float U, float V, float Ez, float* storage )
{
    return calculate(2, U, V, Ez, storage);
}

MATERIAL_PLUGIN(DrudeExamplePlugin);

