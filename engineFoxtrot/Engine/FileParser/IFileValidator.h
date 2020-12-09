#pragma once

/// @brief Interface class for Video facade
class API IFileValidator
{
public:
	IFileValidator(string path, string validationPath) {};
	~IFileValidator() {};

	virtual bool documentIsValid() = 0;
private:

};
