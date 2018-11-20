#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <string>
#include "kmeans.h"
using namespace std;
/**
Created:2018-11-17, Updated:2018-11-17
Author: Siqing Ma
Version: V0.1T
**/

Point::Point(int id_point, vector<double>& values)
{
	this->id_point = id_point;
	nd = values.size();
	for (int i = 0; i < nd; i++) this->values.push_back(values[i]);
	id_cluster = -1;
}

int Point::getID()
{
	return id_point;
}

void Point::setCluster(int id_cluster)
{
	this->id_cluster = id_cluster;
}

int Point::getCluster()
{
	return id_cluster;
}

double Point::getValue(int index)
{
	return values[index];
}

int Point::getDimension()
{
	return nd;
}

void Point::addValue(double value)
{
	values.push_back(value);
}



Cluster::Cluster(int id_cluster, Point point)
{
	this->id_cluster = id_cluster;
	int dimension = point.getDimension();

	for (int i = 0; i < dimension; i++)
		central_values.push_back(point.getValue(i));

	points.push_back(point);
}

void Cluster::addPoint(Point point)
{
	points.push_back(point);
}

bool Cluster::removePoint(int id_point)
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

double Cluster::getCentralValue(int index)
{
	return central_values[index];
}

void Cluster::setCentralValue(int index, double value)
{
	central_values[index] = value;
}

Point Cluster::getPoint(int index)
{
	return points[index];
}

int Cluster::getSize()
{
	return points.size();
}

int Cluster::getID()
{
	return id_cluster;
}


KMeans::KMeans(int nc, int np, int nd, int max_iterations, vector<Point> centers)
{
	this->nc = nc;
	this->np = np;
	this->nd = nd;
	this->max_iterations = max_iterations;
	this->init_centres = centers;
}

// return ID of nearest center 
int KMeans::getNearestCentreId(Point point)
{
	double sum = 0.0, min_dist;
	int nearest_centre_id = 0;

		
	// Initial
	// Uses city block distance
	for (int i = 0; i < nd; i++)
	{
		sum += abs(clusters[0].getCentralValue(i) -
			point.getValue(i));
	}
	min_dist = sum;
		
	for (int i = 1; i < nc; i++)
	{
		double dist;
		sum = 0.0;

		/*
		// Uses euclidean distance
		for (int j = 0; j < nd; j++)
		{
			sum += pow(clusters[i].getCentralValue(j) -
				point.getValue(j), 2.0);
		}
		dist = sqrt(sum);
		*/

		// Uses city block distance
		for (int j = 0; j < nd; j++)
		{
			sum += abs(clusters[i].getCentralValue(j) -
				point.getValue(j));
		}
		dist = sum;

		if (dist < min_dist)
		{
			min_dist = dist;
			nearest_centre_id = i;
		}
	}

	return nearest_centre_id;
}

Cluster KMeans::getCluster(int index)
{
	return clusters[index];
}

vector<int> KMeans::getDependency() 
{
	
	return dependency;
}

void KMeans::run(vector<Point> & points)
{
	if (nc > np)
		return;

	vector<int> now_indexes;

	/*_2018-11-19
	// Initial the cluster centre using exsiting points£¨random pick)
	for (int i = 0; i < nc; i++)
	{
		while (true)
		{
			int index_point = rand() % np;

			if (find(now_indexes.begin(), now_indexes.end(), index_point) == now_indexes.end())
			{
				now_indexes.push_back(index_point);
				points[index_point].setCluster(i);
				Cluster cluster(i, points[index_point]);
				clusters.push_back(cluster);
				break;
			}
		}
	}*/

	// Initial the cluster centre by using the provided centre_2018-11-19
	for (int i = 0; i < nc; i++) 
	{
		Cluster centre(i, init_centres[i]);
		clusters.push_back(centre);
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
				int total_points_cluster = clusters[i].getSize();
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

	for (int i = 0; i < np; i++)
	{
		dependency.push_back(0);
	}
	for (int i = 0; i < nc; i++)
	{
		for (int j = 0; j < getCluster(i).getSize(); j++)
		{
			int id = getCluster(i).getPoint(j).getID();
			//cout << "id: " << id << endl;
			dependency[id] = i;
		}
	}
}

