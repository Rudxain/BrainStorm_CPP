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


using namespace std;

Function::Function()
{

}

double Function::fun(Point point)
{
	//cout << "fun: " << endl;
	double z = 0;
	for (int i = 0; i < 10; i++) 
	{
		z = z + pow(point.getValue(i), 2) + 10 - 10 * cos(2 * 3.141592654 * point.getValue(i));
	}
	return z;
}