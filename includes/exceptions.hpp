#ifndef AIRHOCKEY_EXCEPTIONS_HPP
#define AIRHOCKEY_EXCEPTIONS_HPP

#include <exception>
#include <iostream>

#define START_RED ("\033[1;31m")
#define END_RED ("\033[0m")
#define START_YELLOW ("\033[33m")
#define END_YELLOW ("\033[0m")
#define START_CYAN ("\033[36m")
#define END_CYAN ("\033[0m")

class SdlErr : public std::exception
{
public:
	SdlErr();
	explicit SdlErr(std::string & instr);
	explicit SdlErr(const char* instr);
	~SdlErr() noexcept override = default;
	SdlErr(const SdlErr &other);
	SdlErr &operator=(const SdlErr &other);
	const char* what() const noexcept override;

private:
	std::string  instr_;
};

/*class SdlImageErr : public SdlErr
{
public:
	explicit SdlImageErr() = default;
	explicit SdlImageErr(std::string & instr);
	~SdlImageErr() noexcept override = default;
	SdlImageErr(const SdlImageErr &other);
	SdlImageErr &operator=(const SdlImageErr &other);
	const char* what() const noexcept override;

private:
	std::string  instr_;
};*/

class SdlInitErr : public SdlErr
{
public:
	const char* what() const noexcept override;
};



#endif //AIRHOCKEY_EXCEPTIONS_HPP
