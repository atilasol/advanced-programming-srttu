#ifndef USERNAMEEXISTEX_H
#define USERNAMEEXISTEX_H
#pragma once

#include <iostream>

class usernameExistEx : std::exception
{
public:
	usernameExistEx() noexcept = default;
	~usernameExistEx() noexcept = default;

	virtual const char *what() const noexcept
	{
		return "### USERNAME TAKEN , PLEASE CHOOSE ANOTHER USERNAME ###";
	}
};
#endif