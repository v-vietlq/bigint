#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class Qfloat
{
private:
	uint64_t data[2];
public:
	bool* readDec(string s);
	bool* readBin(string s);
	bool* readDecInt(string s);
	bool* readDecFloat(string s);
	bool* CoverttoTwoComPlement(bool *);
	bool* PlusTwoBit(bool *, bool*);
	bool* SubtractTwoBit(bool *, bool *);
	bool* DivideTwoBit(bool *, bool *);// chia dãy bit cho 1 dãy bit khác
	bool* ModTwoBit(bool*, bool*);
	void Init(bool *&);
	void ScanQfloat();
	void printbit(bool *a);
	string InttoString();
	string FloattoString();
	string DivStringInt(string s);
	string DivStringFloat(string s);
	string Covert(string a, string Coeficient1, string Coeficient2);
	string Output(const string &input);
	unsigned int PointPos(string s);
	string DivTwo(string s);
	string MultiTwo(string s);
	uint64_t Exp10(int);
	string NumberToString(uint64_t n);
	string PlusTwoString(string s1, string s2);
	string QfloatToString();
	bool* DivBitInt(bool*);
	bool* DivBitFloat(bool*);
	//bool* DivBitFloat2(bool*);
	int FindExp(bool *);
	int Find1(bool*);
	bool* SHR(bool *, int);
	bool* SHL(bool *a, int n);
	bool Other(bool *a, bool *b);
	bool* DectoBin();
	Qfloat BintoDec(bool *bit);
	void PrintQfloat();
	Qfloat();
	~Qfloat();
};

