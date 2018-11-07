#include "Qfloat.h"


Qfloat::Qfloat()
{
}


Qfloat::~Qfloat()
{
}

// Khởi tạo dãy bit 128 phần tử
void Qfloat::Init(bool *&a)
{
	a = new bool[128];
	for (int i = 0; i < 128; i++)
		a[i] = 0; // khởi tọa dãy bit 0
}
unsigned int Qfloat::PointPos(string s)
{
	int pos = -1;
	for (unsigned int i = 0; i < s.length(); i++)
	{
		if (s[i] == '.')
			pos = i;
	}
	return pos;
}
string Qfloat::DivTwo(string s)
{
	string Result;
	int temp = 0;
	for (unsigned int i = 0; i < s.length(); i++)
	{
		temp = temp * 10 + (s[i] - '0');  // lấy từng phần tử từ đầu đến cuối chuỗi
		Result.push_back(temp / 2 + '0'); // chia 2
		temp = temp % 2;  // sau đó lấy dư 
	}
	if (Result[0] == '0')
	{
		Result.erase(Result.begin());  // xóa số 0 ở đầu chuỗi
	}
	return Result;
}
string Qfloat::MultiTwo(string s)
{
	string Result;
	int temp = 0;
	for (int i = s.length() - 1; i >= 0; i--)
	{
		temp = temp + (s[i] - '0') * 2;
		Result.push_back(temp % 10 + '0');
		temp /= 10;

	}
	reverse(Result.begin(), Result.end());
	/*if (Result[0] == '0' && Result[1] == '0')
		Result.erase(Result.begin()); */ // xóa số 0 ở đầu chuỗi
	/*if (Result[0] != '0')
		Result.insert(Result.begin(), '1');*/

	return Result;
}
bool* Qfloat::CoverttoTwoComPlement(bool *a)
{
	for (int i = 0; i < 128; i++)
	{
		a[i] = !a[i];  // chuyển về dạng bù 1
	}
	a = PlusTwoBit(a, readDecInt("1"));  // bù 2= bù 1 công cho 1
	return a;

}
bool* Qfloat::PlusTwoBit(bool *a, bool* b)
{
	bool *Result = NULL;
	Init(Result); // dãy lưu kết quả
	bool bitRemember = 0;  // bit nhớ
	for (int i = 127; i >= 0; i--) // chạy từ cuối mảng về
	{
		int temp = a[i] + b[i] + bitRemember;  // tính tổng 
		Result[i] = temp % 2;  // lấy phần dư khia chia cho 2
		if (temp >= 2)  // nếu mà cộng lại >=2 thì bit nhớ là 1
			bitRemember = 1;
		else
			bitRemember = 0;

	}
	return Result;  // trả về kết quả là tổng 
}
bool* Qfloat::SubtractTwoBit(bool *a, bool *b)
{
	bool* temp = new bool[128]; // dùng dãy tạm lưu trữ dãy bit b
	for (int i = 0; i < 128; i++)
		temp[i] = b[i];
	return PlusTwoBit(a, CoverttoTwoComPlement(temp));  // phép trừ được đổi thành cộng cho bù 2
}

// phép chia 2 dãy bit
bool* Qfloat::DivideTwoBit(bool *a, bool *b)
{
	bool *temp = NULL;
	Init(temp);
	bool *Result = NULL;
	Init(Result);
	bool isNagative = false;
	if (a[0] != b[0]) // kiểm tra có âm hay không
		isNagative = true;
	if (a[0] == 1) a = CoverttoTwoComPlement(a); // là số âm chuyển về dạng bù 2
	if (b[0] == 1) b = CoverttoTwoComPlement(b); // là số âm chuyển về dạng bù 2

	for (int i = 127; i >= 0; i--)
	{
		temp = SHL(temp, 1); temp[127] = a[127 - i];  // dịch trái dãy bit dư , gán bit cuối từ đầu a đến cuối a
		Result = SHL(Result, 1);  // dịch trái bit kết quả
		temp = SubtractTwoBit(temp, b);  // kiểm tra xem hiệu phép có âm không
		if (temp[0] == 1)   // nếu <0 thì k chia dc
		{
			temp = PlusTwoBit(temp, b);  // cộng lại
			Result[127] = 0;   // gán bit cuối kq =0
		}
		else Result[127] = 1;  // ngược lại thì bit cuối kq=1

	}

	if (isNagative == true)
		Result = CoverttoTwoComPlement(Result);  // nếu là số âm thì bù 2 lại
	return Result;  // trả về thương
}

// phép chia lấy dư 2 dãy bit
bool* Qfloat::ModTwoBit(bool *a, bool *b)
{
	bool *temp = NULL;
	Init(temp); // khởi tạo dãy bit dư

	bool *Result = NULL;
	Init(Result); // khởi tạo dãy bit kêt quả của phép chia

	if (a[0] == 1) a = CoverttoTwoComPlement(a); // là số âm chuyển về dạng bù 2
	if (b[0] == 1) b = CoverttoTwoComPlement(b); // là số âm chuyển về dạng bù 2

	for (int i = 127; i >= 0; i--)
	{
		temp = SHL(temp, 1); temp[127] = a[127 - i]; // dịch trái dãy bit dư , gán bit cuối từ đầu a đến cuối a
		Result = SHL(Result, 1); // dịch trái bit kết quả
		temp = SubtractTwoBit(temp, b);  // kiểm tra xem hiệu phép có âm không
		if (temp[0] == 1)  // nếu <0 thì k chia dc
		{
			temp = PlusTwoBit(temp, b); // cộng lại
			Result[127] = 0;  // gán bit cuối kq =0
		}
		else Result[127] = 1; // ngược lại thì bit cuối kq=1

	}
	return temp;  // trả về bit dư
}
bool* Qfloat::readDecInt(string s)
{
	bool *bit = NULL;
	Init(bit);
	bool isNegative = false;
	if (s[0] == '-')  // đọc chuỗi vào nếu là số âm 
	{
		isNegative = true;
		s.erase(s.begin());  // xóa nó đi
	}
	int k = 127;
	while (s.length() != 0)
	{
		bit[k] = (s[s.length() - 1] - '0') % 2; // lấy phần dư của số cuối cùng của chuỗi cho 2
		k--;
		s = DivTwo(s);  // chia chuỗi cho 2
	}
	if (isNegative)
	{
		bit = CoverttoTwoComPlement(bit);  // nếu là số âm thì chuyển về dạng bù 2 lại
	}
	return bit;
}
bool* Qfloat::readDecFloat(string s)
{
	bool* bit = NULL;
	Init(bit);
	int k = 0;
	while (k < 128)
	{
			s = MultiTwo(s);
			bit[k] = s[0] - '0';
			k++;
			if (s[0] == '1')
				s[0] = '0';

	}
	return bit;
}
bool* Qfloat::SHR(bool *a, int n)
{
	bool* bit = NULL;
	Init(bit);
	for (int i = 0; i < 128 - n; i++)
	{
		bit[i + n] = a[i];     //  dịch n bit thì bit i cộng n sẽ là bit a[i]
	}
	return bit;
}
bool* Qfloat::SHL(bool *a, int n)
{
	bool *bit = NULL;
	Init(bit);
	for (int i = 0; i < 128 - n; i++)
	{
		bit[i] = a[i + n];    // bit i là bit thứ a[i+n]
	}
	return bit;
}
bool* Qfloat::readDec(string s)
{
	bool* Result = NULL;
	Init(Result);
	string s1;
	string s2;
	s1 = DivStringInt(s);
	s2 = DivStringFloat(s);
	bool* tempInt = readDecInt(s1);
	bool* tempFloat = readDecFloat(s2);
	if (tempInt[0] == 1)
	{
		Result[0] = 1;
		tempInt = CoverttoTwoComPlement(tempInt);
	}
	else
		Result[0] = 0;
	int pos = Find1(tempInt);
	if (pos != -1)
	{
		int Exp = 127 - pos;
		while (Exp>0)
		{
			//tempInt[pos] = 0;
			tempFloat = SHR(tempFloat, 1);
			tempFloat[0] = tempInt[127];
			tempInt = SHR(tempInt, 1);
			
			
			Exp--;
		}
		for (int i = 15; i >=1; i--)
		{
			Result[i] = ((127 - pos+16383) >> (15 - i)) & 1;
		}
		for (int i = 16; i <=127; i++)
		{
			//int j = i - 16;
			Result[i] = tempFloat[i-16];
		}

	}
	else
	{
		int posfloat = Find1(tempFloat)+1;
		tempFloat = SHL(tempFloat, posfloat);
		//tempFloat[posfloat] = 1;
		for (int i = 15; i >= 1; i--)
		{
			Result[i] = ((-posfloat+16383) >> (15 - i)) & 1;
		}
		for (int i = 16; i <= 127; i++)
		{
			Result[i] = tempFloat[i-16];
		}
	}

	return Result;
}
int Qfloat::Find1(bool *a)
{
	int pos = -1;
	for (int i = 0; i < 128; i++)
		if (a[i] == 1)
		{
			pos = i;
			break;
		}
	return pos;
}
string Qfloat::DivStringInt(string s)
{
	string s1;
	unsigned int pos = PointPos(s);
	if (pos == -1)
		s1 = s;
	else
	for (unsigned int i = 0; i < pos; i++)
		s1.push_back(s[i]);
	return s1;
}
string Qfloat::DivStringFloat(string s)
{
	string s1;
	unsigned int pos = PointPos(s);
	if (pos == -1)
		s1 = '0';
	else
	for (unsigned int i = pos + 1; i < s.length(); i++)
		s1.push_back(s[i]);

	s1.insert(s1.begin(), '0');
	return s1;
}
void Qfloat::printbit(bool *a)
{
	for (int i = 0; i < 128; i++)
		cout << a[i];
}

void Qfloat::ScanQfloat()
{
	string s;
	cout << " Enter of big num : ";
	fflush(stdin);
	getline(cin, s);
	*this = BintoDec(readDec(s));


}
void Qfloat::PrintQfloat()
{
	cout<<this->QfloatToString();
}
int Qfloat::FindExp(bool *a)
{
	int exp = 0;
	for (int i = 15; i >= 1; i--)
	{
		exp = exp | (a[i] << (15 - i));
	}
	return  exp-16383;
}
bool* Qfloat::DivBitInt(bool *a)
{
	bool isNagative = false;
	if (a[0] == 1)
		isNagative = true;

	int Exp = FindExp(a);
	bool *temp = NULL;
	Init(temp);
	bool* Result = NULL;
	Init(Result);
	Result[127] = 1;
	for (int i = 0; i < 128; i++)
	{
		if (i + 16 < 128)
			temp[i] = a[i + 16];
		else
			temp[i] = 0;
	}
	while (Exp>0)
	{
		Result = SHL(Result, 1); Result[127] = temp[0];
		temp = SHL(temp, 1);
		Exp--;
	}
	if (isNagative == true)
		Result=CoverttoTwoComPlement(Result);
	return Result;
}
bool* Qfloat::DivBitFloat(bool *a)
{
	int Exp = FindExp(a);
	bool *temp = NULL;
	Init(temp);
	for (int i = 0; i < 128; i++)
	{
		if (i + 16 < 128)
			temp[i] = a[i + 16];
		else
			temp[i] = 0;
	}
	temp = SHL(temp, Exp);
	return temp;
}
string Qfloat::QfloatToString()
{
	string s;
	bool *temp = this->DectoBin();
	bool*Result1 = DivBitInt(temp);
	bool*Result2 = DivBitFloat(temp);
	Qfloat a = BintoDec(Result1);
	Qfloat b = BintoDec(Result2);
	string s1 = a.InttoString();
	string s2 = b.FloattoString();
	return s1 + s2;
}
bool* Qfloat::DectoBin()
{

	bool* bit = NULL;
	Init(bit);
	for (int i = 0; i < 2; i++)
	{
		uint64_t n = this->data[i]; // lấy từng số ra
		int j = 64 * (i + 1) - 1;  // nếu là số đầu thì chỉ có từ 0-63, số 2  từ 64-127
		while (n > 0)
		{
			bit[j--] = n % 2;
			n = n / 2;
		}
	}
	return bit;
}
Qfloat Qfloat::BintoDec(bool *bit)
{
	Qfloat Result;
	Result.data[0] = 0;
	Result.data[1] = 0;

	for (int i = 0; i < 128; i++)
	{
		int pos = i / 64;
		if (bit[i] == 1)
			Result.data[pos] = Result.data[pos] | ((uint64_t)1 << 63 - (i - pos * 64)); // lưu vào 2 số kiểu unsigned int64
	}

	return Result;

}
string Qfloat::InttoString()
{
	string s;
	bool isNagative = false;
	bool *temp = this->DectoBin();  // chuyển về dãy nhị phân 
	if (temp[0] == 1)
	{
		isNagative = true;   // nếu là số âm thì đúng
		temp = CoverttoTwoComPlement(temp);  // đưa về dạng bù 2 để có số dương
	}
	bool *temp10 = readDecInt("10");  // tạo dãy nhị phân của số 10
	while (Other(temp, readDecInt("0")))  // kiểm tra dãy đã bằng 0 hay chưa
	{
		Qfloat t = BintoDec(ModTwoBit(temp, temp10));  // tìm số dư
		s = s + (char)(t.data[1] + '0');  // cộng chuỗi với số dư đó
		temp = DivideTwoBit(temp, temp10);  // chia chuỗi cho 2
	}
	reverse(s.begin(), s.end()); // đão chuỗi lại
	if (isNagative)
		s.insert(s.begin(), '-');  // là số âm thì thêm dấu trừ
	return s;

}
uint64_t Qfloat::Exp10(int i)
{
	if (i == 0) return 1;
	return 10 * Exp10(i - 1);
}
string Qfloat::PlusTwoString(string s1, string s2)
{
	string Result;
	int stringRemember = 0;
	for (int i = s1.length() - 1; i >= 0; i--)
	{
		int temp = (s1[i] - '0') + (s2[i] - '0')+stringRemember;
		Result.push_back(temp%10 + '0');
		stringRemember = temp / 10;
	}
	reverse(Result.begin(), Result.end());
	return Result;
}
string Qfloat::FloattoString()
{
	string s;
	long double n = 0;
	bool*temp = this->DectoBin();
	for (int i = 0; i <=128 ; i++)
	{
		if (temp[i] == 1)
		{
			n = n + pow(2, -(i + 1));
		}
	}
	uint64_t a = n * Exp10(6);
	s = NumberToString(a);
	s.insert(s.begin(), '.');
	return s;
}
string Qfloat::NumberToString(uint64_t n)
{
	string s;
	while (n > 0)
	{
		int temp = n % 10;
		s.push_back(temp+'0');
		n = n / 10;
	}
	reverse(s.begin(), s.end());
	return s;
}
bool Qfloat::Other(bool *a, bool *b)
{
	Qfloat temp1 = BintoDec(a); // chuyển dãy a về kiểu Qint
	Qfloat temp2 = BintoDec(b); // chuyễn dãy b về kiểu Qint
	if (temp1.data[0] == temp2.data[0] && temp1.data[1] == temp2.data[1]) // kiểm tra có trùng không
		return false;
	return true;
}
bool* Qfloat::readBin(string s)
{
	bool* bit = NULL;
	Init(bit);
	int n = s.length();
	int k = 128 - n;
	for (int i = 0; i < n; i++)
		bit[k++] = s[i] - '0';
	return bit;
}
string Qfloat::Covert(string a, string Coeficient1, string Coeficient2)
{
	string Result;
	if (Coeficient1 == "2" && Coeficient2 == "10")
	{
		bool *temp = readBin(a);
		Qfloat x = x.BintoDec(temp);
		Result = x.QfloatToString();
	}
	
	else if (Coeficient1 == "10" && Coeficient2 == "2")
	{
		bool* bit = readDec(a);
		for (int i = 0; i < 128; i++)
			Result = Result + (char)(bit[i] + '0');
	}

	return Result;
}
string Qfloat::Output(const string &input)
{
	
		string coefficient1, coefficient2, a;
		unsigned int i = 0;
		while (input[i] != ' ')
			coefficient1 += input[i++];
		++i;
		while (input[i] != ' ')
			coefficient2 += input[i++];
		++i;
		while (i<input.length())
			a += input[i++];
		return Covert(a, coefficient1, coefficient2);
	
}