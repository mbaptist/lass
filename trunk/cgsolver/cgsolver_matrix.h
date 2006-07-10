// -*- C++ -*-

#ifndef CGSOLVER_MATRIX_H
#define CGSOLVER_MATRIX_H

#include "cgsolver.h"

#include <cmath>

template <class Matrix,class Vector,class Real>
class matrix_linop
{
 public:

  matrix_linop(const Matrix & a_):a(a_){};
  ~matrix_linop(){};

  Vector operator()(const Vector & xx) const
  {
    Vector aux(xx);
    aux=0;
    for(int i=0;i<a.shape()[0];++i)	
      for(int j=0;j<a.shape()[1];++j)
	{
	  aux(i)+=a(i,j)*xx(j);
	}
    return aux;
  }

  Real scalar_prod(const Vector & xx,const Vector & yy) const
    {
      Real aux=0;
      for (int i=0;i<xx.size();++i)
	aux+=xx(i)*yy(i);
      return aux;
    }
  
 private:
  const Matrix & a;

};


//////////////////////////////////////////


template <class Matrix,class Vector,class Real>
class matrix_adjop
{
 public:

  matrix_adjop(const Matrix & a_):a_adjoint(eval_a_adjoint(a_)){};
  ~matrix_adjop(){};

  Vector operator()(const Vector & xx) const
    {
      Vector aux(xx);
      aux=0;
      for(int i=0;i<a_adjoint.shape()[0];++i)	
	for(int j=0;j<a_adjoint.shape()[1];++j)
	  aux(i)+=a_adjoint(i,j)*xx(j);
      return aux;
    }
    

  Real scalar_prod(const Vector & xx,const Vector & yy) const
    {
      Real aux=0;
      for (int i=0;i<xx.size();++i)
	aux+=xx(i)*yy(i);
      return aux;
    }
  
 private:
  Matrix a_adjoint;
  Matrix eval_a_adjoint(const Matrix & a) const
  {
    Matrix aux(a);
    for(int i=0;i<a.shape()[0];++i)
      for(int j=0;j<a.shape()[1];++j)
	aux(i,j)=a(j,i);
    return aux;
  }

};



//////////////////////////////////////////

template <class Vector,class Real>
class PreCond
{
private:
  Real qq;
public:
  PreCond(Real qq__):qq(qq__){};
  ~PreCond(){};
private:
  PreCond();
public:
  Vector operator()(const Vector & xx) const
     {
       Vector aux(xx);
       for(int i=0;i<xx.size();++i)
	 aux(i)=xx(i);
       return aux;
     }
};


///////////////////////////////////////////////////


template <class Matrix,class Vector,class Real>
void cgsolver_matrix(const Matrix & a,Vector & x,const Vector & b,Real eps)
{
  matrix_linop<Matrix,Vector,Real> matrix_linop_obj(a);
  matrix_adjop<Matrix,Vector,Real> matrix_adjop_obj(a);
  PreCond<Vector,Real> linop_precond(.7);
  PreCond<Vector,Real> adjop_precond(1.4);
  cgsolver(matrix_linop_obj,matrix_adjop_obj,linop_precond,
	   adjop_precond,x,b,eps,5,.01,.005);
}


#endif
