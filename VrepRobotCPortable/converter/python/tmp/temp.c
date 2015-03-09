#include <Python.h>
#include <Windows.h>
PyObject *pName, *pModule, *pDict, *pInit, *pDeInit,
         *pMotorFunc, *pGetEncoderFunc, *pSetEncoderFunc, *pGetSensorFunc;
void initPython()
{
    Py_Initialize();

    pName = PyString_FromString("vrepAbstractor");
    pModule = PyImport_Import(pName);

    pDict = PyModule_GetDict(pModule); // all these functions

    pMotorFunc = PyDict_GetItemString(pDict, "set_motor");
    pGetEncoderFunc = PyDict_GetItemString(pDict, "get_encoder");
    pSetEncoderFunc = PyDict_GetItemString(pDict, "set_encoder");
    pGetSensorFunc = PyDict_GetItemString(pDict, "get_sensor");
    pInit = PyDict_GetItemString(pDict, "init");
    pDeInit = PyDict_GetItemString(pDict, "de_init");

    PyObject_CallObject(pInit, NULL);
}

void deInitPython()
{
    PyObject_CallObject(pDeInit, NULL);

    Py_DECREF(pModule);
    Py_DECREF(pName);
    Py_Finalize();
}

void driveMotor(int motor, int speed)
{
    PyObject *pArgs = PyTuple_New(2);
    PyTuple_SetItem(pArgs, 0, PyInt_FromLong(motor));
    PyTuple_SetItem(pArgs, 1, PyInt_FromLong(speed));

    PyObject_CallObject(pMotorFunc, pArgs);

    if(pArgs != NULL) {
        Py_DECREF(pArgs);
    }
}

void setEncoder(int encoder, int value)
{
    PyObject *pArgs = PyTuple_New(2);
    PyTuple_SetItem(pArgs, 0, PyInt_FromLong(encoder));
    PyTuple_SetItem(pArgs, 1, PyInt_FromLong(value));

    PyObject_CallObject(pSetEncoderFunc, pArgs);

    if(pArgs != NULL) {
        Py_DECREF(pArgs);
    }
}

int getEncoder(int encoder)
{
    PyObject *pArgs = PyTuple_New(1);
    PyTuple_SetItem(pArgs, 0, PyInt_FromLong(encoder));

    int result = PyFloat_AsDouble(PyObject_CallObject(pGetEncoderFunc, pArgs));

    if(pArgs != NULL) {
        Py_DECREF(pArgs);
    }

    return result;
}

int getSensor(int sensor)
{
    PyObject *pArgs = PyTuple_New(1);
    PyTuple_SetItem(pArgs, 0, PyInt_FromLong(sensor));

    int result = PyFloat_AsDouble(PyObject_CallObject(pGetSensorFunc, pArgs));

    if(pArgs != NULL) {
        Py_DECREF(pArgs);
    }

    return result;
}
#define rightMotor 2
#define leftMotor 1
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------------------------------------------------*\
|*                                         - Moving Forward -                                         *|
|*                                      ROBOTC on VEX 2.0 CORTEX                                      *|
|*                                                                                                    *|
|*  This program instructs your robot to move forward at full power for three seconds.  There is a    *|
|*  two second pause at the beginning of the program.                                                 *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    1)  Reversing 'rightMotor' (port 2) in the "Motors and Sensors Setup" is needed with the        *|
|*        "Squarebot" mode, but may not be needed for all robot configurations.                       *|
|*    2)  Power levels that can be assigned to a motor port range from -127 (full reverse) to         *|
|*        127 (full forward).                                                                         *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]          [Name]              [Type]                [Description]                     *|
|*    Motor Port 2        rightMotor          VEX 3-wire module     Right side motor                  *|
|*    Motor Port 3        leftMotor           VEX 3-wire module     Left side motor                   *|
\*-----------------------------------------------------------------------------------------------4246-*/


//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
int studentMain()
{
	Sleep(2000);						// Robot waits for 2000 milliseconds before executing program

	// Move forward at full power for 3 seconds
	driveMotor(rightMotor, 127);		  // Motor on 2 is run at full (127) power forward
	driveMotor(leftMotor, 127);		  // Motor on 3 is run at full (127) power forward
	Sleep(3000);			        // Robot runs previous code for 3000 milliseconds before moving on
}												        // Program ends, and the robot stops
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


int main(int argc, char *argv[])
{
	initPython();
	studentMain();
	deInitPython();
}