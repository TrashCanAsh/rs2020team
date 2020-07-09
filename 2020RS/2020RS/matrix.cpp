#include <iostream>
#include "matrix.h"
#include<string.h>
#include"stdafx.h"
using namespace std;


matrix::matrix()
{
}


matrix::~matrix()
{
	if (mat != NULL)
	{
		for (int ii = 0; ii < row; ii++)
		{
			if (mat[ii])
				delete[] mat[ii];
			mat[ii] = NULL;
		}
		delete[] mat;
		mat = NULL;
	}
}

matrix::matrix(int r, int c, double val)
{
	row = r;
	col = c;
	mat = new double*[row];
	for (int ii = 0; ii < row; ii++)
	{
		mat[ii] = new double[col];
		if (mat[ii])
			memset(mat[ii], 0, col * sizeof(double));
	}

	for (int ii = 0; ii < row; ii++)
	{
		for (int jj = 0; jj < col; jj++)
		{
			mat[ii][jj] = val;
		}
	}
}

matrix::matrix(const matrix& b)
{
	if (mat)
	{
		for (int ii = 0; ii < row; ii++)
		{
			if (mat[ii])
				delete[] mat[ii];
			mat[ii] = NULL;
		}
		delete[] mat;
		mat = NULL;
	}
	row = b.row;
	col = b.col;
	mat = new double*[row];
	if (mat)
		memset(mat, 0, row * sizeof(double*));
	for (int ii = 0; ii < row; ii++)
	{
		mat[ii] = new double[col];
		for (int jj = 0; jj < col; jj++)
		{
			mat[ii][jj] = b.mat[ii][jj];
		}
	}
}

void matrix::MatrixPrint()
{
	cout.setf(std::ios::left);
	for (int ii = 0; ii < row; ii++)
	{
		for (int jj = 0; jj < col; jj++)
		{
			cout.width(10);
			cout << mat[ii][jj] << " ";
		}
		cout << endl;
	}
}

matrix matrix::operator*(matrix b)
{
	matrix res(row, b.col, 0);
	if (col != b.row)
	{
		cout << "矩阵大小不能进行相乘" << endl;
		return res;
	}
		

	for (int ii = 0; ii < row; ii++)
	{
		for (int jj = 0; jj < b.col; jj++)
		{
			res.mat[ii][jj] = 0;
			for (int kk = 0; kk < col; kk++)
			{
				res.mat[ii][jj] += mat[ii][kk] * b.mat[kk][jj];
			}
		}
	}
	return res;
}

matrix matrix::operator-(matrix b)
{
	matrix res(row, col);
	for (int ii = 0; ii < row; ii++)
	{
		for (int jj = 0; jj < col; jj++)
		{
			res.mat[ii][jj] = mat[ii][jj] - b.mat[ii][jj];
		}
	}
	return res;
}

matrix matrix::operator+(matrix b)
{
	matrix res(row, col);
	for (int ii = 0; ii < row; ii++)
	{
		for (int jj = 0; jj < col; jj++)
		{
			res.mat[ii][jj] = mat[ii][jj] + b.mat[ii][jj];
		}
	}
	return res;
}

matrix& matrix::operator+=(matrix b)
{
	if (row != b.row || col != b.col)
	{
		cout << "矩阵大小不能进行+=" << endl;
		return *this;
	}

	for (int ii = 0; ii < row; ii++)
	{
		for (int jj = 0; jj < col; jj++)
		{
			mat[ii][jj] += b.mat[ii][jj];
		}
	}
	return *this;
}

matrix& matrix::operator=(const matrix& b)
{
	if (this != &b)
	{
		if (row == b.row&&col == b.col)
		{
			//若矩阵大小相同则直接赋值
			for (int ii = 0; ii < row; ii++)
			{
				for (int jj = 0; jj < col; jj++)
				{
					mat[ii][jj] = b.mat[ii][jj];
				}
			}
		}
		else
		{
			//若矩阵大小不同则重新开辟mat数组并赋值
			if (mat != NULL)
			{
				for (int ii = 0; ii < row; ii++)
				{
					if (mat[ii] != NULL)
						delete[] mat[ii];
					mat[ii] = NULL;
				}
				delete[] mat;
				mat = NULL;
			}

			row = b.row;
			col = b.col;
			mat = new double*[row];
			if (mat)
				memset(mat, 0, row * sizeof(double*));
			for (int ii = 0; ii < row; ii++)
			{
				mat[ii] = new double[col];
				for (int jj = 0; jj < col; jj++)
				{
					mat[ii][jj] = b.mat[ii][jj];
				}
			}
		}
	}

	return *this;
}

matrix matrix::trans()
{
	matrix res(col, row);
	for (int ii = 0; ii < row; ii++)
	{
		for (int jj = 0; jj < col; jj++)
		{
			res.mat[jj][ii] = mat[ii][jj];
		}
	}
	return res;
}

matrix matrix::inv()
{
	//matrix iden = identity(row);
	//行连接一个单位阵
	matrix res = RowConcat(identity(row));
	if (row != col)
		return res;

	//列主元消元法求逆
	double factor; int dcol = col << 1;
	for (int ii = 0; ii < row - 1; ii++)
	{
		////顺序消元法
		//if (res.mat[ii][ii] == 0)
		//{
		//	int tmprow = 0;
		//	double tmp;
		//	for (int jj = ii + 1; jj < row; jj++)
		//	{
		//		//寻找下一个首位不为0的行，希望将其调换为ii行
		//		if (res.mat[jj][ii] != 0)
		//			tmprow = jj;
		//	}
		//	if (tmprow == 0)
		//		cout << "矩阵不是满秩的！";
		//	for (int kk = 0; kk < dcol; kk++)
		//	{
		//		//该行与当前行进行调换
		//		tmp = res.mat[ii][ii];
		//		res.mat[ii][ii] = res.mat[tmprow][ii];
		//		res.mat[tmprow][ii] = tmp;
		//	}
		//}

		//初等变换得到上三角矩阵
		int tmprow = ii;
		double tmp = abs(res.mat[ii][ii]);
		for (int jj = ii + 1; jj < row; jj++)
		{
			//寻找绝对值尽可能大的主元
			if (abs(res.mat[jj][ii]) > tmp)
			{
				tmprow = jj;
				tmp = abs(res.mat[jj][ii]);
			}
		}
		if (res.mat[tmprow][tmprow] == 0)
		{
			cout << "列主元为0！" << "当前列主元为第" << tmprow + 1 << "行" << tmprow + 1 << "列" << endl;
			return res;
		}

		//找到大的主元则交换
		if (tmprow != ii)
		{
			for (int kk = 0; kk < dcol; kk++)
			{
				//该行与当前行进行调换
				tmp = res.mat[ii][kk];
				res.mat[ii][kk] = res.mat[tmprow][kk];
				res.mat[tmprow][kk] = tmp;
			}
		}

		for (int jj = ii + 1; jj < row; jj++)
		{
			if (res.mat[ii][ii] == 0)cout << "除数为0！目前为矩阵求逆的第" << ii + 1 << "行" << ii + 1 << "列" << endl;
			if (res.mat[jj][ii] == 0)
				continue;
			//向下逐步消元
			factor = res.mat[jj][ii] / res.mat[ii][ii];
			for (int kk = 0; kk < dcol; kk++)
			{
				res.mat[jj][kk] -= factor * res.mat[ii][kk];
			}
		}
	}
	for (int ii = 0; ii < row; ii++)
	{
		if (res.mat[ii][ii] == 0)
		{
			cout << "矩阵不是满秩的！" << endl;
			return res;
		}
	}

	//得到上三角矩阵，由最后一行开始对上部分进行初等变换，最终得到单位矩阵
	for (int ii = row - 1; ii >= 0; ii--)
	{
		factor = res.mat[ii][ii];
		for (int kk = ii; kk < dcol; kk++)
		{
			//对角线元素为1，当前行其他每个元素除以行首元素的值
			res.mat[ii][kk] /= factor;
		}

		//与其他行进行计算
		for (int jj = 0; jj < ii; jj++)
		{
			factor = res.mat[jj][ii] / res.mat[ii][ii];
			for (int kk = ii; kk < dcol; kk++)
			{
				res.mat[jj][kk] -= factor * res.mat[ii][kk];
			}
		}
	}

	matrix out(row, row);
	for (int ii = 0; ii < row; ii++)
	{
		for (int jj = 0; jj < row; jj++)
		{
			out.mat[ii][jj] = res.mat[ii][col + jj];
		}
	}

	return out;
}

matrix matrix::identity(int n)
{
	matrix res(n, n);
	for (int ii = 0; ii < n; ii++)
	{
		res.mat[ii][ii] = 1;
	}
	return res;
}

matrix matrix::RowConcat(matrix b)
{
	matrix res(row, col + b.col);
	if (row != b.row)
		return res;
	for (int ii = 0; ii < row; ii++)
	{
		for (int jj = 0; jj < col; jj++)
		{
			res.mat[ii][jj] = mat[ii][jj];
		}
		for (int jj = 0; jj < b.col; jj++)
		{
			res.mat[ii][col + jj] = b.mat[ii][jj];
		}
	}
	return res;
}

matrix matrix::ColConcat(matrix b)
{
	matrix res(row + b.row, col);
	if (col != b.col)
		return res;
	for (int jj = 0; jj < col; jj++)
	{
		for (int ii = 0; ii < row; ii++)
		{
			res.mat[ii][jj] = mat[ii][jj];
		}
		for (int ii = 0; ii < b.row; ii++)
		{
			res.mat[ii + row][jj] = b.mat[ii][jj];
		}
	}

}

double matrix::MaxAbsElement()
{
	double max = abs(mat[0][0]);
	for (int ii = 0; ii < row; ii++)
	{
		for (int jj = 0; jj < col; jj++)
		{
			if (abs(mat[ii][jj]) > max)
				max = abs(mat[ii][jj]);
		}
	}
	return max;
}