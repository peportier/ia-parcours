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
  vector<node*> nei;
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

    x.insert(*u);                     // the node u of y is now white
    y.erase(u);
  }

  return x;
}

int
main()
{
  // example of a graph
  struct node n1; n1.val = 1;
  struct node n2; n2.val = 2;
  struct node n3; n3.val = 3;
  struct node n4; n4.val = 4;
  struct node n5; n5.val = 5;
  struct node n6; n6.val = 6;
  n1.nei.insert(n1.nei.begin(), &n2);
  n1.nei.insert(n1.nei.begin(), &n3);
  n2.nei.insert(n2.nei.begin(), &n4);
  n4.nei.insert(n4.nei.begin(), &n3);
  n4.nei.insert(n4.nei.begin(), &n5);
  n5.nei.insert(n5.nei.begin(), &n2);
  n5.nei.insert(n5.nei.begin(), &n6);

  for( node* n : a(&n4) )
  {
    cout << n->val << " ; ";
  }
  cout << endl;

  return 0;
}
