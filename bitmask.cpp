#include <iostream>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <bitset>
/**
 * A program to test the setting up of bit fields using enum values
 * and the resultant or-ing of those bitfields
 */
enum TRIGGER_SOURCES {
BUMP_LEFT,
BUMP_RIGHT,
START_STOP,
LIFT_DETECT_LEFT,
LIFT_DETECT_RIGHT,
CHARGER_DETECT,
BIN_PRESENCE,
FILTER_PRESENCE,
SPARE_CHANNEL,
DOWN_LOOKER_LEFT,
DOWN_LOOKER_RIGHT
};

int main(int argc, char *argv[])
{
	uint16_t enableMask {(1<<BUMP_LEFT) | (1<<BUMP_RIGHT) | (1<<LIFT_DETECT_RIGHT)};
	uint16_t triggerHighMask = {(1<<BUMP_LEFT) | (1<<LIFT_DETECT_LEFT)};

	uint16_t edgeMask = triggerHighMask & enableMask;
	
	std::cout << "Enable Mask:        " << ((std::bitset<16>)(enableMask)).to_string() << std::endl;
	std::cout << "Trigger bitfield:   " << ((std::bitset<16>)(triggerHighMask)).to_string() << std::endl;
	std::cout << "Resultant bitfield: " << ((std::bitset<16>)(edgeMask)).to_string() << std::endl;
	
	return 0; // success
}
