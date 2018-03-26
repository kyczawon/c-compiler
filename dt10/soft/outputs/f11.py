
def geo(n):
	acc=0
	t=n
	while (t < n):
		acc=acc + t

	return acc
def main():
	return geo(4) + geo(3) + geo(2)
# Boilerplate
if __name__ == "__main__":
	import sys
	ret=main()
	sys.exit(ret)

