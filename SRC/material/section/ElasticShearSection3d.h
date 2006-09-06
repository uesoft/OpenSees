/* ****************************************************************** **
**    OpenSees - Open System for Earthquake Engineering Simulation    **
**          Pacific Earthquake Engineering Research Center            **
**                                                                    **
**                                                                    **
** (C) Copyright 1999, The Regents of the University of California    **
** All Rights Reserved.                                               **
**                                                                    **
** Commercial use of this program without express permission of the   **
** University of California, Berkeley, is strictly prohibited.  See   **
** file 'COPYRIGHT'  in main directory for information on usage and   **
** redistribution,  and for a DISCLAIMER OF ALL WARRANTIES.           **
**                                                                    **
** Developed by:                                                      **
**   Frank McKenna (fmckenna@ce.berkeley.edu)                         **
**   Gregory L. Fenves (fenves@ce.berkeley.edu)                       **
**   Filip C. Filippou (filippou@ce.berkeley.edu)                     **
**                                                                    **
** ****************************************************************** */
                                                                        
// $Revision: 1.1 $
// $Date: 2006-09-06 20:17:34 $
// $Source: /usr/local/cvs/OpenSees/SRC/material/section/ElasticShearSection3d.h,v $

#ifndef ElasticShearSection3d_h
#define ElasticShearSection3d_h

#include <SectionForceDeformation.h>
#include <Matrix.h>
#include <Vector.h>

class Channel;
class FEM_ObjectBroker;
class Information;
class Parameter;

class ElasticShearSection3d : public SectionForceDeformation
{
 public:
  ElasticShearSection3d(int tag, double E, double A, double Iz, 
			double Iy, double G, double J, double alpha);
  ElasticShearSection3d(void);
  ~ElasticShearSection3d(void);
  
  const char *getClassType(void) const {return "ElasticShearSection3d";};
  
  int commitState(void);
  int revertToLastCommit(void);
  int revertToStart(void);
  
  int setTrialSectionDeformation(const Vector&);
  const Vector &getSectionDeformation(void);
  
  const Vector &getStressResultant(void);
  const Matrix &getSectionTangent(void);
  const Matrix &getInitialTangent(void);
  const Matrix &getSectionFlexibility(void);
  const Matrix &getInitialFlexibility(void);
  
  SectionForceDeformation *getCopy(void);
  const ID &getType(void);
  int getOrder(void) const;
  
  int sendSelf(int commitTag, Channel &theChannel);
  int recvSelf(int commitTag, Channel &theChannel,
	       FEM_ObjectBroker &theBroker);
  
  void Print(OPS_Stream &s, int flag = 0);
  
  int setParameter(const char **argv, int argc, Parameter &param);
  int updateParameter(int parameterID, Information &info);
  int activateParameter(int parameterID);
  const Vector& getStressResultantSensitivity(int gradNumber,
					      bool conditional);
  const Vector& getSectionDeformationSensitivity(int gradNumber);
  const Matrix& getInitialTangentSensitivity(int gradNumber);
  int commitSensitivity(const Vector& sectionDeformationGradient,
			int gradNumber, int numGrads);

 protected:
  
 private:
  
  double E, A, Iz, Iy, G, J, alpha;
  
  Vector e;			// section trial deformations
  Vector eCommit;
  
  static Vector s;
  static Matrix ks;
  static ID code;

  int parameterID;
};

#endif
