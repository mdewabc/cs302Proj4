// dijsktras.cpp
//Andrew Hines
//This program finds the shortest path for the player to travel through the environment
//Different parts of the environment have different weights

#include <iostream>
#include <map>
#include <iterator>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;
// Main Execution

struct Node{//Node struct
  int row=0;
  int col=0;
  char id=' ';
  int weight=0;
  Node* backedge=nullptr;
  bool visited=false;
  int distance=-1;
};


int main(int argc, char *argv[]) {
  map<char,int> tilesMap;//Map of the tiles using their chars and keys and storing their weights
  int numtiles;
  int rows;
  int cols;
  cin>>numtiles;
  char id;
  int value;

  for(int i=0;i<numtiles;i++){
    cin>>id;
    cin>>value;
    tilesMap.insert(pair<char,int>(id,value));
  }
  

  cin>>rows;
  cin>>cols;
  
  
  multimap<int, Node*> djMap;
  multimap<int, Node*>::iterator worker;
  vector<Node*> nodeVect;
  map<char,int>::iterator it;
  
  char input;
  //cin the graph and put them into a 1d vector
  for(int i=0;i<cols*rows;i++){
    cin>>input;
    Node* inNode=new Node;
    inNode->row=i/cols;
    inNode->col=i%cols;
    inNode->id=input;
    it=tilesMap.find(input);
    inNode->weight=it->second;
    nodeVect.push_back(inNode);
  }
    
  //fill the map
  Node* zerNode=nodeVect[0];
  zerNode->distance=0;
  djMap.insert(pair<int, Node*>(0,zerNode));
  
  
  bool done=false;
  multimap <int, Node*>::iterator loopitr;
  int d;
  while(!done){
    Node* workerNode;
    //for(auto &loopitr:djMap){
    for(auto loopitr = djMap.begin(); loopitr!= djMap.end();loopitr++){

      workerNode=loopitr->second;
      if(workerNode==nullptr){
        break;
      }

      if(workerNode->visited){
        continue;
      }
      if(workerNode->distance!=loopitr->first){
        continue;
      }
      workerNode->visited=true;
      Node* checkNode;
      if(workerNode->row!=0){//check above
        checkNode=nodeVect.at((((workerNode->row)*cols)+workerNode->col)-cols);
        d=workerNode->distance+checkNode->weight;
        if((checkNode->distance==-1)||(d<checkNode->distance)){
          checkNode->distance=d;
          checkNode->backedge=workerNode;
          djMap.insert(pair<int, Node*>(d,checkNode));
        }
      }
      if(workerNode->row<rows-1){//check below
        checkNode=nodeVect.at((((workerNode->row)*cols)+workerNode->col)+cols);
        d=workerNode->distance+checkNode->weight; 
        if((checkNode->distance==-1)||(d<checkNode->distance)){
          checkNode->distance=d;
          checkNode->backedge=workerNode;
          djMap.insert(pair<int, Node*>(d,checkNode));
        }
      }
      if(workerNode->col<cols-1){//check to the right
        checkNode=nodeVect.at((((workerNode->row)*cols)+workerNode->col)+1);
        d=workerNode->distance+checkNode->weight;
        if((checkNode->distance==-1)||(d<checkNode->distance)){
          checkNode->distance=d;
          checkNode->backedge=workerNode;
          djMap.insert(pair<int, Node*>(d,checkNode));
        }
      }
      if(workerNode->col!=0){//check to the left
        checkNode=nodeVect.at((((workerNode->row)*cols)+workerNode->col)-1);
        d=workerNode->distance+checkNode->weight;
        if((checkNode->distance==-1)||(d<checkNode->distance)){
          checkNode->distance=d;
          checkNode->backedge=workerNode;
          djMap.insert(pair<int, Node*>(d,checkNode));
        }
      }

      if(loopitr->second==nodeVect.at((rows*cols)-1)){
        done=true;  
      }
    }
  }
  int startrow;
  int startcol;
  cin>>startrow;
  cin>>startcol;
  int endrow;
  int endcol;
  cin>>endrow;
  cin>>endcol;

  //List to print the nodes in proper reverse order
  list<Node*> printList;
  Node* minPath=nodeVect.at((endrow*cols)+endcol);
  int distOrigin=minPath->distance;
  //This is because of the way weight is added, I am adding the end index's weight not the beginning. This Fixes that by subtracting the difference
  
  
  
  
  
  unsigned int diffWeight=(nodeVect.at((startrow*cols)+startcol)->weight)-(nodeVect.at((endrow*cols)+endcol)->weight);
  distOrigin=distOrigin+diffWeight;
  

  while(minPath!=nullptr){
    printList.push_front(minPath);
    if((minPath->row==startrow)&&(minPath->col==startcol)){
      break;
    }
    minPath=minPath->backedge;
  }
  cout<<(distOrigin-minPath->distance)<<endl;
  while(!printList.empty()){
    minPath=printList.front();
    cout<<minPath->row<<" "<<minPath->col<<endl;
    printList.pop_front();
  }
  for(unsigned int i=0;i<nodeVect.size();i++){
    delete nodeVect.at(i);
  }
  
  
  
  
  return 0;
}
/*
// dijsktras.cpp
//Andrew Hines
//This program finds the shortest path for the player to travel through the environment
//Different parts of the environment have different weights

#include <iostream>
#include <map>
#include <iterator>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;
// Main Execution

struct Node{ 
  int row=0;
  int col=0;
  char id=' ';
  int weight=0;
  Node* backedge=nullptr;
  bool visited=false;
  int distance=-1;
};


int main(int argc, char *argv[]) {
  map<char,int> tilesMap;
  int numtiles;
  int rows;
  int cols;
  cin>>numtiles;
  char id;
  int value;

  //This may not be needed since the values are usually the same for all the inputs
  //But throwing away those cin lines feels like bad coding
  //And the makefile might test with diff values, if not I can delete later
  for(int i=0;i<numtiles;i++){
    cin>>id;
    cin>>value;
    tilesMap.insert(pair<char,int>(id,value));
  }
  

  cin>>rows;
  cin>>cols;
  
  
  multimap<int, Node*> djMap;
  multimap<int, Node*>::iterator worker;
  vector<Node*> nodeVect;
  map<char,int>::iterator it;
  
  char input;
  //cin the graph
  for(int i=0;i<cols*rows;i++){
    cin>>input;
    Node* inNode=new Node;
    inNode->row=i/cols;
    inNode->col=i%cols;
    inNode->id=input;
    it=tilesMap.find(input);
    inNode->weight=it->second;
    nodeVect.push_back(inNode);
  }
    
  //fill the map
  Node* zerNode=nodeVect[0];
  zerNode->distance=0;
  djMap.insert(pair<int, Node*>(0,zerNode));
  
  
  bool done=false;
  multimap <int, Node*>::iterator loopitr;
  int d;
  while(!done){
    Node* workerNode;
    //for(auto &autoit:djMap){
    for(loopitr = djMap.begin(); loopitr!= djMap.end();loopitr++){

      workerNode=loopitr->second;
      if(workerNode==nullptr){
        break;
      }

      if(workerNode->visited){
        continue;
      }
      if(workerNode->distance!=loopitr->first){
        continue;
      }
      workerNode->visited=true;
      Node* checkNode;
      if(workerNode->row!=0){//check above
        checkNode=nodeVect.at((((workerNode->row)*cols)+workerNode->col)-cols);
        d=workerNode->distance+checkNode->weight;
        if((checkNode->distance==-1)||(d<checkNode->distance)){
          checkNode->distance=d;
          checkNode->backedge=workerNode;
          djMap.insert(pair<int, Node*>(d,checkNode));
        }
      }
      if(workerNode->row<rows-1){//check below
        checkNode=nodeVect.at((((workerNode->row)*cols)+workerNode->col)+cols);
        d=workerNode->distance+checkNode->weight; 
        if((checkNode->distance==-1)||(d<checkNode->distance)){
          checkNode->distance=d;
          checkNode->backedge=workerNode;
          djMap.insert(pair<int, Node*>(d,checkNode));
        }
      }
      if(workerNode->col<cols-1){//check to the right
        checkNode=nodeVect.at((((workerNode->row)*cols)+workerNode->col)+1);
        d=workerNode->distance+checkNode->weight;
        if((checkNode->distance==-1)||(d<checkNode->distance)){
          checkNode->distance=d;
          checkNode->backedge=workerNode;
          djMap.insert(pair<int, Node*>(d,checkNode));
        }
      }
      if(workerNode->col!=0){//check to the left
        checkNode=nodeVect.at((((workerNode->row)*cols)+workerNode->col)-1);
        d=workerNode->distance+checkNode->weight;
        if((checkNode->distance==-1)||(d<checkNode->distance)){
          checkNode->distance=d;
          checkNode->backedge=workerNode;
          djMap.insert(pair<int, Node*>(d,checkNode));
        }
      }
      djMap.erase(djMap.begin());
    }
    if(djMap.empty()){
      done=true;  
    }
  }
  int startrow;
  int startcol;
  cin>>startrow;
  cin>>startcol;
  int endrow;
  int endcol;
  cin>>endrow;
  cin>>endcol;

  //List to print the nodes in proper reverse order
  list<Node*> printList;
  Node* minPath=nodeVect.at((endrow*cols)+endcol);
  int distOrigin=minPath->distance;
  //This is because of the way weight is added, I am adding the end index's weight not the beginning. This Fixes that by subtracting the difference
  
  
  
  
  
  unsigned int diffWeight=(nodeVect.at((startrow*cols)+startcol)->weight)-(nodeVect.at((endrow*cols)+endcol)->weight);
  distOrigin=distOrigin+diffWeight;
  

  while(minPath!=nullptr){
    printList.push_front(minPath);
    if((minPath->row==startrow)&&(minPath->col==startcol)){
      break;
    }
    minPath=minPath->backedge;
  }
  cout<<(distOrigin-minPath->distance)<<endl;
  while(!printList.empty()){
    minPath=printList.front();
    cout<<minPath->row<<" "<<minPath->col<<endl;
    printList.pop_front();
  }
  for(unsigned int i=0;i<nodeVect.size();i++){
    delete nodeVect.at(i);
  }
  
  
  
  
  return 0;
}
*/