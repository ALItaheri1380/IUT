#include<iostream>
#include<string>
using namespace std;
#define max 1000;
string spilit(string a,string c[],int n,string b)
{
	while (2)
	{
		int f = a.find(c[n]);
		if (f != string::npos)
		{
			a.replace(f, c[n].size(), b);
		}
		else
			break;
	}
	return a;
}
int main()
{
	int n, t = 0;
	string inp;
	string matn;
	cin >> n;
	getline(cin, matn);
	getline(cin, inp);
	string* l=new string[n];
	string spi;
	int j = 0;
	int i1 = 0;
	while (i1 < inp.length())
	{

		if (inp[i1] != ',') {

			spi += inp[i1];
			i1++;
		}
		else
		{

			l[j] = spi;
			spi= "";
			j++;
			i1++;
			continue;
		}
		l[j] = spi;
	}
	getline(cin, matn);
	int i = 0;
	while (i < n)
	{
		string s;
		 t= 2 * l[i].size();
		for (int i = 0; i < t; i++)
			s += "*";
		matn=spilit(matn, l, i, s);
		i++;
	}
	cout << matn;
}