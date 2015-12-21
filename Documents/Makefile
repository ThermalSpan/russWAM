TEX = pdflatex -shell-escape -interaction=nonstopmode -file-line-error
BIB = bibtex

.PHONY: all view

all : report.pdf

report.pdf : report.tex report.bbl report.blg
	$(TEX) report.tex

report.bbl report.blg : workscited.bib report.aux
	$(BIB) report

report.aux : report.tex
	$(TEX) report.tex

workscited.bib : report.tex
	$(TEX) report.tex

