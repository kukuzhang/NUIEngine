﻿//  **************************************
//  File:        KObject.h
//  Copyright:   Copyright(C) 2013-2017 Wuhan KOTEI Informatics Co., Ltd. All rights reserved.
//  Website:     http://www.nuiengine.com
//  Description: This code is part of NUI Engine (NUI Graphics Lib)
//  Comments:
//  Rev:         2
//  Created:     2017/4/12
//  Last edit:   2017/4/28
//  Author:      Chen Zhi
//  E-mail:      cz_666@qq.com
//  License: APACHE V2.0 (see license file) 
//  ***************************************
#ifndef _KOBJECT_H_
#define _KOBJECT_H_

#include "NE_pubhead.h"
#include "KLog.h"
class NUI_API KObject
{


public:
	KObject(){};
	virtual ~KObject(){};
	virtual kn_string toString() {return kn_string();};


	
};
#endif //  _CKOBJECT_H_
