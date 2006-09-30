// -*- C++ -*-

#ifndef CGSOLVER_H
#define CGSOLVER_H


#include <iostream>
#include <vector>
#include <cmath>
using namespace std;



///////////////////////////////////////////////////////////////////////////


//evaluate Ax-b,precond(Ax-b)
template <class LinOp,class AdjOp,class PreCond,class Vector>
void eval_lin_op(Vector & result,
		 Vector & precond_result,
		 const Vector & x,
		 const Vector & b,
		 int & nit,
		 const bool & solveadjoint,
		 LinOp & linop,
		 AdjOp & adjop,
		 const PreCond & precond)
{
  result=linop(x)-b;
  Vector precond_result_tmp=precond(result);
  if(solveadjoint)
    {
      precond_result=adjop(precond_result_tmp);
    }
  else
    {
      precond_result=precond_result_tmp;
    }	
  ++nit;
}


//////////////////////////////////////////////////////////////////////////


//evaluate Ax,precond(Ax)
template <class LinOp,class AdjOp,class PreCond,class Vector>
void eval_lin_op(Vector & result,
		 Vector & precond_result,
		 const Vector & x,
		 int & nit,
		 const bool & solveadjoint,
		 LinOp & linop,
		 AdjOp & adjop,
		 const PreCond & precond)
{
  result=linop(x);
  Vector precond_result_tmp=precond(result);
  if(solveadjoint)
    {
      precond_result=adjop(precond_result_tmp);
    }
  else
    {
      precond_result=precond_result_tmp;
    }
  ++nit;
}




////////////////////////////////////////////////////////////////////////////




template <class LinOp,class AdjOp,class PreCond,class Vector,class Real>
void cgsolver(LinOp & linop,
	      AdjOp & adjop,
	      const PreCond & linop_precond,
	      const PreCond & adjop_precond,
	      Vector & x, 
	      const Vector & b,
	      const Real eps,	
	      const int kk,
	      const float linop_small,
	      const float adjop_small)	
{
  //PARAMETERS
  //const float small=.01;
  // const int np1=47;
  //const int kk=5;
  //float small=.01;
  //Real qq=.75; - this is part of PreCond now.

  float small=linop_small;

  const PreCond * precond;
  precond=&linop_precond;

  Vector rr(x),tt(x),br(x),rt(x);

  std::vector<Vector> dd(kk,Vector(x));
  std::vector<Vector> bd(kk,Vector(x));
  std::vector<Vector> bt(kk,Vector(x));

  std::vector<Real> abd(kk,0);

  Real ef,er,al;
  int k;
  int nit=0;

  Real bkj;

  bool adjoint=0;
  
  int exit_adjoint=100;
  //int exit_adjoint=0;	
  int nitea=0;


 d6: 
  eval_lin_op(tt,rr,x,b,nit,adjoint,linop,adjop,*precond);
  ef=linop.scalar_prod(tt,tt);
  er=linop.scalar_prod(rr,rr);
  cout << nit << " " << ef << " " << er << endl;
 d7:
  dd[0]=-rr;
  eval_lin_op(rt,br,rr,nit,adjoint,linop,adjop,*precond);
  ef=linop.scalar_prod(rt,rt);
  er=linop.scalar_prod(br,br);
  cout << nit << " " << ef << " " << er << endl;
  bd[0]=-br;
  bt[0]=-rt;
  k=0;

 d1:
  abd[k]=linop.scalar_prod(bd[k],bd[k]);
  al=-linop.scalar_prod(bd[k],rr)/abd[k];
  //cout << "al= " << al << endl;

  if (abs(al)<small)
    {
      if( ( adjoint==0 ) && ( k >= kk-2 ) )
	{
	  cout << "Entering adjoint... " << endl;
	  small=adjop_small;
	  adjoint=1;
	  precond=&adjop_precond;
	  nitea=nit;
	  goto d6;
	}
      else
	{
	  if( ( adjoint==1 ) && ( nit-nitea>=exit_adjoint ) )
	    {
	      cout << "Exiting adjoint... " << endl;
	      small=linop_small;
	      adjoint=0;
	      precond=&linop_precond;
	      goto d9;
	    }
	}
    }



  x+=al*dd[k];
  rr+=al*bd[k];
  tt+=al*bt[k];

  ef=linop.scalar_prod(tt,tt);
  er=linop.scalar_prod(rr,rr);

  if(ef < eps)
    {
      if(adjoint==1)
	{
		cout << "Exiting adjoint... " << endl;
              small=linop_small;
              adjoint=0;
		precond=&linop_precond;
      	  }
      
      goto d9;
    }
  
  eval_lin_op(rt,br,rr,nit,adjoint,linop,adjop,*precond);
	
  cout << nit << " " << ef << " " << er << endl;	

  dd[k+1]=-rr;
  bd[k+1]=-br;
  bt[k+1]=-rt;  
  for(int j=0;j<k;++j)
    {
      bkj=linop.scalar_prod(bd[j],br)/abd[j];
      dd[k+1]+=bkj*dd[j];
      bt[k+1]+=bkj*bt[j];
      bd[k+1]+=bkj*bd[j];
    }
  if(k == kk-2)
    {
      for(int j=1;j<kk;++j)
	{
	  dd[j-1]=dd[j];
	  bd[j-1]=bd[j];
	  bt[j-1]=bt[j];
	  abd[j-1]=abd[j];
	}
    }
  else
    {
      ++k;
    }

  goto d1;
 
 d9: 
  eval_lin_op(rt,rr,x,b,nit,adjoint,linop,adjop,*precond);
  ef=linop.scalar_prod(rt,rt);
  er=linop.scalar_prod(rr,rr);
  cout << "Iterations: " << nit << "  True errors= " << ef << "  " << er << endl;
  if(ef > eps) 
    goto d7;
}


#endif

