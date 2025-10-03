#ifndef ABOVEOVERTIMEREQUESTEX_H
#define ABOVEOVERTIMEREQUESTEX_H
#pragma once

#include <iostream>

class aboveOverTimeRequestEx : std::exception
{
public:
	aboveOverTimeRequestEx() noexcept = default;
	~aboveOverTimeRequestEx() noexcept = default;

	virtual const char *what() const noexcept
	{
		return "### YOU HAVE REACHED THE MAXIMUM OF REQUESTING OVER TIME ###";
	}
};
#endif