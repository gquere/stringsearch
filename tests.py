from ctypes import cdll
import time
import sys


def do_simple_test(runs, fct):
	i = 0

	tic = time.clock()
	while i < runs:
		a = fct("stupid_spring_concerning_string", "string")
		i+=1
	assert a==25
	return time.clock() - tic

def do_medium_test(runs, fct):
	i = 0
	with open("./tests/medium_text.txt", "r") as file:
		data = file.read().replace('\n', '')

	tic = time.clock()
	while i < runs:
		a = fct(data, "blob")
		i+=1

	assert a==291
	return time.clock() - tic

def do_huge_test(runs, fct):
	i = 0
	with open("./tests/huge_text.txt", "r") as file:
		data = file.read().replace('\n', '')

	tic = time.clock()
	while i < runs:
		a = fct(data, "string")
		i+=1

	assert a==11120
	return time.clock() - tic

def do_adn(runs, fct):
	i = 0
	with open("./tests/adn_text.txt", "r") as file:
		data = file.read().replace('\n', '')

	with open("./tests/adn_pattern.txt", "r") as file:
		pattern = file.read().replace('\n', '')

	tic = time.clock()
	while i < runs:
		a = fct(data, pattern)
		i+=1

	assert a==775286
	return time.clock() - tic



# Bruteforce
libbf = cdll.LoadLibrary('./bruteforce/libbf.so')
bf = libbf.bf
# strstr from libc
libstrstr = cdll.LoadLibrary('./strstr/libstrstr.so')
strstr = libstrstr.strstr2
# Raita
libraita = cdll.LoadLibrary('./raita/libraita.so')
raita = libraita.raita
# BMH
libbmh = cdll.LoadLibrary('./boyer-moore-horspool/libbmh.so')
bmh = libbmh.bmh
# BM
libbm = cdll.LoadLibrary('./boyer-moore/libbm.so')
bm = libbm.bm
# KMP
libkmp = cdll.LoadLibrary('./knuth-morris-pratt/libkmp.so')
kmp = libkmp.kmp
# Shift-Or
libso = cdll.LoadLibrary('./shift-or/libso.so')
so = libso.shiftor
# Python fast search
libpfs = cdll.LoadLibrary('./python_fastsearch/libpfs.so')
pfs = libpfs.pfs
# Quick Search
libqs = cdll.LoadLibrary('./quick_search/libqs.so')
qs = libqs.qs
# Z algorithm
libza = cdll.LoadLibrary('./z_alg/libza.so')
za = libza.za

# RK
librk = cdll.LoadLibrary('./rabin-karp/librk.so')
rk = librk.rabin_karp
# Aho-Corasick
libac = cdll.LoadLibrary('./aho-corasick/libac.so')
ac = libac.ac

# tests to run
fcts = [bf, strstr, raita, bmh, bm, kmp, so, pfs, qs, za, rk]
tests = [do_simple_test, do_medium_test, do_huge_test, do_adn]
reps = [1000000, 1000000, 100000, 1000]
testname = ["SIMPLE", "MEDIUM", "HUGE", "ADN"]


# do tests and print results
print("\t"),
for fct in fcts:
	print(str(fct.__name__) + '\t'),
i = 0
for test in tests:
	print("")
	print(testname[i] + "\t"),
	for fct in fcts:
		tot = test(reps[i], fct)
		print("%.2f" % tot + "\t"),
		sys.stdout.flush()
	i+=1
print("")

