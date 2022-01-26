import os
import argparse
import shutil
from string import ascii_lowercase
from string import ascii_uppercase

def main():
	# clean up old files
	for ch in ascii_lowercase:
		if os.path.isdir(ch):
			print("Removing old directory {}".format(ch))
			shutil.rmtree(ch)

	parser = argparse.ArgumentParser()
	parser.add_argument("First", help="Name of first problem (Ex. A)")
	parser.add_argument("Last", help="Name of last problem (Ex. F)")
	args = parser.parse_args()
	first = args.First
	last = args.Last
		
	if (first not in ascii_lowercase and first not in ascii_uppercase) or len(first) != 1:
		print("{} is not an english letter, try again.".format(first))
		return
	first = first.lower()
	
	if (last not in ascii_lowercase and last not in ascii_uppercase) or len(last) != 1:
		print("{} is not an english letter, try again.".format(last))
		return
	last = last.lower()

	if ord(first) > ord(last):
		print("Need First <= Last, try again.")
		return
	
	def process_dir(ch):
		print("Creating new directory {}".format(ch))
		
		os.mkdir(ch)
		# copy template files
		shutil.copyfile("template.cpp", "{}/{}.cpp".format(ch, ch))
		shutil.copyfile("template.cpp", "{}/template.cpp".format(ch))
		shutil.copyfile("template.cpp", "{}/brute.cpp".format(ch))
		shutil.copyfile("gen.cpp", "{}/gen.cpp".format(ch))
		shutil.copyfile("testlib.h", "{}/testlib.h".format(ch))
		
		# template brute force checker script
		shutil.copyfile("s_template.sh", "{}/s.sh".format(ch))
		s = open("{}/s.sh".format(ch), 'r')
		content = s.read()
		content = content.replace('@', ch)
		s.close()
		s = open("{}/s.sh".format(ch), 'w')
		s.write(content)
		s.close()

		# templated Makefile, a bit hacky rn
		shutil.copyfile("MakefileTemplate", "{}/Makefile".format(ch))
		makefile = open("{}/Makefile".format(ch), "r")
		content = makefile.read()
		content = content.replace("@", ch)
		content = content.replace("&", ch.upper())
		makefile.close()
		makefile = open("{}/Makefile".format(ch), "w")
		makefile.write(content)
		makefile.close()

	for ch in ascii_lowercase:
		if ord(first) <= ord(ch) <= ord(last):
			process_dir(ch)

if __name__ == '__main__':
	main()
