#ifndef CUSTOMEREXISTEX_H
#define CUSTOMEREXISTEX_H
#pragma once

#include <iostream>

class customerExistEx : std::exception
{
public:
	customerExistEx() noexcept = default;
	~customerExistEx() noexcept = default;

	virtual const char *what() const noexcept
	{
		return "### THERE IS A CUSTOMER WITH THESE INFORMATION ###";
	}
};
#endif