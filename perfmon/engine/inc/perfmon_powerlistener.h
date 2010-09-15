/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies). 
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:  
*
*/


#ifndef PERFMON_POWERLISTENER_H
#define PERFMON_POWERLISTENER_H

// INCLUDES
#include <HWRMPower.h>

#include "perfmon.hrh"

// HWRM reporting interval multiplier
const TInt KSampleIntervalMultiple = 1;
const TInt KReportingDuration = 0;  // Infinite duration

class CPerfMonPowerListener : public CBase, public MHWRMBatteryPowerObserver
    {
public:
    static CPerfMonPowerListener* NewL();
    ~CPerfMonPowerListener();

private:
    CPerfMonPowerListener();
    void ConstructL();

    // Handling central repository max reporting period key
    void GetReportingPeriodL();
    void SetReportingPeriodL(TInt aDuration);

public:
    static TBool IsSupported();

    // Start monitoring power values
    TInt Activate();
    // Stop monitoring power values
    void DeActivate();

    // Get average power since last read.
    TInt GetPower();
    // Maximum power value since measurement started
    inline TInt GetMaxPower()       { return iMaxPower; }

    virtual void PowerMeasurement(TInt aErrCode, CHWRMPower::TBatteryPowerMeasurementData& aMeasurement);

private:
    CHWRMPower*                     iHWRMPower;
    RArray<TInt>                    iPowerBuffer;
    TInt                            iLastPowerAvg;
    TInt                            iMaxPower;

    TInt                            iOriginalMaxReportingPeriod;
    };

#endif
