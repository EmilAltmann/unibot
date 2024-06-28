# Assembly notes:

After 3D printing the two halves of the chassis can be glued together.
For increased stiffness for plastic shims can be added, inside the motor bays, as seen in all my pictures.

The 3D print needs fitting of threaded inserts in all 4mm holes (every hole you can find except the four holes for the battery contacts).
The threaded inserts are m3 with an outer dimension of 4mm by 6mm.

## Power supplies:

The next step is fitting of the power supplies.
For that you need to produce the two battery contacts (as seen in the battery_contact_drawing.pdf).
The fixation of the power cables need to be done with a washer followed by the ring terminal, another washer and a self locking nut.
The best way to insure alignment of the battery contacts is by loosely tighten the back screw and firmly tighten the front one.
Then check if the contacts can be tilted around the front screw.
With that you can align the contacts by sliding the battery pack in.
After removal of the battery pack you can tighten the screws fully.

The battery positive should be routed trow the red switch via a red cable.
from the red switch three red cables should be routed to the two lm2596 dc regulators.
Furthermore the third cable should be routed to the black switch.

The output from the black switch (+VBat) should be routed via a blue or purple cable to the distribution board.

The output from one of the regulators should be set to +5V and be routed via a red or white cable to the distribution board.

The output from the other regulator should be set to +3.3V and be routed via a yellow or gray cable to the distribution board.

Lastly the ground should be routed from the negative battery connection via a black cable to both dc regulators and (optionally throw the output of one) to the distribution board.

## All the connections:

The cable harness of the chassis consist out of 5 pieces.
There are two identical motor bay harnesses, one controller power connection, one controller data connection and the bay to interposer harness.
(see cable_harness.jpg)

The pinout and cable color of all db9 connectors should be:

	pin1 - data1 (blue)
	pin2 - data2 (green)
	pin3 - data3 (yellow)
	pin4 - data4 (orange)
	pin5 - data5 (red)

	pin6 - VBat (purple)
	pin7 - +3.3V (gray)
	pin8 - +5V (white)
	pin9 - GND (black)

- The controller power connection
	a 100mm cable for power (and no data)

- The motor bay harnesses
	a 9x5 hole PCB with a male 9 pin DuPont connector. The PCB is directly
	connected to one of the db9 connectors. The other two are paralleled
	via a 130mm cable pair to the PCB.

- The controller data harness
	two db25 connectors connected via 100mm cables.
	Wired as pin1 to pin1 ... pin 25 to pin25.

- The bay to interposer harness
	the interposer has a db37 connector with the following pinout:
	
	TopFront 120mm power and 60mm data connected to DB37 pin(1-5)
	TopMiddle 60mm power and 200mm data connected to DB37 pin(6-10)
	TopBack 130mm power and X270mm data connected to DB37 pin(11-15)

	BottomFront 120mm power and 60mm data connected to DB37 pin(32-36)
	BottomMiddle 60mm power and 120mm data connected to DB37 pin(27-31)

	LeftMotor 100mm power and 200mm data connected to DB37 pin(22-26)
	RightMotor 100mm power and 200mm data connected to DB37 pin(16-19 & 37)

	pin 20 and 21 are not connected and reserved for 5v power (20-GND 21-5V)

	The left and right motor cables should be terminated in a 9-pin DuPont.


