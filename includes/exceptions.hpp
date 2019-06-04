#ifndef AIRHOCKEY_EXCEPTIONS_HPP
#define AIRHOCKEY_EXCEPTIONS_HPP

#include <exception>
#include <iostream>

#define START_RED ("\033[1;31m")
#define END_RED ("\033[0m")

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

class SdlInitErr : public SdlErr
{
public:
    const char* what() const noexcept override;
};

#endif
