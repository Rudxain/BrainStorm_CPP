#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <string>
using namespace std;
/**
Created:2018-11-17, Updated:2018-11-17
Author: Siqing Ma
Version: V0.1T
**/

class Point
{
  private:
	int id_point, id_cluster;
	vector<double> values;
	int nd;

  public:
	  Point(int id_point, vector<double>& values);
	  int getID();
	  void setCluster(int id_cluster);
	  int getCluster();
	  double getValue(int index);
	  int getDimension();
	  void addValue(double value);
};

class Cluster
{
  private:
	  int id_cluster;
	  vector<double> central_values;
	  vector<Point> points;

  public:
	  Cluster(int id_cluster, Point point);
	  void addPoint(Point point);
	  bool removePoint(int id_point);
	  double getCentralValue(int index);
	  void setCentralValue(int index, double value);
	  Point getPoint(int index);
	  int getID();
	  int getSize();
};

class KMeans
{
  private:
	  int nc, nd, np, max_iterations;
	  vector<Point> centers;
	  vector<Cluster> clusters;
	  vector<int> dependency;
	  // return ID of nearest center 
	  int getNearestCentreId(Point point);
	
  public:
	  KMeans(int nc, int np, int nd, int max_iterations, vector<Point> centers);
	  Cluster getCluster(int index);
	  vector<int> getDependency();
	  void run(vector<Point> & points);
};
