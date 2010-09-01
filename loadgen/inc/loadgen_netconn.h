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


#ifndef LOADGEN_NETCONN_H
#define LOADGEN_NETCONN_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <downloadmgrclient.h>

#include "loadgen_loadbase.h"
#include "loadgen_loadattributes.h"


// FORWARD DECLARATIONS
class CNetConnManager;


// CLASS DECLARATIONS

class CNetConn : public CLoadBase
    {
public:
    static CNetConn* NewL(TNetConnAttributes& aAttributes, TInt aReferenceNumber);
    virtual ~CNetConn();
        
private: // Constructors
    CNetConn(TNetConnAttributes& aAttributes, TInt aReferenceNumber);
    void ConstructL();  

public:  // New methods
    virtual void Resume();
    virtual void Suspend();
    virtual void SetPriority();
    virtual void Close();
    virtual TPtrC Description();
    inline TNetConnAttributes& Attributes() { return iAttributes; }

public:  // New static methods
    static TInt ThreadFunction(TAny* aThreadArg);

private:  // New static methods
    static void GenerateLoad(TNetConnAttributes& aAttributes);

private: // Data
    TNetConnAttributes          iAttributes;    
    RThread                     iThread;
    };


class CNetConnManager : public CActive, public MHttpDownloadMgrObserver
    {
public:
    static CNetConnManager* NewL(TNetConnAttributes& aAttributes);
    ~CNetConnManager();

private:
    CNetConnManager(TNetConnAttributes& aAttributes);
    void ConstructL();

private:
    void RunL();
    void DoCancel();

private:
    static TInt PeriodicTimerCallBack(TAny* aAny);
    void StartDownloadL();

private: // MHttpDownloadMgrObserver
    void HandleDMgrEventL(RHttpDownload& aDownload, THttpDownloadEvent aEvent); 
public:
    inline CPeriodic* PeriodicTimer() { return iPeriodicTimer; }

private:
    TNetConnAttributes&     iAttributes;    
    CPeriodic*              iPeriodicTimer;
    RHttpDownloadMgr        iDownloadMgr;
    }; 

#endif
