import os
import time

while True:
	while os.path.isfile("exampleGdat"):
		time.sleep(1)
	os.system("cp example.gdat exampleGdatX ; mv exampleGdatX exampleGdat")
	time.sleep(1)
	
