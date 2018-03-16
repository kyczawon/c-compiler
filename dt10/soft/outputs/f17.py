
def main():
	x=0
	y=0
	acc=2
	x=0
	y=0
	while (x < 6):
		y=0
		while (y != x):
			acc=acc + y
			y=y + 1

		x=x + 2

	return acc - x - y
# Boilerplate
if __name__ == "__main__":
	import sys
	ret=main()
	sys.exit(ret)

