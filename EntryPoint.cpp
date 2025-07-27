#include <windows.h>
#include <iostream>
#include <string>
#include "RenderOnePixel.h"  // Make this header to declare RunRenderOnePixel
#include "RenderOneSquare.h" // Make this header to declare RunRenderOneSquare

enum TestToRun
{
    RUNRENDERONEPIXEL,
	RUNRENDERONESQUARE,
    RUNMAIN,
    END
};

//convert testToRun to string for output
std::string TestToRunToString(TestToRun test) {
	switch (test) {
	case RUNRENDERONEPIXEL: return "RUNRENDERONEPIXEL";
	case RUNMAIN: return "RUNMAIN";
	case RUNRENDERONESQUARE: return "RUNRENDERONESQUARE";
	default: return "UNKNOWN";
	}
}

int main() {
    TestToRun testToRun = RUNRENDERONEPIXEL;

	for (int i = 0; i < END; ++i) {
		std::cout << i << ": " << TestToRunToString((TestToRun)i) << std::endl;
	}

	std::string inputSTR;
	std::cin >> inputSTR;
	int input = std::stoi(inputSTR);

	if (input < 0 || input >= END) {
		std::cerr << "Invalid input. Exiting." << std::endl;
		return 1;
	}

    switch ((TestToRun)input) {
    case RUNRENDERONEPIXEL:
        RenderOnePixel::RunRenderOnePixel();
        break;
	case RUNRENDERONESQUARE:
		RenderOneSquare::RunRenderOneSquare();
    case RUNMAIN:
        // Placeholder for later
        break;
    default:
        break;
    }

    return 0;
}