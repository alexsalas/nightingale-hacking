/*
//
// BEGIN SONGBIRD GPL
//
// This file is part of the Songbird web player.
//
// Copyright(c) 2005-2008 POTI, Inc.
// http://songbirdnest.com
//
// This file may be licensed under the terms of of the
// GNU General Public License Version 2 (the "GPL").
//
// Software distributed under the License is distributed
// on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, either
// express or implied. See the GPL for the specific language
// governing rights and limitations.
//
// You should have received a copy of the GPL along with this
// program. If not, go to http://www.gnu.org/licenses/gpl.html
// or write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
//
// END SONGBIRD GPL
//
*/

#ifndef __SB_AUTORWLOCK_H__
#define __SB_AUTORWLOCK_H__

#include <nsAutoLock.h>
#include <prrwlock.h>

/** 
 * sbAutoReadLock
 * Stack-based read locking object for PRRWLock.
 **/
class NS_COM_GLUE sbAutoReadLock : public nsAutoLockBase {
private:
    PRRWLock* mLock;
    PRBool mLocked;

    // Not meant to be implemented. This makes it a compiler error to
    // construct or assign an nsAutoLock object incorrectly.
    sbAutoReadLock(void) {}
    sbAutoReadLock(sbAutoReadLock& /*aLock*/) {}
    sbAutoReadLock& operator =(sbAutoReadLock& /*aLock*/) {
        return *this;
    }

    // Not meant to be implemented. This makes it a compiler error to
    // attempt to create an sbAutoReadLock object on the heap.
    static void* operator new(size_t /*size*/) CPP_THROW_NEW {
        return nsnull;
    }
    static void operator delete(void* /*memory*/) {}

public:

    /**
     * NewLock
     * Allocates a new PRRWLock for use with sbAutoReadLock. name is
     * not checked for uniqueness.
     * @param rank Lock rank.
     * @param name A name which can reference this lock
     * @param lock A valid PRRWLock* that was created by
     *             sbAutoReadLock::NewLock()
     * @returns nsnull if failure
     *          A valid PRRWLock* if successful, which must be destroyed
     *          by sbAutoReadLock::DestroyLock()
     **/
    static PRRWLock* NewLock(PRUint32 rank, const char* name);
    static void      DestroyLock(PRRWLock* lock);

    /**
     * Constructor
     * The constructor aquires the given lock for reading.  The destructor
     * releases the lock.
     * 
     * @param aLock A valid PRRWLock* returned from the NSPR's 
     * PR_NewRWLock() function.
     **/
    sbAutoReadLock(PRRWLock* aLock)
        : nsAutoLockBase(aLock, eAutoLock),
          mLock(aLock),
          mLocked(PR_TRUE) {
        PR_ASSERT(mLock);

        // This will assert deep in the bowels of NSPR if you attempt
        // to re-enter the lock.
        PR_RWLock_Rlock(mLock);
    }
    
    ~sbAutoReadLock(void) {
        if (mLocked)
            PR_RWLock_Unlock(mLock);
    }

    /** 
     * lock
     * Client may call this to reaquire the given lock. Take special
     * note that attempting to aquire a locked lock will hang or crash.
     **/  
    void lock() {
        Show();
        PR_ASSERT(!mLocked);
        PR_RWLock_Rlock(mLock);
        mLocked = PR_TRUE;
    }


    /** 
     * unlock
     * Client may call this to release the given lock. Take special
     * note unlocking an unlocked lock has undefined results.
     **/ 
     void unlock() {
        PR_ASSERT(mLocked);
        PR_RWLock_Unlock(mLock);
        mLocked = PR_FALSE;
        Hide();
    }
};

class sbAutoReadUnlock : nsAutoUnlockBase
{
private:
    PRRWLock *mLock;
     
public:
    sbAutoReadUnlock(PRRWLock *lock) : 
        nsAutoUnlockBase(lock),
        mLock(lock)
    {
        PR_RWLock_Unlock(mLock);
    }

    ~sbAutoReadUnlock() {
        PR_RWLock_Rlock(mLock);
    }
};

/** 
 * sbAutoWriteLock
 * Stack-based write locking object for PRRWLock.
 **/
class NS_COM_GLUE sbAutoWriteLock : public nsAutoLockBase {
private:
    PRRWLock* mLock;
    PRBool mLocked;

    // Not meant to be implemented. This makes it a compiler error to
    // construct or assign an nsAutoLock object incorrectly.
    sbAutoWriteLock(void) {}
    sbAutoWriteLock(sbAutoWriteLock& /*aLock*/) {}
    sbAutoWriteLock& operator =(sbAutoWriteLock& /*aLock*/) {
        return *this;
    }

    // Not meant to be implemented. This makes it a compiler error to
    // attempt to create an sbAutoWriteLock object on the heap.
    static void* operator new(size_t /*size*/) CPP_THROW_NEW {
        return nsnull;
    }
    static void operator delete(void* /*memory*/) {}

public:

    /**
     * NewLock
     * Allocates a new PRRWLock for use with sbAutoWriteLock. name is
     * not checked for uniqueness.
     * @param rank Lock rank.
     * @param name A name which can reference this lock
     * @param lock A valid PRRWLock* that was created by
     *             sbAutoWriteLock::NewLock()
     * @returns nsnull if failure
     *          A valid PRRWLock* if successful, which must be destroyed
     *          by sbAutoWriteLock::DestroyLock()
     **/
    static PRRWLock* NewLock(PRUint32 rank, const char* name);
    static void      DestroyLock(PRRWLock* lock);

    /**
     * Constructor
     * The constructor aquires the given lock for writing.  The destructor
     * releases the lock.
     * 
     * @param aLock A valid PRRWLock* returned from the NSPR's 
     * PR_NewRWLock() function.
     **/
    sbAutoWriteLock(PRRWLock* aLock)
        : nsAutoLockBase(aLock, eAutoLock),
          mLock(aLock),
          mLocked(PR_TRUE) {
        PR_ASSERT(mLock);

        // This will assert deep in the bowels of NSPR if you attempt
        // to re-enter the lock.
        PR_RWLock_Wlock(mLock);
    }
    
    ~sbAutoWriteLock(void) {
        if (mLocked)
            PR_RWLock_Unlock(mLock);
    }

    /** 
     * lock
     * Client may call this to reaquire the given lock. Take special
     * note that attempting to aquire a locked lock will hang or crash.
     **/  
    void lock() {
        Show();
        PR_ASSERT(!mLocked);
        PR_RWLock_Wlock(mLock);
        mLocked = PR_TRUE;
    }


    /** 
     * unlock
     * Client may call this to release the given lock. Take special
     * note unlocking an unlocked lock has undefined results.
     **/ 
     void unlock() {
        PR_ASSERT(mLocked);
        PR_RWLock_Unlock(mLock);
        mLocked = PR_FALSE;
        Hide();
    }
};

class sbAutoWriteUnlock : nsAutoUnlockBase
{
private:
    PRRWLock *mLock;
     
public:
    sbAutoWriteUnlock(PRRWLock *lock) : 
        nsAutoUnlockBase(lock),
        mLock(lock)
    {
        PR_RWLock_Unlock(mLock);
    }

    ~sbAutoWriteUnlock() {
        PR_RWLock_Wlock(mLock);
    }
};

#endif /* __SB_AUTORWLOCK_H__ */
