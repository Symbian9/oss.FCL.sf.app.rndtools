#
# Copyright (c) 2010 Nokia Corporation and/or its subsidiary(-ies).
# All rights reserved.
# This component and the accompanying materials are made available
# under the terms of "Eclipse Public License v1.0"
# which accompanies this distribution, and is available
# at the URL "http://www.eclipse.org/legal/epl-v10.html".
#
# Initial Contributors:
# Nokia Corporation - initial contribution.
#
# Contributors:
#
# Description: 
#
#

TEMPLATE = subdirs

BLD_INF_RULES.prj_platforms += "$${LITERAL_HASH}include \"bld_generic.inf\""
#TODO: Functionality broken 
#BLD_INF_RULES.prj_exports += "../rom/perfmon_datapopup.iby CORE_IBY_EXPORT_PATH(tools,perfmon_datapopup.iby)"