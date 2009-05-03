/*
 //
 // BEGIN SONGBIRD GPL
 //
 // This file is part of the Songbird web player.
 //
 // Copyright(c) 2005-2009 POTI, Inc.
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

#ifndef SBITUNESAGENTPROCESSOR_H_
#define SBITUNESAGENTPROCESSOR_H_

#include <deque>
#include <fstream>
#include <string>
#include <vector>
#include <assert.h>

#include "sbError.h"


/**
 * This is the base class for the iTunes agent processor.
 * It provides an interface for tasks. And contains platform neutral code such
 * as parsing the agent ini file.
 * ProcessTaskFile is the main entry point for this class. All other methods are
 * called from there.
 */
class sbiTunesAgentProcessor
{
public:
  static int const BATCH_SIZE = 300;
  
  /**
   * Clean up any resources
   */
  virtual ~sbiTunesAgentProcessor();
  
  /**
   * Returns true if there are any tasks file ready to process
   */
  virtual bool TaskFileExists() = 0; 
  
  /**
   * Removes the task file
   */
  virtual void RemoveTaskFile() = 0;
  
  /**
   * Process the task file
   * This basically opens the file and calls ProcessStream
   */
  sbError ProcessTaskFile();
  
  /**
   * Waits for the iTunes process to start
   */
  virtual sbError WaitForiTunes()=0;
  
  /**
   * Adds a track to the iTunes database given a path
   */
  sbError AddTrack(std::string const & aSource,
                   std::string const & aPath);

  /**
   * Reports the error, returns true if app should continue
   */
  virtual bool ErrorHandler(sbError const & aError) = 0;
  
  /**
   * Registers the application to startup when the user logs in
   */
  virtual sbError RegisterForLogin()=0;

  /**
   * Unregisters the application to startup when the user logs in
   */
  virtual sbError UnregisterForLogin()=0;
protected:
  typedef std::deque<std::string> Tracks;
  
  /**
   * Initialize any state
   */
  sbiTunesAgentProcessor();
  
  /**
   * Adds a track to the iTunes database given a path
   */
  virtual sbError AddTracks(std::string const & aSource,
                            Tracks const & aPaths)=0;
  
  /**
   * Removes a playlist from the iTunes database
   */
  virtual sbError RemovePlaylist(std::string const & aPlaylist)=0;
  
  /**
   * Creates a playlist (Recreates it if it already exists)
   */
  virtual sbError CreatePlaylist(std::string const & aPlaylistName) = 0;
  
  /**
   * Retrieve the path to the task file
   */
  virtual bool OpenTaskFile(std::ifstream & aStream) = 0;
  
  /**
   * Performs any initialization necessary. Optional to implement
   */
  virtual sbError Initialize() { return sbNoError; }
  
  /**
   * Logs the message to the platform specific log device
   */
  virtual void Log(std::string const & aMsg) = 0;
  
  /**
   * Returns true if we should shutdown
   */
  virtual bool Shutdown() = 0;
  
  /**
   * Sleep for x milliseconds
   */
  virtual void Sleep(unsigned long aMilliseconds) = 0;
  
  /**
   * This allows the derived class to perform any kind of
   * cleanup needed after shutdown has been processed. Default
   * implementation is to do nothing
   */
  virtual void ShutdownDone() {}
  
  enum VersionAction {
    OK,     // It's OK, we like this version we know it well
    ABORT,  // Have no clue what to do with it, so just stop
    RETRY   // Retry we've converted the file and there's a new one to process 
            // it. The parser will just delete this file
  };
  
  /**
   * Returns what to do with the file given it's version
   */
  virtual VersionAction VersionCheck(std::string const & aVersion) = 0;
  
private:
  std::ifstream  mInputStream;
  Tracks         mTrackBatch;
  std::string    mLastSource;
};

//------------------------------------------------------------------------------

// Utility method to create a itunes agent parser.
typedef std::auto_ptr<sbiTunesAgentProcessor> sbiTunesAgentProcessorPtr;
sbiTunesAgentProcessor * sbCreatesbiTunesAgentProcessor();

#endif /* SBITUNESAGENTPROCESSOR_H_ */

