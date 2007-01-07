ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
c
c vzdeigen - dominant eigenvalue and vector of a linear operator
c
c Original Code by Vlad Zheligovsky
c
c Interface improvements by Manuel Baptista (2005)
c
ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc

c     Find the dominant eigenvalue for the operator
c     v1 - Array containing the initial condition and the
c       dominant eigenvector
c     xp - real part of the dominant eigenvalue
c     eim - imaginary part of the dominant eigenvalue
c     ep - tolerance (stopping criterium)
c     M - size of v1
c     v2..v7 - Set of arrays of size M
c     mp - 
c     sc - 
c     nseq - 
c     name - filename for intermediate outputs
      subroutine vzdeigen(v1,xp,eim,ep,thr,M,v2,v3,v4,v5,v6,v7,
     *mp_,sc_,nseq_,name)
      IMPLICIT REAL*8 (A-H,O-Z)
      IMPLICIT INTEGER*4 (I-N)
      parameter(ncomplex=20,small1=1d-9,thri=.5,
     * nmd=31,ms=3*(2*nmd+1)*(nmd+1)*(nmd+1),
     * small2=1d-12,iter0=1500000,itst=500,init=1,kopt=1)
      DIMENSION V1(M),V2(M),V3(M),V4(M),V5(M),V6(M),V7(M)
      character*100 name
c      common/cc/visc,sc,CF(2,ncomplex),ell,gamma,du(3,12),mp,nseq,nf
      common/cc/sc,CF(2,ncomplex),mp,nseq
      common/uu/qq,z1,z2
c      print *,"M=",M," ",xp,eim,ep,thr,name
      sc=sc_
      mp=mp_
      nseq=nseq_
      call EIGEN(v1,xp,eim,ep,thr,M,name,v2,v3,v4,v5,v6,v7) 
      end

c     Subroutine that interfaces with any externally supplied routine
c     to evaluate the product of the linear operator by the vector
c     NIT - current iteration
c     VI - Array with input vector
c     VO - Array with input vector
c     M - Size of the arrays
      SUBROUTINE PRODX(NIT,VI,VO,M)
      IMPLICIT REAL*8 (A-H,O-Z)
      IMPLICIT INTEGER*4 (I-N)
      parameter(ncomplex=20)
      dimension vi(M),vo(M)
      common/cc/sc,CF(2,ncomplex),mp,nseq
      call external_prodx(NIT,VI,VO,M)
      vo=vi+vo/sc
c      print *,sum(VI),sum(VO)
      END

c     Subroutine to load a fortran binary file of doubles
c     into a vector
      subroutine vzdeigen_load_ffile(v,m,name) 
      IMPLICIT REAL*8 (A-H,O-Z)
      character*100 name
      real*8 v(m)
      OPEN(3,STATUS='OLD',FILE=name,
     *     FORM='UNFORMATTED',ACCESS='DIRECT',RECL=8*m)
      READ(3,REC=1) v

      X1=0D0
      DO 4 L=M,1,-1
 4    X1=X1+V(L)*V(L)
      print *,"Norm V1: " , X1
      print *,"new conf v1: ",(v(i),i=15,30)



      CLOSE(3)
      end

c     Subroutine to save a vector of doubles into a fortran
c     binary file
      subroutine vzdeigen_save_ffile(v,m,name) 
      IMPLICIT REAL*8 (A-H,O-Z)
      character*100 name
      real*8 v(m)
      character*200 cmd 
c      cmd=ADJUSTL("if [ ! -f ")//TRIM(ADJUSTL(name))//" ]; then  mv "
c     *//TRIM(ADJUSTL(name))//" "//TRIM(ADJUSTL(name))//".old; fi"
c      cmd=TRIM(ADJUSTL(cmd))
c      print *,cmd
c      call system(cmd)
      OPEN(3,STATUS='UNKNOWN',FILE=name,
     *     FORM='UNFORMATTED',ACCESS='DIRECT',RECL=8*m)
      WRITE(3,REC=1) v
      CLOSE(3)
      end


ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
c
c Original Code by Vlad Zheligovsky (vlad@mitpu.ru) must be available
c as yuio.f in the same directory
c
ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc

