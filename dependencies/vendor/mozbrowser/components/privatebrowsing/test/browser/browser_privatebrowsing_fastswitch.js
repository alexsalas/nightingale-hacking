/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Private Browsing Tests.
 *
 * The Initial Developer of the Original Code is
 * Mozilla Foundation.
 * Portions created by the Initial Developer are Copyright (C) 2009
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *    Ehsan Akhgari <ehsan@mozilla.com>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

// This test makes sure that users are prevented from toggling the private
// browsing mode too quickly, hence be proctected from symptoms in bug 526194.

function test() {
  // initialization
  let pb = Cc["@mozilla.org/privatebrowsing;1"].
           getService(Ci.nsIPrivateBrowsingService);
  let pbCmd = document.getElementById("Tools:PrivateBrowsing");
  waitForExplicitFinish();

  let pass = 1;
  function observer(aSubject, aTopic, aData) {
    switch (aTopic) {
      case "private-browsing-transition-complete":
        if (pass++ == 1) {
          setTimeout(function () {
            ok(!pbCmd.hasAttribute("disabled"),
               "The private browsing command should be re-enabled after entering the private browsing mode");

            pb.privateBrowsingEnabled = false;
          }, 100);
        }
        else {
          setTimeout(function () {
            ok(!pbCmd.hasAttribute("disabled"),
               "The private browsing command should be re-enabled after exiting the private browsing mode");

            finish();
          }, 100);
        }
        break;
    }
    Services.obs.removeObserver(observer, "private-browsing-transition-complete");
  }
  let originalOnEnter = gPrivateBrowsingUI.onEnterPrivateBrowsing;
  gPrivateBrowsingUI.onEnterPrivateBrowsing = function() {
    originalOnEnter.apply(gPrivateBrowsingUI, arguments);
    ok(pbCmd.hasAttribute("disabled"),
       "The private browsing command should be disabled right after entering the private browsing mode");
    Services.obs.addObserver(observer, "private-browsing-transition-complete", false);
  };
  let originalOnExit = gPrivateBrowsingUI.onExitPrivateBrowsing;
  gPrivateBrowsingUI.onExitPrivateBrowsing = function() {
    originalOnExit.apply(gPrivateBrowsingUI, arguments);
    ok(pbCmd.hasAttribute("disabled"),
       "The private browsing command should be disabled right after exiting the private browsing mode");
    Services.obs.addObserver(observer, "private-browsing-transition-complete", false);
  };
  registerCleanupFunction(function() {
    gPrivateBrowsingUI.onEnterPrivateBrowsing = originalOnEnter;
    gPrivateBrowsingUI.onExitPrivateBrowsing = originalOnExit;
  });

  pb.privateBrowsingEnabled = true;
}