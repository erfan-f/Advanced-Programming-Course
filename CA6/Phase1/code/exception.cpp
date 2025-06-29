#include "exception.hpp"


MethodException::MethodException(std::string text)
:runtime_error(text)
{
	message = text;
}


CommandException::CommandException(std::string text)
:runtime_error(text)
{
	message = text;
}

AcessibilityException::AcessibilityException(std::string text)
:runtime_error(text)
{
	message = text;
}

ArgumentException::ArgumentException(std::string text)
:runtime_error(text)
{
	message = text;
}

AvailabilityException::AvailabilityException(std::string text)
:runtime_error(text)
{
	message = text;
}