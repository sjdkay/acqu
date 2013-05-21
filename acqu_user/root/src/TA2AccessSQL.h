//*************************************************************************
//* Author: Patrik Ott
//*************************************************************************/

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TA2AccessSQL                                                         //
//                                                                      //
// Class used for reading the SQL config database.                      //
//                                                                      //
//////////////////////////////////////////////////////////////////////////


#ifndef __TA2AccessSQL_h__
#define __TA2AccessSQL_h__

#include "TA2Physics.h"
#include "CaLibReader_t.h"




enum {
    ESQL_USE_CALIB = 20200,
    ESQL_CALIB_MISC,
    ESQL_CALIB_TAGG,
    ESQL_CALIB_CB,
    ESQL_CALIB_TAPS,
    ESQL_CALIB_PID,
    ESQL_CALIB_VETO,
};

static const Map_t AccessSQLConfigKeys[] = {
    // General keys
    {"Use-CaLib:"                    , ESQL_USE_CALIB},                      // key for CaLib activation
    {"Use-CaLib-Misc:"               , ESQL_CALIB_MISC},                     // key for miscellaneous CaLib configuration
    {"Use-CaLib-TAGG:"               , ESQL_CALIB_TAGG},                     // key for CaLib tagger configuration
    {"Use-CaLib-CB:"                 , ESQL_CALIB_CB},                       // key for CaLib CB configuration
    {"Use-CaLib-TAPS:"               , ESQL_CALIB_TAPS},                     // key for CaLib TAPS configuration
    {"Use-CaLib-PID:"                , ESQL_CALIB_PID},                      // key for CaLib PID configuration
    {"Use-CaLib-Veto:"               , ESQL_CALIB_VETO},                     // key for CaLib Veto configuration
    // Termination
    {NULL        , -1           }
};



class TA2AccessSQL : public TA2Physics
{
private:
	CaLibReader_t*	fCaLibReader;                            // CaLib reader
	Int_t			fRunNumber;
	
	void ApplyCaLib();

public:
    TA2AccessSQL(const char* name, TA2Analysis* analysis);
    virtual ~TA2AccessSQL();

    virtual void SetConfig(Char_t* line, Int_t key);
    virtual void PostInit();
    virtual void LoadVariable();
    virtual	void Reconstruct();
    
    ClassDef(TA2AccessSQL, 1)
};



#endif
