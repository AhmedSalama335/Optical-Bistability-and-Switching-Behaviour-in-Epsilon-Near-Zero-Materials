/*
    Copyright 2013 Lumerical Solutions, Inc. All rights reserved.
*/
#include "threestepindexwithelectricfield.h"
#include <cmath>

/*!
    \class StepIndexMaterialPlugin

*/


const char* ThreeStepIndexwithelecricfieldPlugin::names[19] = {"delta_eps1","delta_eps2","delta_eps3", "delta_eps4","delta_eps5","delta_eps6","time_start", "time_stop","time_start2", "time_stop2","time_start3", "time_stop3","time_start4", "time_stop4","time_start5", "time_stop5","time_start6", "time_stop6", 0};

void ThreeStepIndexwithelecricfieldPlugin::initialize(const double** parameters, double dt)
{
    for(int i=0; i<3; i++){
        delta_eps1[i] = float(parameters[0][i]);
		delta_eps2[i] = float(parameters[1][i]);
		delta_eps3[i] = float(parameters[2][i]);
		delta_eps4[i] = float(parameters[3][i]);
		delta_eps5[i] = float(parameters[4][i]);
		delta_eps6[i] = float(parameters[5][i]);
    }

    time_start = parameters[6][0];
    time_stop = parameters[7][0];
	time_start2 = parameters[8][0];
    time_stop2 = parameters[9][0];
	time_start3 = parameters[10][0];
    time_stop3 = parameters[11][0];
	time_start4 = parameters[12][0];
    time_stop4 = parameters[13][0];
	time_start5 = parameters[14][0];
    time_stop5 = parameters[15][0];
	time_start6 = parameters[16][0];
    time_stop6 = parameters[17][0];
    time_dt = dt;

}

float ThreeStepIndexwithelecricfieldPlugin::calculate(int axis, float U, float V, float E, float* storage)
{
    storage[0] += time_dt;
    bool change_index1 = ((storage[0] > time_start) && (storage[0] < time_stop)) ;  
	bool change_index2 = ((storage[0] > time_start2) && (storage[0] < time_stop2));  
	bool change_index3 = ((storage[0] > time_start3) && (storage[0] < time_stop3));  
	bool change_index4 = ((storage[0] > time_start4) && (storage[0] < time_stop4)) ;  
	bool change_index5 = ((storage[0] > time_start5) && (storage[0] < time_stop5));  
	bool change_index6 = ((storage[0] > time_start6) && (storage[0] < time_stop6));  

	storage[1] = delta_eps1[axis]*E*E;
	storage[2] = delta_eps2[axis]*E*E;
	storage[3] = delta_eps3[axis]*E*E;
	storage[4] = delta_eps4[axis]*E*E;
	storage[5] = delta_eps5[axis]*E*E;
	storage[6] = delta_eps6[axis]*E*E;

	storage[7] = U+delta_eps1[axis]*E*E;
	storage[8] = U+delta_eps2[axis]*E*E;
	storage[9] = U+delta_eps3[axis]*E*E;
	storage[10] = U+delta_eps4[axis]*E*E;
	storage[11] = U+delta_eps5[axis]*E*E;
	storage[12] = U+delta_eps6[axis]*E*E;

	storage[13] = U;

    return change_index1 ? V/(U+delta_eps1[axis]*E*E) : change_index2 ? V/(U+delta_eps2[axis]*E*E): change_index3 ? V/(U+delta_eps3[axis]*E*E): change_index4 ? V/(U+delta_eps4[axis]*E*E): change_index5 ? V/(U+delta_eps5[axis]*E*E): change_index6 ? V/(U+delta_eps6[axis]*E*E) : V/U;
}

float ThreeStepIndexwithelecricfieldPlugin::calculateEx( float U, float V, float Ex, float* storage )
{
    return calculate(0, U, V, Ex, storage);
}

float ThreeStepIndexwithelecricfieldPlugin::calculateEy( float U, float V, float Ey, float* storage )
{
    return calculate(1, U, V, Ey, storage);
}

float ThreeStepIndexwithelecricfieldPlugin::calculateEz( float U, float V, float Ez, float* storage )
{
    return calculate(2, U, V, Ez, storage);
}

MATERIAL_PLUGIN(ThreeStepIndexwithelecricfieldPlugin);
