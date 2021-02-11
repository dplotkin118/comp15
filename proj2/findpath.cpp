/*
 * findpath.cpp
 * COMP15
 * Daniel Plotkin (dplotk01)
 * Spring 2020
 *
 * Main driver for the implementation of the floo network
 */

#include "graph.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
  if (argc < 3){
    cerr << "Usage: findpath vertex_data edge_data" << endl;
    return 0;
  }
  Graph graph;
  string infile = argv[1];
  if(!graph.read_vertices(infile)){
    return 0;
  }
  string second_infile = argv[2];
  if(!graph.read_edges(second_infile)){
    return 0;
  }
  graph.run_program();
  return 0;
}
