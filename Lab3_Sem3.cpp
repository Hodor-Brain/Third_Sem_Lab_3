#include "Header.h"

int main()
{
	while (true)
	{
		system("cls");

		std::cout << "0 - Exit" << std::endl;
		std::cout << "1 - Check your phrase on compressing and decompressing" << std::endl;
		std::cout << "2 - Compress the file" << std::endl;
		std::cout << "3 - Decompress the file" << std::endl;

		int key = -1;
		bool isExit = false;

		std::cin >> key;

		switch (key)
		{
		case 0:
			system("cls");
			isExit = true;
			break;
		case 1:
			system("cls");
			CheckSinglePhrase();
			break;
		case 2:
			system("cls");
			CompressFile();
			break;
		case 3:
			system("cls");
			DecompressFile();
			break;
		default:
			break;
		}

		if (isExit)
			break;
	}

	std::cout << "Good luck";
}
