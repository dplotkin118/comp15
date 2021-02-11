/*
 * graph.cpp
 * COMP15
 * Daniel Plotkin (dplotk01)
 * Spring 2020
 *
 * Implementation of the graph class.
 */


#include <iostream>
#include "graph.h"
#include "Location.h"

using namespace std;

Graph::Graph(){}

Graph::~Graph(){}


/*
 *
 * add_vertex
 * Purpose: add a vertex to the network of vertices
 * Arguments - string name, four doubles of latitude and longitude hours and
 * minutes, and a vector of vertices of its neighbors
 * Returns: none
 * Effects: adds a new vertex to the network vector
 * Notes: bool checked is always initialized as false
 */
void Graph::add_vertex(string name, double lat1, double lat2, double long1,
                       double long2, vector<Vertex*> neighbors){
    Vertex new_vertex = {name, lat1, lat2, long1, long2, false, neighbors};
    network.push_back(new_vertex);
}
/*
 * add_edge
 * Purpose: add an edge to the network
 * Arguments - string name of origin, string name of destination
 * Returns: none
 * Effects: adds a new edge to the neighbors vector in the given origin
 * Notes: none
 */
void Graph::add_edge(string origin, string destination){
  for (int i = 0; i < int(network.size()); i++){
    if (network[i].name == origin){
      for (int j = 0; j < int(network.size()); j++){
        if (network[j].name == destination){
          network[i].neighbors.push_back(&network[j]);
        }
      }
    }
  }

}

/*
 * read_vertices
 * Purpose: reads in a file of vertices and adds them to the network
 * Arguments - string name of file
 * Returns: boolean true or false whether the file succeeded in opening
 * Effects: adds read in vertices to the network
 * Notes: uses add_vertex
 */
bool Graph::read_vertices(string filename){
  ifstream infile(filename.c_str());
  if (infile.fail()){
    cerr << "Unable to open " << filename << endl;
    return false;
  }
  string name;
  double lat1, lat2, long1, long2;
  vector<Vertex*> neighbors;
  while(infile >> name){
    infile >> lat1;
    infile >> lat2;
    infile >> long1;
    infile >> long2;
    add_vertex(name, lat1, lat2, long1, long2, neighbors);
  }
  return true;
}

/*
 * read_edges
 * Purpose: reads in a file of edges and adds them to the network
 * Arguments - string name of file
 * Returns: boolean true or false whether the file succeeded in opening
 * Effects: adds read in edges to the corresponding vertices' vectors
 * Notes: uses add_edge
 */
bool Graph::read_edges(string filename){
  ifstream infile(filename.c_str());
  if (infile.fail()){
    cerr << "Unable to open " << filename << endl;
    return false;
  }
  string origin, destination;
  while(infile >> origin){
    infile >> destination;
    add_edge(origin, destination);
  }
  return true;
}

/*
 * print_graoh
 * Purpose: prints all vertex names in order
 * Arguments - none
 * Returns: none
 * Effects: none
 * Notes: prints with an endline after each vertex
 */
void Graph::print_graph(){
  for (int i = 0; i < int(network.size()); i++){
    cout << network[i].name << endl;
  }
  cout << "-EOT-" << endl;
}

/*
 * compute_lat_degrees
 * Purpose: computes the latitude degrees from hours and minutes
 * Arguments: string name of location
 * Returns: a double of degree decimal latitude
 * Effects: none
 * Notes: does not use seconds
 */
double Graph::compute_lat_degrees(string loc){
    if (!is_in(loc)){
      return -1;
    }
    Vertex *loc_vec;
    for (int i = 0; i < int(network.size()); i++){
         if (network[i].name == loc){
             loc_vec = &network[i];
         }
    }
     double lat_decimal;
     if (loc_vec->lat_degrees > 0){
         lat_decimal = loc_vec->lat_degrees + (loc_vec->lat_minutes / 60);
     }
     else{
         lat_decimal = -(abs(loc_vec->lat_degrees) + (loc_vec->lat_minutes / 60));
     }

     return lat_decimal;
}

/*
 * compute_long_degrees
 * Purpose: computes the longitude degrees from hours and minutes
 * Arguments: string name of location
 * Returns: a double of degree decimal longitude
 * Effects: none
 * Notes: does not use seconds
 */
double Graph::compute_long_degrees(string loc){
    if (!is_in(loc)){
      return -1;
    }
    Vertex *loc_vec;
    for (int i = 0; i < int(network.size()); i++){
         if (network[i].name == loc){
             loc_vec = &network[i];
         }
    }
     double long_decimal;
     if (loc_vec->long_degrees > 0){
         long_decimal = loc_vec->long_degrees + (loc_vec->long_minutes / 60);
     }
     else{
         long_decimal = -(abs(loc_vec->long_degrees) + (loc_vec->long_minutes / 60));
     }
     return long_decimal;
}

/*
 * compute_distance
 * Purpose: compute the distance between a set of latitudes and longitudes
 * Arguments: 4 doubles of latitude and longitude, 2 string names of locations
 * Returns: a distance, represented by a double
 * Effects: none
 * Notes: none
 */
double Graph::compute_distance(double lat1, double lat2, double long1,
                               double long2, string loc1, string loc2)
{
     if (!is_in(loc1) || !is_in(loc2)){
       return -1;
     }
     Location *location1 = new Location(lat1, long1);
     Location *location2 = new Location(lat2, long2);
     string city1 = location1->to_string();
     string city2 = location2->to_string();
     double distance;
     distance = location1->distance_to(location2);
     return distance;
}

/*
 * run_program
 * Purpose: main driver of the program, allows for user input
 * Arguments: none
 * Returns: none
 * Effects: allows user input of command names and values
 * Notes: limited to the commands quit, list, dist, and path
 */
void Graph::run_program(){
    bool running = true;
    string input;
    while(running){
      cin >> input;
      if (input == "quit"){
        running = false;
      }
      else if (input == "list"){
        print_graph();
      }
      else if (input == "dist"){
        string loc1, loc2;
        cin >> loc1 >> loc2;
        double lat1, lat2, long1, long2, distance;
        lat1 = compute_lat_degrees(loc1);
        lat2 = compute_lat_degrees(loc2);
        long1 = compute_long_degrees(loc1);
        long2 = compute_long_degrees(loc2);
        distance = compute_distance(lat1, lat2, long1, long2, loc1, loc2);
        cout << setprecision(2) << fixed;
        cout << distance << endl << "-EOT-" << endl;
      }
      else if (input == "path"){
        string loc1, loc2;
        int maxpaths;
        cin >> loc1 >> loc2 >> maxpaths;
        path(loc1, loc2, maxpaths);
      }
    }
}

/*
 * string_to_vertex
 * Purpose: converts a string into its corresponding vertex in the network
 * Arguments: string name of location in network
 * Returns: a pointer to a vertex in the network
 * Effects: none
 * Notes: none
 */
Vertex *Graph::string_to_vertex(string loc){
  Vertex *loc_vec;
  for (int i = 0; i < int(network.size()); i++){
       if (network[i].name == loc){
           loc_vec = &network[i];
       }
  }
  return loc_vec;
}

/*
 * path
 * Purpose: finds and prints maxpaths number of paths between two locations
 * Arguments: two string location names, integer max number of paths printed
 * Returns: none
 * Effects: prints if there are errors, changes all members to be unchecked
 * Notes: calls print_paths, the helper function, to do the path recursion
 */
void Graph::path(string loc1, string loc2, int maxpaths){
  for (int i = 0; i < int(network.size()); i++){
    network[i].checked = false;
  }
  if ( !is_in(loc1) || !is_in(loc2)){
    cout << loc1 << " " << loc2 << endl;
    cout << "ERROR: unknown city" << endl;
    return;
  }
  Vertex *city1 = string_to_vertex(loc1);
  Vertex *city2 = string_to_vertex(loc2);
  if (!is_path(city1->name, city2->name) || maxpaths <= 0){
    cout << "ERROR: no-path-possible" << endl;
    return;
  }
  vector <Vertex> paths;
  for (int i = 0; i < int(network.size()); i++){
    network[i].checked = false;
  }
  int iterations = 0;
  print_paths(city1, city2, paths, maxpaths, iterations);
  cout << "-EOT-" << endl;

}
/*
 * print_paths
 * Purpose: recursive helper function of path, finds maxpath number of paths
 * and prints them
 * Arguments: a starting and ending vertex, a vector of vertices of the paths,
 * the maximum number of paths, and the iteration number
 * Returns: none
 * Effects: changes checked status of members
 * Notes: calls print_locations function for actual printing
 */
void Graph::print_paths(Vertex *current, Vertex *end, vector<Vertex> &paths,
                        int &maxpaths, int &iteration)
{
  if (maxpaths > 0){
    current->checked = true;
    paths.push_back(*current);

    if (current->name == end->name){
      iteration++;
      print_locations(paths, iteration);
      maxpaths--;
    }
    else{
      for (int i = 0; i < int(current->neighbors.size()); i++){
        if (!current->neighbors[i]->checked){
          print_paths(current->neighbors[i], end, paths, maxpaths, iteration);
        }
      }
    }
    paths.pop_back();
    current->checked = false;
  }
}

/*
 * is_in
 * Purpose: determines whether a location is in the network
 * Arguments: string name of location in network
 * Returns: a boolean true or false
 * Effects: none
 * Notes: none
 */
bool Graph::is_in(string loc){
  for (int i = 0; i < int(network.size()); i++){
    if (network[i].name == loc){
      return true;
    }
  }
  return false;
}
/*
 * print_locations
 * Purpose: final helped function of path, prints names, lat, long, and
 * distances of cities in the path
 * Arguments: vector of vertices of locations, int number of iterations
 * Returns: none
 * Effects: prints
 * Notes: none
 */
void Graph::print_locations(vector <Vertex> locations, int &iterations){
  vector <string> names;
  vector <double> latitudes;
  vector <double> longitudes;
  vector <int> distances;
  for (int i = 0; i < int(locations.size()); i++){
    names.push_back(locations[i].name);
  }
  for (int i = 0; i < int(names.size()); i++){
    double lats;
    lats = compute_lat_degrees(names[i]);
    latitudes.push_back(lats);
  }
  for (int i = 0; i < int(names.size()); i++){
    double longs;
    longs = compute_long_degrees(names[i]);
    longitudes.push_back(longs);
  }
  distances.push_back(0);
  for (int i = 0; i < int(names.size()) - 1; i++){
    int distance;

    distance = compute_distance(latitudes[i], latitudes[i+1], longitudes[i],
                                longitudes[i+1], names[i], names[i + 1]);
    distances.push_back(distance);
  }
  cout << "PATH " << iterations << " ::";
  for (int i = 0; i < int(names.size()); i++){
    cout << " " << distances[i] << " " << names[i] << " ";
    cout << setprecision(2) << fixed << latitudes[i] << " " << longitudes[i];
  }
  cout << endl;

}

/*
 * is_path
 * Purpose: recursively determines if there is a path between two locations
 * Arguments: two string names of locations
 * Returns: a boolean
 * Effects: changes checked status of locations
 * Notes: none
 */
bool Graph::is_path(string loc1, string loc2){
  Vertex *city1 = string_to_vertex(loc1);
  Vertex *city2 = string_to_vertex(loc2);
  city1->checked = true;
  if (city1->name == city2->name){
    return true;
  }
  else{
    for (int i = 0; i < int(city1->neighbors.size()); i++){
      if (!city1->neighbors[i]->checked){
        if (is_path(city1->neighbors[i]->name, city2->name)){
          return true;
        }

      }
    }
  }
  return false;
}

/*
 * print_neighbors
 * Purpose: prints the neighbors of a given location
 * Arguments: string name of location
 * Returns: none
 * Effects: prints
 * Notes: none
 */
void Graph::print_neighbors(string loc){
  Vertex *city = string_to_vertex(loc);
  for (int i = 0; i < int(city->neighbors.size()); i++){
    cout << city->neighbors[i]->name << endl;
  }
}
