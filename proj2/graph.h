/*
 * graph.h
 * COMP15
 * Daniel Plotkin (dplotk01)
 * Spring 2020
 *
 * Interface of the graph class.
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;


struct Vertex {
  string name;
  double lat_degrees, lat_minutes, long_degrees, long_minutes;
  bool checked;
  vector<Vertex*> neighbors;
};

class Graph {

public:
  //constructor
  Graph();
  //destructor
  ~Graph();
  //adds a vertex to the network
  void add_vertex(string name, double lat1, double lat2, double long1,
                         double long2, vector<Vertex*> neighbors);
  //adds an edge to the network
  void add_edge(string origin, string destination);
  //reads in vertices from a .vdat file and adds them to the network
  bool read_vertices(string filename);
  //reads in edges from a .adat file and adds them to the network
  bool read_edges(string filename);
  //prints the names of all vertices of the graph
  void print_graph();
  //the main driver function of the program. Allows for user input
  void run_program();
  //computes the latitude in degrees of a location
  double compute_lat_degrees(string loc);
  //computes the longitude in degrees of a location
  double compute_long_degrees(string loc);
  //computes the distance between two sets of latitudes and longitudes
  double compute_distance(double lat1, double lat2, double long1, double long2,
                          string loc1, string loc2);
  //prints out maxpaths number of paths between two cities
  void path(string city1, string city2, int maxpaths);
  //converts a string to its corresponding vertex
  Vertex *string_to_vertex(string loc);
  //checks if a location name is in the network
  bool is_in(string loc);
  //print function for path
  void print_locations(vector<Vertex> locations, int &iterations);
  //determines whether there is a path between two locations
  bool is_path(string loc1, string loc2);
  //prints a location's neighbors
  void print_neighbors(string loc);
  //helper function for path
  void print_paths(Vertex *current, Vertex *end, vector<Vertex> &paths,
                    int &maxpaths, int &iteration);




private:
  vector<Vertex> network;



};

#endif
