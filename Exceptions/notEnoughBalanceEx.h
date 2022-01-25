#ifndef NOTENOUGHBALANCEEX_H
#define NOTENOUGHBALANCEEX_H
#pragma once
	
class notEnoughBalanceEx  
{
public:
	notEnoughBalanceEx() noexcept = default;
	~notEnoughBalanceEx() noexcept = default;

	virtual const char *what() const noexcept
	{
		return "### THERE IS NOT ENOUGH MONEY IN THE ACCOUNT ###";
	}
};
#endif