#include "pch.h"

template <typename T>
void tprint(T const& toPrint, std::string prefix = "")
{
	std::cout << prefix << ": " << toPrint << std::endl;
}

namespace Utils
{

}

std::ostream& operator<<(std::ostream& os, AEVec2 rhs);