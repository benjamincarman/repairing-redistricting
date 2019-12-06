#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace cv;
using namespace std;

void colorCounty(Mat &map, int x, int y, Vec3b color)
{
  Vec3b white(255, 255, 255);
  if (map.at<Vec3b>(Point(x,y)) != color)
  {
    map.at<Vec3b>(Point(x,y)) = color;
  }

  if (x > 0 && y > 0 && map.at<Vec3b>(Point(x-1,y-1)) == white) colorCounty(map, x-1, y-1, color);
  if (x > 0 && map.at<Vec3b>(Point(x-1,y)) == white) colorCounty(map, x-1, y, color);
  if (x > 0 && y < map.rows && map.at<Vec3b>(Point(x-1,y+1)) == white) colorCounty(map, x-1, y+1, color);
  if (y > 0 && map.at<Vec3b>(Point(x,y-1)) == white) colorCounty(map, x, y-1, color);
  if (y < map.rows && map.at<Vec3b>(Point(x,y+1)) == white) colorCounty(map, x, y+1, color);
  if (x < map.cols && y > 0 && map.at<Vec3b>(Point(x+1,y-1)) == white) colorCounty(map, x+1, y-1, color);
  if (x < map.cols && map.at<Vec3b>(Point(x+1,y)) == white) colorCounty(map, x+1, y, color);
  if (x < map.cols && y < map.rows && map.at<Vec3b>(Point(x+1,y+1)) == white) colorCounty(map, x+1, y+1, color);
}

int main(int argc, char** argv)
{
  //Read in image from input
  if (argc < 6)
  {
    cout << "Proper use is ./mapColoring <image-name> <county-locations> <district-choices> <blues> <reds> <leansDemocrat>" << endl;
    return EXIT_FAILURE;
  }

  Mat map = imread(argv[1], 1);
  if (map.empty()) {return -1;}

  //Input county locations
  vector<pair<int, int> > locations;
  ifstream ins;
  ins.open(argv[2]);
  string line;
  getline(ins, line);
  while (!ins.eof())
  {
    stringstream ss;
    ss << line;
    string trash;
    ss >> trash;
    int x, y;
    ss >> x;
    ss >> y;
    locations.push_back(make_pair(x, y));
    getline(ins, line);
  }
  ins.close();

  //Input district choices
  vector<int> districtChoices;
  ins.open(argv[3]);
  getline(ins, line);
  while (!ins.eof())
  {
    stringstream ss;
    ss << line;
    string trash;
    ss >> trash;

    string val;
    ss >> val;
    int count = 0;
    while (val != "1")
    {
      count++;
      ss >> val;
    }
    districtChoices.push_back(count);
    getline(ins, line);
  }
  ins.close();

  //Input blue color choices
  vector<Vec3b> blues;
  ins.open(argv[4]);
  getline(ins, line);
  while (!ins.eof())
  {
    stringstream ss;
    ss << line;
    int rval, gval, bval;
    ss >> rval;
    ss >> gval;
    ss >> bval;
    Vec3b color(rval, gval, bval);
    blues.push_back(color);
    getline(ins, line);
  }
  ins.close();

  //Input red color choices
  vector<Vec3b> reds;
  ins.open(argv[5]);
  getline(ins, line);
  while (!ins.eof())
  {
    stringstream ss;
    ss << line;
    int rval, gval, bval;
    ss >> rval;
    ss >> gval;
    ss >> bval;
    Vec3b color(rval, gval, bval);
    reds.push_back(color);
    getline(ins, line);
  }
  ins.close();

  //Input leansDemocrat
  vector<bool> leansDemocrat;
  ins.open(argv[6]);
  getline(ins, line);
  while (!ins.eof())
  {
    stringstream ss;
    ss << line;
    string trash;
    ss >> trash;
    int val;
    ss >> val;
    if (val == 0)
    {
      leansDemocrat.push_back(false);
    }
    else
    {
      leansDemocrat.push_back(true);
    }
    getline(ins, line);
  }
  ins.close();

  //Set district colors based on leansDemocrat
  vector<Vec3b> districtColors(16);
  size_t numDem = 0;
  size_t numRep = 0;
  for (size_t i = 0; i < 16; i++)
  {
    if (leansDemocrat[i] == true)
    {
      districtColors[i] = blues[numDem];
      numDem++;
    }
    else
    {
      districtColors[i] = reds[numRep];
      numRep++;
    }
  }

  for (size_t i = 0; i < locations.size(); i++)
  {
    colorCounty(map, locations[i].first, locations[i].second, districtColors[districtChoices[i]]);
    //circle(map, Point(locations[i].first, locations[i].second), 5, Scalar(0, 0, 0), -1);
  }

  string imName = argv[3];
  imName = imName.substr(0, imName.size() - 4) + ".jpg";
  imwrite(imName, map);

  namedWindow("Colored Map", WINDOW_AUTOSIZE);
  imshow("Colored Map", map);
  waitKey(0);
  destroyWindow("Colored Map");

  return EXIT_SUCCESS;
}
