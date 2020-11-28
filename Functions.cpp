#include "Header.h"

void CheckSinglePhrase()
{
	std::string a;
	while (a.length() == 0)
	{
		system("cls");
		std::cout << "Enter your phrase : ";
		std::getline(std::cin, a);
	}

	std::cout << "Length of original word : " << strlen(a.c_str()) << std::endl << std::endl;


	std::cout << "Compressing : " << std::endl;

	char b[4096] = {};
	char c[4096] = {};

	int newlength = smaz_compress((char*)a.c_str(), strlen(a.c_str()), b, sizeof(b));

	std::cout << "New length : " << newlength << std::endl;

	int change = (int)((double)(abs((int)((double)a.length() - (double)newlength))) * (double)((double)100 / (double)a.length()));

	if (a.length() >= newlength)
		std::cout << "Compressed by " << change << "%" << std::endl << std::endl;
	else
		std::cout << "Enlarged by " << change << "%" << std::endl << std::endl;

	/*for (int i = 0; i < strlen(b); i++)
	{
		std::cout << b[i];
	}

	std::cout << std::endl;*/

	std::cout << "Decompressing : " << std::endl;

	int decompr = smaz_decompress(b, newlength, c, sizeof(c));

	std::cout << "Old length : " << decompr << std::endl << "Phrase was : ";

	for (int i = 0; i < strlen(c); i++)
		std::cout << c[i];

	std::cout << std::endl;

	system("pause");
}