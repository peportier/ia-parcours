/*
Copyright 2018 Pierre-Edouard Portier
peportier.me

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
)
*/

#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct
node
{
  int val;
  vector< node* > nei;
  node() {};
  node(int i) : val(i) {}
};

set<node*>
a( node* src )
{
  set<node*> x;
  set<node*> y;
  y.insert(src);                      // the source is initially grey

  while( !y.empty() )
  {
    set<node*>::iterator u = y.begin();

    for( node* n : (*u)->nei )        // n is in the successors of y
    {
      if( (x.end() == x.find(n)) &&
          (y.end() == y.find(n)) )    // n is not in (x U y)
      {
        y.insert(n);                  // we still didn't see the succ of n
                                      // thus, it is a grey node
      }
    }

    x.insert(*u);                     // the node u of y is now black
    y.erase(u);
  }

  return x;
}

int
main()
{
  // example of a graph
  node n1(1); node n2(2); node n3(3);
  node n4(4); node n5(5); node n6(6);
  n1.nei.push_back( &n2 );
  n1.nei.push_back( &n3 );
  n2.nei.push_back( &n4 );
  n4.nei.push_back( &n3 );
  n4.nei.push_back( &n5 );
  n5.nei.push_back( &n2 );
  n5.nei.push_back( &n6 );

  for( node* n : a(&n4) )
  {
    cout << n->val << " ; ";
  }
  cout << endl;

  return 0;
}
