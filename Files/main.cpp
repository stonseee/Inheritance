#include<iostream>
#include<fstream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

//#define WRITE_TO_FILE
#define READ_FROM_FILE

void main()
{
	setlocale(LC_ALL, "");
#ifdef WRITE_TO_FILE
	cout << "Hello Files" << endl;

	std::ofstream fout;                                  //создать поток
	fout.open("File.txt", std::ios_base::app);           //открыть поток
	fout << "Hello Files" << endl;                       //писать в поток
	fout << "Привет" << endl;                       //писать в поток
	fout.close();                                        //закрыть поток

	system("notepad File.txt");
#endif // WRITE_TO_FILE

	std::ifstream fin("File.txt"); //создание и открытие 
	if (fin.is_open())             
	{
		while (!fin.eof()) //пока не конец файла читать поток
		{
			const int SIZE = 1024000;
			char buffer[SIZE]{};
			//fin >> buffer;     //до пробела
			fin.getline(buffer, SIZE);
			cout << buffer << endl;
		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: File not found" << endl;
	}
}