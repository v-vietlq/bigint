#include "Qint.h"
#include "Qfloat.h"

int main(int argc, char* argv[])
{
	
	if (argc == 3)
	{
		string in(argv[1]);
		string out(argv[2]);

		ifstream fin; fin.open(in);
		ofstream fout; fout.open(out);

		if (fin.fail())
		{
			cout << in << "Does not exist! \n";
			return -1;
		}
		Qint  x;
		//Qfloat y;
		string temp;
		while (!fin.eof())
		{
			getline(fin, temp);
			fout << x.Output(temp) << endl;
			fflush(stdin);
		}
		cout << "Success! \n";

	}
	else
	{
		cout << "Invalid command line \n";
	}
	system("pause");
}