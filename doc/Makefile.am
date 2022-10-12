SUBDIRS = html

man3dir = $(DESTDIR)$(mandir)/man3
apidir = $(DESTDIR)$(datadir)/doc/@PACKAGE@-@PACKAGE_VERSION@/api

EXTRA_DIST = \
	mainPage.txt

.PHONY: dox pdf

all-local: dox #pdf

dox: html html/api/index.html
html/api/index.html: Doxyfile
	@DOXYGEN@

pdf: @PACKAGE_TARNAME@.pdf
@PACKAGE@.pdf:
	$(MAKE) -C ./latex pdf
	ln -s ./latex/refman.ps	 @PACKAGE_TARNAME@.ps
	ln -s ./latex/refman.pdf @PACKAGE_TARNAME@.pdf


install-data-local:
	$(mkinstalldirs) $(man3dir)
	@for i in ./man/man3/log4shib.3 ./man/man3/log4shib_*.3; do \
		inst=`basename $$i | sed 's/_/::/g'`; \
		echo "$(INSTALL_DATA) $$i $(man3dir)/$$inst"; \
		$(INSTALL_DATA) $$i $(man3dir)/$$inst; \
	done
	$(mkinstalldirs) $(apidir)
	cp -r html $(apidir)
	$(RM) -r -f $(apidir)/html/.svn $(apidir)/html/Makefile*

uninstall-local:
	$(RM) $(man3dir)/log4shib.3
	$(RM) $(man3dir)/log4shib::*.3
	$(RM) -r -f $(apidir)

clean-local:
	$(RM) -r latex
	$(RM) -r html/api man @PACKAGE_TARNAME@.ps @PACKAGE_TARNAME@.pdf
