AUTOMAKE_OPTIONS = foreign
SUBDIRS = \
	  src/

install-data-hook:
	mkdir -p $(pkgdatadir)

	cp $(abs_top_srcdir)/marginal-prob-script.py $(pkgdatadir)/marginal-prob-script.py
	cp $(abs_top_srcdir)/c5-marginal-prob-script.py $(pkgdatadir)/c5-marginal-prob-script.py
##	cp $(abs_top_srcdir)/tuffy.jar $(pkgdatadir)/tuffy.jar
##	cp $(abs_top_srcdir)/tuffy.conf $(pkgdatadir)/tuffy.conf
	cp $(abs_top_srcdir)/lpmln2asp.py $(bindir)/lpmln2asp
	cp $(abs_top_srcdir)/lpmln2asp2.py $(bindir)/lpmln2asp2
	cp $(abs_top_srcdir)/lpmln2mln.py $(bindir)/lpmln2mln
	
