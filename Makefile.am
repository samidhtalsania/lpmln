AUTOMAKE_OPTIONS = foreign
SUBDIRS = \
	  src/

install-data-hook:
	mkdir -p $(pkgdatadir)

	cp $(abs_top_srcdir)/prob-script.py $(pkgdatadir)/prob-script.py
	cp $(abs_top_srcdir)/marginal-prob-script.py $(pkgdatadir)/marginal-prob-script.py
	