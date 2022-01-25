#ifndef ACCOUNTISNOTACTIVEEX_H
#define ACCOUNTISNOTACTIVEEX_H

#pragma once
#include <iostream>

class accountIsNotActiveEx : std::exception
{
public:
	accountIsNotActiveEx() noexcept = default;
	~accountIsNotActiveEx() noexcept = default;

	virtual const char* what() const noexcept
	{
		return "### ACCOUNT IS NOT ACTIVE ###";
	}
};
#endif