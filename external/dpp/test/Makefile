BIN	 = dsp_test
CC	 = ../../../prebuilts/toolschain/usr/bin/arm-linux-gcc
CPP	 = ../../../prebuilts/toolschain/usr/bin/arm-linux-g++
INCS	 = -I./../../../out/system/include/
LIBS	 = -L./../../../out/system/lib -lion
CSRCS	 = $(wildcard ./*.c)

define all-cpp-files-under
$(shell find $(1) -name "*."$(2) -and -not -name ".*" )
endef

define all-subdir-cpp-files  
$(call all-cpp-files-under,.,"cc")
endef

CPPSRCS	 = $(call all-subdir-cpp-files)
COBJS	:= $(CSRCS:.c=.o)
CPPOBJS	:= $(CPPSRCS:.cc=.o)

DEBUGFLAGS = -funwind-tables -g -rdynamic -O0 -DDEBUG
OPTIMIZEFLAGS = -O2
CFLAGS	 =
CPPFLAGS = -DSUPPORT_ION -std=c++11 -DLINUX  -DENABLE_ASSERT

CFLAGS += $(DEBUGFLAGS)
CPPFLAGS += $(DEBUGFLAGS)
#CFLAGS += $(OPTIMIZEFLAGS)
#CPPFLAGS += $(OPTIMIZEFLAGS)

all : $(BIN)

$(COBJS) : %.o : %.c
	@$(CC) -c $< -o $@ $(INCS) $(CFLAGS) $(LIBS)
$(CPPOBJS) : %.o : %.cc
	@$(CPP) -c $< -o $@ $(INCS) $(CPPFLAGS) $(LIBS)

$(BIN) : $(COBJS) $(CPPOBJS)
	@$(CPP) -o $(BIN) $(COBJS) $(CPPOBJS) $(LIBS)
	@-rm $(COBJS) $(CPPOBJS) 
	@echo "dsp test bin build success!"


clean:
	@rm -f $(BIN) $(COBJS) $(CPPOBJS)
	@echo "dsp test bin clean success!"
