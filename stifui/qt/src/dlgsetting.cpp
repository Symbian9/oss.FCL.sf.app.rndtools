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
 * Description: QT C++ based Class.
 * 
 */

#include "dlgsetting.h"
#include <QtGui>

DlgSetting::DlgSetting(UiSetting* settingObj, QWidget *parent)
    : QDialog(parent), setting(settingObj)
    {
    SetupUI();
    }

void DlgSetting::SetupUI()
    {
    this->setContextMenuPolicy(Qt::NoContextMenu);
    QGridLayout *mainLayout = new QGridLayout(this);
    this->setLayout(mainLayout);
    
    chkShowoutput = new QCheckBox(this);
    chkShowoutput->setText(tr("Show output in execution."));
    chkShowoutput->setChecked(setting->ReadSetting("showoutput") == "true");
    
    QWidget *toolWidget = new QWidget(this);
    QGridLayout *toolLayout = new QGridLayout();
    
    toolWidget->setLayout(toolLayout);
    btnOk = new QPushButton(tr("Ok"), toolWidget);
    btnOk->setFixedSize(100, 30);
    QObject::connect(btnOk, SIGNAL(clicked()), this,
            SLOT(on_btnOk_clicked()));
    btnCancel = new QPushButton(tr("Cancel"), toolWidget);
    btnCancel->setFixedSize(100, 30);
    QObject::connect(btnCancel, SIGNAL(clicked()), this,
            SLOT(on_btnCancel_clicked()));
    toolLayout->addWidget(btnOk, 0, 0);
    toolLayout->addWidget(btnCancel, 0, 1);

    mainLayout->addWidget(chkShowoutput, 0, 0);
    mainLayout->addWidget(toolWidget, 2, 0);    
    }

void DlgSetting::on_btnOk_clicked()
    {
    if(chkShowoutput->checkState() == Qt::Checked)
        {
        setting->SetSetting("showoutput", "true");
        }
    else
        {
        setting->SetSetting("showoutput", "false");    
        }
    this->accept();
    }

void DlgSetting::on_btnCancel_clicked()
    {
    this->reject();
    }
