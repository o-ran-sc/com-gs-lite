import os
import time

while True:
	while os.path.isfile("exampleCsv"):
		time.sleep(1)
	os.system("cp example.data exampleCsvX ; mv exampleCsvX exampleCsv")
	time.sleep(1)
	
