#include <iostream>
#include <Windows.h>


int main()
{
	HINSTANCE load;
	load = LoadLibrary(L"sha-1.dll");
	typedef std::string(*str) (const std::string&);
	str sha1;
	sha1 = (str)GetProcAddress(load, "sha1");


	std::string message = "Hello, SHA-1!";
	std::string sha1Hash = sha1(message);

	std::cout << "Message: " << message << std::endl;
	std::cout << "SHA-1 Hash: " << sha1Hash << std::endl;

	FreeLibrary(load);

	system("pause");
	return 0;
}