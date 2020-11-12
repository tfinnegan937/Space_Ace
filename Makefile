#  squaresdemo Makefile
#  this is just the standard nusystem makefile

include $(ROOT)/usr/include/make/PRdefs

NUSYSINCDIR  = /usr/include/n64/nusys
NUSYSLIBDIR  = /usr/lib/n64/nusys

LIB = $(ROOT)/usr/lib
LPR = $(LIB)/PR
INC = $(ROOT)/usr/include

LCDEFS =	-DNU_DEBUG -DF3DEX_GBI_2
LCINCS =	-I. -I$(NUSYSINCDIR) -I$(ROOT)/usr/include/PR
LCOPTS =	-G 0
LDIRT  =    $(APP)
LDFLAGS = $(MKDEPOPT) -L$(LIB) -L$(NUSYSLIBDIR) -lnusys_d -lultra_d -L$(N64_LIBGCCDIR) -lgcc -L$(N64_NEWLIBDIR) -lc

OPTIMIZER =	-g

APP =		spaceace.out

TARGETS =	spaceace.n64

HFILES =	graphic.h speaker.h space_texture_test.h projectile.h

CODEFILES   = 	main.c stage00.c graphic.c gfxinit.c debug.c usb.c projectile.c

CODEOBJECTS =	$(CODEFILES:.c=.o)  $(NUSYSLIBDIR)/nusys.o

DATAFILES   =

DATAOBJECTS =	$(DATAFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS)


default:        $(TARGETS)

include $(COMMONRULES)

$(CODESEGMENT):	$(CODEOBJECTS) Makefile
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

$(TARGETS):	$(OBJECTS)
		$(MAKEROM) spec -I$(NUSYSINCDIR) -r $(TARGETS) -s 9 -e $(APP)
		makemask $(TARGETS)


