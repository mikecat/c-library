CC=gcc
CFLAGS=-Wall -Wextra -O2
CXX=g++
CXXFLAGS=-Wall -Wextra -O2
LDFLAGS=

TARGET=libclibrary.a

OBJS=my_stdio.o

TESTOBJS=test_main.o \
	my_stdio_test.o

SRCDIR=src
INCLUDEDIR=include
TESTSRCDIR=test

OBJDIR=obj
TESTBINDIR=testbin

$(TARGET): $(addprefix $(OBJDIR)/,$(OBJS))
	ar -cr $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c .$(OBJDIR)_exists
	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDEDIR)

.$(OBJDIR)_exists:
	mkdir -p $(OBJDIR)
	touch .$(OBJDIR)_exists

.PHONY: test
test: $(TESTBINDIR)/test
	$(TESTBINDIR)/test

$(TESTBINDIR)/test: $(TARGET) $(addprefix $(TESTBINDIR)/,$(TESTOBJS))
	$(CXX) $(LDFLAGS) -o $@ $^ -L . -lcppunit -lclibrary
	touch $@

$(TESTBINDIR)/%.o: $(TESTSRCDIR)/%.cpp .$(TESTBINDIR)_exists
	$(CXX) $(CXXFLAGS) -c -o $@ $< -I $(INCLUDEDIR)

.$(TESTBINDIR)_exists:
	mkdir -p $(TESTBINDIR)
	touch .$(TESTBINDIR)_exists

.PHONY: clean
clean:
	rm -rf $(TARGET) $(OBJDIR) $(TESTBINDIR) .$(OBJDIR)_exists .$(TESTBINDIR)_exists
