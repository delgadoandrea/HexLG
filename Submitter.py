import os, sys

directory = 'Jobs/'

r = range(-10,11)
#r = range(-5,6)
#jobCounter = 0

for x in r:
	for y in r:
		print(x,y)
		filename=directory+"photon"+str(x)+"_"+str(y)+".mac"
		file = open(filename, "w")
		file.write("/run/initialize\n")
		file.write("/gun/particle opticalphoton\n")
		file.write("/HexLG/gun/optPhotonPolar\n")
		xpos = "/HexLG/detector/gunPosX "+str(x)
		file.write(xpos+"\n")		
		ypos = "/HexLG/detector/gunPosY "+str(y)
		file.write(ypos+"\n")
		file.write("/run/beamOn 10000\n")
		file.close()
		os.system("./HexLG "+filename)
		outfile = directory+"HexLG_"+str(x)+"_"+str(y)+".root"
		os.system("mv HexLG.root "+outfile)				
