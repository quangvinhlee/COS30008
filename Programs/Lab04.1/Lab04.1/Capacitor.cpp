#define _USE_MATH_DEFINES

#include "Capacitor.h"
#include <cmath>
#include <cassert>

Capacitor::Capacitor(double aBaseValue) noexcept :
	ComponentBase(aBaseValue, "F", "Fmunp")
{
}

bool Capacitor::mustAdjust(double aValue) const noexcept
{
	return aValue <= 1.0;
}

const double Capacitor::getScalar() const noexcept
{
	return 1000;
}

double Capacitor::getReactance(double aFrequency) const noexcept
{
	assert(aFrequency != 0.0 && getBaseValue() != 0.0);
	return 1.0 / (2 * M_PI * aFrequency * getBaseValue());
}

