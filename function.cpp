#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <string>
#include "kmeans.h"
#include "function.h"
#include <stack>
#include "engine.h"     
#pragma comment( lib, "libeng.lib")
#pragma comment( lib, "libmx.lib")
#pragma comment( lib, "libmat.lib")

using namespace std;

Function::Function() 
{

}
int Function::mod(double in, int num) 
{
	int cd = floor(in / num);
	int r = in - cd * num;
	return r;
}

double Function::std(vector<double> in)
{
	double mean;
	double sum = 0;
	for (int i = 0; i < in.size(); i++) 
	{
		sum = sum + in[i];
	}
	mean = sum / in.size();

	double summ = 0;
	for (int i = 0; i < in.size(); i++) 
	{
		summ = summ + pow(in[i] - mean, 2);
	}

	return pow(summ / in.size(), 1 / 2);
}

vector<double> Function::pwelch(vector<double> in) 
{
	Engine *ep;

	// open engine
	if (!(ep = engOpen("\0")))
	{
		fprintf(stderr, "\nCan't start MATLAB engine\n");
	}
	int Nsample = 20;
	double *t = new double[Nsample];

	for (int i = 0; i < Nsample; i++)
	{
		t[i] = in[i];
	}

	mxArray *T = NULL;
	T = mxCreateDoubleMatrix(1, in.size(), mxREAL);
	memcpy((void *)mxGetPr(T), (void *)t, Nsample * sizeof(t[0]));
	engPutVariable(ep, "T", T);

	engEvalString(ep, "Y=pwelch(T);");
	mxArray* y = engGetVariable(ep, "Y");
	double* p = (double*)mxGetData(y);

	vector<double> ret(20);
	for (int i = 0; i < Nsample; i++)
	{
		ret[i] = p[i];
	}
	mxDestroyArray(T);
	engEvalString(ep, "close;");

	return ret;
}

vector<double> Function::fliplr(vector<double> in)
{
	vector<double> key;
	stack<double> fliplr1;
	for (int i = 0; i < in.size(); i++)
	{
		fliplr1.push(in[i]);
	}
	for (int i = 0; i < in.size(); i++)
	{
		key.push_back(fliplr1.top());
		fliplr1.pop();
	}
	return key;
}

double Function::fun(Point point) 
{
	
	const int n = 2; // 3-1
	const double epi = 23.1406926327792690;
	const double start = 12.3456789012345678;
	double z = 0;
	vector<int> x100(n);

	for (int i = 0; i < n; i++) 
	{
		x100[i] = round(point.getValue(i) * 100);
	}

	double res = epi * pow(10, 18);
	vector<double> pwdRabt(20);

	for (int i = 0; i < 20; i++) 
	{
		pwdRabt[i] = round(mod(res,10));
		res = floor(res / 10);
	}

	vector<double> key = fliplr(pwdRabt);
	vector<double> energE = pwelch(key);

	res = start * pow(10, 18);
	

	for (int i = 0; i < 20; i++)
	{
		pwdRabt[i] = round(mod(res, 10));
		res = floor(res / 10);
	}

	key = fliplr(pwdRabt);
	for (int idx = 0; idx < n; idx++)
	{
		int left = mod(x100[idx], 20);
		int right = 19 - left;
		swap(key[left], key[right]);
	}

	for (int idx = 0; idx < n; idx++) 
	{
		int left = mod(x100[idx], 17);
		int right = 19 - left;
		swap(key[left], key[right]);
	}

	for (int idx = 0; idx < n; idx++)
	{
		int left = mod(x100[idx], 13);
		int right = 19 - left;
		swap(key[left], key[right]);
	}

	vector<double> energS = pwelch(key);
	
	z = 509 * abs(std(energS) - std(energE));
	return z;
}