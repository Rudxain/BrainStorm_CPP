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
double randa() 
{
	default_random_engine e;
	random_device r;
	e.seed(r());
	uniform_real_distribution<double> u(0, 1);
	return u(e);
}

vector<Point> mat_random(double min, double max, int m, int n) 
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

Point po_random(double min, double max, int m, int n, int id) 
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
	Point point(id, content);
	return point;

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
		vector<Point> po = mat_random(rang_l, rang_r, np, nd);
		vector<Point> po_sort = mat_random(rang_l, rang_r, np, nd);
		
		vector<double> prob(nc);
		vector<double> best(nc);
		
		vector<Point> centers = mat_random(rang_l, rang_r, nc, nd);
		vector<Point> centers_copy = mat_random(rang_l, rang_r, nc, nd);
		vector<double> best_fitness(max_iteration);

		vector<double> fit_popu(np);
		vector<double> fit_popu_sorted(np);
		Point in_te = po_random(rang_l, rang_r, nc, nd, 0);

		// Evaluate the fitness of n ideas
		for (int times = 0; times < np; times++) 
		{
			fit_popu[times] = 1; // Add the evaluation function!!!!!!!!
		}

		int n_iteration = 0;
		while (n_iteration < max_iteration) 
		{
			cout << "Iteration: " << n_iteration << endl;
			KMeans kmeans(nc, np, nd, 100, centers);
			kmeans.run(po);
			

			vector<int> cluster = kmeans.getDependency(); // Containing cluster indices of each observation.
			vector<double> fit_values(nc);
			vector<int> number_in_cluster(nc); // The number of points in each cluster

			for (int clu = 0; clu < nc; clu++) 
			{
				fit_values[clu] = INF;
				number_in_cluster[clu] = kmeans.getCluster(clu).getSize();
				cout << "number_in_cluster: clu: " << clu << " value: " << number_in_cluster[clu] << endl;
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
			// Accumulated number of individuals in previous clusters
			vector<int> acculate_num_cluster(nc);
			acculate_num_cluster[0] = 0;
			cout << "acculate_num_cluster: " << 0 << " value: " << acculate_num_cluster[0] << endl;

			// Check with every cluster
			for (int times = 1; times < nc; times++) 
			{
				acculate_num_cluster[times] = acculate_num_cluster[times - 1] + number_in_cluster[times - 1];
				cout << "acculate_num_cluster: " << times << " value: " << acculate_num_cluster[times] << endl;
			}
			
			
			// Evaluate the individuals
			for (int times = 0; times < np; times++) 
			{
				counter_cluster[cluster[times]]++;
				int temldx = acculate_num_cluster[cluster[times]] + counter_cluster[cluster[times]];
				//cout << "times: " << times << " temldx: " << temldx << endl;
				po_sort[temldx-1] = po[times];
				fit_popu_sorted[temldx-1] = fit_popu[times];
			}
			
			// Rank individuals in each cluster
			for (int times = 0; times < nc; times++) 
			{
				centers[times] = po[best[times]];
			}
			// make a copy
			centers_copy.assign(centers.begin(), centers.end());
			
			
			// Select one cluster center to be replaced by a randomly generated center
			if (randa() < 0.2) 
			{
				int cenldx = floor(randa()*nc);
				centers[cenldx] = po_random(rang_l, rang_r, nc, nd, cenldx);
			}

			// Calculate cluster probabilities based on number of individuals in each cluster
			for (int times = 0; times < nc; times++) 
			{
				prob[times] = number_in_cluster[times] / np;
				if (times > 0) 
				{
					prob[times] = prob[times] + prob[times - 1];
				}
			}
			
			int indi_1;
			// Generate new individuals
			for (int times = 0; times < np; times++) 
			{
				double r_1 = randa();
				if (r_1 < 0.8) 
				{
					double r = randa();
					for (int idj = 0; idj < nc; idj++) 
					{
						if (r < prob[idj]) 
						{
							if (randa() < 0.4) 
							{
								in_te = centers[idj];
							}
							else 
							{
								indi_1 = acculate_num_cluster[idj] + floor(randa() * number_in_cluster[idj]);
								in_te = po_sort[indi_1];
							}
							break;
						}
					}
				}
				else 
				{
					int c1 = floor(randa() * nc);
					indi_1 = acculate_num_cluster[c1] + ceil(randa() * number_in_cluster[c1]);
					int c2 = floor(randa() * nc);
					int indi_2 = acculate_num_cluster[c2] + ceil(randa() * number_in_cluster[c2]);
					double tem = randa();
					if (randa() < 0.5) 
					{
						//写一个能将一个样本点里值全部乘系数的函数。
					}
				}
			
			
			}
			
			



			n_iteration++;
		}
	}

	int i;
	cin >> i;
	return 0;
}

