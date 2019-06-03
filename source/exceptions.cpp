#include "exceptions.hpp"

SdlErr::SdlErr()
{
	std::cout << START_RED << "SDL error: ";//TODO закрыть
}

SdlErr::SdlErr(std::string &instr) : instr_(instr)
{}

SdlErr::SdlErr(const char* instr) : instr_(instr) {}

SdlErr& SdlErr::operator=(const SdlErr &other)
{
	if (this != &other)
		instr_ = other.instr_;
	return (*this);
}

SdlErr::SdlErr(const SdlErr &other)
{
	*this = other;
}

const char* SdlErr::what() const noexcept
{
	return (instr_.c_str());
}

/*SdlImageErr::SdlImageErr(std::string & instr) : instr_(instr) {
	instr_.insert(0, "Unable to load image ");
}

SdlImageErr& SdlImageErr::operator=(const SdlImageErr &other) {
	if (this != &other)
		instr_ = other.instr_;
	return (*this);
}

SdlImageErr::SdlImageErr(const SdlImageErr &other) {
	*this = other;
}

const char* SdlImageErr::what() const noexcept{
	return (instr_.c_str());
}
*/
const char* SdlInitErr::what() const noexcept
{
	return ("SDL_Init Error: ");
}

