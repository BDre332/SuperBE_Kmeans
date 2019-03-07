#include "kmeans.h"




int id_point, id_cluster;
vector<double> values;

string name;


vector<double> central_values;
vector<Point_K> points;

int K; // number of clusters
int total_values, total_points, max_iterations;
vector<Cluster_K> clusters;
int numTimes;


// return ID of nearest center (uses euclidean distance)



void Cluster_K::addPoint(Point_K point)
	{
		points.push_back(point);
	}
bool Cluster_K::removePoint(int id_point)
	{
		int total_points = points.size();

		for(int i = 0; i < total_points; i++)
		{
			if(points[i].getID() == id_point)
			{
				points.erase(points.begin() + i);
				return true;
			}
		}
		return false;
	}
double Cluster_K::getCentralValue(int index)
	{
		return central_values[index];
	}

void Cluster_K::setCentralValue(int index, double value)
	{
		central_values[index] = value;
	}

Point_K Cluster_K::getPoint(int index)
	{
		return points[index];
	}

int Cluster_K::getTotalPoints()
	{
		return points.size();
	}

int Cluster_K::getID_cluster()
	{
		return id_cluster;
	}



// sthis is a break 



int Point_K::getID()
	{
		return id_point;
	}

void Point_K::setCluster(int id_cluster1)
	{
		id_cluster = id_cluster1;
	}
int Point_K::getCluster()
	{
		return id_cluster;
	}

double Point_K::getValue(int index)
	{
		return values[index];
	}

int Point_K::getTotalValues()
	{
		return total_values;
	}

void Point_K::addValue(double value)
	{
		values.push_back(value);
	}

string Point_K::getName()
	{
		return name;
	}
int KMeans::getIDNearestCenter(Point_K point)
	{
		double sum = 0.0, min_dist;
		int id_cluster_center = 0;

		for(int i = 0; i < total_values; i++)
		{
			sum += pow(clusters[0].getCentralValue(i) -
					   point.getValue(i), 2.0);
		}

		min_dist = sqrt(sum);

		for(int i = 1; i < K; i++)
		{
			double dist;
			sum = 0.0;

			for(int j = 0; j < total_values; j++)
			{
				sum += pow(clusters[i].getCentralValue(j) -
						   point.getValue(j), 2.0);
			}

			dist = sqrt(sum);

			if(dist < min_dist)
			{
				min_dist = dist;
				id_cluster_center = i;
			}
		}

		return id_cluster_center;
	}



vector<double> KMeans::K_means_run(vector<Vec3b> SuperPixelValues){

	
//cout << "Entering K Means Run Function \n";
// note TODO make sure that this goes into the run method. 
	vector<Vec3b> SuperPixelValues1 ;
	SuperPixelValues1 = SuperPixelValues;
	int total_points, total_values, K, max_iterations, has_name;
	total_points = SuperPixelValues1.size();				
	total_values = 3;
	K = 3; 								// how many centroids
	max_iterations = 10000;
	has_name = 0;
	//int SuperPixelID1 = SuperPixelID
	vector<Point_K> points;
	string point_name;
	vector<double> cluster_vals;	
	cluster_vals.clear();
	cluster_vals.resize(total_values);
	numTimes++;
	if (numTimes == 1){
		cout << "Kmeans Clustering Running...";
	}


	//run through each superpixel set of pixels 
	for(int i=0; i<total_points; i++) {
		//cout << "run through each superpixel \n";
        	vector<double> values;
		values.resize(3);
        	Vec3b vals = SuperPixelValues1[i];
		//cout << "-------  Pixel Numnber:  " << i << "-------\n";
		for( int j = 0; j < total_values; j++){
			//cout << "run through each RGB value and append onto the vector values\n";	

			
			//cout << "Pixel" << j << ": "  << static_cast<double>(vals.val[j]) << "\n";
			values[j]=static_cast<double>(vals.val[j]);
	
			//	double rgbValue = static_cast<double>(vals.val[j]);
			//	values.push_back(vals)
			Point_K p(i, values);
			points.push_back(p);
		}
		//cout << "-------------------------------------------------\n\n\n";
	}
				
    	
	



	//cin >> total_points >> total_values >> K >> max_iterations >> has_name;

	

/*	for(int i = 0; i < total_points; i++)
	{
		vector<double> values;

		for(int j = 0; j < total_values; j++)
		{
			double value;
			cin >> value;
			values.push_back(value);
		}

		if(has_name)
		{
			cin >> point_name;
			Point p(i, values, point_name);
			points.push_back(p);
		}
		else
		{
			Point p(i, values);
			points.push_back(p);
		}
	}*/

	
		//if(K > total_points)
		//	return;

		vector<int> prohibited_indexes;

		// cout << "choose K distinct values for the centers of the clusters\n"
		for(int i = 0; i < K; i++)
		{
			//cout << "choose K distinct values for the centers of the clusters\n";
			while(true)
			{
				int index_point = rand() % total_points;

				if(find(prohibited_indexes.begin(), prohibited_indexes.end(),
						index_point) == prohibited_indexes.end())
				{
					prohibited_indexes.push_back(index_point);
					points[index_point].setCluster(i);
					Cluster_K cluster(i, points[index_point]);
					clusters.push_back(cluster);
					break;
				}
			}
		}

		int iter = 1;

		while(true)
		{
		//cout << "choose K distinct values for the centers of the clusters\n";
			bool done = true;

			// associates each point to the nearest center
			for(int i = 0; i < total_points; i++)
			{//cout << "associates each point to the nearest center\n";
				int id_old_cluster = points[i].getCluster();
			
				int id_nearest_center = getIDNearestCenter(points[i]);
			
				if(id_old_cluster != id_nearest_center)
				{
					if(id_old_cluster != -1)
						clusters[id_old_cluster].removePoint(points[i].getID());

					points[i].setCluster(id_nearest_center);
					clusters[id_nearest_center].addPoint(points[i]);
					done = false;
				}
			}

			// recalculating the center of each cluster
			for(int i = 0; i < K; i++)
			{//cout << "recalculate the center\n";
				for(int j = 0; j < total_values; j++)
				{
					int total_points_cluster = clusters[i].getTotalPoints();
					double sum = 0.0;

					if(total_points_cluster > 0)
					{
						for(int p = 0; p < total_points_cluster; p++)
							sum += clusters[i].getPoint(p).getValue(j);
						clusters[i].setCentralValue(j, sum / total_points_cluster);
					}
				}
			}

			if(done == true || iter >= max_iterations)
			{
				//cout << "Break in iteration " << iter << "\n\n";
				break;
			}

			iter++;
		}

		
		//cout << "Cluster values for point: " << numTimes << "\n";
		// shows elements of clusters
		//cluster_vals.resize(total_points);
		
		for(int i = 0; i < K; i++)
		{
			int total_points_cluster =  clusters[i].getTotalPoints();

			//cout << "Cluster_K " << clusters[i].getID_cluster() + 1 << endl;
			for(int j = 0; j < total_points_cluster; j++)
			{
				//cout << "Point_K " << clusters[i].getPoint(j).getID() + 1 << ": ";
				for(int p = 0; p < total_values; p++)
					//cout << clusters[i].getPoint(j).getValue(p) << " ";

				string point_name = clusters[i].getPoint(j).getName();

				if(point_name != "")
					cout << "- " << point_name;

				
			}


			
		}
		for(int j = 0; j < total_values; j++){
			//cout << (clusters[0].getCentralValue(j))*1000 << " ";
		}
		//cout << "\n\n";

			
        			
       	
		for (int y =0; y < total_values; y++){
	           	cluster_vals[y]= (clusters[0].getCentralValue(y)); // Set up the Cluster Values for sending to the SuperBE Algorithm
			//cout << "Cluster  "<< y <<": " << cluster_vals[y] << " -----------\n";
	           }	
		//cout << "\n\n";
		
		return cluster_vals;
		
		if (numTimes == total_values){
			numTimes = 0;
		}
	}



void kmeans_main(int argc, char *argv[], int total_points1, int total_values1, int K1, int max_iterations1, int has_name1)
{

	

	
}
