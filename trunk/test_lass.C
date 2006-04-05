
#include "lass.h"

#include <cat.h>

#include<iostream>

using namespace std;
using namespace cat;
 
void small_test();
void big_test(int size);


int main()
{
  //small_test();
  big_test(100);
  return 0;
}


void small_test()
{
  cat::array<double,1> x(2),b(2);
  cat::array<double,2> a(2,2);

  a(0,0)=-20.;
  a(0,1)=1;
  a(1,0)=-5;
  a(1,1)=20.;

  for(int i=0;i<2;++i)
    {
      x(i)=0;
      b(i)=0;
      for(int j=0;j<2;++j)
	b(i)+=a(i,j);
    }
 
  cgsolver_matrix(a,x,b,1.e-5);

  for(int i=0;i<2;++i)
    cout << x(i) << endl;

}
    
void big_test(int size)
{
  cat::array<double,1> x(size),b(size);
  cat::array<double,2> a(size,size);

  srand(clock());

  for(int i=0;i<size;++i)
    for(int j=0;j<size;++j)
      {
	a(i,j)=-1+(double(rand())/RAND_MAX)*2.;
	if (i==j)
	  a(i,j)+=(2*(size+1));
      }

  for(int i=0;i<size;++i)
    {
      x(i)=0;
      b(i)=0;
      for(int j=0;j<size;++j)
	b(i)+=2*a(i,j);
    }

  cgsolver_matrix(a,x,b,1.e-5);
  
  for(int i=0;i<size;++i)
    cout << "x(" << i << ")= " << x(i) << endl;

}
