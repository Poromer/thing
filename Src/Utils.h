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
AEVec2 operator-(AEVec2 lhs, AEVec2 rhs);
AEVec2 operator+(AEVec2 lhs, AEVec2 rhs);
bool operator==(AEVec2 lhs, AEVec2 rhs);
bool operator!=(AEVec2 lhs, AEVec2 rhs);