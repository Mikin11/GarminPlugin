/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * GarminPlugin
 * Copyright (C) Andreas Diesner 2013 <garminplugin [AT] andreas.diesner [DOT] de>
 *
 * GarminPlugin is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GarminPlugin is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FITMSG_LISTENER_H
#define FITMSG_LISTENER_H

#include <string>
#include "fitMsg.hpp"

using namespace std;

class FitMsg_Listener
{
public:
    FitMsg_Listener() {};

    virtual ~FitMsg_Listener() {};

    /**
     * Overwrite to receive fit messages
     */
    virtual void fitMsgReceived(FitMsg *msg)=0;

    /**
     * Overwrite and enable debug to receive debug messages
     */
    virtual void fitDebugMsg(string msg) {};
};

#endif // FITMSG_LISTENER_H
