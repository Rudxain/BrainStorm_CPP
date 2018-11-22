#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <string>
#include <random>
#include "kmeans.h"
#define INF 100000000;
using namespace std;


/**
Created:2018-11-17, Updated:2018-11-17
Author: Siqing Ma
Version: V0.1T
**/


vector<Point> mat_randomt(double min, double max, int m, int n)
{
	vector<Point> po;
	for (int i = 0; i < m; i++)
	{
		vector<double> content;
		for (int j = 0; j < n; j++)
		{
			
			default_random_engine e;
			random_device r;
			e.seed(r());
			uniform_real_distribution<double> u(min, max);
			content.push_back(u(e));
		}
		Point point(i, content);
		po.push_back(point);
	}
	return po;
}

/*
int main(int argc, char *argv[])
{

	const int np = 48; // Number of population
	const int nd = 24; // Number of dimension
	const int nc = 3;  // Number of cluster
	// Ideas limits
	const double rang_l = -5.12;
	const double rang_r = 5.12;
	// Pick any deviations you want
	const int max_iterations = 8;
	// Pick any laps you want
	const int max_run = 1;

	cout << "K_means start" << endl;
	
	vector<Point> centers = mat_randomt(rang_l, rang_r, nc, nd);
	vector<Point> po = mat_randomt(rang_l, rang_r, np, nd);

	KMeans kmeans(nc, np, nd, max_iterations, centers);
	kmeans.run(po);

	for (int i = 0; i < nc; i++)
	{
		int total_points_cluster = kmeans.getCluster(i).getSize();

		cout << "Cluster " << kmeans.getCluster(i).getID() << " size: " << kmeans.getCluster(i).getSize() << endl;
		for (int j = 0; j < total_points_cluster; j++)
		{
			cout << "Point " << kmeans.getCluster(i).getPoint(j).getID() << ": ";
			
			
			//for (int p = 0; p < nd; p++)
				//cout << kmeans.getCluster(i).getPoint(j).getValue(p) << " ";
			

			cout << endl;
		}

		cout << "Cluster values: ";

		for (int j = 0; j < nd; j++)
			cout << kmeans.getCluster(i).getCentralValue(j) << " ";

		cout << "\n\n";
	}


	for (int i = 0; i < np; i++)
	{
		vector<int>dependency = kmeans.getDependency();
		cout << i << ": " << dependency[i] << endl;
	}

	int i;
	cin >> i;
	return 0;
}

/*
测试问题， 聚类后存在重复值，换初始聚类中心方式后出现

*/