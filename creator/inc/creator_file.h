/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies). 
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




#ifndef __CREATORFiles_H__
#define __CREATORFiles_H__

#include "creator_model.h"
#include "creator_modulebase.h"

#include <caf/caf.h>
using namespace ContentAccess;

#include <e32base.h>
#include <bautils.h>
#include <pathinfo.h>
#include <apgcli.h> // RApaLsSession

class CCreatorEngine;
class CFilesParameters;
class CDRMPermission;
class CDRMConstraint;

class CCreatorFiles : public CBase, public MCreatorModuleBase
    {
public: 
    static CCreatorFiles* NewL(CCreatorEngine* aEngine);
    static CCreatorFiles* NewLC(CCreatorEngine* aEngine);
    ~CCreatorFiles();

private:
    CCreatorFiles();
    void ConstructL(CCreatorEngine* aEngine); // from MCreatorModuleBase

public:
    TBool AskDataFromUserL(TInt aCommand, TInt& aNumberOfEntries); // from MCreatorModuleBase
    TInt CreateFileEntryL(CFilesParameters *aParameters, TInt aCommand);    
    void DeleteAllL();
    void DeleteAllCreatedByCreatorL();

private:
    
    void EncryptFileL( const TDesC& aFileName, const TDesC& aOutFileName, CFilesParameters *aParameters );
    void SetPermissionsL( CMetaDataArray* aMetaData, const TDesC& aOutFileName, CFilesParameters *aParameters );
    void SetMimeTypeL( const TDesC& aFileName, TDes8& aMime, CFilesParameters *aParameters );
    TBool AskDRMDataFromUserL();
    TBool AskDRMCDDataFromUserL();
    void StorePathsForDeleteL( CDesCArray& aPaths );
    void GenerateFileNameL( TFileName& aRootName );
    
private:
    CFilesParameters* iParameters;
    CFilesParameters* iUserParameters;
    HBufC* iDirectoryQueriedFromUser;
    RFs& iFs;
    RApaLsSession iApaLs;
    CDesCArray* iFilePaths;
    TInt iFileId;

public:
    };


class CFilesParameters : public CCreatorModuleBaseParameters
    {
public: 
    HBufC*          iFullFilePath;
    TInt            iFileCommand;
    CDRMPermission* iPermission;
    TBool           iEncrypt;
    
public:
    CFilesParameters();
    CFilesParameters( CFilesParameters& aCopy );
    ~CFilesParameters();
    };



#endif // __CREATORFiles_H__
