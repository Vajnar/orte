#export QTDIR=/usr/local/qt
QMAKE=qmake

all: default

default:
	$(QMAKE) -o Makefile.qmake ortedemo.pro
	$(MAKE) -f Makefile.qmake

clean:
	rm -f Makefile.qmake
	rm -fr .ui
	rm -fr .moc
	rm -fr .obj
	rm -f ortedemo
