# SelfParkingCar
This is for arduino to make a self parking car. 
Using a smart car kit pruduced by ELEGOO.

In autonomous parking, I need to create algorithms and position sensors according to certain assumptions. My assumptions will be as follows in this project. In the scenario, the left side of the road will consist of walls and park areas. There are 2 sensors in total, one on the front of the car and the other on the rear.

# System Algorithm
The two sensors on the front and rear understand that the wall is 15cm smaller than the measured value and move forward. It records this in memory. The sensors measure continuously, and when these values are the same as the resultant values, you have to decide how to park.

# Park Method Selection Algorithm
Case 1: If the measured value is bigger than the car and smaller than the length of the car, the parallel parking system will operate.
Case 2: If the measured value is greater than the length of the car, the robor will park vertically.

# Parallel Parking Algorithm
In this case, the car crosses the parking area and the car stops when two sensor see the wall again.
He comes back a little and turns right 45 degrees.
While moving backwards, the rear sensor goes into the park area by measuring and starts to turn left. 
During the left movement, the sensors measure continuously and the sensors continue to turn left until the measured value equals each other. 
Stop when you are equal.
The front sensor measures and goes forward until it is small by 10cm and stops when it is small by 10cm.
Parking is over.

# Verical Parking Algorithm
If the sensors measures the value too much over the length of the car, the car stops and turns 90 degrees to the left.
They start moving towards the parking lot.
At this time, the front sensor continuously measures and the car stops if the measured value is less than 10cm.
Park operation is completed.

# Materials
Arduino Mega
Adafruit Motor Shield
4 Dc Motor Robot Kit
2 Pieces HC-SR04 Ultrasonic Sensor
LM 393 Infrared Speed Sensor
Lipo Battery 
Jumper calbes

