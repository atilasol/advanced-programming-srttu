public:
	customerExistEx() noexcept = default;
	~customerExistEx() noexcept = default;

	virtual const char *what() const noexcept
	{
		return "### THERE IS A CUSTOMER WITH THESE INFORMATION ###";
	}