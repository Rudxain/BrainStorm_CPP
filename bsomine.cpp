#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <string>
#include "kmeans.h"
using namespace std;


int main(int argc, char *argv[])
{
	srand(time(NULL));
	cout << "K_means start" << endl;
	int np, nd, nc, max_iterations, has_name;

	cin >> np >> nd >> nc >> max_iterations >> has_name;

	vector<Point> points;
	string point_name;

	for (int i = 0; i < np; i++)
	{
		vector<double> values;

		for (int j = 0; j < nd; j++)
		{
			double value;
			cin >> value;
			values.push_back(value);
		}

		Point p(i, values);
		points.push_back(p);
	}

	KMeans kmeans(nc, np, nd, max_iterations);
	kmeans.run(points);

	for (int i = 0; i < nc; i++)
	{
		int total_points_cluster = kmeans.getCluster(i).getTotalPoints();

		cout << "Cluster " << kmeans.getCluster(i).getID() + 1 << endl;
		for (int j = 0; j < total_points_cluster; j++)
		{
			cout << "Point " << kmeans.getCluster(i).getPoint(j).getID() + 1 << ": ";
			for (int p = 0; p < nd; p++)
				cout << kmeans.getCluster(i).getPoint(j).getValue(p) << " ";


			cout << endl;
		}

		cout << "Cluster values: ";

		for (int j = 0; j < nd; j++)
			cout << kmeans.getCluster(i).getCentralValue(j) << " ";

		cout << "\n\n";
	}

	int i;
	cin >> i;
	return 0;
}