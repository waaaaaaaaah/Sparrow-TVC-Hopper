# Sparrow-TVC-Hopper

	Inspired by Joe Barnard’s Scout series of rockets, I decided to build a similar vehicle that can autonomously stabilize and land itself. I just think the concept looks really cool in flight, and I think that I can improve on his success rate with better shock absorption. I also think this is a logical continuation of my flights with a parachute-landing thrust vector controlled rocket last summer. The rocket is powered by a pair of solid rocket motors, specifically Estes D12's. The first motor is used to launch the rocket up to its apogee, or its highest altitude, while the second motor is ignited at a precise time to slow the rocket down for landing. As these motors cannot be throttled or shut down, the only way to control touchdown speed is by controlling ignition time. Moreover, there is a small window for ignition, too early and the motor burns out high above the ground and the rocket drops, too late and the rocket hits the ground too fast. This is where the flight controller comes in. It takes two measurements of altitude, one through a barometer, and another by integrating accelerometer data to dead reckon position. It then combines these measurements to produce an accurate estimate of altitude that it uses to time the ignition of the second motor. The flight controller also has to keep the rocket stable; as the rocket will be traveling in two directions through the air and needs to be stable in both, fins wont work as they would cause the rocket to flip on the way down. Therefore, to stabilize, there needs to be some form of active control. This rocket accomplishes this by vectoring the motor mount. The flight controller uses a gyroscope to estimate the current orientation and measure the angular rates of the rocket, and using these measurements, commands the servos that control the motor’s orientation to move. By controlling the motors orientation, the flight controller can control the torque acting on the rocket. The flight controller therefore can keep the rocket pointing straight up and down, despite destabilizing aerodynamic forces. While the flight controller is able to keep the rocket stable and time the ignition of the landing motor, it’s not perfect; the rocket will always touch down with some vertical velocity. To absorb this shock, the airframe is designed with large shock absorbing landing legs.

Picture of Sparrow Cad:

Picture of Flight Controller CAD:


Electronics Hookups:

Accessing the Design Files:
PCB: Download and extract the zipped KiCad project and open the KiCad project file in the folder
CAD: Download and install the STEP file, opening it in a cad software of your choice, alternatively, open the Onshape link in your browser 
