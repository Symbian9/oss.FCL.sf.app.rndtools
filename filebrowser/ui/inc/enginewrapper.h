/*
* Copyright (c) 2010 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef ENGINEWRAPPER_H
#define ENGINEWRAPPER_H

#include <QString>
#include <QStringList>
#include <QModelIndexList>
#include <driveentry.h>
#include <fileentry.h>
#include <engine.h>

#include "filebrowsersettings.h"

#include <FBFileUtils.h>

class CEngine;
class SearchAttributes;
class SearchResults;
class FileBrowserView;

class QModelIndex;

class OverwriteOptions
{
public:
    OverwriteOptions() :
            doFileOperations(true),
            queryIndex(0),
            overWriteFlags(CFileMan::EOverWrite)
    {}

    bool doFileOperations;
    int queryIndex;
    QString postFix;
    int overWriteFlags;
};

/**
 * class that is used for communicating between Symbian and Qt code.
 */
class EngineWrapper : MFileBrowserUI {
public:
    
    /**
     * Constructor
     */
    EngineWrapper();
    
    /**
     * Destructor
     */
    ~EngineWrapper();
    
    /**
     * Initializes Engine Wrapper
     * @return true if engine was started successfully
     */
    bool init();

public: // from MFileBrowserUI
    /* Functions that are called from engine: */
//    TInt QueryCurrentItemIndex();

    void ShowInformationNote(const TDesC& aDescText);
    void ShowErrorNote(const TDesC& aDescText, TBool aNoTimeout = EFalse);
    void ShowConfirmationNote(const TDesC& aDescText, TBool aNoTimeout = EFalse);
    TBool ShowConfirmationQuery(const TDesC& aDescText);

public: 
    /* Functions that are called from UI */
    bool searchFiles();
    SearchAttributes getFileSearchAttributes();
    int setFileSearchAttributes(SearchAttributes attributes);
    SearchResults getSearchResults();

    FileBrowserSettings &settings() { return mSettings; }
    const FileBrowserSettings &settings() const { return mSettings; }

    void saveSettings(bool aNotifyModules = true);

    void startExecutingCommands(const QString &aCommandsExecutionMessage);
    void refreshView();
//    TBool IsCurrentDriveReadOnly();
//    TBool IsCurrentItemDirectory();
    void moveUpOneLevel();
    void moveDownToDirectory(const QModelIndex& index);
    int clipboardCut(const QModelIndexList &aSelectionIndices);
    int clipboardCopy(const QModelIndexList &aSelectionIndices);
    void clipboardPaste(const OverwriteOptions &aOverwriteOptions);
    void copyToFolder(const QString &aTargetDir, const OverwriteOptions &aOverwriteOptions, bool aMove);
    void createNewFile(const QString &aNewFileName);
    void createNewDirectory(const QString &aNewDirectoryName);
    void deleteItems(const QModelIndexList& aSelectionIndices);
    bool selectionHasDirs();
    void rename(const QModelIndex& aIndex, const QString aNewName);
    void touch(bool aRecurse);
    void properties(const QModelIndex &aCurrentItemIndex, QStringList &aPropertyList, QString &aTitleText);

    bool openAppArc(QString fileName);
    bool openDocHandler(QString fileName, bool embeddedVal = false);

    bool isDriveListViewActive();
    bool isCurrentDriveReadOnly();
    bool isClipBoardListInUse();
    int itemCount() const;
    DriveEntry getDriveEntry(const QModelIndex& aIndex) const;
    FileEntry getFileEntry(const QModelIndex& aIndex) const;
	
    const CArrayFix<TInt> *convertSelectionList(const QModelIndexList &aSelectionIndices);
    void setCurrentSelection(const QModelIndexList &aSelectionIndices);
    bool isDestinationEntriesExists(const QModelIndexList &aSelectionIndices, QString aTargetDir);
    bool targetExists(const QModelIndex& aIndex, const QString aNewName);
    QString currentPath() const;
    TOverwriteOptions convertOverwriteOptions(const OverwriteOptions &aOverwriteOptions);
    bool hasDrivePassword(const QModelIndex &aIndex);
    bool isDriveRemovable(const QModelIndex &aIndex);
    bool isDriveLocked(const QModelIndex &aIndex);
    void GetDriveName(const QModelIndex &aIndex, QString &aDriveName);
    void GetDriveVolumeLabel(const QModelIndex &aIndex, QString &aDriveName);

    void DiskAdminSetDrivePassword(const QModelIndex &aIndex, const QString &aOldPassword, const QString &aNewPassword);
    void DiskAdminUnlockDrive(const QModelIndex &aIndex, const QString &aOldPassword);
    void DiskAdminClearDrivePassword(const QModelIndex &aIndex, const QString &aOldPassword);
    void DiskAdminEraseDrivePassword(const QModelIndex &aIndex);
    void DiskAdminFormatDrive(const QModelIndex &aIndex, bool aQuickFormat);
    void DiskAdminQuickFormatDrive(const QModelIndex &aIndex, bool aQuickFormat);
    void DiskAdminCheckDisk(const QModelIndex &aIndex);
    void DiskAdminScanDrive(const QModelIndex &aIndex);
    void DiskAdminSetDriveName(const QModelIndex &aIndex, const QString &aDriveName);
    void DiskAdminSetDriveVolumeLabel(const QModelIndex &aIndex, const QString &aVolumeLabel);
    void DiskAdminEjectDrive(const QModelIndex &aIndex);
    void DiskAdminDismountDrive(const QModelIndex &aIndex);
    void DiskAdminEraseMBR(const QModelIndex &aIndex);
    void DiskAdminPartitionDrive(const QModelIndex &aIndex, bool aEraseMBR, int aAmountOfPartitions);

    void ToolsSetErrRd(bool aEnable);
    bool ErrRdFileExists();

    void ToolsErrorSimulateLeave(int aLeaveCode);
    void ToolsErrorSimulatePanic(QString aPanicCategory, int aPanicCode);
    void ToolsErrorSimulateException(int aExceptionCode);

    quint32 getDebugMask();
    void toolsSetDebugMask(quint32 aDbgMask);

private:
    // FB engine
    CEngine *mEngine;
    // List of found files results for Ui
    QStringList mFilesFound;
    FileBrowserSettings mSettings;
    };

#endif //ENGINEWRAPPER_H
