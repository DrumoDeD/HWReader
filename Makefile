TARGET = hwreader
CC = gcc
CFLAGS = -Wall -Wextra -O2
LIBS = -lpci

RM=/usr/bin/rm
MKDIR=/usr/bin/mkdir
CP=/usr/bin/cp
CHMOD=/usr/bin/chmod

BINDIR=/usr/bin
DATADIR=/usr/share
LIBEXECDIR=/usr/libexec
SYSCONFDIR=/etc

DESTDIR ?=
DATA=data
SRCS = $(wildcard src/*.c)
all: $(TARGET)
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LIBS)

clean:
	$(RM) -f $(TARGET)

install:
	$(MKDIR) -p $(DESTDIR)$(LIBEXECDIR)
	$(MKDIR) -p $(DESTDIR)$(BINDIR)
	$(MKDIR) -p $(DESTDIR)$(SYSCONFDIR)/hwreader
	$(MKDIR) -p $(DESTDIR)$(DATADIR)/polkit-1/actions
	$(CP) $(TARGET) $(DESTDIR)$(LIBEXECDIR)
	$(CP) $(DATA)/HWReader $(DESTDIR)$(BINDIR)
	$(CHMOD) 755 $(DESTDIR)$(BINDIR)/HWReader
	$(CP) $(DATA)/path.conf $(DESTDIR)$(SYSCONFDIR)/hwreader/
	$(CP) $(DATA)/org.freedesktop.policykit.hwreader.policy $(DESTDIR)$(DATADIR)/polkit-1/actions/