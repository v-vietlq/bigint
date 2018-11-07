#pragma once
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <fstream>

using namespace std;
class Qint
{
private:
	uint64_t data[2];

public:
	void ScanQint();
	void printQint();
	void Init(bool *&);
	bool* readDec(string s);
	bool* CoverttoTwoComPlement(bool *);
	bool *DectoBin();
	
	void printbit(bool *a);
	Qint BintoDec(bool *bit);
	string QinttoString();
	string DivTwo(string s);
	string Caculator(string a, string b, string Coefficient, string Cal);
	string Covert(string, string, string);
	string Output(const string &input);
	char* BinToHex(bool *);
	char* DecToHex();
	void printchar(char *);


	//Operator
	Qint operator/(const Qint &x);
	Qint operator*(const Qint &x);
	Qint operator-(const Qint &x);
	Qint operator+(const Qint &x);
	Qint operator=(const Qint &x);
	Qint operator&(const Qint &x);
	Qint operator|(const Qint &x);
	Qint operator^(const Qint &x);
	Qint operator~();
	Qint ROL(int n);
	Qint ROR(int n);
	Qint operator<<(int n);
	Qint operator>>(int n);
	

	//phép tính trên dãy bit
	bool* PlusTwoBit(bool *, bool *);
	bool* SubtractTwoBit(bool *, bool *);
	bool* DivideTwoBit(bool *,bool *);// chia dãy bit cho 1 dãy bit khác
	bool* ModTwoBit(bool*, bool*);
	bool* MultiTwoBit(bool *, bool *);

	// phép dịch, xoay trên bit
	bool* SHL(bool *, int n);
	bool* SHR(bool *, int n);
	bool* ROL(bool *, int n);
	bool* ROR(bool *, int n);

	// phep and or xor not tren bit
	bool* AND(bool *, bool *);
	bool* OR(bool *, bool *);
	bool* XOR(bool *, bool *);
	bool* NOT(bool *);


	bool Other(bool*, bool *);

	bool* ReadBin(string s);
	bool* ReadHex(string s);
	Qint();
	~Qint();
};


