#include <iostream>
#include <cstdint>

/**
 * Verify the output of casting an 8bit unsigned int to a signed 6bit
 * Number. This is how data is represented on the MMA7660FC Accelerometer
 *
 * This program checks that the bit-twiddling works as expected
 */

struct Accel
{
	int data:6;
};

int main(int argc, char* argv[])
{
 Accel accel;
 for (uint8_t i = 0; i < 65; ++i)
 {
				 accel.data = i;
				 std::cout << (int)i  << " -> " << accel.data <<std::endl;
 }
	return 0; //success
}


