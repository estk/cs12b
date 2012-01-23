# Prototype user .cshrc file
#
# $Id: .cshrc,v 1.15 1991/08/21 19:08:30 jik Exp $

# This file sources a system-wide cshrc file, which:
#      - sets up standard environment variables
#      - sources user file ~/.environment, if it exists
#      - sets standard path, OR sources user file ~/.path, if it exists
#      - sets up standard cshell variables, aliases, etc.
#      - source user file ~/.cshrc.mine, if it exists

if (-d /usr/athena/lib/init) then
	set initdir=/usr/athena/lib/init
else
	set initdir=/usr/lib/init
endif

if (-r $initdir/cshrc) then
        source $initdir/cshrc
else
	if ($?prompt) then		# Don't echo if noninteractive
	  echo "Warning: System-wide initialization files not found."
	  echo "C Shell initialization has not been performed."
	  stty dec
	endif
	# set some basic defaults if failed initialization
	umask 077
	set path=( . ~/${hosttype}bin /srvd/patch /usr/athena \
		/bin/athena /usr/bin/X /usr/new /usr/new/mh/bin \
		/usr/ucb /bin /usr/bin /usr/ibm )
endif

set path=($path /afs/cats.ucsc.edu/courses/cmps012b-wm/bin)

# If you want to ADJUST the cshell initialization sequence, create any of 
# the following files (as appropriate) in your home directory, with commands
# to achieve the effect listed:
#
#      .environment - setup session environment (set environmental variables, 
#                     attach lockers, etc.)
#      .path        - set default search path (you can refer to shell
#                     variable $athena_path, which lists athena default path,
#                     when you set path, e.g., "set path=(. $athena_path)")
#      .cshrc.mine  - setup cshell environment (set shell variables, aliases,
#                     unset system defaults, etc.)
                      
# If you want to CHANGE the cshell initialization sequence, revise this .cshrc
# file (the one you're reading now).  You may want to copy the contents of
# the system-wide cshrc file as a starting point.
#
# WARNING: If you revise this .cshrc file, you will not automatically
# get any changes that Project Athena may make to the system-wide file at 
# a later date.  Be sure you know what you are doing.
