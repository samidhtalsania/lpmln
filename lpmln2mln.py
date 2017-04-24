#!/usr/bin/python

import argparse
import sys
import os
from math import exp
from subprocess import Popen, PIPE
import ipdb


def print_error(error, dest):
	if error is not None:
		if dest is not None:
			print_output(error, dest)
		else:
			print >> sys.stderr, "*** Error \n"
			print >> sys.stderr, error
	
			

def main():
	parser = argparse.ArgumentParser(description='LPMLN2MLN')
	parser.add_argument('-i', help='input file. [REQUIRED]', nargs=1)
	parser.add_argument('-e', help='evidence file', nargs=1)
	parser.add_argument('-r', help='output file. [REQUIRED]',  nargs=1)
	parser.add_argument('-q', help='query predicate.', nargs=1)
	parser.add_argument('-a', help='[DEFAULT] Compile for Alchemy', action="store_true", default=False)
	parser.add_argument('-t', help='Compile for Tuffy', action="store_true", default=False)
	parser.add_argument('-ro', help='Compile for rockit', action="store_true", default=False)
	parser.add_argument('-extra', help='Extra options for the respective solvers. Passed as it is.', nargs='*')
	


	args = parser.parse_args()

	arglist = []
	target = False
	arglist.append('lpmlncompiler')
	arglist.append('-p')



	if args.a is True and target is False:
		arglist.append('-M')
		target = True

	if args.t is True and target is False:
		arglist.append('-T')
		target = True

	if args.r is True and target is False:
		arglist.append('-R')
		target = True

	if target is False:
		arglist.append('-M')
		args.a = True

	if args.i is None or not os.path.isfile(args.i[0]):
		print_error("Check input file.", None)
		parser.print_help()
		sys.exit(0)
	else:
		arglist.append(args.i[0])


	fn = "input-compiled-lpmln.mln"

	# ipdb.set_trace()

	process = Popen(arglist, stdout=PIPE)
	(output, err) = process.communicate()
	exit_code = process.wait()
	if err is not None and err.strip() is not None:
		print_error(err, None)
		sys.exit(0)

	
	print_output(output, [fn])
	temp = " ".join(x for x in arglist)
	print '[LOG] LPMLN executed with: \n'+ temp + ' > ' + fn
	inferarglist = []
	inferarglist.append('infer')

	if args.a is True:
		inferarglist.append('-i')
		inferarglist.append(fn)

		if args.e is not None:
			inferarglist.append('-e')
			inferarglist.append(args.e[0])
		else:
			open('empty.db', 'w').close()
			inferarglist.append('-e')
			inferarglist.append('empty.db')
			

		if args.r is not None:
			inferarglist.append('-r')
			inferarglist.append(args.r[0])
		else:
			print_error("Output file required.", None)
			sys.exit(0)

		if args.q is not None:
			inferarglist.append('-q')
			inferarglist.append(args.q[0])
		else:
			print_error("Query required.", None)
			sys.exit(0)



		if args.extra is not None:
			inferarglist.append(args.extra[0])

		temp = " ".join(x for x in inferarglist)
		print '[LOG] Alchemy executed with: \n'+ temp 



		process = Popen(temp, shell=True)
		(output, err) = process.communicate()
		exit_code = process.wait()
		if err is not None and err.strip() is not None:
			print_error(err, None)
			sys.exit(0)

		# with open(args.r[0], 'r') as fin:
		# 	print fin.read()


	tuffyarglist = []
	tuffyarglist.append('java -jar tuffy.jar')
	
	if args.t is True:
		tuffyarglist.append('-i')
		tuffyarglist.append(os.path.abspath("input.mln"))

		if args.e is not None:
			tuffyarglist.append('-e')
			tuffyarglist.append(os.path.abspath(args.e[0]))

		if args.r is not None:
			tuffyarglist.append('-r')
			tuffyarglist.append(args.r[0])
		else:
			print_error("Output file required", None)

		if args.q is not None:
			tuffyarglist.append('-q')
			tuffyarglist.append(args.q[0])
		else:
			print_error("Query required.", None)
			sys.exit(0)

		if args.extra is not None:
			tuffyarglist.append(args.extra[0])

		print "Execute the following line in the location of tuffy jar file:\n"
		print " ".join(x for x in tuffyarglist)







	



	
		

def print_output(output, dest):
	if dest is not None:
		with open(dest[0], "w") as outputFile:
				outputFile.write(output)
	else:
		print output

if __name__ == "__main__":
    main()
