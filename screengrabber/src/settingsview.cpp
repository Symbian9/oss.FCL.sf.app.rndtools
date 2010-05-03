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

#include <hbdataform.h>
#include <hbdataformmodelitem.h>
#include <hbdataformmodel.h>
#include <hbdataformviewitem.h>
#include <hbaction.h>
#include <hbmenu.h>
#include <hbtoolbar.h>
#include <hbabstractviewitem.h>
#include <hbaction.h>


#include "settingsview.h"
#include "enginewrapper.h"
#include "sgengine.h"
#include "hbslider.h"
#include "notifications.h"



// ---------------------------------------------------------------------------

SettingsView::SettingsView(HbView &mainView, HbMainWindow &mainWindow, EngineWrapper &engineWrapper): 
    mEngineWrapper(engineWrapper), 
    mMainWindow(mainWindow), 
    mMainView(mainView)
{
    // Set title and add this view to main window
    setTitle("Settings");
    
    HbAction *actionSaveSettings = menu()->addAction(QString("Save & close"));
    HbAction *actionCancel = menu()->addAction("Cancel & close");
    
    toolBar()->addAction(actionSaveSettings);
    toolBar()->addAction(actionCancel);
  
    
    //create setting form
    mSettingForm = new HbDataForm();
    
    //create a model class
    mModel = new HbDataFormModel(this);
    
    // DataFormItem for mode selection
    mModeItem = mModel->appendDataFormItem(
            HbDataFormModelItem::RadioButtonListItem, QString("Capture mode"), 0);
    //setting the text property of check box.
    mModeItem->setData(HbDataFormModelItem::KeyRole, QString("mode"));
    mModeItem->setContentWidgetData(QString("items"), CAPTUREMODES);
    
    // Create setting model
     createSingleCaptureComponents(mModel, 0);
     createSequentialCaptureComponents(mModel, 0);
     createVideoCaptureComponents(mModel, 0);
 
    // Set created model model to form
    mSettingForm->setModel(mModel);
    setWidget(mSettingForm);//takes ownership
    
    // Get view item of mode selection item
    HbDataFormViewItem *viewItemVideoPage = mSettingForm->dataFormViewItem(mModel->indexFromItem(mModeItem));

    loadSettings();
    
    // Connect signals from item modifications and close with this form's slots
   
//    connect(viewItemVideoPage, SIGNAL(itemModified(QPersistentModelIndex, QVariant)), this, SLOT(updateShownItems()));
    connect(actionSaveSettings, SIGNAL(triggered()), this, SLOT(saveAndClose()));
    connect(actionCancel, SIGNAL(triggered()), this, SLOT(close()));
	
	HbAction *mDefaultNavigationAction = new HbAction(Hb::QuitNaviAction, this);
	connect(mDefaultNavigationAction,SIGNAL(triggered()), this, SLOT(saveAndClose()));
	setNavigationAction(mDefaultNavigationAction);
	


}


// ---------------------------------------------------------------------------

SettingsView::~SettingsView()
{

}

// ---------------------------------------------------------------------------

void SettingsView::loadSettings()
{

    // get settings from engine;
    mSettings = mEngineWrapper.getGrabSettings();
    
    //Capture mode
    mModeItem->setContentWidgetData("selected", mSettings.mCaptureMode);
    
    // Still image 
    mImageHotKeyItem->setContentWidgetData("selected", mSettings.mSingleCaptureHotkey);
    mImageFormatItem->setContentWidgetData("selected", mSettings.mSingleCaptureImageFormat);
    mImageMemoryInUseItem->setContentWidgetData("selected", mSettings.mSingleCaptureMemoryInUseMultiDrive);
    mImageFileNameItem->setContentWidgetData("text", mSettings.mSingleCaptureFileName);
       
    // Seguantial image components
    mSequantialHotKeyItem->setContentWidgetData("selected", mSettings.mSequantialCaptureHotkey);
    mSequantialFormatItem->setContentWidgetData("selected", mSettings.mSequantialCaptureImageFormat);
    mSequantialDelayItem->setContentWidgetData("text", mSettings.mSequantialCaptureDelay);
    mSequantialMemoryInUseItem->setContentWidgetData("selected", mSettings.mSequantialCaptureMemoryInUseMultiDrive);
    mSequantialFileNameItem->setContentWidgetData("text", mSettings.mSequantialCaptureFileName);
    
    // Video capture components
    mVideoHotKeyItem->setContentWidgetData("selected", mSettings.mVideoCaptureHotkey);
    mVideoFormatItem->setContentWidgetData("selected", mSettings.mVideoCaptureVideoFormat);
    mVideoMemoryInUseItem->setContentWidgetData("selected", mSettings.mVideoCaptureMemoryInUseMultiDrive);
    mVideoFileNameItem->setContentWidgetData("text", mSettings.mVideoCaptureFileName);
    
	
}

// ---------------------------------------------------------------------------

void SettingsView::createSingleCaptureComponents(HbDataFormModel *model, HbDataFormModelItem *parent)
{
    
    // Create Group for single image components
    mGroupImageCapture = model->appendDataFormGroup(QString("Single image settings"), parent);

    // DataFormItem for hotkey selection
    mImageHotKeyItem = model->appendDataFormItem(
            HbDataFormModelItem::RadioButtonListItem, QString("Capture hotkey"), mGroupImageCapture);
    //setting the text property of check box.
    mImageHotKeyItem->setData(HbDataFormModelItem::KeyRole, QString("image_hotkey"));
    mImageHotKeyItem->setContentWidgetData(QString("items"), KEYS);

    // DataFormItem for image format selection
    mImageFormatItem = model->appendDataFormItem(
            HbDataFormModelItem::RadioButtonListItem, QString("Image format"), mGroupImageCapture);
    //setting the text property of check box.
    mImageFormatItem->setData(HbDataFormModelItem::KeyRole, QString("image_format"));
    mImageFormatItem->setContentWidgetData(QString("items"), IMAGEFORMATS);
    
    // DataFormItem for memory in use selection
    mImageMemoryInUseItem = model->appendDataFormItem(
            HbDataFormModelItem::RadioButtonListItem, QString("Memory in use"), mGroupImageCapture);
    //setting the text property of check box.
    mImageMemoryInUseItem->setData(HbDataFormModelItem::KeyRole, QString("image_memory"));
    mImageMemoryInUseItem->setContentWidgetData(QString("items"), MEMORYMODES);
    
    // DataFormItem for file name
    mImageFileNameItem = model->appendDataFormItem(
            HbDataFormModelItem::TextItem, QString("File name"), mGroupImageCapture);
    //setting the text property of check box.
    mImageFileNameItem->setData(HbDataFormModelItem::KeyRole, QString("image_name"));
    mImageFileNameItem->setContentWidgetData(QString("text"), QString("Shot"));
    
}

// ---------------------------------------------------------------------------

void SettingsView::createSequentialCaptureComponents(HbDataFormModel *model, HbDataFormModelItem *parent)
{
    
    
    // Create Group for sequential image components
    mGroupSeguantialCapture = model->appendDataFormGroup(QString("Sequential image settings"), parent);
    
    // DataFormItem for hotkey selection
    mSequantialHotKeyItem = model->appendDataFormItem(
            HbDataFormModelItem::RadioButtonListItem, QString("Capture hotkey"), mGroupSeguantialCapture);
    //setting the text property of check box.
    mSequantialHotKeyItem->setData(HbDataFormModelItem::KeyRole, QString("seguential_hotkey"));
    mSequantialHotKeyItem->setContentWidgetData(QString("items"), KEYS);
    
    // DataFormItem for image format selection
    mSequantialFormatItem = model->appendDataFormItem(
            HbDataFormModelItem::RadioButtonListItem, QString("Image format"), mGroupSeguantialCapture);
    //setting the text property of check box.
    mSequantialFormatItem->setData(HbDataFormModelItem::KeyRole, QString("seguential_format"));
    mSequantialFormatItem->setContentWidgetData(QString("items"), IMAGEFORMATS);
    
    // DataFormItem for delay between images selection
    mSequantialDelayItem = model->appendDataFormItem(
            HbDataFormModelItem::TextItem, QString("Delay between two images(ms)"), mGroupSeguantialCapture);
    //setting the text property of check box.
    mSequantialDelayItem->setData(HbDataFormModelItem::KeyRole, QString("seguential_name"));
    mSequantialDelayItem->setContentWidgetData(QString("text"), QString("Shot"));
    
    // DataFormItem for memory selection
    mSequantialMemoryInUseItem = model->appendDataFormItem(
            HbDataFormModelItem::RadioButtonListItem, QString("Memory in use"), mGroupSeguantialCapture);
    //setting the text property of check box.
    mSequantialMemoryInUseItem->setData(HbDataFormModelItem::KeyRole, QString("seguential_memory"));
    mSequantialMemoryInUseItem->setContentWidgetData(QString("items"), MEMORYMODES);
    
    // DataFormItem for file name
    mSequantialFileNameItem = model->appendDataFormItem(
            HbDataFormModelItem::TextItem, QString("File name"), mGroupSeguantialCapture);
    //setting the text property of check box.
    mSequantialFileNameItem->setData(HbDataFormModelItem::KeyRole, QString("seguential_name"));
    mSequantialFileNameItem->setContentWidgetData(QString("text"), QString("Shot"));
    
}

// ---------------------------------------------------------------------------

void SettingsView::createVideoCaptureComponents(HbDataFormModel *model, HbDataFormModelItem *parent)
{

    // Create Group for video capturing components
    mGroupVideoCapture = model->appendDataFormGroup(QString("Video settings"), parent);
    
    // DataFormItem for hotkey selection
    mVideoHotKeyItem = model->appendDataFormItem(
            HbDataFormModelItem::RadioButtonListItem, QString("Start/Stop hotkey"), mGroupVideoCapture);
    //setting the text property of check box.
    mVideoHotKeyItem->setData(HbDataFormModelItem::KeyRole, QString("video_hotkey"));
    mVideoHotKeyItem->setContentWidgetData(QString("items"), KEYS);
    
    // DataFormItem for video format selection
    mVideoFormatItem = model->appendDataFormItem(
            HbDataFormModelItem::RadioButtonListItem, QString("Video format"), mGroupVideoCapture);
    //setting the text property of check box.
    mVideoFormatItem->setData(HbDataFormModelItem::KeyRole, QString("video_format"));
    mVideoFormatItem->setContentWidgetData(QString("items"), VIDEOFORMATS);
    
    // DataFormItem for memory selection
    mVideoMemoryInUseItem = model->appendDataFormItem(
            HbDataFormModelItem::RadioButtonListItem, QString("Memory in use"), mGroupVideoCapture);
    //setting the text property of check box.mGroupVideoCapture
    mVideoMemoryInUseItem->setData(HbDataFormModelItem::KeyRole, QString("video_memory"));
    mVideoMemoryInUseItem->setContentWidgetData(QString("items"), MEMORYMODES);
    
    // DataFormItem for file name
    mVideoFileNameItem = model->appendDataFormItem(
            HbDataFormModelItem::TextItem, QString("File name"), mGroupVideoCapture);
    //setting the text property of check box.
    mVideoFileNameItem->setData(HbDataFormModelItem::KeyRole, QString("video_name"));
    mVideoFileNameItem->setContentWidgetData(QString("text"), QString("Video"));
    
}

// ---------------------------------------------------------------------------

void SettingsView::saveAndClose()
{

    readFormItems();
    if (!mEngineWrapper.saveSettings(mSettings)) {
        Notifications::error("Unable to save settings");
    }    
    
    mEngineWrapper.EnableRcpOfFoc(EFalse);
    mMainWindow.setCurrentView(&mMainView);
	
}



// ---------------------------------------------------------------------------

void SettingsView::readFormItems()
{
    
    //TODO this does not work correctly with WK38 ( Text box items )

    mSettings.mCaptureMode = mModeItem->contentWidgetData("selected").toInt();

    mSettings.mSingleCaptureImageFormat = mImageFormatItem->contentWidgetData("selected").toInt();
    mSettings.mSingleCaptureHotkey = mImageHotKeyItem->contentWidgetData("selected").toInt();
    mSettings.mSingleCaptureMemoryInUseMultiDrive = mImageMemoryInUseItem->contentWidgetData("selected").toInt(); 
    mSettings.mSingleCaptureFileName = mImageFileNameItem->contentWidgetData("text").toString();
    
    mSettings.mSequantialCaptureImageFormat = mSequantialFormatItem->contentWidgetData("selected").toInt();
    mSettings.mSequantialCaptureHotkey = mSequantialHotKeyItem ->contentWidgetData("selected").toInt();
    mSettings.mSequantialCaptureMemoryInUseMultiDrive = mSequantialMemoryInUseItem ->contentWidgetData("selected").toInt();
    mSettings.mSequantialCaptureFileName = mSequantialFileNameItem->contentWidgetData("text").toString();
    mSettings.mSequantialCaptureDelay = mSequantialDelayItem->contentWidgetData("text").toInt();
    

    mSettings.mVideoCaptureVideoFormat = mVideoFormatItem->contentWidgetData("selected").toInt();
    mSettings.mVideoCaptureHotkey = mVideoHotKeyItem ->contentWidgetData("selected").toInt();
    mSettings.mVideoCaptureMemoryInUseMultiDrive = mVideoMemoryInUseItem ->contentWidgetData("selected").toInt();
    mSettings.mVideoCaptureFileName = mVideoFileNameItem ->contentWidgetData("text").toString();
	
   
}


// ---------------------------------------------------------------------------
/*
void SettingsView::updateShownItems()
{ 

    if (mMainWindow.currentView() == this) {
        // Get view items of each group
        HbDataFormViewItem *viewItemImageGroup = mSettingForm->dataFormViewItem(mModel->indexFromItem(mGroupImageCapture));
        HbDataFormViewItem *viewItemSequantialGroup = mSettingForm->dataFormViewItem(mModel->indexFromItem(mGroupSeguantialCapture));
        HbDataFormViewItem *viewItemVideoGroup = mSettingForm->dataFormViewItem(mModel->indexFromItem(mGroupVideoCapture));

    
        // Set certain group expanded according to selected mode. 
        // TODO this does not work correctly with WK38(selectedItem is for some reason always 1)
    
        int selectedItem = mModeItem->contentWidgetData("selected").toInt();
        
        if (selectedItem == SINGLE){
            viewItemImageGroup->setExpanded(true);
            viewItemSequantialGroup->setExpanded(false);
            viewItemVideoGroup->setExpanded(false);
    
        }
        else if (selectedItem == SEQUENTIAL){
            viewItemImageGroup->setExpanded(false);
            viewItemSequantialGroup->setExpanded(true);
            viewItemVideoGroup->setExpanded(false);    
        }
        
        else if (selectedItem == VIDEO){
            viewItemImageGroup->setExpanded(false);
            viewItemSequantialGroup->setExpanded(false);
            viewItemVideoGroup->setExpanded(true);
        }
        
        
    }
    
}
*/
// ---------------------------------------------------------------------------

void SettingsView::close()
{
    mEngineWrapper.EnableRcpOfFoc(EFalse);
    mMainWindow.setCurrentView(&mMainView);
}
