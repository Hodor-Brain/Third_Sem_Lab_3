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

void CompressFile()
{
	std::string a;
	while (a.length() == 0)
	{
		system("cls");
		std::cout << "Enter name of file : ";
		std::getline(std::cin, a);
	}

	a.insert(a.length(), ".TXT");

	std::cout << a;
	
	FILE* file;
	FILE* input;
	char buffer[100];
	char compressed[400];
	char decomr[400];

	int oldlength = 0, newlength = 0;

	fopen_s(&file, a.c_str(), "r");
	fopen_s(&input, "CompressedText", "wb");
	if (file == NULL) perror("Error opening file");
	else
	{
		while (!feof(file))
		{
			if (fgets(buffer, 100, file) == NULL) break;
			//fputs(buffer, stdout);
			oldlength += strlen(buffer);

			if (buffer[strlen(buffer)] == EOF)
			{
				oldlength--;
				buffer[strlen(buffer)] = '\0';
			}

			int templength = smaz_compress(buffer, strlen(buffer), compressed, sizeof(compressed));

			/*int tl = smaz_decompress(compressed, templength, decomr, sizeof(decomr));

			for (int i = 0; i < tl; i++)
				std::cout << decomr[i];*/
			
			for (int i = 0; i < templength; i++)
				fputc(compressed[i], input);

			newlength += templength;
		}
		fclose(file);
		fclose(input);
	}

	std::cout << std::endl << std::endl << "Symbols in original file : " << oldlength << std::endl << "Symbols after compressing : " << newlength << std::endl << std::endl;

	int change = (int)((double)(abs((int)((double)oldlength - (double)newlength))) * (double)((double)100 / (double)oldlength));

	if (oldlength >= newlength)
		std::cout << "Compressed by " << change << "%" << std::endl << std::endl;
	else
		std::cout << "Enlarged by " << change << "%" << std::endl << std::endl;

	std::cout << "All compressed data is located in 'CompressedText' file" << std::endl << std::endl;

	system("pause");
}


void DecompressFile()
{
	std::string a;
	while (a.length() == 0)
	{
		system("cls");
		std::cout << "Enter name of file : ";
		std::getline(std::cin, a);
	}

	std::cout << a << std::endl;

	FILE* file;
	FILE* input;
	char buffer[100];
	char decompressed[400];

	fopen_s(&file, a.c_str(), "rb");
	fopen_s(&input, "DecompressedText.TXT", "w");

	struct stat st;
	stat(a.c_str(), &st);
	int size = st.st_size;

	int fullreads = size / 99;
	int partread = size % 99;

	if (file == NULL) perror("Error opening file");
	else
	{
		int reads = 0;

		while (true)
		{
			reads++;

			int symb = 0;

			if (reads != fullreads + 1)
			{
				buffer[99] = '\0';
				symb = 99;
			}
			else
				symb = partread;


			for (int i = 0; i < symb; i++)
			{
				char c;
				c = fgetc(file);
				buffer[i] = c;
			}

			/*if (fgets(buffer, 100, file) == NULL) break;
			fputs(buffer, stdout);*/

			int templength = smaz_decompress(buffer, symb, decompressed, sizeof(decompressed));

			for (int i = 0; i < templength; i++)
			{
				fputc(decompressed[i], input);
				//fputc(decompressed[i], stdout);
			}

			if (symb == partread)
				break;
		}
		fclose(file);
		fclose(input);
	}

	std::cout << std::endl << "Successfully decompressed, you can find decompressed data in 'DecompressedText.TXT' file" << std::endl << std::endl;

	system("pause");
}