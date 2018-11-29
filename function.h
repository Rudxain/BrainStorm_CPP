#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <string>
#include "kmeans.h"
using namespace std;

class Function 
{
	private:
		vector<double> pwelch(vector<double> in);
		vector<double> fliplr(vector<double> in);
		int mod(double in, int num);
		double std(vector<double> in);
	public:
		Function();
		double fun(Point point);
};