#include"FibonacciSequenceGenerator.h"
#include<cassert>

FibonacciSequenceGenerator::FibonacciSequenceGenerator(const std::string& aID) noexcept :
	fID(aID),
	fPrevious(0),
	fCurrent(1)
{}

const std::string& FibonacciSequenceGenerator::id() const noexcept
{
	return fID;
}

const long long& FibonacciSequenceGenerator::operator*() const noexcept
{
	return fCurrent;
}

FibonacciSequenceGenerator::operator bool() const noexcept
{
	return hasNext();
}

void FibonacciSequenceGenerator::reset() noexcept
{
	fPrevious = 0;
	fCurrent = 1;
}

bool FibonacciSequenceGenerator::hasNext() const noexcept {
	return fCurrent + fPrevious >= 0;
}

void FibonacciSequenceGenerator::next() noexcept
{
	
	assert(fCurrent >= 0);
	long long nextFib = fPrevious + fCurrent;
	fPrevious = fCurrent;
	fCurrent = nextFib;
}