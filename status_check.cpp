#include <iostream>
#include <string>

std::string getTiltStatus(int tilt)
{
				std::string status("");
				uint back_front = (tilt & 3);       // tilt - bits 0:1
				uint orientation = (tilt & 28)>>2;  // tilt - bits 2:4
				uint tap = (tilt & 32)>>5;          // tilt - bits 5
				uint alert = (tilt & 64)>>6;        // tilt - bits 6
				uint shake = (tilt & 128)>>7;       // tilt - bits 7

				if (back_front == 0)        status.append("|").append("UNKNOWN_FRONT_BACK");
				else if (back_front == 1)   status.append("|").append("FRONT");
				else if (back_front == 2)   status.append("|").append("BACK");

				if (orientation == 0)       status.append("|").append("UNKNOWN_ORIENTATION");
				else if (orientation == 1)  status.append("|").append("LEFT");
				else if (orientation == 2)  status.append("|").append("RIGHT");
				else if (orientation == 3)  status.append("|").append("DOWN");
				else if (orientation == 4)  status.append("|").append("UP");

				if (tap == 1)               status.append("|").append("TAP");

				if (alert == 1)             status.append("|").append("ALERT");

				if (shake == 1)             status.append("|").append("SHAKE");

				status.append("|");
				return status;
}

int main(int argc, char* argv[])
{
	std::cout << "Hello World!" << std::endl;

	for (int i = 0 ; i < 128; ++i)
	{
					std::cout <<i <<" " << getTiltStatus(i) <<std::endl;
	}
	return 0; //success
}


