#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	ifstream inFile;
	ofstream outFile;

	string getEncrypt(ifstream& input);
	string getDecrypt(ifstream& input);

	string choice;
	int method = -1;

	cout << "Choose To [E]ncrypt or [D]ecrypt" << endl;
	
	while (method == -1) {
		getline(cin, choice);
		if (choice[0] == 'E') {
			method = 0;
		}
		else if (choice[0] == 'D') {
			method = 1;
		}
		else {
			cout << "Failed: Please choose either E or D" << endl;
		}
	}

	cout << "Enter a file name" << endl;
	getline(cin, choice);

	inFile.open(choice);

	if (!inFile.good())
	{
		cout << "File Error!" << endl;
		return 1;
	}
	
	string output = method == 0 ? getEncrypt(inFile) : getDecrypt(inFile);
	inFile.close();
	outFile.open(choice);
	outFile.write(output.c_str(), output.length());
	outFile.close();
}

string getEncrypt(ifstream& input) {
	char currCharacter;
	char charOut = '0';
	string returnVal = "";
	do
	{
		currCharacter = input.get();
		if (currCharacter == EOF)break;
		__asm {
			mov al, currCharacter
			ror al, 4
			xor al, 01011010
			ror al, 2
			xor al, 10101110
			ror al, 3
			mov charOut, al
		};
		returnVal += charOut;
	} while (!input.eof());
	return returnVal;
}

string getDecrypt(ifstream& input) {

	char currCharacter;
	char charOut = '0';
	string returnVal = "";
	do
	{
		currCharacter = input.get();
		if (currCharacter == EOF)break;
		__asm {
			mov al, currCharacter
			rol al, 3
			xor al, 10101110
			rol al, 2
			xor al, 01011010
			rol al, 4
			mov charOut, al
		};
		returnVal += charOut;
	} while (!input.eof());
	return returnVal;
}