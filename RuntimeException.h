#ifndef RUNTIMEEXCEPTION_H_
#define RUNTIMEEXCETPTION_H_

#include<iostream>
#include<string>

using namespace std;

class RuntimeException
{
	private:
		string errorMsg;
	
	public:
		RuntimeException(const string& err) {errorMsg = err;}
		string getMessage() const {return errorMsg;}
};

inline std::ostream& operator << (ostream& out, const RuntimeException& e)
{
	out << e.getMessage();
	return out;
}

#endif