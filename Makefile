# new makefile

CC = gcc

CFLAGS ?= -Wall -Werror -Wextra -O3

SRCDIR = ./sources/
BUILDDIR = ./build/

DEBUG = -g

CFLAGS += $(DEBUG)

CSRCS = $(SRCDIR)main.c     		\
		$(SRCDIR)lsm/lsm.c  		\
		$(SRCDIR)SLE/SLE.c  		\
		$(SRCDIR)gnuplot/gnuplot.c


SUBS := $(CSRCS)
SUBS := $(subst $(SRCDIR), $(BUILDDIR), $(SUBS))


OBJS = $(SUBS:.c=.o)
DEPS = $(SUBS:.c=.d)



all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o run -lm

$(BUILDDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -c -o $@



$(BUILDDIR)%.d: $(SRCDIR)%.c
	@echo "Colecting deps for $< ..."
	@mkdir -p $(dir $@)
	@$(CC) -E $(CFLAGS) $< -MM -MT $(@:.d=.o) > $@


include $(DEPS)

.PHONY: clean
clean:
	rm -rf $(OBJS) $(DEPS) *.out temps run vgcore.*

.PHONY: clean_data
clean_data:
	rm -rf *.dat *.res /*.ps *.sh /*.png
