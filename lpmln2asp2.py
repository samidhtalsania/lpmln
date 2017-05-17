#!/usr/bin/python

import argparse
import sys
import os
from math import exp
from subprocess import Popen, PIPE
# import ipdb

def print_error(error, dest):
	if error is not None:
		if dest is not None:
			print_output(error, dest)
		else:
			print >> sys.stderr, "*** Error \n"
			print >> sys.stderr, error
	

def processOutput(output, mf):
	val = 0
	for line in output.split("\n"):
		if "Optimization:" in line:
			val = val + exp(-1*(int(line.split()[-1])/1000.0))
	return val
			

def main():
	parser = argparse.ArgumentParser(description='LPMLN2ASP')
	parser.add_argument('-i', help='input file. [REQUIRED]', nargs=1)
	parser.add_argument('-e', help='evidence file', nargs=1)
	parser.add_argument('-r', help='output file. If not provided output would be to STDOUT', nargs=1)
	parser.add_argument('-q', help='query predicate.', nargs=1)
	parser.add_argument('-clingo', help='clingo options passed as it is to the solver. Pass all clingo options in \'single quotes\'', nargs=1)
	parser.add_argument('-hr', help='[FALSE] Translate hard rules', action="store_true", default=False)
	#parser.add_argument('-prob', help='[MAP] Use this option to activate marginal inference. Using -e defaults to MAP', action="store_true", default=False)
	parser.add_argument('-all',help='Display probability of all stable models.', action="store_true", default=False)
	parser.add_argument('-mf', help='[1000] Multiplying factor for weak constraints value', nargs=1)
	parser.add_argument('-d', help='[FALSE] Debug. Print all debug information', action="store_true", default=False)


	mf = 1000

	args = parser.parse_args()
	# ipdb.set_trace()
	arglist = []
	arglist.append('lpmln2cl')
	

	if args.i is None or not os.path.isfile(args.i[0]):
		print_error("Check input file.", None)
		parser.print_help()
		sys.exit(0)
	else:
		arglist.append(args.i[0])

	if args.mf is not None:
		arglist.append('--mf='+args.mf[0])
		mf = int (args.mf[0])
	else:
		arglist.append('--mf=1000')

	if args.all is False and args.q is not None:
		arglist.append('-c quiet=true')
		arglist.append('--quiet')

	if args.all is True:
		arglist.append('--infer-type=query')

	# if args.prob is True:
	# 	arglist.append('--infer-type=query')
		
	if args.q is not None:
		arglist.append('-c q='+args.q[0].replace(',','__LP__'))
		arglist.append('--infer-type=query')

	if args.hr is True:
		arglist.append('--tr-hr=true')

	if args.clingo is not None:
		arglist.append(args.clingo[0].strip("'"))

	if args.e is not None and os.path.isfile(args.e[0]):
		arglist.append(args.e[0])

	arglist.append('--c5=true')

	process = Popen(arglist, stdout=PIPE)
	(output, err) = process.communicate()
	exit_code = process.wait()
	print_error(err, args.r)
	print_output(output, args.r)
		

def print_output(output, dest):
	if dest is not None:
		with open(dest[0], "w") as outputFile:
				outputFile.write(output)
	else:
		print output

if __name__ == "__main__":
    main()
