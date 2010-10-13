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



#ifndef CREATORBROWSERELEMENT_H_
#define CREATORBROWSERELEMENT_H_

#include "creator_scriptelement.h"

namespace creatorbrowser
{
_LIT(KBookmark, "bookmark");
_LIT(KBookmarkFolder, "bookmarkfolder");
_LIT(KSavedPage, "savedpage");
_LIT(KSavedPageFolder, "savedpagefolder");

_LIT(KName, "name");
_LIT(KPath, "path");
_LIT(KUsername, "username");
_LIT(KPassword, "password");
_LIT(KUrl, "url");
}

class CCreatorBrowserElement : public CCreatorScriptElement
{
public:
    static CCreatorBrowserElement* NewL(CCreatorEngine* aEngine, const TDesC& aName, const TDesC& aContext = KNullDesC);
    void ExecuteCommandL();
    
protected:
    CCreatorBrowserElement(CCreatorEngine* aEngine);    
    TInt GetBrowserCommandL() const;
};
#endif /*CREATORBROWSERELEMENT_H_*/
