# ***********************************************************************************
#
# makefile_profile.mak
#
#
# Use:
# - Called by parent makefile named "makefile"
# - Can be called directly using gMake's -f option; refer to the syntax used
#   by the "parent" makefile to invoke this make file
# - Currently builds for ARM9 target, however other targets can be supported. 
# - User can specify PROFILE (either debug
#   or release or all) when invoking the parent makefile
# - All dependencies (e.g. header files) are handled by the dependency rule
# - Uses Configuro to consume packages delivered by TI
# - All tools paths are specified in setpaths.mak located two levels above /app
#
# ***********************************************************************************


# *****************************************************************************
#
#    (Early) Include files
#
# *****************************************************************************

# ---------------------------------------------------------------------
# setpaths.mak includes all absolute paths for DaVinci tools
#   and is located two levels above the /app directory.
# ---------------------------------------------------------------------
-include ../../setpaths.mak


# *****************************************************************************
#
#    User-defined vars
#
# *****************************************************************************

# ---------------------------------------------------------------------
# AT: - Used for debug, it hides commands for a prettier output
#     - When debugging, you may want to set this variable to nothing by
#       setting it to "" below, or on the command line
# ---------------------------------------------------------------------
AT := @

# ---------------------------------------------------------------------
# Location and build option flags for gcc build tools
#   - CS_GCC and CS_INSTALL_PATH are defined in setpaths.mak
#   - CC_ROOT is passed to configuro for building with gcc
#   - CC is used to invoke gcc compiler
#   - CFLAGS, LINKER_FLAGS are generic gcc build options
#   - DEBUG/RELEASE FLAGS are profile specific options
# ---------------------------------------------------------------------
CC      := $(CS_GCC)                         # CC is used to invoke gcc compiler
CC_ROOT := $(CS_INSTALL_PATH)                # CC_ROOT is passed to configuro for building with gcc

CFLAGS       := -Wall -fno-strict-aliasing -march=armv5t -D_REENTRANT -I$(CS_INSTALL_PATH)/include -I$(LLIB_INSTALL_DIR)/include -I$(PWD)
LINKER_FLAGS := -lpthread -L$(LLIB_INSTALL_DIR)/lib -lasound 

debug_CFLAGS   := -g -D_debug_ -D_DEBUG_
release_CFLAGS := -O2

# ---------------------------------------------------------------------
# C_SRCS used to build two arrays:
#   - C_OBJS is used as dependencies for executable build rule 
#   - C_DEPS is '-included' below; .d files are build in rule #3 below
#
# Three functions are used to create these arrays
#   - Wildcard
#   - Substitution
#   - Add prefix
# ---------------------------------------------------------------------
C_SRCS := $(wildcard *.c)

OBJS   := $(subst .c,.o,$(C_SRCS))
C_OBJS  = $(addprefix $(PROFILE)/,$(OBJS))

DEPS   := $(subst .c,.d,$(C_SRCS))
C_DEPS  = $(addprefix $(PROFILE)/,$(DEPS))


# ---------------------------------------------------------------------
# Configuro related variables
# ---------------------------
#  - XDCROOT is defined in setpaths.mak
#  - CONFIGURO is where the XDC configuration tool is located
#  - Configuro searches for packages (i.e. smart libraries) along the
#    path specified in XDCPATH; it is exported so that it's available
#    when Configuro runs
#  - Configuro requires that the TARGET and PLATFORM are specified
#  - Here are some additional target/platform choices
#      TARGET   := ti.targets.C64
#      PLATFORM := ti.platforms.evmEM6446, gnu.targets.arm.GCArmv5T
#      TARGET   := gnu.targets.Linux86, ti.platforms.evm3530
#      PLATFORM := host.platforms.PC
# ---------------------------------------------------------------------
XDCROOT        := $(XDC_INSTALL_DIR)
CONFIGURO      := $(XDCROOT)/xs xdc.tools.configuro -b $(PWD)/../../config.bld
LAB_DIR        := $(PWD)/..
export XDCPATH := $(LAB_DIR);$(LAB_DIR)/../myDisplay/packages;$(DMAI_INSTALL_DIR)/packages;$(CE_INSTALL_DIR)/packages;$(CE_INSTALL_DIR)/examples;$(XDAIS_INSTALL_DIR)/packages;$(DSPLINK_INSTALL_DIR);$(CMEM_INSTALL_DIR)/packages;$(BIOS_INSTALL_DIR)/packages;$(BIOSUTILS_INSTALL_DIR)/packages;$(LPM_INSTALL_DIR)/packages;$(FC_INSTALL_DIR)/packages;$(XDCROOT)/packages

TARGET   := gnu.targets.arm.GCArmv5T	
PLATFORM := ti.platforms.evm3530	

# ---------------------------------------------------------------------
# Project related variables
# -------------------------
#   PROGNAME defines the name of the program to be built
#   CONFIG:  - defines the name of the configuration file
#            - the actual config file name would be $(CONFIG).cfg
#            - also defines the name of the folder Configuro outputs to
#   PROFILE: - defines which set of build flags to use (debug or release)
#            - output files are put into a $(PROFILE) subdirectory
#            - set to "debug" by default; override via the command line
#   INSTALL_OSD_IMAGE:  - defines image file being alpha-blended as part
#                         of the OSD thread
#                       - leave blank if OSD is not being used
#   INSTALL_SERVER:     - defines the name of the DSP server being used 
#                         in our program
#                       - in the DM6446 lab exercises, we always used a
#                         server named "server"; in the OMAP3530 labs,
#                         we use two different server names
#                       - leave blank if no server is being used
# ---------------------------------------------------------------------
PROGNAME          := app
CONFIG            := app_cfg
INSTALL_OSD_IMAGE := ../osdfiles/ti_rgb24_640x80.bmp
INSTALL_SERVER    :=

PROFILE  := debug

# -------------------------------------------------
# ----- always keep these intermediate files ------
# -------------------------------------------------
.PRECIOUS : $(C_OBJS)
.PRECIOUS : $(PROFILE)/$(CONFIG)/linker.cmd $(PROFILE)/$(CONFIG)/compiler.opt


# -------------------------------------------------
# --- delete the implicit rules for object files --
# -------------------------------------------------
%.o : %.c


# *****************************************************************************
#
#    Targets and Build Rules
#
# *****************************************************************************


# ---------------------------------------------------------------------
# 1. Build Executable Rule  (.x)
# ------------------------------
#  - For reading convenience, we called this rule #1
#  - The actual ARM executable to be built
#  - Built using the object files compiled from all the C files in 
#    the current directory
#  - linker.cmd is the other dependency, built by Configuro
# ---------------------------------------------------------------------
$(PROGNAME)_$(PROFILE).xv5T : $(C_OBJS) $(PROFILE)/$(CONFIG)/linker.cmd
	@echo; echo "1.  ----- Need to generate executable file: $@ "
	$(AT) $(CC) $(CFLAGS) $(LINKER_FLAGS) $^ -o $@
	@echo "          Successfully created executable : $@ " ; echo


# ---------------------------------------------------------------------
# 2. Object File Rule (.o)
# ------------------------
#  - This was called rule #2
#  - Pattern matching rule builds .o file from it's associated .c file
#  - Since .o file is placed in $(PROFILE) directory, the rule includes
#    a command to make the directory, just in case it doesn't exist
#  - Unlike the TI DSP Compiler, gcc does not accept build options via
#    a file; therefore, the options created by Configuro (in .opt file)
#    must be included into the build command via the shell's 'cat' command
# ---------------------------------------------------------------------
$(PROFILE)/%.o : %.c $(PROFILE)/$(CONFIG)/compiler.opt 
	@echo "2.  ----- Need to generate:      $@ (due to: $(wordlist 1,1,$?) ...)"
	$(AT) mkdir -p $(dir $@)
	$(AT) $(CC) $(CFLAGS) $($(PROFILE)_CFLAGS) $(shell cat $(PROFILE)/$(CONFIG)/compiler.opt) -c $< -o $@
	@echo "          Successfully created:  $@ "


# ---------------------------------------------------------------------
# 3. Dependency Rule (.d)
# -----------------------
#  - Called rule #3 since it runs between rules 2 and 4
#  - Created by the gcc compiler when using the -MM option
#  - Lists all files that the .c file depends upon; most often, these
#    are the header files #included into the .c file
#  - Once again, we make the subdirectory it will be written to, just
#    in case it doesn't already exist
#  - For ease of use, the output of the -MM option is piped into the
#    .d file, then formatted, and finally included (along with all
#    the .d files) into this make script
#  - We put the formatting commands into a make file macro, which is
#    found towards the end of this file
# ---------------------------------------------------------------------
$(PROFILE)/%.d : %.c $(PROFILE)/$(CONFIG)/compiler.opt
	@echo "3.  ----- Need to generate dep info for:        $< "
	@echo "          Generating dependency file   :        $@ "
	$(AT) mkdir -p $(PROFILE)
	$(AT) $(CC) -MM $(CFLAGS) $($(PROFILE)_CFLAGS) $(shell cat $(PROFILE)/$(CONFIG)/compiler.opt) $<   > $@

	@echo "          Formatting dependency file:           $@ "
	$(AT) $(call format_d ,$@,$(PROFILE)/)
	@echo "          Dependency file successfully created: $@ " ; echo


# ---------------------------------------------------------------------
# 4. Configuro Rule (.cfg)
# ------------------------
#  - The TI configuro tool can read (i.e. consume) RTSC packages
#  - Many TI and 3rd Party libraries are packaged as Real Time Software
#    Components (RTSC) - which includes metadata along with the library
#  - To improve readability of this scripts feedback, the Configuro's
#    feedback is piped into a a results log file
#  - In the case where no .cfg file exists, this script makes an empty
#    one using the shell's 'touch' command; in the case where this
#    occurs, gMake will delete the file when the build is complete as 
#    is the case for all intermediate build files (note, we used the
#    precious command earlier to keep certain intermediate files from
#    being removed - this allows us to review them after the build)
# ---------------------------------------------------------------------
$(PROFILE)/%/linker.cmd $(PROFILE)/%/compiler.opt : %.cfg $(INSTALL_SERVER)
	@echo "4.  ----- Starting Configuro for $^  (note, this may take a minute)"
     ifdef DUMP
	$(AT) $(CONFIGURO) -c $(CC_ROOT) -t $(TARGET) -p $(PLATFORM) -r $(PROFILE) -o $(PROFILE)/$(CONFIG) $<
     else
	$(AT) mkdir -p $(PROFILE)/$(CONFIG)
	$(AT) $(CONFIGURO) -c $(CC_ROOT) -t $(TARGET) -p $(PLATFORM) -r $(PROFILE) -o $(PROFILE)/$(CONFIG) $< \
                > $(PROFILE)/$(CONFIG)_results.log
     endif
	@echo "          Configuro has completed; it's results are in $(CONFIG) " ; echo

# ---------------------------------------------------------------------
# The "no" .cfg rule
# ------------------
#  - This additional rule creates an empty config file if one doesn't 
#    already exist
#  - See the Configuro rule comments above for more details
# ---------------------------------------------------------------------
%.cfg :
	$(AT) touch $(CONFIG).cfg


# *****************************************************************************
#
#    Convenience Rules
#
# *****************************************************************************

# ---------------------------------------------------------------------
#  "all" Rule
# -----------
#  - Provided in case the a user calls the commonly found "all" target
#  - Called a Phony rule since the target (i.e. "all") doesn't exist
#    and shouldn't be searched for by gMake
# ---------------------------------------------------------------------
.PHONY  : all 
all : $(PROGNAME)_$(PROFILE).xv5T
	@echo ; echo "The target ($<) has been built." 
	@echo


# ---------------------------------------------------------------------
#  "clean" Rule
# -------------
#  - Cleans all files associated with the $(PROFILE) specified above or
#    via the command line
#  - Cleans the associated files in the containing folder, as well as
#    the ARM executable files copied by the "install" rule
#  - EXEC_DIR is specified in the included 'setpaths.mak' file
#  - Called a Phony rule since the target (i.e. "clean") doesn't exist
#    and shouldn't be searched for by gMake
# ---------------------------------------------------------------------
.PHONY : clean
clean  : 
	@echo ; echo "--------- Cleaning up files for $(PROFILE) -----"
	rm -rf $(PROFILE)
	rm -rf $(PROGNAME)_$(PROFILE).xv5T
	rm -rf $(EXEC_DIR)/$(PROGNAME)_$(PROFILE).xv5T 
	rm -rf $(C_DEPS)
	rm -rf $(C_OBJS)
	@echo


# ---------------------------------------------------------------------
#  "install" Rule
# ---------------
#  - The install target is a common name for the rule used to copy the
#    executable file from the build directory, to the location it is 
#    to be executed from
#  - Once again, a phony rule since we don't have an actual target file
#    named 'install' -- so, we don't want gMake searching for one
#  - This rule depends upon the ARM executable file (what we need to 
#    copy), therefore, it is the rule's dependency
#  - We make the execute directory just in case it doesn't already
#    exist (otherwise we might get an error)
#  - EXEC_DIR is specified in the included 'setpaths.mak' file; in our
#    target system (i.e. the DVEVM board), we will use /opt/workshop as 
#    the directory we'll run our programs from
# ---------------------------------------------------------------------
.PHONY  : install 
install : $(PROGNAME)_$(PROFILE).xv5T $(INSTALL_OSD_IMAGE) $(INSTALL_SERVER)
	@echo
	@echo  "0.  ----- Installing $< to 'Execution Directory' -----"
	@echo  "          Execution Directory:  $(EXEC_DIR)"
	$(AT) mkdir -p $(EXEC_DIR)
	$(AT) cp    $^ $(EXEC_DIR)
	@echo  "          Install (i.e. copy) has completed" ; echo


# *****************************************************************************
#
#    Macros
#
# *****************************************************************************
# format_d 
# --------
#  - This macro is called by the Dependency (.d) file rule (rule #3)
#  - The macro copies the dependency information into a temp file,
#    then reformats the data via SED commands
#  - Two variations of the rule are provided
#     (a) If DUMP was specified on the command line (and thus exists), 
#         then a warning command is embed into the top of the .d file;
#         this warning just lets us know when/if this .d file is read
#     (b) If DUMP doesn't exist, then we build the .d file without
#         the extra make file debug information
# ---------------------------------------------------------------------
ifdef DUMP
  define format_d
   @# echo " Formatting dependency file: $@ "
   @# echo " This macro has two parameters: "
   @# echo "   Dependency File (.d): $1     "
   @# echo "   Profile: $2                  "
   @mv -f $1 $1.tmp
   @echo '$$(warning --- Reading from included file: $1 ---)' > $1
   @sed -e 's|.*:|$2$*.o:|' < $1.tmp >> $1
   @rm -f $1.tmp
  endef
else
  define format_d
   @# echo " Formatting dependency file: $@ "
   @# echo " This macro has two parameters: "
   @# echo "   Dependency File (.d): $1     "
   @# echo "   Profile: $2                  "
   @mv -f $1 $1.tmp
   @sed -e 's|.*:|$2$*.o:|' < $1.tmp > $1
   @rm -f $1.tmp
  endef
endif


# *****************************************************************************
#
#    (Late) Include files
#
# *****************************************************************************
#  Include dependency files
# -------------------------
#  - Only include the dependency (.d) files if "clean" is not specified
#    as a target -- this avoids an unnecessary warning from gMake
#  - C_DEPS, which was created near the top of this script, includes a
#    .d file for every .c file in the project folder
#  - With C_DEPS being defined recursively via the "=" operator, this
#    command iterates over the entire array of .d files
# ---------------------------------------------------------------------
ifneq ($(filter clean,$(MAKECMDGOALS)),clean)
  -include $(C_DEPS)
endif


# *****************************************************************************
#
#    Additional Debug Information
#
# *****************************************************************************
#  Prints out build & variable definitions
# ----------------------------------------
#  - While not exhaustive, these commands print out a number of
#    variables created by gMake, or within this script
#  - Can be useful information when debugging script errors
#  - As described in the 2nd warning below, set DUMP=1 on the command
#    line to have this debug info printed out for you
#  - The $(warning ) gMake function is used for this rule; this allows
#    almost anything to be printed out - in our case, variables
# ---------------------------------------------------------------------

ifdef DUMP
  $(warning To view build commands, invoke make with argument 'AT= ')
  $(warning To view build variables, invoke make with 'DUMP=1')

  $(warning Source Files: $(C_SRCS))
  $(warning Object Files: $(C_OBJS))
  $(warning Depend Files: $(C_DEPS))

  $(warning Base program name : $(PROGNAME))
  $(warning Configuration file: $(CONFIG))
  $(warning Make Goals        : $(MAKECMDGOALS))

  $(warning Xdcpath :  $(XDCPATH))
  $(warning Target  :  $(TARGET))
  $(warning Platform:  $(PLATFORM))
endif


