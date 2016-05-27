#include<iostream>
#include"Matrix.h"
using namespace std;

void Test()
{
	int a[6][5] = {
		{ 1, 0, 3, 0, 5 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0 },
		{ 2, 0, 4, 0, 6 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0 }
	};
	SparseMatrix <int> sm1((int*)a,6, 5, 0);
	sm1.Display();
	SparseMatrix <int> sm2 = sm1.Transpose();
	sm2.Display();

	SparseMatrix <int> sm3 = sm1.FastTranspose();

	sm3.Display();
}

int main()
{
	Test();
	return 0;
}
