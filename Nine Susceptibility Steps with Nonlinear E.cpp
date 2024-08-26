/*
    Copyright 2013 Lumerical Solutions, Inc. All rights reserved.
*/
#include "ninestepindexwithandwithoutelectricfield.h"
#include <cmath>

/*!
    \class StepIndexMaterialPlugin

*/


const char* NineStepIndexwithAndWithoutelecricfieldPlugin::names[28] = {"delta_eps1","delta_eps2","delta_eps3", "delta_eps4","delta_eps5","delta_eps6","delta_eps7","delta_eps8","delta_eps9","time_start", "time_stop","time_start2", "time_stop2","time_start3", "time_stop3","time_start4", "time_stop4","time_start5", "time_stop5","time_start6", "time_stop6","time_start7", "time_stop7","time_start8", "time_stop8","time_start9", "time_stop9", 0};

void NineStepIndexwithAndWithoutelecricfieldPlugin::initialize(const double** parameters, double dt)
{
    for(int i=0; i<3; i++){
        delta_eps1[i] = float(parameters[0][i]);
		delta_eps2[i] = float(parameters[1][i]);
		delta_eps3[i] = float(parameters[2][i]);
		delta_eps4[i] = float(parameters[3][i]);
		delta_eps5[i] = float(parameters[4][i]);
		delta_eps6[i] = float(parameters[5][i]);
		delta_eps7[i] = float(parameters[6][i]);
		delta_eps8[i] = float(parameters[7][i]);
		delta_eps9[i] = float(parameters[8][i]);
    }

    time_start = parameters[9][0];
    time_stop = parameters[10][0];
	time_start2 = parameters[11][0];
    time_stop2 = parameters[12][0];
	time_start3 = parameters[13][0];
    time_stop3 = parameters[14][0];
	time_start4 = parameters[15][0];
    time_stop4 = parameters[16][0];
	time_start5 = parameters[17][0];
    time_stop5 = parameters[18][0];
	time_start6 = parameters[19][0];
    time_stop6 = parameters[20][0];
	time_start6 = parameters[21][0];
    time_stop6 = parameters[22][0];
	time_start6 = parameters[23][0];
    time_stop6 = parameters[24][0];
	time_start6 = parameters[25][0];
    time_stop6 = parameters[26][0];
    time_dt = dt;

}

float NineStepIndexwithAndWithoutelecricfieldPlugin::calculate(int axis, float U, float V, float E, float* storage)
{
    storage[0] += time_dt;
    bool change_index1 = ((storage[0] > time_start) && (storage[0] < time_stop)) ;  
	bool change_index2 = ((storage[0] > time_start2) && (storage[0] < time_stop2));  
	bool change_index3 = ((storage[0] > time_start3) && (storage[0] < time_stop3));  
	bool change_index4 = ((storage[0] > time_start4) && (storage[0] < time_stop4)) ;  
	bool change_index5 = ((storage[0] > time_start5) && (storage[0] < time_stop5));  
	bool change_index6 = ((storage[0] > time_start6) && (storage[0] < time_stop6));  
	bool change_index7 = ((storage[0] > time_start7) && (storage[0] < time_stop7)) ;  
	bool change_index8 = ((storage[0] > time_start8) && (storage[0] < time_stop8));  
	bool change_index9 = ((storage[0] > time_start9) && (storage[0] < time_stop9));  

	storage[1] = delta_eps1[axis];
	storage[2] = delta_eps2[axis];
	storage[3] = delta_eps3[axis];
	storage[4] = delta_eps4[axis]*E*E;
	storage[5] = delta_eps5[axis]*E*E;
	storage[6] = delta_eps6[axis]*E*E;
	storage[7] = delta_eps7[axis];
	storage[8] = delta_eps8[axis];
	storage[9] = delta_eps9[axis];

	storage[10] = U+delta_eps1[axis];
	storage[11] = U+delta_eps2[axis];
	storage[12] = U+delta_eps3[axis];
	storage[13] = U+delta_eps4[axis]*E*E;
	storage[14] = U+delta_eps5[axis]*E*E;
	storage[15] = U+delta_eps6[axis]*E*E;
	storage[16] = U+delta_eps4[axis];
	storage[17] = U+delta_eps5[axis];
	storage[18] = U+delta_eps6[axis];

	storage[19] = U;

    return change_index1 ? V/(U+delta_eps1[axis]) : change_index2 ? V/(U+delta_eps2[axis]): change_index3 ? V/(U+delta_eps3[axis]): change_index4 ? V/(U+delta_eps4[axis]*E*E): change_index5 ? V/(U+delta_eps5[axis]*E*E): change_index6 ? V/(U+delta_eps6[axis]*E*E): change_index7 ? V/(U+delta_eps7[axis]): change_index8 ? V/(U+delta_eps8[axis]): change_index6 ? V/(U+delta_eps9[axis]) : V/U;
}

float NineStepIndexwithAndWithoutelecricfieldPlugin::calculateEx( float U, float V, float Ex, float* storage )
{
    return calculate(0, U, V, Ex, storage);
}

float NineStepIndexwithAndWithoutelecricfieldPlugin::calculateEy( float U, float V, float Ey, float* storage )
{
    return calculate(1, U, V, Ey, storage);
}

float NineStepIndexwithAndWithoutelecricfieldPlugin::calculateEz( float U, float V, float Ez, float* storage )
{
    return calculate(2, U, V, Ez, storage);
}

MATERIAL_PLUGIN(NineStepIndexwithAndWithoutelecricfieldPlugin);
