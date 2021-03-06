/* ****************************************************************************** *\

Copyright (C) 2003-2009 Intel Corporation.  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
- Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.
- Neither the name of Intel Corporation nor the names of its contributors
may be used to endorse or promote products derived from this software
without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY INTEL CORPORATION "AS IS" AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL INTEL CORPORATION BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

File Name: umc_automatic_mutex.h

\* ****************************************************************************** */

#ifndef __UMC_AUTOMATIC_MUTEX_H__
#define __UMC_AUTOMATIC_MUTEX_H__

#include "vm_mutex.h"

namespace UMC
{

#pragma pack(1)

class AutomaticMutex
{
public:
    // Constructor
    AutomaticMutex(vm_mutex &mutex)
    {
        if (vm_mutex_is_valid(&mutex))
        {
            m_pMutex = &mutex;

            // lock mutex
            vm_mutex_lock(m_pMutex);
            m_bLocked = true;
        }
        else
        {
            m_pMutex = (vm_mutex *) 0;
            m_bLocked = false;
        }
    }

    // Destructor
    ~AutomaticMutex(void)
    {
        Unlock();
    }

    // lock mutex again
    void Lock(void)
    {
        if (m_pMutex)
        {
            if ((vm_mutex_is_valid(m_pMutex)) && (false == m_bLocked))
            {
                vm_mutex_lock(m_pMutex);
                m_bLocked = true;
            }
        }
    }

    // Unlock mutex
    void Unlock(void)
    {
        if (m_pMutex)
        {
            if ((vm_mutex_is_valid(m_pMutex)) && (m_bLocked))
            {
                vm_mutex_unlock(m_pMutex);
                m_bLocked = false;
            }
        }
    }

protected:
    vm_mutex *m_pMutex;                                         // (vm_mutex *) pointer to using mutex
    bool m_bLocked;                                             // (bool) mutex is own locked
};

#pragma pack()

} // end namespace UMC

#endif // __UMC_AUTOMATIC_MUTEX_H__
