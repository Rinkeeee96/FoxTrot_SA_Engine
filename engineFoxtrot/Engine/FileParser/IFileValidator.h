#pragma once

/// @brief Interface class for Video facade
class API IFileValidator
{
public:
	IFileValidator(string path, string validationPath) {};
	~IFileValidator() {};

	/// @brief Checks if document is valid.
	/// @return 
	virtual bool documentIsValid() = 0;
private:

};
