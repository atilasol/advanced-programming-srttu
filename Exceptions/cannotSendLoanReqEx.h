#ifndef CANNOTSENDLOANREQEX_H
#define CANNOTSENDLOANREQEX_H
#pragma once

#include <iostream>

class cannotSendLoanReqEx : std::exception
{
public:
	cannotSendLoanReqEx() noexcept = default;
	~cannotSendLoanReqEx() noexcept = default;

	virtual const char *what() const noexcept
	{
		return "### YOUR ACCOUNT DOES NOT HAVE THE POTENTIAL FOR GETTING LOAN ###";
	}
};
#endif