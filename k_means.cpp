#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <string>

using namespace std;

class Point
{
private:
	int id_point, id_cluster;
	vector<double> values;
	int nd;

public:
	Point(int id_point, vector<double>& values)
	{
		this->id_point = id_point;
		nd = values.size();
		for (int i = 0; i < nd; i++) this->values.push_back(values[i]);
		id_cluster = -1;
	}

	int getID()
	{
		return id_point;
	}

	void setCluster(int id_cluster)
	{
		this->id_cluster = id_cluster;
	}

	int getCluster()
	{
		return id_cluster;
	}

	double getValue(int index)
	{
		return values[index];
	}

	int getDimension()
	{
		return nd;
	}

	void addValue(double value)
	{
		values.push_back(value);
	}
};

class Cluster
{
private:
	int id_cluster;
	vector<double> central_values;
	vector<Point> points;

public:
	Cluster(int id_cluster, Point point)
	{
		this->id_cluster = id_cluster;

		int total_values = point.getDimension();

		for (int i = 0; i < total_values; i++)
			central_values.push_back(point.getValue(i));

		points.push_back(point);
	}

	void addPoint(Point point)
	{
		points.push_back(point);
	}

	bool removePoint(int id_point)
	{
		int total_points = points.size();

		for (int i = 0; i < total_points; i++)
		{
			if (points[i].getID() == id_point)
			{
				points.erase(points.begin() + i);
				return true;
			}
		}
		return false;
	}

	double getCentralValue(int index)
	{
		return central_values[index];
	}

	void setCentralValue(int index, double value)
	{
		central_values[index] = value;
	}

	Point getPoint(int index)
	{
		return points[index];
	}

	int getTotalPoints()
	{
		return points.size();
	}

	int getID()
	{
		return id_cluster;
	}
};

class KMeans
{
private:
	int nc, nd, np, max_iterations;
	vector<Cluster> clusters;

	// return ID of nearest center 
	int getNearestCentreId(Point point)
	{
		double sum = 0.0, min_dist;
		int id_cluster_center = 0;

		/*
		// Uses euclidean distance
		for (int i = 0; i < nd; i++)
		{
			sum += pow(clusters[0].getCentralValue(i) -
				point.getValue(i), 2.0);
		}*/

		// Uses city block distance
		for (int i = 0; i < nd; i++)
		{
			sum += abs(clusters[0].getCentralValue(i) -
				point.getValue(i));
		}

		min_dist = sqrt(sum);

		for (int i = 1; i < nc; i++)
		{
			double dist;
			sum = 0.0;

			for (int j = 0; j < nd; j++)
			{
				sum += pow(clusters[i].getCentralValue(j) -
					point.getValue(j), 2.0);
			}

			dist = sqrt(sum);

			if (dist < min_dist)
			{
				min_dist = dist;
				id_cluster_center = i;
			}
		}

		return id_cluster_center;
	}

public:
	KMeans(int nc, int np, int nd, int max_iterations)
	{
		this->nc = nc;
		this->np = np;
		this->nd = nd;
		this->max_iterations = max_iterations;
	}

	void run(vector<Point> & points)
	{
		if (nc > np)
			return;

		vector<int> prohibited_indexes;

		// choose K distinct values for the centers of the clusters
		for (int i = 0; i < nc; i++)
		{
			while (true)
			{
				int index_point = rand() % np;

				if (find(prohibited_indexes.begin(), prohibited_indexes.end(),
					index_point) == prohibited_indexes.end())
				{
					prohibited_indexes.push_back(index_point);
					points[index_point].setCluster(i);
					Cluster cluster(i, points[index_point]);
					clusters.push_back(cluster);
					break;
				}
			}
		}

		int iter = 1;

		while (true)
		{
			bool done = true;

			// associates each point to the nearest center
			for (int i = 0; i < np; i++)
			{
				int id_old_cluster = points[i].getCluster();
				int id_nearest_center = getNearestCentreId(points[i]);

				if (id_old_cluster != id_nearest_center)
				{
					if (id_old_cluster != -1)
						clusters[id_old_cluster].removePoint(points[i].getID());

					points[i].setCluster(id_nearest_center);
					clusters[id_nearest_center].addPoint(points[i]);
					done = false;
				}
			}

			// recalculating the center of each cluster
			for (int i = 0; i < nc; i++)
			{
				for (int j = 0; j < nd; j++)
				{
					int total_points_cluster = clusters[i].getTotalPoints();
					double sum = 0.0;

					if (total_points_cluster > 0)
					{
						for (int p = 0; p < total_points_cluster; p++)
							sum += clusters[i].getPoint(p).getValue(j);
						clusters[i].setCentralValue(j, sum / total_points_cluster);
					}
				}
			}

			if (done == true || iter >= max_iterations)
			{
				cout << "Break in iteration " << iter << "\n\n";
				break;
			}

			iter++;
		}

		// shows elements of clusters
		for (int i = 0; i < nc; i++)
		{
			int total_points_cluster = clusters[i].getTotalPoints();

			cout << "Cluster " << clusters[i].getID() + 1 << endl;
			for (int j = 0; j < total_points_cluster; j++)
			{
				cout << "Point " << clusters[i].getPoint(j).getID() + 1 << ": ";
				for (int p = 0; p < nd; p++)
					cout << clusters[i].getPoint(j).getValue(p) << " ";


				cout << endl;
			}

			cout << "Cluster values: ";

			for (int j = 0; j < nd; j++)
				cout << clusters[i].getCentralValue(j) << " ";

			cout << "\n\n";
		}
	}
};

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
	int i;
	cin >> i;
	return 0;
}
