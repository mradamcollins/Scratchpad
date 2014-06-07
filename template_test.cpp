#include <iostream>
struct Register {
    enum class MODE {
        STANDBY,
        ACTIVE
    };

    enum class TILT {
        BACK,
        FRONT
    };
};


int main (int argc, char* argv[])
{
    printf("hello World\n");
    // write(Register::MODE::STANDBY);
    return 0;

}
