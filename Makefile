#
# Simple Makefile that compiles all .c and .s files in the same folder
#

# If you move this project you can change the directory 
# to match your GBDK root directory (ex: GBDK_HOME = "C:/GBDK/"
GBDK_HOME = C:/gbdk/

LCC = $(GBDK_HOME)bin/lcc 

# You can uncomment the line below to turn on debug output
# LCC = $(LCC) -debug

# You can set the name of the .gb ROM file here
PROJECTNAME    = Example

BINS	    = $(PROJECTNAME).gb
CSOURCES   := main.c

all:	$(BINS)

compile.bat: Makefile
	@echo "REM Automatically generated from Makefile" > compile.bat
	@make -sn | sed y/\\//\\\\/ | grep -v make >> compile.bat

# Compile and link all source files in a single call to LCC
$(BINS):	$(CSOURCES)
	$(LCC) -Wf-ba0 -c -o  savedata.o savedata.c
	$(LCC) -Wm-yt0x03 -Wl-yo2 -Wl-ya4 -o $@ $(CSOURCES) savedata.o

clean:
	rm -f *.o *.lst *.map *.gb *.ihx *.sym *.cdb *.adb *.asm

