#include "ComponentTester.h"

int main(int argc, char* argv[])
{
	ComponentTester componentTester((argc > 1 && argv[1] == std::string("-v")));

	componentTester.run();

	return 0;
}