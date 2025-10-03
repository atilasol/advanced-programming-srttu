#ifndef EMPLOYEEEXISTEX_H
#define EMPLOYEEEXISTEX_H
#pragma once

#include <iostream>

class employeeExistEx : std::exception
{
public:
	employeeExistEx() noexcept = default;
	~employeeExistEx() noexcept = default;

	virtual const char *what() const noexcept
	{
		return "### THERE IS AN EMPLOYEE WITH THESE INFORMATION ###";
	}
};
#endif