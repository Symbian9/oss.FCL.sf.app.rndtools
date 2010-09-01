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




#ifndef __CREATORMESSAGES_H__
#define __CREATORMESSAGES_H__

#include "creator_model.h"
#include "creator_modulebase.h"

#include <e32base.h>
#include <e32std.h>
#include <msvapi.h>
#include <mtclbase.h>
#include <mtclreg.h>
#include <smut.h>
#include <smuthdr.h>
#include <smsclnt.h>
#include <miutset.h>
#include <mmsclient.h>
#include <ircmtm.h>
#include <irmsgtypeuid.h>
#include <btmsgtypeuid.h>
#include <bif.h>
#include <biouids.h>
#include <miuthdr.h>

#include <cmsvmimeheaders.h>
#include <smtcmtm.h>
#include <ircmtm.h>
#include <btcmtm.h>
#include <mmsvattachmentmanager.h>

#if(!defined __SERIES60_30__ && !defined __SERIES60_31__)
#include <MVPbkSingleContactOperationObserver.h>
#include <MVPbkContactStoreListObserver.h>
#include <MVPbkContactFindObserver.h>
class CVPbkContactManager;
#endif

class CCreatorEngine;
class CMessagesParameters;
class CAsyncWaiter; 

enum TMessageType
    {
    ESMS = 0,
    EMMS,
    EAMS,
    EEmail,
    ESmartMessage,
    EIrMessage,
    EBTMessage
    };

enum TFolderType
    {
    EInbox = 0,
    EDrafts,
    EOutbox,
    ESent,
    EMailbox
    };
    
class CRecipientInfo : public CBase
{
public:
    CRecipientInfo();
    virtual ~CRecipientInfo();
    
    void SetPhoneNumber(HBufC* aPhone);
    void SetEmailAddress(HBufC* aEmail);
    const HBufC* PhoneNumber() const;
    const HBufC* EmailAddress() const;
    
private:
    HBufC* iPhoneNumber;
    HBufC* iEmailAddress;
};

#if(!defined __SERIES60_30__ && !defined __SERIES60_31__)
class CCreatorMessages : public CBase, public MCreatorModuleBase, public MMsvSessionObserver, 
    public MVPbkSingleContactOperationObserver, public MVPbkContactStoreListObserver, public MVPbkContactFindObserver
#else
class CCreatorMessages : public CBase, public MCreatorModuleBase, public MMsvSessionObserver
#endif
    {
public: 
    static CCreatorMessages* NewL(CCreatorEngine* aEngine);
    static CCreatorMessages* NewLC(CCreatorEngine* aEngine);
    ~CCreatorMessages();

private:
    CCreatorMessages();
    void ConstructL(CCreatorEngine* aEngine); // from MCreatorModuleBase

    TInt CreateSMSEntryL(const CMessagesParameters& parameters);
    TInt CreateMMSEntryL(const CMessagesParameters& parameters);
    TInt CreateAMSEntryL(const CMessagesParameters& parameters);
    TInt CreateEmailEntryL(const CMessagesParameters& parameters);
    TInt CreateSmartMessageEntryL(const CMessagesParameters& parameters);
    TInt CreateObexEntryL(TUid aMtm, const CMessagesParameters& parameters);
    void HandleAttachementsL(const CMessagesParameters& parameters, CMsvStore* store, TInt err );
    void HandleAttachementL(CMsvStore* store, TInt err, TFileName& sourceFileName );

    CMsvEntrySelection* DoGetListOfAccountsL(CMsvSession& aSession, TUid aMtm, TBool aAlwaysListHidden);
    TMsvId DefaultServiceForMTML(CMsvSession& aSession, TUid aMtm, TBool aFindFirstServiceIfNoDefault);

    void HandleSessionEventL(TMsvSessionEvent aEvent, TAny* aArg1, TAny* aArg2, TAny* aArg3); // from MMsvSessionObserver
    
    void AddRecipientsL(CBaseMtm& aMtm, const CMessagesParameters& aParameters, TBool aUseEmailAddress );
    void GetLinkedAddressesL(   RPointerArray<HBufC>& aAddressArray, 
                                const RArray<TLinkIdParam>& aLinkIds, 
                                TBool aUseEmailAddress,
                                TInt aNumOfExistingAddresses );
    
    void GetAllRecipientsL(RPointerArray<HBufC>& aRecipientArray, const CMessagesParameters& aParameters, TBool aUseEmailAddress );
    void SetSenderToEntryDetails(TMsvEntry& aMsgEntry, const CMessagesParameters& aParameters, TBool aUseEmailAddress);
    void SetRecipientToEntryDetails(TMsvEntry& aMsgEntry, const CMessagesParameters& aParameters, TBool aUseEmailAddress);
    void AddSenderToMtmAddresseeL(CBaseMtm& aMtm, const CMessagesParameters& aParameters, TBool aUseEmailAddress );
    void AddMtmSenderL(CMmsClientMtm& aMtm, const CMessagesParameters& aParameters, TBool aUseEmailAddress );
    void GetSendersL(RPointerArray<HBufC>& aSenderArray, const CMessagesParameters& aParameters, TBool aUseEmailAddress, TInt aMaxNum );
    void DeleteAllMessagesL( TBool aOnlyCreatedWithCreator );
    void DeleteAllFromFolderL( const TMsvId aContext, CMsvSession* aSession, CSmsClientMtm* aClientMtm, TBool aOnlyCreatedWithCreator = EFalse );
    
public:
    TBool AskDataFromUserL(TInt aCommand, TInt& aNumberOfEntries); // from MCreatorModuleBase

    TInt CreateMessageEntryL(CMessagesParameters *aParameters, TBool aTakeUserGivenParameters=EFalse);    
    TInt CreateRandomMessageEntryL(TInt aCommand);
    void DeleteAllL();
    void DeleteAllCreatedByCreatorL();
    
#if(!defined __SERIES60_30__ && !defined __SERIES60_31__)
    // From MVPbkSingleContactOperationObserver:
    virtual void VPbkSingleContactOperationComplete(
            MVPbkContactOperationBase& aOperation,
            MVPbkStoreContact* aContact );
            
    virtual void VPbkSingleContactOperationFailed(
            MVPbkContactOperationBase& aOperation, 
            TInt aError );
    
    void HandleSingleContactResultL();
            
    // From MVPbkContactStoreListObserver
    virtual void OpenComplete();
    virtual void StoreReady(MVPbkContactStore&);
    virtual void StoreUnavailable(MVPbkContactStore&, TInt);
    virtual void HandleStoreEventL(MVPbkContactStore&, TVPbkContactStoreEvent);
    
    // From MVPbkContactFindObserver
    virtual void FindCompleteL( MVPbkContactLinkArray* aResults );
    virtual void FindFailed( TInt aError );
#endif

private:
    CMessagesParameters*    iParameters;
    TMessageType            iMessageType;
    TFolderType             iFolderType;
    TInt                    iDefinedMessageLength;
    CArrayFixFlat<TInt>*    iAttachments; 
    //RPointerArray<HBufC>    iAttachmentPaths;
    TBool                   iCreateAsUnread;
    TMsvId                  iUserSelectedMailbox;
    HBufC*                  iTmpPhoneNumber;
    HBufC*                  iTmpEmail;
    RArray<TInt>            iEntryIds; // TMsvId ( == TInt32 ) TMsvEntry::Id()
    CMsvSession*            iSession;
#if(!defined __SERIES60_30__ && !defined __SERIES60_31__)
    MVPbkContactLinkArray*  iExistingContacts;
    CVPbkContactManager* iContactManager;
    MVPbkContactStore* iStore;
    MVPbkStoreContact* iTempContact;
#endif
    CAsyncWaiter* iWaiter;
    RPointerArray<HBufC>    iSenderArray;
    RPointerArray<HBufC>    iRecipientArray;
public:
    };


class CMessagesParameters : public CCreatorModuleBaseParameters
    {
public: 
    TMessageType            iMessageType;
    TFolderType             iFolderType;
    HBufC*                  iSenderAddress;    
    HBufC*                  iRecipientAddress;
    RPointerArray<HBufC>    iRecipientAddressArray;
    HBufC*                  iMessageSubject;
    HBufC*                  iMessageBodyText;
    CArrayFixFlat<TInt>*    iAttachments; 
    RPointerArray<HBufC>    iAttachmentPaths;
    TInt                    iDefinedMessageLength;
    TUid                    iBIOMessageType;
    TBool                   iCreateAsUnread;
    RArray<TLinkIdParam>    iRecipientLinkIds;
    RArray<TLinkIdParam>    iSenderLinkIds;
    TInt                    iNumberOfExistingRecipients;
    TInt                    iNumberOfExistingSenders;

public:
    CMessagesParameters();
    ~CMessagesParameters();
    };



#endif // __CREATORMESSAGES_H__
