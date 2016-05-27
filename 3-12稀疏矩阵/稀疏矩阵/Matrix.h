#pragma once
/*ϡ�����M X N�ľ����У���ЧֵԶԶС����Чֵ��invalid���ĸ������ҷֲ�������
��ѹ���洢��ֻ�洢��Ч���ݣ�ʹ��(row,col,value)��Ԫ��洢ÿһ����Ч���ݣ���Ԫ��
��ԭ�����е�˳���������ȵ�˳��洢*/
#include<vector>
using namespace std;

template <class T>
struct Trituple   //��Ԫ��ṹ
{
	int _row;
	int _col;
	T _value;
};

template <class T>
class SparseMatrix
{

private:
	//Trituple * _array;//ѹ���洢
	//size_t size;      //ϡ�������������ݵĸ���          //�޷�ȷ������Ŀռ�Ϊ���
	vector<Trituple<T>> _array; //���Զ�����
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
	//ת�ã������µľ���sm��
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
	
	//����ת��
	SparseMatrix<T> FastTranspose()
	{
		SparseMatrix<T> sm;
		sm._colSize = _rowSize;
		sm._rowSize = _colSize;
		sm._invalid = _invalid;
		//rowCounts:ת�ú����ÿһ�е����ݸ���
		//roeStart:ת�ú����ÿһ����ѹ�������д洢�Ŀ�ʼλ��
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
		//����rowStart����λת�ú�ѹ���洢��λ��
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