all:
	rm -f *.o *.gch
	git add .
	git commit -m "update"
	git push
