#
#	Author: Jacob Rede 830172687
#	Class: CT320
#
import socket
import sys, getopt
import time
import datetime

counter = 0

def main(argv): 
	global counter
	try:                                
		opts, args = getopt.getopt(argv, "a:p:f:", ["host=", "port=", "file="]) 
	except getopt.GetoptError:           
		usage()                          
		sys.exit(2)  
	host = ""
	portSelection = ""
	optFile = ""
	for opt, arg in opts:       
		if opt in ("-a", "--host"):      
			host = arg                
		elif opt in ("-p", "--port"):               
			portSelection = arg                 
		elif opt in ("-f", "--file"): 
			optFile = arg

	if optFile == "":
		remoteServerIP = socket.gethostbyname(host)
		scan_server(remoteServerIP, portSelection)
	else:
		f = open(optFile)
		lines = [line.strip() for line in open(optFile)]
		f.close()
		for address in lines:
			counter = 0
			return_result = scan_server(address, "all")
			if return_result:
				print "%s %s" % (address, counter)
	sys.exit()



def scan_server(address, port):
	global counter
	if port.isdigit():
		sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		result = sock.connect_ex((address, int(port)))
		if result == 0:
			counter+=1
			print "Connected to server {%s} on port {%s}." % (socket.gethostbyaddr(address)[0], port)
			sock.close()
			return True
		sock.close()
		return False
	else:
		
		for port in range(1,1024):  
			sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
			sock.settimeout(0.05)
			result = sock.connect_ex((address, port))
			if result == 0:
				counter+=1
				#print "Connected to server {%s} on port {%s}." % (socket.gethostbyaddr(address)[0], port)
			sock.close()
	if counter > 0:
		return True
	else: 
		return False

if __name__ == "__main__":
	main(sys.argv[1:])