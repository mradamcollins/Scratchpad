#include <iostream>
#include <fstream>
#include <sstream>
#include <Eigen/Dense>
#include <Eigen/Geometry>

using namespace Eigen;

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
	
	
	// The objective function F minimising a measured gravitational field with an assumed gravity vector of 0,0,1
	MatrixXd F(3,1);
	F << 	2*(qEst.x()*qEst.z() - qEst.w()*qEst.y()) - a.x(),
			2*(qEst.w()*qEst.x() + qEst.y()*qEst.z()) - a.y(),
			2*(0.5 - qEst.x()*qEst.x() - qEst.y()*qEst.y()) - a.z();		 
	
	
	// The gradient of the solution solution surface
	MatrixXd gradF(4,1);
	gradF = J.transpose() * F;

	//qEst = qEst + (qDot - beta*gradF.normalized)*deltaT
	qEst.coeffs() += (qDot.coeffs() - beta*gradF.normalized())*deltaT_sec;	
}

bool getValues(std::istream& is, double& prevW, double& prevX, double& prevY, double& prevZ,
				double& gX, double& gY, double& gZ,
				double& aX, double& aY, double& aZ,
				double& period,
				double& w, double& x, double& y, double& z)
{
	if (!is.good()){
		return false;
	}
	std::string line;
	std::stringstream ss;
	getline(is, line);
	char c;

	ss.str(line);
	ss.clear();
	
	ss >> prevW >> c >> prevX >> c >> prevY >> c >> prevZ  >> c >> 
		 gX >> c >> gY >> c >> gZ >> c >> 
		 aX >> c >> aY >> c >> aZ >> c >> 
		 period >> c >> 
		 w >> c >> x >> c >> y >> c >> z ;
			
	return !ss.fail();
}

int main(int argc, char const *argv[])
{

	// if (argc < 2)
	// {
	// 	std::cerr << "You didn't pass in a valid file! try: " << argv[0] << " <filename.csv>" << std::endl;
	// 	exit 1;
	// }
	std::string filename("madgwick_data.csv");
	std::ifstream is(filename.c_str());
	if (!is.is_open()) {
		std::cerr << "Couldnt open " << filename << " ABORTING" <<std::endl;
		return 1;
	}
	Quaterniond qBaseline,qEst,qW,qA;
	double prevW, prevX, prevY, prevZ, gX, gY, gZ, aX, aY, aZ, period, w, x, y,z;
	double beta = 0.033;

	while (getValues(is, prevW, prevX, prevY, prevZ, gX, gY, gZ, aX, aY, aZ, period, w, x, y,z))
		{
			qBaseline = Quaterniond(w, x, y, z);

			qEst = Quaterniond(prevW, prevX, prevY, prevZ);
			qW = Quaterniond(0, gX, gY, gZ);
			qA = Quaterniond(0, aX, aY, aZ).normalized();
			UpdateAttitude(qEst,qW,qA,period,beta);
			
			// std::cout<< "est:" << std::endl << qEst.coeffs() << std::endl << "baseline: " << std::endl << qBaseline.coeffs() << std::endl << "err: " << std::endl << qBaseline.coeffs() - qEst.coeffs() << std::endl;
			// std::cout << qEst.isApprox(qBaseline) << std::endl;
			std::cout << qBaseline.w() - qEst.w() << "," <<
						qBaseline.x() - qEst.x() << "," <<
						qBaseline.y() - qEst.y() << "," <<
						qBaseline.z() - qEst.z() << std::endl;
		}
		

	is.close();
	return 0;
}