Nightingale is a community based fork of the Songbird Media player
distributed under the GNU GPL and portions (XULRunner and Mozilla libs)
licensed under the Mozilla MPL/BSD license. 

The goal of Nightingale is to create a Media Player, which will 
eventually use only system libraries to conserve space. Currently, some
libraries are still bundled, but progress is being made to change this 
fact.

This git tree is the Songbird trunk, rebranded for Nightingale. It's a 
reflection of what our Xul 6+ releases will be like.

Notes
=====

  * To build, you need to have all of the gstreamer0.10 packages for your 
distro, svn, wget, and git (if pulling the tree down) installed, 
as well as the usual dependencies for building software upon your 
distro.

  * If it gets python errors, make sure you have python2 installed,
and try the build.sh script again.

  * If it doesn't play music, you'll need to copy /usr/lib/gstreamer0.10/*
into compiled-dist-linux-[your arch]/dist/gst-plugins and then 
rerun nightingale. It should then play music.

Building
========
If on Linux, simply run the [build.sh](build.sh) script. It will download the deps
and build the app for you. You'll generally need the usual build deps
for most software packages, though.

Ubuntu and Debian users should note you'll need (and a few more, checkout the build article for a full list):
libdbus-glib-1-dev
libgstreamer-plugins-base0.10-dev

Also note that because of Ubuntu and Debian's incompatible taglib,
you'll want to add `ac_add_options --with-taglib-source=packaged` to your nightingale.config

More information can be gleaned from the Nightingale wiki:

  * [Windows](http://tinyurl.com/ce3anjo)
  * [Mac](http://tinyurl.com/ckca4no)
  * [Linux](http://tinyurl.com/d569knt)

Configure Options
=================

`ac_add_options (option here)`

 option                                  | description 
-----------------------------------------|-------------
`--with-taglib-source=[system,packaged]` | use system taglib or not
`--enable-debug`                         | whether or not to compile debug
`--enable-jars`                          | whether or not to create jars
`--enable-installer`                     | whether or not to make installer
`--enable-official`                      | whether or not to official build
`--enable-nightly`                       | whether or not to nightly build
`--enable-tests`                         | whether or not to build tests
`--enable-update-channel=CHANNEL`        | which update channel to use
`--enable-breakpad`                      | whether or not to enable breakpad
`--enable-static`                        | single-component static build
`--enable-compiler-environment-checks`   | only allow supported compilers  
`--enable-libnotify`                     | Optionally enable libnotify
`--enable-unity-integration`             | Optional support for Unity's sound menu
`--enable-system-nspr`                   | Optionally use your system's NSPR instead of the bundled one from Mozilla

Notes for Configurable Options
==============================

libnotify support
-----------------
dependencies:
  * libnotify-dev
  * libgtk2.0-dev

Unity sound menu integration
----------------------------
dependencies:
  * libunity-dev
  * libnotify-dev
  * libgtk2.0-dev

System NSPR
-----------
dependencies:
  * libnspr4-dev

Contributions
=============
To join in and help, please visit [our forum](http://forum.getnightingale.com/)
or jump into #nightingale on irc.mozilla.org.

Contributors
============
  * Steven Bengtson - Stevo
  * Janek Bevendorff - Manko10
  * Downward
  * Lukas Diener - Lukas_Skywalker
  * Matt Dwyer - MattSD
  * Martin Giger - freaktechnik
  * Geoffrey Gates - Timmythepirate
  * Andrew Luecke - Auzy
  * Matt Parnell - Ilikenwf
  * Dirk Steinmetz - rsjtdrjgfuzkfg
  * Antoine Turmel - GeekShadow
  * Mark Yen - Mook
  * Akil Krishnan - LIB53
  * Alexander Korenev - LookingMan
  * John Murray - johnmurrayvi
  * David Rogers - Ezekial1000
  * Luis Gallego - luisgmarine
  * Lars Tobias Skjong-Børsting - larstobi
  * chocolateboy
  * Logan Smyth - loganfsmyth
  * Unit 193 / Ukikie
  * Mark Becwar - thebecwar
  * djcj


REMINDER!!!!
============

This is an open source software and everyone who works on it is a
volunteer! Don't be a troll towards the people giving you free
software and hard work!
```

░░░░░▄▄▄▄▀▀▀▀▀▀▀▀▄▄▄▄▄▄░░░░░░░
░░░░░█░░░░▒▒▒▒▒▒▒▒▒▒▒▒░░▀▀▄░░░░
░░░░█░░░▒▒▒▒▒▒░░░░░░░░▒▒▒░░█░░░
░░░█░░░░░░▄██▀▄▄░░░░░▄▄▄░░░░█░░
░▄▀▒▄▄▄▒░█▀▀▀▀▄▄█░░░██▄▄█░░░░█░
█░▒█▒▄░▀▄▄▄▀░░░░░░░░█░░░▒▒▒▒▒░█
█░▒█░█▀▄▄░░░░░█▀░░░░▀▄░░▄▀▀▀▄▒█
░█░▀▄░█▄░█▀▄▄░▀░▀▀░▄▄▀░░░░█░░█░
░░█░░░▀▄▀█▄▄░█▀▀▀▄▄▄▄▀▀█▀██░█░░
░░░█░░░░██░░▀█▄▄▄█▄▄█▄████░█░░░
░░░░█░░░░▀▀▄░█░░░█░█▀██████░█░░
░░░░░▀▄░░░░░▀▀▄▄▄█▄█▄█▄█▄▀░░█░░
░░░░░░░▀▄▄░▒▒▒▒░░░░░░░░░░▒░░░█░
░░░░░░░░░░▀▀▄▄░▒▒▒▒▒▒▒▒▒▒░░░░█░
░░░░░░░░░░░░░░▀▄▄▄▄▄░░░░░░░░█░░
```