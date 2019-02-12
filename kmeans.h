// Implementation of the KMeans Algorithm
// reference: http://mnemstudio.org/clustering-k-means-example-1.htm

#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>




//function declarations 
using namespace std;
int kmeans_main(int argc, char *argv[], int total_points1, int total_values1, int K1, int max_iterations1, int has_name1);

class Point
{
public:
	int id_point, id_cluster;
	vector<double> values;
	int total_values;
	string name;

public:
	Point(int id_point, vector<double>& values, string name = "")
	{
		this->id_point = id_point;
		total_values = values.size();

		for(int i = 0; i < total_values; i++)
			this->values.push_back(values[i]);

		this->name = name;
		id_cluster = -1;
	}

	int getID();

	void setCluster(int id_cluster);

	int getCluster();

	double getValue(int index);

	int getTotalValues();
	void addValue(double value);
	string getName();
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

		int total_values = point.getTotalValues();

		for(int i = 0; i < total_values; i++)
			central_values.push_back(point.getValue(i));

		points.push_back(point);
	}

	void addPoint(Point point);
	bool removePoint(int id_point);

	double getCentralValue(int index);


	void setCentralValue(int index, double value);

	Point getPoint(int index);

	int getTotalPoints();

	int getID_cluster();
};

class KMeans
{
private:
	int K; // number of clusters
	int total_values, total_points, max_iterations;
	

	// return ID of nearest center (uses euclidean distance)
	int getIDNearestCenter(Point point);
public:
	vector<Cluster> clusters;
	KMeans(int K, int total_points, int total_values, int max_iterations)
		{
			this->K = K;
			this->total_points = total_points;
			this->total_values = total_values;
			this->max_iterations = max_iterations;
		}
	void run(vector<Point> & points) ;

	
};
