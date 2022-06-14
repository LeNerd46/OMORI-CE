# ----------------------------
# Makefile Options
# ----------------------------

NAME = OMORI
ICON = icon.png
DESCRIPTION = "OMORI for the TI-84 Plus CE"
COMPRESSED = YES
ARCHIVED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
