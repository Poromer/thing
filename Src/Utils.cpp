#include "pch.h"

namespace Utils
{

}

std::ostream& operator<<(std::ostream& os, AEVec2 rhs)
{
	os << "[" << rhs.x << "," << rhs.y << "]";
	return os;
}
