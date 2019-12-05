#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <utility>

using namespace std;

void dijkstraShortestPath(int gSize, int srcNode, vector<vector<int> > &adjacencyMatrix, vector<int> &shortestPath, vector<int> &pred)
{
  for (int j = 0; j < gSize; j++)
  {
    shortestPath.push_back(adjacencyMatrix[srcNode][j]);

    //If adjacency is true
    if (adjacencyMatrix[srcNode][j] == 1)
    {
      pred[j] = srcNode; //Initialize the predecessor of that city to srcNode
    }
  }

  bool *shortestPathFound;
  shortestPathFound = new bool[gSize];

  //Initialize to all false for shortestPathFound
  for (int j = 0; j < gSize; j++)
  {
    shortestPathFound[j] = false;
  }

  shortestPathFound[srcNode] = true;
  shortestPath[srcNode] = 0; //0 to distance to reach origin
  pred[0] = 0; //Reach origin from origin

  for (int i = 0; i < gSize - 1; i++)
  {
      int minDistance = INT_MAX; //Pseudo-infinity
      int v;

      for (int j = 0; j < gSize; j++)
      {
        if (!shortestPathFound[j])
        {
          if (shortestPath[j] < minDistance)
          {
              v = j;
              minDistance = shortestPath[v];
          }
        }
      }

      shortestPathFound[v] = true;

      for (int j = 0; j < gSize; j++)
      {
        if (!shortestPathFound[j])
        {
          if (minDistance + adjacencyMatrix[v][j] < shortestPath[j])
          {
            shortestPath[j] = minDistance + adjacencyMatrix[v][j];
            pred[j] = v; //Update pred if smaller route found
          }
        }
      }
  } //end for
} //end shortestPath


int main(int argc, char** argv)
{
  //Input county names
  vector<string> countyNames;
  ifstream ins;
  ins.open(argv[1]);
  string line;
  getline(ins, line);
  stringstream ss;
  ss << line;
  string county;
  while (!ss.eof())
  {
    ss >> county;
    countyNames.push_back(county);
  }

  // Get adjacency matrix
  vector<vector<int> > adjacencyMatrix;
  getline(ins, line);
  while (!ins.eof())
  {
    stringstream ss;
    ss << line;
    string trash;
    ss >> trash;
    vector<int> row;
    int val;
    while (!ss.eof())
    {
      ss >> val;
      if (val == 0) val = 100000;
      row.push_back(val);
    }
    adjacencyMatrix.push_back(row);
    getline(ins, line);
  }
  ins.close();

  vector<vector<int> > distanceMatrix;

  for (size_t i = 0; i < adjacencyMatrix.size(); i++)
  {
    vector<int> shortestPath; //Hold shortest path to any given node when done

    //Hold predecessor to given visited county, -1 means never reached
    vector<int> pred (adjacencyMatrix.size(), -1);

    dijkstraShortestPath(adjacencyMatrix.size(), i, adjacencyMatrix, shortestPath, pred);

    distanceMatrix.push_back(shortestPath);
  }

  for (size_t i = 0; i < distanceMatrix.size(); i++)
  {
    for (size_t j = 0; j < distanceMatrix.size(); j++)
    {
      cout << distanceMatrix[i][j] << " ";
    }
    cout << endl;
  }
  return EXIT_SUCCESS;
}
