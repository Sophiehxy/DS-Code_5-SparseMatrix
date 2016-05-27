#pragma once
/*稀疏矩阵：M X N的矩阵中，有效值远远小于无效值（invalid）的个数，且分布不规律
其压缩存储：只存储有效数据，使用(row,col,value)三元组存储每一个有效数据，三元组
按原矩阵中的顺序，以行优先的顺序存储*/
#include<vector>
using namespace std;

template <class T>
struct Trituple   //三元组结构
{
	int _row;
	int _col;
	T _value;
};

template <class T>
class SparseMatrix
{

private:
	//Trituple * _array;//压缩存储
	//size_t size;      //稀疏矩阵的有数数据的个数          //无法确定所需的空间为多大
	vector<Trituple<T>> _array; //能自动扩容
	size_t _colSize;
	size_t _rowSize;
	T _invalid;
public:
	SparseMatrix()
		:_colSize(0)
		, _rowSize(0)
	{}
	SparseMatrix(T* a, size_t m, size_t n, const T& invalid)
		:_rowSize(m)
		,_colSize(n)
		,_invalid(invalid)
	{
		for (size_t i = 0; i < m; i++)
		{
			for (size_t j = 0; j < n; j++)
			{
				if (a[i*n + j] != _invalid)
				{
					Trituple <T> t;
					t._row = i;
					t._col = j;
					t._value = a[i*n + j];
					_array.push_back(t);
				}
			}
		}
	}

	void Display()
	{
		size_t index = 0;
		for (size_t i = 0; i < _rowSize; i++)
		{
			for (size_t j = 0; j < _colSize; j++)
			{
				if ((index < _array.size()) 
					&&(_array[index]._row == i) && (_array[index]._col == j))
				{
					cout << _array[index++]._value << " ";
				}
				else
				{
					cout << _invalid << " ";
				}
			}
			cout << endl;
		}
		cout << endl;
	}
	//转置（产生新的矩阵sm）
	SparseMatrix<T> Transpose()
	{
		SparseMatrix<T> sm;
		sm._rowSize = _colSize;
		sm._colSize = _rowSize;
		sm._invalid = _invalid;
		for (size_t i = 0; i < _colSize; i++)
		{
			size_t index = 0;
			while (index < _array.size())
			{
				if (_array[index]._col == i)
				{
					Trituple<T> t;
					t._row = _array[index]._col;
					t._col = _array[index]._row;
					t._value = _array[index]._value;
					sm._array.push_back(t);
				}
				++index;
			}
		}
		return sm;
	}
	
	//快速转置
	SparseMatrix<T> FastTranspose()
	{
		SparseMatrix<T> sm;
		sm._colSize = _rowSize;
		sm._rowSize = _colSize;
		sm._invalid = _invalid;
		//rowCounts:转置后矩阵每一行的数据个数
		//roeStart:转置后矩阵每一行在压缩矩阵中存储的开始位置
		int* rowCounts = new int[_colSize];
		int* rowStart = new int[_colSize];
		memset(rowCounts, 0, sizeof(int)*_colSize);
		memset(rowStart, 0, sizeof(int)*_colSize);
		size_t index = 0;
		//cout << _array.size();
		while (index < _array.size())
		{
			rowCounts[_array[index]._col]++;			
			//cout << rowCounts[_array[index]._col] << endl;
			++index;
		}
		rowStart[0] = 0;
		for (int i = 1; i < _colSize;++i)
		{
			rowStart[i] = rowStart[i - 1] + rowCounts[i - 1];
			//cout << rowStart[i] << endl;

		}
		//借助rowStart来定位转置后压缩存储的位置
		index = 0;
		sm._array.resize(_array.size());
	
		while(index < _array.size())
		{
			size_t begin = rowStart[_array[index]._col];
			Trituple <T> t;
			t._col = _array[index]._row;
			t._row = _array[index]._col;
			t._value = _array[index]._value;
			sm._array[begin] = t;
			++rowStart[_array[index]._col];
			++index;
		}
		delete[] rowCounts;
		delete[] rowStart;
		return sm;
	}
};