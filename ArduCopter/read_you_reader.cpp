 
#include "Copter.h"
#include "Python.h"

void Copter::read_motion_and_pid()//float &roll_in, float &pitch_in,float &yaw_in,float &throttle_in)
{
double result,x,y,z,yaw;
Py_Initialize();
PyRun_SimpleString("import sys;sys.path.append('.')");
PyObject* myModuleString=PyString_FromString((char*)"reader");
PyObject * myModule=NULL;
PyObject * a=NULL;
PyObject * b=NULL;
PyObject * c=NULL;
PyObject * d=NULL;
PyObject * l=PyList_New(3);

myModule=PyImport_Import(myModuleString);

PyObject* myFunction=PyObject_GetAttrString(myModule,"reading_serial");

if (myFunction!=NULL)
{
	l=PyObject_CallObject(myFunction,NULL);

	a=PyList_GetItem(l,0);
	b=PyList_GetItem(l,1);
	c=PyList_GetItem(l,2);
	d=PyList_GetItem(l,3);

	x = PyFloat_AsDouble(a);
	y = PyFloat_AsDouble(b);
	z = PyFloat_AsDouble(c);
	yaw = PyFloat_AsDouble(d);
}
else{
	PyErr_Print();
}
Py_Finalize();

if (x==0 && y==0 && z==0 && yaw==0){
    return;
}


float dt=0.04;
_yaw_in=constrain_float(5*(-yaw),-40,40);
_yaw_in=_yaw_in*45*4.5/40;

_throttle_in=20*(-z);
_dz=((-z)-_inputz)/dt+0.01*(((-z)-_inputz)/dt-_dz);
_throttle_in+=7*_dz;
_throttle_in=constrain_float(_throttle_in,-25,25);
_throttle_in=(_throttle_in+25)/50;
_throttle_in=constrain_float(_throttle_in,0.1,0.75);


_pitch_in=10*(-x);
_dx=((-x)-_inputx)/dt+0.01*(((-x)-_inputx)/dt-_dx);
_pitch_in+=9*_dz;
_pitch_in=constrain_float(_pitch_in,-15,15);
_pitch_in=(_pitch_in)*45/15;


_roll_in=10*(-y);
_dy=((-y)-_inputy)/dt+0.01*(((-y)-_inputy)/dt-_dy);
_roll_in=9*_dy;
_roll_in=constrain_float(_roll_in,-15,15);
_roll_in=(-_roll_in)*45/15;

_inputx=-x;
_inputy=-y;
_inputz=-z;

return;

}
