# $Id: Makefile,v 1.21 2016/07/03 02:37:47 mchaboll Exp $
# Marcos Chabolla [1437530]
# ID:mchaboll
# Amit Khatri [1398993]

MKFILE      = Makefile
DEPFILE     = ${MKFILE}.dep
NOINCL      = ci clean spotless
NEEDINCL    = ${filter ${NOINCL}, ${MAKECMDGOALS}}
GMAKE       = ${MAKE} --no-print-directory
COMPILECPP  = g++ -std=gnu++14 -g -O0 -Wall -Wextra
MAKEDEPCPP  = g++ -std=gnu++14 -MM

MODULES     = ubigint bigint libfns scanner debug util
CPPHEADER   = ${MODULES:=.h} iterstack.h relops.h
CPPSOURCE   = ${MODULES:=.cpp} main.cpp
EXECBIN     = ydc
OBJECTS     = ${CPPSOURCE:.cpp=.o}
MODULESRC   = ${foreach MOD, ${MODULES}, ${MOD}.h ${MOD}.cpp}
OTHERSRC    = ${filter-out ${MODULESRC}, ${CPPHEADER} ${CPPSOURCE}}
ALLSOURCES  = ${MODULESRC} ${OTHERSRC} ${MKFILE}
LISTING     = Listing.ps

all : ${EXECBIN}

${EXECBIN} : ${OBJECTS}
	${COMPILECPP} -o $@ ${OBJECTS}

%.o : %.cpp
	${COMPILECPP} -c $<

ci : ${ALLSOURCES}
	- checksource ${ALLSOURCES}
	- cpplint.py.perl ${CPPSOURCE}
	ci + ${ALLSOURCES}

lis : ${ALLSOURCES}
	mkpspdf ${LISTING} ${ALLSOURCES} ${DEPFILE}

clean :
	- rm ${OBJECTS} ${DEPFILE} core ${EXECBIN}.errs

spotless : clean
	- rm ${EXECBIN} ${LISTING} ${LISTING:.ps=.pdf}

dep : ${CPPSOURCE} ${CPPHEADER}
	@ echo "# ${DEPFILE} created `LC_TIME=C date`" >${DEPFILE}
	${MAKEDEPCPP} ${CPPSOURCE} >>${DEPFILE}

${DEPFILE} :
	@ touch ${DEPFILE}
	${GMAKE} dep

again :
	${GMAKE} spotless dep ci all lis

ifeq (${NEEDINCL}, )
include ${DEPFILE}
endif

