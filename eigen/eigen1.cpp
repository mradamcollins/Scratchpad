#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Geometry>

using namespace Eigen;
using namespace std;

// qEst = qEst + (qDot - beta*gradF.normalised)*deltaT
// inputs: qEst, w, a, deltaT, beta
// output: qEst 
void UpdateAttitude( 	Quaterniond& qEst, 		// Reference to the current esitmate- will be update to reflect the new estimate
						const Quaterniond& w,	// [0, wx, wy, wz] rad/s
						const Quaterniond& a,	// [0, ax, ay, az] m/s/s
						const double deltaT_sec,// sample period (seconds)
						const double beta ) 	// Gain factor to account for all zero mean noise (sqrt(3/4)*[o,wx_noise, wy_noise, wz_noise])
{
	// rate of change of orientation
	Quaterniond qDot;
	qDot = (qEst*w).coeffs() * 0.5;
	
	// Jacobian of the objective function F
	MatrixXd J(3,4);
	J << 	-2*qEst.y(), 2*qEst.z(), -2*qEst.w(), 2*qEst.x(),
			 2*qEst.x(), 2*qEst.w(),  2*qEst.z(), 2*qEst.y(),
			 0,			-4*qEst.x(), -4*qEst.y(), 0;
	
	cout << J << endl;
	// The objective function F minimising a measured gravitational field with an assumed gravity vector of 0,0,1
	MatrixXd F(3,1);
	F << 	2*(qEst.x()*qEst.z() - qEst.w()*qEst.y()) - a.x(),
			2*(qEst.w()*qEst.x() + qEst.y()*qEst.z()) - a.y(),
			2*(0.5 - qEst.x()*qEst.x() - qEst.y()*qEst.y()) - a.z();		 
	
	cout << F << endl;
	// The gradient of the solution solution surface
	MatrixXd gradF(4,1);
	gradF = J.transpose() * F;

	//qEst = qEst + (qDot - beta*gradF.normalized)*deltaT
	qEst.coeffs() += (qDot.coeffs() - beta*gradF.normalized())*deltaT_sec;	
}

int main()
{   // Quaterniond specified in (w,x,y,z)
	Quaterniond qEst = Quaterniond(0,0,0,1); // unit z (normalized) // initial guess
	Quaterniond w = Quaterniond(0, M_PI*0.5, 0, 0); // pi/2 rad/s around x
	Quaterniond a = Quaterniond(0, 0, 0, 1); //(0, ax, ay, az) in m/s/s (normalized)
	AngleAxisd offset = AngleAxisd(M_PI/10,Vector3d::UnitX());
	a = a*offset;
	cout << "a: " <<endl << a.coeffs() <<endl;
	double deltaT = 0.01;
	double beta = 0.033;	
	UpdateAttitude(qEst, w, a, deltaT, beta);
	cout << "qEst:" << endl << qEst.coeffs() << endl;
	// manual quaternion multiplication
	Vector4d result;
	result << 
	qEst.w()*w.w() - qEst.x()*w.x() - qEst.y()*w.y() - qEst.z()*w.z() , 
	qEst.w()*w.x() + qEst.x()*w.w() + qEst.y()*w.z() - qEst.z()*w.y() , 
	qEst.w()*w.y() - qEst.x()*w.z() + qEst.y()*w.w() + qEst.z()*w.x() , 
	qEst.w()*w.z() + qEst.x()*w.y() - qEst.y()*w.x() + qEst.z()*w.w() ;

	cout << "manual qDot: " << endl << 0.5*result << endl;
}