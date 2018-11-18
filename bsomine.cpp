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


vector<Point> random_mat(double min, double max, int m, int n) 
{
	vector<Point> po;
	for (int i = 0; i < m; i++)
	{
		vector<double> content;
		for (int j = 0; j < n; j++)
		{
			default_random_engine e;
			uniform_real_distribution<double> u(min, max);
			content.push_back(u(e));
		}
		Point point(i, content);
		po.push_back(point);
	}
	return po;
}

int main(int argc, char *argv[])
{	
	srand(time(NULL));

	const int np = 48; // Number of population
	const int nd = 24; // Number of dimension
	const int nc = 3;  // Number of cluster
	// Ideas limits
	const double rang_l = -5.12;
	const double rang_r = 5.12;
	// Pick any deviations you want
	const int max_iteration = 8;
	// Pick any laps you want
	const int max_run = 1;

	// Runs off laps from here
	for (int idx = 0; idx < max_run; idx++) 
	{
		// Genetate a random 
		vector<Point> po = random_mat(rang_l, rang_r, np, nd);
		vector<Point> po_s = random_mat(rang_l, rang_r, np, nd);
		
		vector<double> prob(nc);
		vector<double> best(nc);
		
		vector<Point> centers = random_mat(rang_l, rang_r, nc, nd);
		vector<Point> centers_copy = random_mat(rang_l, rang_r, nc, nd);
		vector<double> best_fitness(max_iteration);

		vector<double> fit_popu(np);
		vector<double> fit_popu_sorted(np);

		// Evaluate the fitness of n ideas
		for (int times = 0; times < np; times++) 
		{
			fit_popu[times] = 1; // Add the evaluation function!!!!!!!!
		}

		int n_iteration = 0;
		while (n_iteration < max_iteration) 
		{
			KMeans kmeans(nc, np, nd, 100, centers);
			kmeans.run(po);
			vector<int> cluster = kmeans.getDependency(); // Containing cluster indices of each observation.
			vector<double> fit_values(nc);
			vector<int> number_in_cluster(nc); // The number of points in each cluster

			for (int clu = 0; clu < nc; clu++) 
			{
				fit_values[clu] = INF;
				number_in_cluster[clu] = kmeans.getCluster(clu).getSize();
			}

			for (int times = 0; times < np; times++) 
			{
				if (fit_values[cluster[times]] > fit_popu[times]) 
				{
					fit_values[cluster[times]] = fit_popu[times];
					best[cluster[times]] = times;					
				}
			}

			// Initialization cluster
			vector<int> counter_cluster(nc);
			vector<int> acculate_num_cluster(nc);
			acculate_num_cluster[0] = 0;

			// Check with every cluster
			for (int times = 1; times < nc; times++) 
			{
				acculate_num_cluster[times] = acculate_num_cluster[times - 1] + number_in_cluster[times - 1];
			}

			// Evaluate the indiciduals
			for (int times = 0; times < np; times++) 
			{
				counter_cluster[cluster[times]]++;
				int temldx = acculate_num_cluster[cluster[times]] + counter_cluster[cluster[times]];
				po_s[temldx] = po[times];
				fit_popu_sorted[temldx] = fit_popu[times];
			}

			// Rank individuals in each cluster
			for (int times = 0; times < nc; times++) 
			{
				//centers[times]
			}


			n_iteration++;
		}
	}

	int i;
	cin >> i;
	return 0;
}

