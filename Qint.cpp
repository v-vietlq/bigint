#include "Qint.h"


// Constructor
Qint::Qint()
{
	this->data[0] = 0;
	this->data[1] = 0;
}

Qint::~Qint()
{
}
// Khởi tạo 128 bit =0
void Qint::Init(bool *&a)
{
	a = new bool[128];
	for (int i = 0; i < 128; i++)
	{
		a[i] = 0; // khởi tạo 128 bit bằng 0 
	}
}

// Hàm chuyển bit về dạng bù 2
bool* Qint::CoverttoTwoComPlement(bool *a)
{
	for (int i = 0; i < 128; i++)
	{
		a[i] = !a[i];  // chuyển về dạng bù 1
	}
	a = PlusTwoBit(a, readDec("1"));  // bù 2= bù 1 công cho 1
	return a;

}
// Hàm chia chuỗi cho 2
string Qint::DivTwo(string s)
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

// Hàm chuyển một chuỗi thành dãy nhị phân
bool* Qint::readDec(string s)
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

// Hàm chuyển dãy nhị phân thành kiểu Qint
Qint Qint::BintoDec(bool *bit)
{
	Qint Result;
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
/*bool* Qint::DectoBin()
{

	bool* bit = NULL;
	Init(bit);
	for (int i = 127; i >= 64; i--)
	{
		bit[i] = (this->data[1] >> (127 - i))& (uint64_t)1;
	}
	for (int i = 63; i >= 0; i--)
	{
		bit[i] = (this->data[0] >> (63 - i))& (uint64_t)1;
	}


	return bit;

}*/

// Hàm chuyển kiểu Qint thành dãy nhị phân
bool* Qint::DectoBin()
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

// Hàm chuyển hệ 2 sang hệ 16
char* Qint::BinToHex(bool *a)
{
	char s[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' }; // khởi tạo mảng char gôm 16 kí tự
	char*Hex = new char[33];
	int temp = 0;
	for (int i = 0; i < 128; i += 4)  // gôm 4 bit lại 
	{
		int x = a[i] * 8 + a[i + 1] * 4 + a[i + 2] * 2 + a[i + 3];  // tính giá trị của 4 bit 
		Hex[temp] = s[x];  // gán 
		temp++;
	}
	Hex[temp] = NULL;
	return Hex;
}
// Hàm chuyển từ hệ 10 sang hệ 16
char* Qint::DecToHex()
{
	bool *temp = this->DectoBin();  // chuyển về nhị phân 
	return this->BinToHex(temp);   // từ nhị phân về hệ 16
}

// Hàm nhập Qint
void Qint::ScanQint()
{
	string s;
	cout << " Enter of big num : ";
	fflush(stdin);
	getline(cin, s);
	
	
	*this = BintoDec(readDec(s));

}

// Hàm xuất Qint
void Qint::printQint()
{
	cout << QinttoString();
}

// HÀm chuyển từ kiểu Qint sang chuỗi
string Qint::QinttoString()
{
	string s;
	bool isNagative = false;
	bool *temp = this->DectoBin();  // chuyển về dãy nhị phân 
	if (temp[0] == 1)
	{
		isNagative = true;   // nếu là số âm thì đúng
		temp = CoverttoTwoComPlement(temp);  // đưa về dạng bù 2 để có số dương
	}
	bool *temp10 = readDec("10");  // tạo dãy nhị phân của số 10
	while (Other(temp,readDec("0")))  // kiểm tra dãy đã bằng 0 hay chưa
	{
		Qint t = BintoDec(ModTwoBit(temp, temp10));  // tìm số dư
		s = s + (char)(t.data[1] + '0');  // cộng chuỗi với số dư đó
		temp = DivideTwoBit(temp, temp10);  // chia chuỗi cho 2
	}
	reverse(s.begin(), s.end()); // đão chuỗi lại
	if (isNagative)
		s.insert(s.begin(), '-');  // là số âm thì thêm dấu trừ
	return s;

}
string Qint::Caculator(string a, string b, string Coefficient, string cal)
{
	Qint x, y, z;
	if (Coefficient == "2")
	{
		x = BintoDec(ReadBin(a));
		y = BintoDec(ReadBin(b));
	}
	if (Coefficient == "10")
	{
		x = BintoDec(readDec(a));
		y = BintoDec(readDec(b));
	}
	if (Coefficient == "16")
	{
		x = BintoDec(ReadHex(a));
		y = BintoDec(ReadHex(b));
	}
	if (cal == "+") z = x + y;
	else if (cal == "-") z = x - y;
	else if (cal == "*") z = x * y;
	else if (cal == "/") z = x / y;
	else if (cal == "&") z = x & y;
	else if (cal == "^") z = x ^ y;
	else if (cal == "|") z = x | y;
	else if (cal == ">>") z = x >> (int) y.data[1];
	else if (cal == "<<") z = x << (int) y.data[1];
	else if (cal == "rol") z = x.ROL((int)y.data[1]);
	else if (cal == "ror") z = x.ROR((int)y.data[1]);
	if (Coefficient == "10")
		return z.QinttoString();
	else
		return Covert(z.QinttoString(), "10", Coefficient);

}
string Qint::Covert(string a, string Coeficient1, string Coeficient2)
{
	string Result;
	if (Coeficient1 == "2" && Coeficient2 == "10")
	{
		bool *temp = ReadBin(a);
		Qint x = x.BintoDec(temp);
		Result = x.QinttoString();
	}
	else if (Coeficient1 == "2" && Coeficient2 == "16")
	{
		string temp=BinToHex(ReadBin(a));
		Result = temp;
	}
	else if (Coeficient1 == "2" && Coeficient2 == "~")
	{
		bool* bit = NOT(ReadBin(a));
		for (int i = 0; i < 128; i++)
			Result = Result + (char)(bit[i] + '0');
	}
	else if (Coeficient1 == "10" && Coeficient2 == "2")
	{
		bool* bit = readDec(a);
		for (int i = 0; i < 128; i++)
			Result = Result + (char)(bit[i] + '0');
	}
	else if (Coeficient1 == "10" && Coeficient2 == "16")
	{
		bool*bit = readDec(a);
		string temp =BinToHex(bit);
		Result = temp;
	}
	else if (Coeficient1 == "10" && Coeficient2 == "~")
	{
		bool *bit = NOT(readDec(a));
		Qint x = x.BintoDec(bit);
		Result = x.QinttoString();
	}
	else if (Coeficient1 == "16" && Coeficient2 == "2")
	{
		bool* bit = ReadHex(a);
		for (int i = 0; i < 128; i++)
		{
			Result = Result + (char)(bit[i] + '0');
		}
	}
	else if (Coeficient1 == "16" && Coeficient2 == "10")
	{
		bool *temp = ReadHex(a);
		Qint x = x.BintoDec(temp);
		Result = x.QinttoString();
	}
	else if (Coeficient1 == "16" && Coeficient2 == "~")
	{
		bool *temp = ReadHex(a);
		Qint x;
		Result = x.BinToHex(NOT(temp));
	}
	while (Result[0] == '0')
		Result.erase(Result.begin());
	return Result;
}
string Qint::Output(const string &input)
{
	string cal = "";
	string s[12] = { "+","-","*","/","&","^","~","|",">>","<<","rol","ror"};
	for (int i = 0;i<12; i++)
	{
		size_t found = input.find(s[i]);
		if (found != string::npos)
			cal = s[i];
	}
	if (cal.length() && cal!="~" )
	{
		string coefficient, a, b;
		unsigned int i = 0;
		while (input[i] != ' ')
		{
			coefficient += input[i++];
		}
		++i;
		while (input[i] != ' ')
		{
			a += input[i++];
		}
		i = i + cal.length() + 2;
		while (i < input.length())
		{
			b += input[i++];
		}
		return Caculator(a, b, coefficient, cal);
	}
	else
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
		return Covert(a,coefficient1,coefficient2);
	}
}
//Operator 
Qint Qint::operator=(const Qint &x)
{
	this->data[0] = x.data[0];
	this->data[1] = x.data[1];
	return *this;
}
Qint Qint::operator/(const Qint &x)
{
	Qint temp = x;
	*this = BintoDec(DivideTwoBit(this->DectoBin(), temp.DectoBin()));
	return *this;
}
Qint Qint::operator*(const Qint &x)
{
	Qint temp = x;
	*this = BintoDec(MultiTwoBit(this->DectoBin(), temp.DectoBin()));
	return *this;
}
Qint Qint::operator-(const Qint &x)
{
	Qint temp = x;
	*this = BintoDec(SubtractTwoBit(this->DectoBin(), temp.DectoBin()));
	return *this;
}
Qint Qint::operator+(const Qint &x)
{
	Qint temp = x;
	*this = BintoDec(PlusTwoBit(this->DectoBin(), temp.DectoBin()));
	return *this;
}
Qint Qint::ROL(int n)
{
	*this = this->BintoDec(ROL(this->DectoBin(), n));
	return *this;
}
Qint Qint::ROR(int n)
{
	return this->BintoDec(ROR(this->DectoBin(), n));
}
Qint Qint::operator&(const Qint &x)
{
	Qint temp = x;
	*this = BintoDec(AND(this->DectoBin(), temp.DectoBin()));
	return *this;
}
Qint Qint::operator|(const Qint &x)
{
	Qint temp = x;
	*this = BintoDec(OR(this->DectoBin(), temp.DectoBin()));
	return *this;
}
Qint Qint::operator^(const Qint &x)
{
	Qint temp = x;
	*this = BintoDec(XOR(this->DectoBin(), temp.DectoBin()));
	return *this;
}
Qint Qint::operator~()
{
	Qint temp;
	temp = BintoDec(NOT(this->DectoBin()));
	return temp;
}
Qint Qint::operator<<(int n)
{
	Qint temp;
	temp = BintoDec(SHL(this->DectoBin(), n));
	return temp;
}
Qint Qint::operator>>(int n)
{
	Qint temp;
	temp = BintoDec(SHR(this->DectoBin(), n));
	return temp;
}

// phép dịch trái bit
bool* Qint::SHL(bool *a, int n)
{
	bool *bit = NULL;
	Init(bit);
	for (int i = 0; i < 128 - n; i++)
	{
		bit[i] = a[i + n];    // bit i là bit thứ a[i+n]
	}
	return bit;
}

// Phép dịch phải bit
bool* Qint::SHR(bool *a, int n)
{
	bool* bit = NULL;
	Init(bit);
	for (int i = 0; i < 128 - n; i++)
	{
		bit[i + n] = a[i];     //  dịch n bit thì bit i cộng n sẽ là bit a[i]
	}
	return bit;
}

//phép xoay trái bit
bool* Qint::ROL(bool* a, int n)
{
	bool* bit = NULL;
	Init(bit);
	for (int i = 0; i < 128; i++)
	{
		if (i < 128 - n)
			bit[i] = a[i + n];        //  (128-n ) bit đầu sẽ lấy giá trị vào bit i
		else
			bit[i] = a[i - (128 - n)];  // n bit sau sẽ lấy giá trị n bít đầu của a

	}
	return bit;
}

//Phep xoay phải bit
bool* Qint::ROR(bool *a, int n)
{
	bool* bit = NULL;
	Init(bit);
	for (int i = 0; i < 128; i++)
	{
		if (i < n)
		{
			bit[i] = a[(128 - n) + i];   // n bit đầu sẽ lấy n bit cuối của a
		}
		bit[i + n] = a[i];    // những bit sau sẽ lấy từ bit đầu của a
	}
	return bit;
}

 //  phép  and bit
bool* Qint::AND(bool *a, bool *b)
{
	bool *Result;
	Init(Result);
	for (int i = 0; i < 128; i++)
	{
		Result[i] = a[i] & b[i];   // And từng phần tử
	}
	return Result;
}

// phép or bit
bool* Qint::OR(bool *a, bool *b)
{
	bool *Result;
	Init(Result);
	for (int i = 0; i < 128; i++)
	{
		Result[i] = a[i] | b[i];   // Or từng phần tử
	}
	return Result;
}

// phép xor bit
bool* Qint::XOR(bool *a, bool *b)
{
	bool *Result;
	Init(Result);
	for (int i = 0; i < 128; i++)
	{
		Result[i] = a[i] ^ b[i];  // xor từng phần tử
	}
	return Result;
}

// phép not 
bool*Qint::NOT(bool *a)
{
	bool* Result;
	Init(Result);
	for (int i = 0; i < 128; i++)
	{
		Result[i] = !a[i];    // phần tử a[i] sẽ bằng đối của a[i]
	}
	return Result;
}

// phép cộng 2 dãy bit
bool* Qint::PlusTwoBit(bool *a, bool* b)
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

// phép trừ 2 dãy bit
bool* Qint::SubtractTwoBit(bool *a, bool *b)
{
	bool* temp = new bool[128]; // dùng dãy tạm lưu trữ dãy bit b
	for (int i = 0; i < 128; i++)
		temp[i] = b[i];
	return PlusTwoBit(a, CoverttoTwoComPlement(temp));  // phép trừ được đổi thành cộng cho bù 2
}

// phép chia 2 dãy bit
bool* Qint::DivideTwoBit(bool *a, bool *b)
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
bool* Qint::ModTwoBit(bool *a, bool *b)
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

// Phép nhân 2 dãy bit
bool* Qint::MultiTwoBit(bool *q, bool *m)
{
	bool* Result = NULL;
	Init(Result);  // khởi tạo bit kết quả
	for (int i = 127; i >= 0; i--)   
	{
		if (m[i] == 1) // kiểm tra bit thứ i được nhân có là 1 không
		{
			Result = PlusTwoBit(Result, SHL(q, 127 - i));  // dịch trái bit nhân (127-i) lần rồi cộng vào kết quả
		}
	}

	return Result;  // trả về kết quả
}

// Kiểm tra 2 dãy bit có khác không nếu có trả về true , còn sai thì ngược lại
bool Qint::Other(bool *a, bool *b)
{
	Qint temp1 = BintoDec(a); // chuyển dãy a về kiểu Qint
	Qint temp2 = BintoDec(b); // chuyễn dãy b về kiểu Qint
	if (temp1.data[0] == temp2.data[0] && temp1.data[1] == temp2.data[1]) // kiểm tra có trùng không
		return false;
	return true;
}

// in dãy bit
void Qint::printbit(bool *a)
{
	for (int i = 0; i < 128; i++)
		cout << a[i];
}

// int dãy kí tự
void Qint::printchar(char *a)
{
	for (int i = 0; i < 32; i++)
	{
		cout << a[i];
	}
}

bool* Qint::ReadBin(string s)
{
	bool* bit = NULL;
	Init(bit);
	int n = s.length();
	int k = 128 - n;
	for (int i = 0; i < n; i++)
		bit[k++] = s[i] - '0';
	return bit;
}
bool* Qint::ReadHex(string s)
{
	bool* bit = NULL;
	Init(bit);
	string data[16] = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111" };
	string temp;
	for (unsigned int i = 0; i < s.length(); i++)
	{
		if (s[i] >= '0'&&s[i] <= '9')
			temp = temp + data[s[i] - '0'];
		else
			temp = temp + data[s[i] - 'A' + 10];
	}
	return ReadBin(temp);
}
