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

#ifndef MEMSPYVIEWPROCESSES_H
#define MEMSPYVIEWPROCESSES_H

// System includes
#include <coecntrl.h>
#include <aknlists.h>

// User includes
#include "MemSpyViewBase.h"

// Classes referenced
class CMemSpyProcess;
class CAknSearchField;


class CMemSpyViewProcesses : public CMemSpyViewBase
    {
public:
    CMemSpyViewProcesses( CMemSpyEngine& aEngine, MMemSpyViewObserver& aObserver );
    CMemSpyViewProcesses( CMemSpyEngine& aEngine, MMemSpyViewObserver& aObserver, CMemSpyProcess& aProcess );
    ~CMemSpyViewProcesses();
    void ConstructL( const TRect& aRect, CCoeControl& aContainer, TAny* aSelectionRune = NULL );

public: // API
    CMemSpyProcess& CurrentProcess() const;

public: // From CMemSpyViewBase
    void RefreshL();
    TMemSpyViewType ViewType() const;
    CMemSpyViewBase* PrepareParentViewL();
    CMemSpyViewBase* PrepareChildViewL();
    TBool HandleCommandL( TInt aCommand );

public: // Menu framework
    TUint MenuCascadeResourceId() const { return R_MEMSPY_MENUPANE_PROCESS; }
    TInt MenuCascadeCommandId() const { return EMemSpyCmdProcess; }
    void DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane );

private: // Command handlers

    // Sorting
    void OnCmdSortByIdL();
    void OnCmdSortByNameL();
    void OnCmdSortByThreadCountL();
    void OnCmdSortByCodeSegsL();
    void OnCmdSortByHeapUsageL();
    void OnCmdSortByStackUsageL();

    // Info
    void OnCmdInfoSummaryL();
    void OnCmdInfoHandlesL();

    // Ending
    void OnCmdEndTerminateL();
    void OnCmdEndPanicL();
    void OnCmdEndKillL();

private: // From CMemSpyViewBase
    void SetListBoxModelL();
    void HandleListBoxItemActionedL( TInt aIndex );
    void HandleListBoxItemSelectedL( TInt aIndex );
    
private: // From CCoeControl
    void SizeChanged();
    TInt CountComponentControls() const;
    CCoeControl* ComponentControl( TInt aIndex ) const;
	TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );
    void FocusChanged( TDrawNow /*aDrawNow*/ );

private: // From MCoeControlObserver
    void HandleControlEventL( CCoeControl* aControl, TCoeEvent aEventType );

private: // Internal methods
    void SelectListBoxItemByFindTextL();

private: // Data members
    CMemSpyProcess* iCurrentProcess;
    CAknSearchField* iSearchField;
    HBufC* iMatcherBuffer;
    };


#endif
