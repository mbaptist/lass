// -*- C++ -*-

#ifndef CGSOLVER_H
#define CGSOLVER_H


namespace lass
{

#include <iostream>
#include <vector>
using namespace std;

template <class LinOp,class AdjOp,class Vector,
	  class Real,class PreCond,class Prod>

void cgsolver(const LinOp & linop,
	      const AdjOp & adjop,
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
  PreCond * precond;
  precond=linop_precond;
  
  Vector rr(x),tt(x),br(x),rt(x);

  vector<Vector> dd(kk,Vector(x));
  vector<Vector> bd(kk,Vector(x));
  vector<Vector> bt(kk,Vector(x));

  vector<Real> abd(kk,0);

  Real ef,er,al;
  int k;
  int nit=0;

  Vector aux(x);
  Real bkj;

  bool adjoint=0;
  
  int exit_adjoint=100;
  int nitea=0;

 d6: 
  eval_lin_op(tt,rr,x,b,nit,adjoint,op);
  ef=op.scalar_prod(tt,tt);
  er=op.scalar_prod(rr,rr);
  cout << nit << " " << ef << " " << er << endl;
 d7:
  dd[0]=-rr;
  eval_lin_op(rt,br,rr,nit,adjoint,op);
  ef=op.scalar_prod(rt,rt);
  er=op.scalar_prod(br,br);
  cout << nit << " " << ef << " " << er << endl;
  bd[0]=-br;
  bt[0]=-rt;
  k=0;

 d1:
  abd[k]=op.scalar_prod(bd[k],bd[k]);
  //al=op.scalar_prod(br,rr)/abd[k];
  al=-op.scalar_prod(bd[k],rr)/abd[k];

  //cout << "al= " << al << endl;

  if (abs(al)<small)
    {
      if( ( adjoint==0 ) && ( k >= kk-2 ) )
	{
	  cout << "Entering adjoint... " << endl;
	  small=adjop_small;
	  adjoint=1;
	  precond=adjop_precond;
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
	      precond=linop_precond;
	      goto d9;
	    }
	}
    }

  aux=dd[k];
  aux*=al;
  x+=aux;

  //cout << "norm before: " << op.scalar_prod(rr,rr) << endl;

  aux=bd[k];
  aux*=al;
  rr+=aux;

  //cout << "norm after: " << op.scalar_prod(rr,rr) << endl;

  aux=bt[k];
  aux*=al;
  tt+=aux;

  ef=op.scalar_prod(tt,tt);
  er=op.scalar_prod(rr,rr);
  //cout << nit << " " << ef << " " << er << endl;
  if(ef < eps)
    {
      adjoint=0;
      goto d9;
    }

  eval_lin_op(rt,br,rr,qq,nit,adjoint,op);
	
	cout << nit << " " << ef << " " << er << endl;	

  dd[k+1]=-rr;
  bd[k+1]=-br;
  bt[k+1]=-rt;  
  for(int j=0;j<k;++j)
    {
      bkj=op.scalar_prod(bd[j],br)/abd[j];
      aux=dd[j];
      aux*=bkj;
      dd[k+1]+=aux;
      aux=bt[j];
      aux*=bkj;
      bt[k+1]+=aux;
      aux=bd[j];
      aux*=bkj;
      bd[k+1]+=aux;
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
  eval_lin_op(rt,rr,x,b,qq,nit,adjoint,op);
  ef=op.scalar_prod(rt,rt);
  er=op.scalar_prod(rr,rr);
  cout << "Iterations: " << nit << "  True errors= " << ef << "  " << er << endl;
  if(ef > eps) 
    goto d7;
}







//evaluate Ax-b,precond(Ax-b)
template <class Linear,class Vector,class Real>
void eval_lin_op(Vector & result,
		 Vector & precond_result,
		 const Vector & x,
		 const Vector & b,
		 int & nit,
		 const bool solveadjoint,
		 const Linear & op)
{
  result=linop(x);
  result-=b;
  precond_result=*precond(result);
  if (solveadjoint)
    {
      precond_result=adjop(precond_result);
    }
  ++nit;
}

//evaluate Ax,precond(Ax)
template <class Linear,class Vector,class Real>
void eval_lin_op(Vector & result,
		 Vector & precond_result,
		 const Vector & x,
		 int & nit,
		 const bool solveadjoint,
		 const Linear & op)
{
  result=op.apply_direct(x);
  precond_result=*precond(result);
  if(solveadjoint)
    {
      precond_result=adjop(precond_result);
    }
  ++nit;
}



}

#endif
