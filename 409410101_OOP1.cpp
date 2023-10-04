#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <climits>

using namespace std;

class Neighborhood{

  public:
    int neighborId;
    int old_weight;
    int new_weight;

};

class NODE{

  public:
    vector<Neighborhood> neighbor;
    map<unsigned int, unsigned int> OldPath;
    map<unsigned int, unsigned int> NewPath; // Path[destination] = Nextnode

};

class NODE node[1000];

int main()
{

  int num_node = 0, num_destination = 0, links = 0;
  int destination[1000] = {0};

  // get the information
  cin >> num_node >> num_destination >> links;
  for(int i = 0;i < num_destination;i++){

    cin >> destination[i];

  }

  // get the node
  int linkid = 0, node1 = 0, node2 = 0, oldW = 0, newW = 0;
  Neighborhood temp;

  for(int i = 0;i < links;i++){

    cin >> linkid >> node1 >> node2 >> oldW >> newW;

    // store their neighbor

    temp.old_weight = oldW;
    temp.new_weight = newW;
    temp.neighborId = node2;
    node[node1].neighbor.push_back(temp);  // store node1's neighbor
    temp.neighborId = node1;
    node[node2].neighbor.push_back(temp);  // store node2's neighbor

  }

  // find their shortest path between each node and destination ( OldPath )
  for(int i = 0;i < num_destination;i++){

    int visited[1000] = {0};
    int distance[1000] = {0};  // record the distance between the node and destination
    // initialize
    for(int t = 0;t < num_node;t++){
      distance[t] = INT_MAX;
    }

    // shortest path
    int NowNode = destination[i];
    distance[NowNode] = 0;

    for(int k = 0;k < num_node;k++){

      // find the smallest distance not yet check
      int Min = INT_MAX;
      NowNode = -1;
      for(int t = 0;t < num_node;t++){
        if(distance[t] < Min && !visited[t]){
          Min = distance[t];
          NowNode = t;
        }
      }

      visited[NowNode] = 1; //the node has been visited already
      int neighborsize = node[NowNode].neighbor.size();
      for(int t = 0;t < neighborsize;t++){

        if( !visited[node[NowNode].neighbor[t].neighborId] && (distance[NowNode]+node[NowNode].neighbor[t].old_weight) <= distance[node[NowNode].neighbor[t].neighborId] ){  // if the new path is shorter than old one, change the record

          // change record
          // compare the old record, if the distance is the same, but the number of destination of node if smaller than the old one, change it
          map<unsigned int, unsigned int>:: iterator iter;
          iter = node[node[NowNode].neighbor[t].neighborId].OldPath.find(destination[i]);
          if((distance[NowNode]+node[NowNode].neighbor[t].old_weight) < distance[node[NowNode].neighbor[t].neighborId]){
            node[node[NowNode].neighbor[t].neighborId].OldPath[destination[i]] = NowNode;
          }
          else if( iter != node[node[NowNode].neighbor[t].neighborId].OldPath.end() && (unsigned int)NowNode < iter->second){
            node[node[NowNode].neighbor[t].neighborId].OldPath[destination[i]] = NowNode;
          }
          distance[node[NowNode].neighbor[t].neighborId] = distance[NowNode]+node[NowNode].neighbor[t].old_weight;

        }

      }

    }

  }


  // find their shortest path between each node and destination ( NewPath )
  for(int i = 0;i < num_destination;i++){

    int visited[1000] = {0};
    int distance[1000] = {0};  // record the distance between the node and destination
    // initialize
    for(int t = 0;t < num_node;t++){
      distance[t] = INT_MAX;
    }

    // shortest path
    int NowNode = destination[i];

    distance[NowNode] = 0;

   for(int k = 0;k < num_node;k++){

      // find the smallest distance not yet check
      int Min = INT_MAX;
      NowNode = -1;
      for(int t = 0;t < num_node;t++){
        if(distance[t] < Min && !visited[t]){
          Min = distance[t];
          NowNode = t;
        }
      }

      visited[NowNode] = 1;  //the node has been visited already
      int neighborsize = node[NowNode].neighbor.size();
      for(int t = 0;t < neighborsize;t++){

        if( !visited[node[NowNode].neighbor[t].neighborId] && (distance[NowNode]+node[NowNode].neighbor[t].new_weight) <= distance[node[NowNode].neighbor[t].neighborId] ){  // if the new path is shorter than old one, change the record

          // change record
          // compare the old record, if the distance is the same, but the number of destination of node if smaller than the old one, change it
          map<unsigned int, unsigned int>:: iterator iter;
          iter = node[node[NowNode].neighbor[t].neighborId].NewPath.find(destination[i]);
          if((distance[NowNode]+node[NowNode].neighbor[t].new_weight) < distance[node[NowNode].neighbor[t].neighborId]){
            node[node[NowNode].neighbor[t].neighborId].NewPath[destination[i]] = NowNode;
          }
          else if( iter != node[node[NowNode].neighbor[t].neighborId].NewPath.end() && (unsigned int)NowNode < iter->second){
            node[node[NowNode].neighbor[t].neighborId].NewPath[destination[i]] = NowNode;
          }
          distance[node[NowNode].neighbor[t].neighborId] = distance[NowNode]+node[NowNode].neighbor[t].new_weight;

        }

      }

    }

  }

  //print the old path
  map<unsigned int, unsigned int>::iterator iter,same;

  for(int i = 0;i < num_node;i++){
    cout << i << endl;
    for(iter = node[i].OldPath.begin();iter != node[i].OldPath.end();++iter){
      cout << iter->first << " " << iter->second << endl;
      // look into the NewPath, if they have the same value in OldPath, delete it.
      same = node[i].NewPath.find(iter->first);
      if(same->second == iter->second){  // find it, and delete
        node[i].NewPath.erase(same);
      }
    }
  }

  // print the path which is changed
  for(int i = 0;i < num_node;i++){
    if(!node[i].NewPath.empty()){
      cout << i << endl;
      for(iter = node[i].NewPath.begin();iter != node[i].NewPath.end();++iter){
        cout << iter->first << " " << iter->second << endl;
      }
    }
  }

  return 0;
}
