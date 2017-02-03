//--Author	JRM Annand   30th Aug 2003
//--Rev 	A.Starostin..24th Jan 2004  add theta,phi
//--Rev 	JRM Annand   30th Jan 2004  mod neighbour determination
//--Rev 	JRM Annand   21st Oct 2004  cluster time
//--Rev 	JRM Annand    9th Mar 2005  protected instead of private vars
//--Rev 	JRM Annand   14th Apr 2005  energy fraction central crystal
//--Rev 	JRM Annand    6th Jun 2005  up to 48 nearest neighbours
//--Rev 	JRM Annand   13th Jul 2005  add Merge function
//--Rev 	JRM Annand   19th Oct 2005  up to 64 nearest neighbours
//--Rev 	JRM Annand   12th May 2007  mean radius
//--Update	D Glazier    24th Aug 2007  Add IsTime check
//--Description
//                *** Acqu++ <-> Root ***
// Online/Offline Analysis of Sub-Atomic Physics Experimental Data
//
// HitClusterUCLA_t
// Specimen for hit cluster determination in a segmented calorimeter
// Mean cluster position obtained from the sqrt(E) weighted sum
//
//---------------------------------------------------------------------------

#include "HitClusterUCLA_t.h"
#include "TA2CalArray.h"

//---------------------------------------------------------------------------

HitClusterUCLA_t::HitClusterUCLA_t ( Char_t* line, UInt_t index, Int_t sizefactor ) : HitCluster_t( line, index, sizefactor )
{
  //  store input parameters
  //  # inner nearest neighbours (outer calculated from total read)
  //  coordinates of center of front face of central element
  //  List of nearest neighbours inner & outer
  UInt_t hit[64];
  Int_t nw;     //*sp*
  fIndex = index;
  UInt_t n =
    sscanf( line,
	    "%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",
	    &fNNearNeighbour,
	    hit,   hit+1, hit+2, hit+3, hit+4, hit+5, hit+6, hit+7,
	    hit+8, hit+9, hit+10,hit+11,hit+12,hit+13,hit+14,hit+15,
	    hit+16,hit+17,hit+18,hit+19,hit+20,hit+21,hit+22,hit+23,
 	    hit+24,hit+25,hit+26,hit+27,hit+28,hit+29,hit+30,hit+31,
	    hit+32,hit+33,hit+34,hit+35,hit+36,hit+37,hit+38,hit+39,
	    hit+40,hit+41,hit+42,hit+43,hit+44,hit+45,hit+46,hit+47,
	    hit+48,hit+49,hit+50,hit+51,hit+52,hit+53,hit+54,hit+55,
	    hit+56,hit+57,hit+58,hit+59,hit+60,hit+61,hit+62,hit+63 );

  // Consistency check...1st hit must be the index
  if((n < (fNNearNeighbour + 1)) || (index != *hit))
  {
    printf(" Error in nearest neighbour input at line:\n %s\n", line);
    return;
  }
  n -= 2;                         // # neighbours around central element
  fNNeighbour = n;
  fMaxHits = n * sizefactor;
  if(n > 7) nw = 22+230;    // *sp*
  else      nw = 19+230;    // *sp*
  if(nw>fMaxHits) fHits = new UInt_t[nw]; // *sp*
  else fHits = new UInt_t[ fMaxHits ];
  fHits[0] = ENullHit;
  fNhits = 0;
  fEnergy = (Double_t)ENullHit;
  fSqrtEtot = (Double_t)ENullHit;     // *sp*
  fSqrtEtUp = 0.;                     // *sp*
  fSqrtEtDn = 0.;                     // *sp*
  //for( UInt_t i=0; i<n; i++ ) fNeighbour[i] = hit[i+1];
  //fMeanPosition = new TVector3(0.0, 0.0, 0.0);
  fMeanPosUp = new TVector3(0.0, 0.0, 0.0);  // *sp*
  fMeanPosDn = new TVector3(0.0, 0.0, 0.0);  // *sp*
  fTheta = (Double_t)ENullHit;               // *sp*
  fPhi   = (Double_t)ENullHit;               // *sp*
  fTime = 0.0;                   // in case its not defined
}

//---------------------------------------------------------------------------
HitClusterUCLA_t::~HitClusterUCLA_t()
{
  if( fMeanPosUp )  delete fMeanPosUp;  // *sp*
  if( fMeanPosDn )  delete fMeanPosDn;  // *sp*
}

//---------------------------------------------------------------------------

void HitClusterUCLA_t::ClusterDetermineUCLA(TA2CalArray* cldet)
{
  // Determine the boundary of the cluster the local total energy
  // and the sqrt(energy)-weighted centre-of-gravity vector

  //std::cout<<"ClusterDetermineUCLA"<<std::endl;
  const Double_t Peng = 2./3.;
  UInt_t i, k, m, icl;
  Double_t energyi, wtime;
  Double_t* energy = cldet->GetEnergy();
  Double_t* time = cldet->GetTime();
  UInt_t* hits = cldet->GetTempHits2();
  TVector3** pos = cldet->GetPosition();
  UInt_t nhits = cldet->GetNhits();
  UInt_t nelem = cldet->GetNelement();
  TVector3 vcr, vcl, vdif;

  fEnergy = energy[fIndex];                   // energy in "central" element
  if(fEnergy > 2000.) printf("wrong fEnergy = %lf, %d, %d\n", fEnergy, fIndex, nhits);
  Double_t sqrtE = pow(fEnergy,Peng);
  fSqrtEtot = sqrtE;
  //fTime = time[fIndex];       // time in central element
  if(nelem==720) wtime = energy[fIndex];
  //if (nelem==720) wtime = sqrtE;
  //else wtime = 1.;
  //else wtime = energy[fIndex];
  else wtime = sqrtE;
  fTime = time[fIndex]*wtime;                       // time in central element
  for(m=0;m<nhits;m++)
    if(fIndex==hits[m]) hits[m] = ENullHit;
  vcr = *(pos[fIndex]);
  //std::cout<<"vcr: "<<vcr.X()<<","<<vcr.Y()<<","<<vcr.Z()<<std::endl;
  if (nelem==720)
  {
    if (vcr.Y()>0.)
    {
      fSqrtEtUp = sqrtE;
      *fMeanPosUp = vcr * sqrtE;
    }
    else
    {
      fSqrtEtDn = sqrtE;
      //std::cout<<"here before crash"<<std::endl;
      *fMeanPosDn = vcr * sqrtE;
    }
  }
  *fMeanPosition = vcr * sqrtE;   // position = "centre"
  fHits[0] = fIndex;
  k = 1;

  // Accumulate weighted mean position
  UInt_t nneib = fNNeighbour;
  for(m=0;m<nneib;m++)
  {
    icl = fNeighbour[m];

    for(i=0; i<nhits; i++)
    {
      if (icl == hits[i])
      {
	hits[i] = ENullHit;
	fHits[k] = icl;                           // add to cluster hits collection
	energyi = energy[icl];
	sqrtE = pow(energyi, Peng);
	if (energyi > 2000.) printf("wrong energy[icl] = %lf, %d, %d\n", energy[icl], icl, nhits);
	fEnergy+=energyi;
	if(nelem==720) wtime = energyi;
	//if(nelem==720) wtime = sqrtE;
	//else wtime = 1.;
	//else wtime = energyi;
	else wtime = sqrtE;
	fTime += time[icl]*wtime;
	fSqrtEtot += sqrtE;
	vcr = *(pos[icl]);
	if (nelem==720)
        {
	  if (vcr.Y()>0.)
          {
	    fSqrtEtUp+=sqrtE;
	    *fMeanPosUp+=vcr * sqrtE;
	  }
	  else
          {
	    fSqrtEtDn+=sqrtE;
	    *fMeanPosDn+=vcr * sqrtE;
	  }
	}
	*fMeanPosition+=vcr * sqrtE;
	k++;
      }
    }
  }

  const Double_t difmax1=18., difmax2=8.;
  const Double_t opangl1 = 14., opangl2 = 16.;
  Double_t oang, difmax, opangl;
  for(i=0; i<nhits; i++)
  {
    if((icl = hits[i])==ENullHit) continue; // was previously counted
    vcl = (*fMeanPosition) * (1./fSqrtEtot);
    vcr = *(pos[icl]);
    energyi = energy[icl];
    if (nelem==720)
    {
      oang = vcl.Angle(vcr)*TMath::RadToDeg();
      opangl = opangl1 + opangl2 * fEnergy / 1000.;
      if ( oang > opangl ) continue;
    }
    else
    {
      difmax = difmax1 + difmax2 * fEnergy / 1000.;
      vdif = vcl - vcr;
      if (vdif.Mag() > difmax) continue;
    }
    hits[i] = ENullHit;               // so its not double counted
    fHits[k] = icl;                   // add to cluster hits collection
    sqrtE = pow(energyi,Peng);
    fEnergy += energyi;
    if (nelem==720) wtime = energyi;
    //if(nelem==720) wtime = sqrtE;
    //else wtime = 1.;
    //else wtime = energyi;
    else wtime = sqrtE;
    fTime+=time[icl]*wtime;
    fSqrtEtot+=sqrtE;
    *fMeanPosition+=vcr * sqrtE;
    k++;
  }

  fNhits = k;
  fHits[k] = EBufferEnd;
  *fMeanPosition = (*fMeanPosition) * (1./fSqrtEtot ); // normalise weighted mean
  if(nelem==720)
  {
    if(fSqrtEtUp > 0.) *fMeanPosUp = (*fMeanPosUp) * (1./ fSqrtEtUp);
    if(fSqrtEtDn > 0.) *fMeanPosDn = (*fMeanPosDn) * (1./ fSqrtEtDn);
  }
  fTheta = TMath::RadToDeg() * fMeanPosition->Theta();
  fPhi   = TMath::RadToDeg() * fMeanPosition->Phi();
  fCentralFrac = energy[fIndex]/fEnergy;
  if (nelem==720) fTime/=fEnergy;
  //if (nelem==720) fTime/=fSqrtEtot;
  //else fTime /= (Double_t)fNhits;
  //else fTime /= fEnergy;
  else fTime /= fSqrtEtot;
}

//---------------------------------------------------------------------------

Bool_t HitClusterUCLA_t::ClusterDetermineUCLA2(TA2CalArray* cldet)
{
  // Determine the boundary of the cluster the local total energy
  // and the sqrt(energy)-weighted centre-of-gravity vector

  const Double_t Peng = 2./3.;
  const Double_t difmax1=24., difmax2=10.;
  const Double_t opangl1 = 30., opangl2 = 7.;
  Double_t difmax, opangl;
  UInt_t k, ind, l;
  Double_t sqrtE;

  Double_t energyi, oang, wtime;
  Double_t* energy = cldet->GetEnergy();
  Double_t* time = cldet->GetTime();
  UInt_t* hits = cldet->GetTempHits2();
  TVector3** pos = cldet->GetPosition();
  UInt_t nhits = cldet->GetNhits();
  UInt_t nelem = cldet->GetNelement();
  TVector3 vcr, vcl, vdif;

  UInt_t nhitold = fNhits;

  *fMeanPosition = (*fMeanPosition) * fSqrtEtot; // unnormalise weighted mean
  if(nelem==720) fTime*=fEnergy;
  //if ( nelem==720 ) fTime *= fSqrtEtot;
  //else fTime*=(Double_t)fNhits;
  //else fTime*=fEnergy;
  else fTime *= fSqrtEtot;

  if(nelem==720)
  {
    if(fSqrtEtUp > 0.) *fMeanPosUp = (*fMeanPosUp) * fSqrtEtUp;
    if(fSqrtEtDn > 0.) *fMeanPosDn = (*fMeanPosDn) * fSqrtEtDn;
  }
  k=fNhits;

  for(l=0; l<nhits; l++)
  {
    if((ind = hits[l])==ENullHit) continue; // was previously counted
    vcl = (*fMeanPosition) * (1./fSqrtEtot);
    vcr = *(pos[ind]);
    energyi = energy[ind];
    if ( nelem==720 ) {
      oang = vcl.Angle(vcr)*TMath::RadToDeg();
      opangl = opangl1 + opangl2 * fEnergy / 1000.;
      if(oang > opangl) continue;
    }
    else
    {
      difmax = difmax1 + difmax2 * fEnergy / 1000.;
      vdif = vcl - vcr;
      if(vdif.Mag() > difmax) continue;
    }
    hits[l] = ENullHit;               // so its not double counted
    fHits[k] = ind;                   // add to cluster hits collection
    sqrtE = pow(energyi,Peng);
    fEnergy += energyi;
    if(nelem==720) wtime = energyi;
    //if(nelem==720) wtime = sqrtE;
    //else wtime = 1.;
    //else wtime = energyi;
    else wtime = sqrtE;
    fTime += time[ind]*wtime;
    fSqrtEtot += sqrtE;
    *fMeanPosition += vcr * sqrtE;
    k++;
  }
  fNhits = k;
  fHits[k] = EBufferEnd;
  *fMeanPosition = (*fMeanPosition) * (1./fSqrtEtot); // normalise weighted mean
  if(nelem==720)
  {
    if(fSqrtEtUp > 0.) *fMeanPosUp = (*fMeanPosUp) * (1./fSqrtEtUp);
    if(fSqrtEtDn > 0.) *fMeanPosDn = (*fMeanPosDn) * (1./fSqrtEtDn);
  }
  fCentralFrac = energy[fIndex]/fEnergy;
  if (nelem==720) fTime/=fEnergy;
  //if ( nelem==720 ) fTime/=fSqrtEtot;
  //else fTime/=(Double_t)fNhits;
  //else fTime/=fEnergy;
  else fTime/=fSqrtEtot;
  fTheta = TMath::RadToDeg() * fMeanPosition->Theta();
  fPhi   = TMath::RadToDeg() * fMeanPosition->Phi();
  if(fNhits==nhitold) return EFalse;
  else return ETrue;
}

//---------------------------------------------------------------------------

Double_t HitClusterUCLA_t::ClusterRadiusUCLA(TA2CalArray* cldet)
{
  // Determine the boundary of the cluster the local total energy
  // and the sqrt(energy)-weighted centre-of-gravity vector

  UInt_t i, ind;
  TVector3 vcl, vcr, vdif;

  Double_t* energy = cldet->GetEnergy();
  TVector3** pos = cldet->GetPosition();
  UInt_t nelem = cldet->GetNelement();
  fRadius = 0.;
  Double_t thet = fTheta*TMath::DegToRad(), phi = fPhi*TMath::DegToRad();
  Double_t vdev, vmag = 1.;
  if(nelem!=720)
  {
    vcr = *(pos[1]);
    vmag = vcr.Z();
  }
  vcl.SetMagThetaPhi(vmag/cos(thet), thet, phi);
  for(i=0; i<fNhits; i++)
  {
    ind = fHits[i];
    vcr = *(pos[ind]);
    if(nelem==720)
    {
      vdev = vcl.Angle(vcr)*TMath::RadToDeg();
      if(vdev>0.) fRadius += energy[ind] * vdev * vdev;
    }
    else
    {
      vdif = vcl - vcr;
      vdev = vdif.Mag();
      if(vdev>0.) fRadius += energy[ind] * vdev * vdev;
    }
  }
  if(fRadius>0.) fRadius = sqrt(fRadius/fEnergy);
  return fRadius;
}

//---------------------------------------------------------------------------
