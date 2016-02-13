# Script created by Group 14 in the team
from serial import * 
import argparse

PORT_BLUE = '/dev/tty.usbmodem1421'
PORT_RED = '/dev/tty.usbserial-DA00SY6T'

# Parse the inputs
ap = argparse.ArgumentParser()
ap.add_argument("-r", "--room",
	help="which room(s) we are commanding", default="both")
ap.add_argument("-t", "--temp",
	help="temperature for the AC unit", default = 21)
args = vars(ap.parse_args())

target = args["room"]
temp = args["temp"]

if (target == "red"):
	ard_red = Serial(PORT_RED, 9600)
	ard_red.write(temp)
elif (target == "blue"):
	ard_blue = Serial(PORT_BLUE, 9600)
	ard_blue.write(temp)
else: # Both boards
	ard_blue = Serial(PORT_BLUE, 9600)
	ard_red = Serial(PORT_RED, 9600)

	ard_blue.write(temp)
	ard_red.write(temp)