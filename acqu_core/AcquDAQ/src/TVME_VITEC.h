//--Author	JRM Annand   3rd Sep 2013
//--Rev 	JRM Annand
//--Update	JRM Annand  17th Sep 2013  Mods for new firmware
//
//--Description
//                *** AcquDAQ++ <-> Root ***
// DAQ for Sub-Atomic Physics Experiments.
//
// TVME_VITEC
// VITEC piggy back card to the KPh i686 VMEbus SBC
// Used for "interrupt" and event-ID processing
//

#ifndef __TVME_VITEC_h__
#define __TVME_VITEC_h__

#include "TVMEmodule.h"

enum{
  EVIT_ECLin,
  EVIT_ECLout,
  EVIT_NIMin,
  EVIT_NIMout,
  EVIT_EvIDlsb,
  EVIT_EvIDmsb,
  EVIT_Status,
  EVIT_FwID,
};
enum{ EVIT_EvIDTimeout = 250 };

class TVME_VITEC : public TVMEmodule {
 protected:
  Bool_t    fIsIRQEnabled;
  UInt_t fEvID;                 // event ID
 public:
  TVME_VITEC( Char_t*, Char_t*, FILE*, Char_t* );
  virtual ~TVME_VITEC();
  virtual void SetConfig( Char_t*, Int_t );   // configure VME module
  virtual void PostInit( );
  virtual Bool_t CheckHardID();
  virtual void WaitIRQ();
  virtual void SetIRQ(){ Write(EVIT_NIMout,(UInt_t)0x1); }
  virtual void ResetIRQ(){ Write(EVIT_NIMout,(UInt_t)0x0); }
  virtual void EnableIRQ(){ fIsIRQEnabled = kTRUE; }
  virtual void DisableIRQ(){ fIsIRQEnabled = kFALSE; }
  virtual UInt_t GetEventID();
  Bool_t IsIRQEnabled(){ return fIsIRQEnabled; }

  ClassDef(TVME_VITEC,1)   

    };

//-----------------------------------------------------------------------------
inline void TVME_VITEC::WaitIRQ( )
{
  // Poll the state of the status register
  // When bit 15 set exit loop
  // and set NIM output 1: ACK
  Int_t datum;
  for(;;){
    if( fIsIRQEnabled ){                 // "interrupt" software enabled?
      datum = Read(EVIT_Status);         // poll status register
      if( datum & 0x8000 )break;         // exit when bit 15 set
    }
  }
  SetIRQ();                              // set ACK (NIM output 1)
}

//-----------------------------------------------------------------------------
inline UInt_t TVME_VITEC::GetEventID( )
{
  // Read the event ID
  //
  Int_t datum,evid;
  Int_t i=0;
  for(;;){
    datum = Read(EVIT_Status);
    if( (datum & 0x1a) == 0x1a ) break;   // start/stop bits set...OK
    else if((datum & 0x11) == 0x11){
      evid = 0xffffffff;
      return evid;
    }
    else if(i > EVIT_EvIDTimeout){
      evid = 0xffffffff;
      return evid;
    }
    i++;
    usleep(1);
  }
  evid = Read(EVIT_EvIDlsb);           // get the event ID
  datum = Read(EVIT_EvIDmsb);
  evid = evid | (datum << 16);
  return evid;
}

#endif
