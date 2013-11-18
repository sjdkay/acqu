#ifndef __TVME_VUPROM_Scaler_h__
#define __TVME_VUPROM_Scaler_h__

#include <vector>
#include "TVMEmodule.h"


class TVME_VUPROM_Scaler : public TVMEmodule {
private:
  std::vector<VMEreg_t> fVUPROMregs; // instead of this enum/pointer hell
  // consecutive scalers form a block, 
  // we store the offset to access fVUPROMregs in the first value
  // and the length of the block (a.k.a the number of the scalers) in the second  
  std::vector< std::pair<size_t,size_t> > fScalerBlockOffsets; 
  UInt_t fScalerOffset;
  
  void StopScalers();
  void StartScalers();
  
protected:

public:
  TVME_VUPROM_Scaler( Char_t*, Char_t*, FILE*, Char_t* );
  virtual void SetConfig( Char_t*, Int_t );   // configure VME module
  virtual void PostInit( );
  virtual Bool_t CheckHardID();
  virtual void ReadIRQScaler(void**); 
 
  ClassDef(TVME_VUPROM_Scaler,1)

};

#endif
