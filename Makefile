#makefile for msvc using nmake

!include <Win32.Mak>

OUTDIR = lib
INCDIR = include
SRC = src\*.cpp
OBJFILES = lib\*.obj
TARGET = lib\ARDrone.lib

all: $(OUTDIR) $(OUTDIR)\$(TARGET)

$(OUTDIR):
	if not exitst "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

$(OUTDIR)\*.obj: $(SRC)
	cl.exe $(cflags) $(cvars) /I $(INCDIR) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $(SRC)

$(OUTDIR)\$(TARGET): $(OUTDIR)\*.obj
	lib.exe /MACHINE:IX86 /OUT:$(TARGET)  $(OBJFILES)  $(conlibs)

clean:
	$(CLEANUP)
