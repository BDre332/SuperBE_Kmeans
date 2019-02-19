// Implementation of the KMeans Algorithm
// reference: http://mnemstudio.org/clustering-k-means-example-1.htm
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/ximgproc.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>




//function declarations 
using namespace cv;
using namespace std;
using namespace cv::ximgproc;

//int kmeans_main(int argc, char *argv[], int total_points1, int total_values1, int K1, int max_iterations1, int has_name1);

class Point_K
{
public:
	int id_point, id_cluster;
	vector<double> values;
	int total_values;
	string name;
public:
	Point_K(int id_point, vector<double>& values, string name = "")
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

class Cluster_K
{
private:
	int id_cluster;
	vector<double> central_values;
	vector<Point_K> points;

public:
	Cluster_K(int id_cluster, Point_K point)
	{
		this->id_cluster = id_cluster;
		int total_values = point.getTotalValues();
		for(int i = 0; i < total_values; i++)
			central_values.push_back(point.getValue(i));

		points.push_back(point);
	}
	void addPoint(Point_K point);
	bool removePoint(int id_point);
	double getCentralValue(int index);
	void setCentralValue(int index, double value);
	Point_K getPoint(int index);
	int getTotalPoints();
	int getID_cluster();
};

class KMeans
{
private:
	int K; // number of clusters
	int total_values, total_points, max_iterations;
	// return ID of nearest center (uses euclidean distance)
	int getIDNearestCenter(Point_K point);
public:

	vector<Cluster_K> clusters;
	vector<Vec3b> SuperPixelValues;
	vector<double> cluster_vals;
	//vector<Vec3b> get3bCluster();
	vector<double> K_means_run(vector<Vec3b> SuperPixelValues) ;

	
};

/*class DoubleVect
{
private:
	double cluster1, cluster2, cluster3;

public:
	


	double getCluster1();
	double getCluster2();
	double getCluster3();
	void setCluster1(double clusterValue);
	void setCluster1(double clusterValue);
	void setCluster1(double clusterValue);

}*/
