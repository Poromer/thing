#include "pch.h"

namespace Utils
{

}

std::ostream& operator<<(std::ostream& os, AEVec2 rhs)
{
	os << "[" << rhs.x << "," << rhs.y << "]";
	return os;
}

AEVec2 operator-(AEVec2 lhs, AEVec2 rhs)
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	return lhs;
}

AEVec2 operator+(AEVec2 lhs, AEVec2 rhs)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	return lhs;
}

bool operator==(AEVec2 lhs, AEVec2 rhs)
{
	if (lhs.x == rhs.x && lhs.y == rhs.y)
		return true;
	return false;
}

bool operator!=(AEVec2 lhs, AEVec2 rhs)
{
	if (!(lhs == rhs))
		return true;
	return false;
}
