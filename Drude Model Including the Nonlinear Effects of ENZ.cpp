/*
    Copyright 2014 Lumerical Solutions, Inc. All rights reserved.
*/
#include "drudemodified.h"
#include <cmath>
#include <algorithm>
/*!
    \class LorentzExample

    \brief This is a simple linear Lorentz material purely for the purpose of
    demonstrating how Lumerical Material Plugins work.
*/
const double DrudeModfiedPlugin::C = 2.99792458e8;
const double DrudeModfiedPlugin::PI = 3.1415926535897931;
const double DrudeModfiedPlugin::HBAR = 1.05457148e-34;
const double DrudeModfiedPlugin::EPS0 = 8.854187817e-12;

const char* DrudeModfiedPlugin::names[8] = {"wp0", "att","tau","n0", "N","Ef","gamma", 0};

void DrudeModfiedPlugin::initialize(const double** parameters, double dt)
{
    for(int i=0; i<3; i++){
        double wp0 = parameters[0][i];
        double att = parameters[1][i];
        double tau = parameters[2][i];
        double n0 = parameters[3][i];
        double N = parameters[4][i];
        double Ef = parameters[5][i];
        double gamma = parameters[6][i];
        a1[i] = float(4/(gamma*dt+2.));
        a2[i] = float((gamma*dt-2.)/(gamma*dt+2.));
        a3[i] = float(2*wp0*wp0*dt*dt/(gamma*dt+2.));
		delta_wp[i] = float (att*tau*n0*C/(N*Ef*2*PI));
    }
}

float DrudeModfiedPlugin::calculate(int axis, float U, float V, float E, float* storage)
{
    float Pn = storage[0];
    float Pnm1 = storage[1];

	float Snm1 = storage[2];
    float Sn   = storage[3];

	float E2 = E*E;

	float Snp1 = a1[axis]*Sn + a2[axis]*Snm1 - delta_wp[axis]*a3[axis]*E2;

    float Pnp1 = a1[axis]*Pn + a2[axis]*Pnm1 + a3[axis]*E;

    storage[0] = Pnp1;
    storage[1] = Pn;

	float Enp1 = V-Pnp1/(U+Snp1);
	
	storage[2] = Sn;
    storage[3] = Snp1;

	
   

    return Enp1;

}

float DrudeModfiedPlugin::calculateEx( float U, float V, float Ex, float* storage )
{
    return calculate(0, U, V, Ex, storage);
}

float DrudeModfiedPlugin::calculateEy( float U, float V, float Ey, float* storage )
{
    return calculate(1, U, V, Ey, storage);
}

float DrudeModfiedPlugin::calculateEz( float U, float V, float Ez, float* storage )
{
    return calculate(2, U, V, Ez, storage);
}

MATERIAL_PLUGIN(DrudeModfiedPlugin);

