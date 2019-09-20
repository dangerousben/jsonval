AM_YFLAGS = -d
AM_LFLAGS = -d
jsonval_SOURCES = common.h json_parser.y json_scanner.l main.c

TEST_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) \
                  $(top_srcdir)/build-aux/tap-driver.sh
TESTS = JSONTestSuite.test
EXTRA_DIST = $(TESTS)

bin_PROGRAMS = jsonval
