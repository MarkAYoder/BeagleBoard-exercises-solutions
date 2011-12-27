# ********************************************************************************
#
# makefile
#
# Use:
# - This is the PARENT makefile to makefile_profile.mak. You can specify any
#   profile (i.e. release, debug, all) and it will pass this profile to the child
#   and run gMake with the proper options.
# - Invoke this file with a target called "help" to get more information
#   (i.e. "make help")
#
# ********************************************************************************


# ----------------------------------------------------------------------
# --------------------          Variables          ---------------------
# ----------------------------------------------------------------------

# ---------------------------------------------------------------------
# AT: 
#  - Used for debug purposes, it hides commands for a prettier output 
#    by making use of the @ makefile symbol.
#  - When debugging, you may want to set this to nothing, which means
#    that the $(AT) reference resolves to "" rather than "@", letting
#    the commands be echo'd to the standard output.
#  - This symbol is defined in both this makefile, and the child 
#    makefile (i.e. makefile_profile.mak). Even so, we pass the value
#    in this command onto the child makefile so you don't have to edit
#    it in both places if you want to change it's value.
# ---------------------------------------------------------------------
  AT := @

# ---------------------------------------------------------------------
# MAKE_OPTIONS: 
#  - This variable is used to hold any command-line options that we
#    might want to use for make.
#  - In our case, we have only added the option which forces make to
#    ignore all the implicit (i.e. built-in) rules. In our opinion,
#    it's better to explicitly define each rule to be run.
# ---------------------------------------------------------------------
MAKE_OPTIONS := --no-builtin-rules

# ---------------------------------------------------------------------
# ---------    INSTALL: See description from 'help' below    ----------
# ---------------------------------------------------------------------
# The install rule is described in the Help section below.
# This ifeq statement checks to see if the word 'install' is in the 
# makefile argument list, if so the INSTALL variable is set to the
# word "install", otherwise it's set to null.
ifeq ($(filter install,$(MAKECMDGOALS)),install)
  INSTALL := install
else
  INSTALL := 
endif

# ---------------------------------------------------------------------
# -----------------             Rules            ----------------------
# ---------------------------------------------------------------------

# PHONY indicates that while these are makefile targets, they don't 
# represent an actual filename. PHONY rules are often called 
# 'convenience' rules.
.PHONY  : all debug release clean install help

# If no target is specified, the first target found is built. We have
# chosen the first target to be "all", which will force both "debug" 
# and "release" to be built.
all     : debug release

# If "install" is the only argument passed on the command-line, then 
# this makefile will only build the "debug" profile. We could have had
# it default to "all" or "debug release", but chose "debug" to minimize
# the build time.
ifeq ($(MAKECMDGOALS),install)
  install : debug
	@echo "Install was called without other targets, so only 'debug' was built"
else
  install : 
	@echo 
endif

debug   : 
	@echo ; echo "Building 'debug' profile by calling:  make -f makefile_profile.mak PROFILE=debug" ; echo
	$(AT) make $(MAKE_OPTIONS) -f makefile_profile.mak $(INSTALL) PROFILE=debug | grep -v -F "directory"
	@       echo "Done building 'debug' for $(PWD)"   ; echo

release : 
	@echo ; echo "Building 'release' profile by calling:  make -f makefile_profile.mak PROFILE=release" ; echo
	$(AT) make $(MAKE_OPTIONS) -f makefile_profile.mak $(INSTALL) PROFILE=release | grep -v -F "directory"
	@       echo "Done building 'release'" ; echo

clean   : 
	@echo ; echo "--------- Cleaning up files for $(firstword $(MAKEFILE_LIST)) ---------------------"
	$(AT) make -f makefile_profile.mak clean PROFILE=debug   | grep -v -F make
	$(AT) make -f makefile_profile.mak clean PROFILE=release | grep -v -F make

clean_server :
	@echo ; echo "--------- Cleaning up files for server --------------------------------------------"
	$(AT) cd ../server ; make -f makefile_server.mak clean_server ; echo

build_server :
	@echo ; echo "--------- Building the server -----------------------------------------------------"
	$(AT) 	cd ../server ; make -f makefile_server.mak build_server PROFILE=release ; echo

help	:
	@echo
	@echo "This makefile serves as a 'parent' (or master) makefile. That is, it calls another makefile        "
	@echo "called 'makefile_profile.mak'. If the child makefile is called directly, it will build only        "
	@echo "one profile (by default, it builds the 'debug' profile). This parent makefile allows               "
	@echo "you to easily build for multiple profiles with a single invocation.                                "
	@echo 
	@echo "The goals allowed by this makefile are:  help, all, debug, release, clean, install                 "
	@echo "                                               build_server, clean_server                          "
	@echo 
	@echo "     debug:  calls the child makefile with the "debug" profile                                     "
	@echo "   release:  calls the child makefile with the "release" profile                                   "
	@echo "       all:  calls the child makefile twice, once with "debug", then with "release"                "
	@echo "     clean:  calls the child makefile twice to clean both debug and release                        "
	@echo "   install:  adds the 'install' goal to the child makefile's target, then calls child. By itself,  "
	@echo "             install will only make the 'debug' profile and install it to the EVM                  "
	@echo "   server:   'build_server' and 'clean_server' are provided for labs 12 & 13. They are provided    "
	@echo "             for convenience only, as they will call the same targets from 'makefile_server.mak'   "
	@echo
	@echo
	@echo "One other tip we've used here is to precede each command with $(AT). Then, we set AT=@. In this    "
	@echo "way, we don't usually have to see the actual command syntax -- that is, it makes our output        "
	@echo "look prettier. If, for debug reasons, you want to see the commands printed out, you can just add   " 
	@echo "'AT= ' to the makefile command -- like this:                                                       "
	@echo 
	@echo "              make debug AT=                                                                       "
	@echo
	@echo "Your value for AT then overrides the default, and the commands will be displayed. Of course, you   "
	@echo "can accomplish the same thing by just editing this makefile, setting AT=                           "
	@echo
	@echo "To DUMP additonal makefile variables, use 'DUMP=1' when you run make.                              "
	@echo

