a = "11010101"
for i in a:
	if(i == "1"):
		print("00000001", end="")
	else:
		print("00000000", end="")