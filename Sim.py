#NOTE: None of the values in this sim for tuning or rocket stats are final or have flown but are instead guesses 
import matplotlib.pyplot as plt
import numpy as np
import math
import random
tMax = 1000000
timestep = 0.0001
thrust = 0.2 #current state variables
time = 0.0 #s
alt = 0.0 #m
yVel = 0.0 #m/s
mass = 0.7 #kg
motorPropMass = 0.021 #motor stats (Kg and Kg/s)
motorCaseMass = 0.022 
motorDecayRate = -0.0127273
Gimbald = 0.3 #distance from gimbal to COM
kP = 0.02 #PID values for gimbal 
kD = 0.007
LP = 0.81 #tuning values for landing function
LT = 0.0
timeLBS = 0 #second burn time
gTarget = 0.0 #current gimbal target
torqueTarget = 0 #torque requested by controller
moi = 0.043 #kgm^2
gAngle = 0.0 #deg
Angle = 10 #deg
angularVel = 0.0 #deg/s
fCase = "Launch"
aIgnite = 0 #ignition altitude, which is based on maxAlt
maxAlt = 0
thrustRand = 0.05 * 2*(random.random()-0.5)+1 #randomization for motor thrust
tTimePID = 0 #used to time pid and servo delays
delayPID = 0.004 #time delay for pid and servo response 
gRand = 0.0 #gimbal randomness constant
gVel = 360 #gimbal speed deg/s
delay = 0.25 * (0.2 * 2*(random.random()-0.5)+1) #ignition delay
servoTarget = [0.0,0.0] #array used to add the time delay; each time delay the last value is moved to the first one, creating a response delay
G = 9.8 #gravitational acceleration 
D12 = [[0.049, 2.569], [0.116, 9.369], [0.184, 17.275], [0.237, 24.258], [0.282, 29.73], [0.297, 27.01], [0.311, 22.589], [0.322, 17.99], [0.348, 14.126], [0.386, 12.099], [0.442, 10.808], [0.546, 9.876], [0.718, 9.306], [0.879, 9.105], [1.066, 8.901], [1.257, 8.698], [1.436, 8.31], [1.59, 8.294], [1.612, 4.613], [1.65, 0.01]] #stores motor thrust
heightp = [alt] #arrays used to create graphs
timep = [time]
anglep = [Angle]
yVelp = [yVel]
thrustp = [thrust]
massp = [mass]
counter = 0
while(counter < 3):
    match fCase:
        case "Launch": 
            mass += motorPropMass*2+motorCaseMass*2 #adds motor masses to mass
            while(time<1.65 and abs(Angle)<30.5): #loop for motor burn; runs until burnout of first motor
                thrustcheck = tMax
                for r in D12: #finds nearest time in D12 array and uses the coresponding thrust
                    if(abs(time - r[0])<abs(thrustcheck)):
                        thrustcheck = time - r[0]
                        thrust = r[1] * (thrustRand)
                mass += motorDecayRate*timestep #decays motor mass
                torqueTarget = -kP * Angle - kD*angularVel #PD controller determines target torque
                if((abs(torqueTarget)>(thrust*Gimbald))):
                    torqueTarget = thrust*Gimbald
                print(time)
                if(time - tTimePID >= delayPID): #delays the servo response and updates the gimbal targets
                    gTarget = math.degrees(math.asin(torqueTarget/(thrust*Gimbald)))
                    if(gTarget > 5):
                        gTarget = 5
                    if(gTarget < -5):
                        gTarget = -5
                    servoTarget[0] = servoTarget[1]
                    servoTarget[1] = gTarget
                    print(servoTarget)
                    tTimePID = time
                if(gAngle > servoTarget[0]): #moves the gimbal with its speed
                    gAngle -= gVel*timestep + 2*(random.random()-0.5)*gRand
                if(gAngle < servoTarget[0]):
                    gAngle += gVel*timestep + 2*(random.random()-0.5)*gRand
                if(gAngle == servoTarget[0]):
                    gAngle += 2*(random.random()-0.5)*gRand
                Angle += angularVel*timestep #integrates angle
                angularVel += math.degrees(((math.sin(math.radians(gAngle))*thrust*Gimbald)/moi))*timestep #det. angular velocity 
                if(Angle>180):
                    Angle = -180
                if(Angle<-180):
                    Angle = 180
                alt += yVel*timestep #integrates vertical velocity 
                yVel += ((thrust*(math.cos(math.radians(Angle+gAngle))))/mass - G)*timestep #det. vertical velocity 
                if(alt < 0):   #stops rocket from falling through ground
                    alt = 0
                    yVel = 0
                if(alt>maxAlt): #finds maximum altitude 
                    maxAlt=alt
                anglep.append(Angle) #adds values to graph arrays
                timep.append(time)
                heightp.append(alt)
                yVelp.append(yVel)
                thrustp.append(thrust)
                massp.append(mass)
                time += timestep
            fCase = "Coast"
            counter +=1
        case "Coast": 
            while(alt > aIgnite): #just integrates angvel and vertical velocity until ignition altitude is reached
                if(alt>maxAlt):
                    maxAlt=alt
                aIgnite = (LP)*maxAlt+LT
                alt += yVel*timestep
                yVel += -1*G*timestep
                Angle += angularVel*timestep
                anglep.append(Angle)
                timep.append(time)
                heightp.append(alt)
                yVelp.append(yVel)
                thrustp.append(thrust)
                massp.append(mass)
                time += timestep
            delayt=delay
            delay +=time
            while(time<=delay): #integrates flight variables until ingnition delay passes 
                alt += yVel*timestep
                yVel += -1*G*timestep 
                Angle += angularVel*timestep 
                anglep.append(Angle)
                timep.append(time)
                heightp.append(alt)
                yVelp.append(yVel)
                thrustp.append(thrust)
                massp.append(mass)
                time += timestep             
            fCase = "Landing"
            counter +=1
        case "Landing": #basically the same as launch; same basic simulation core
            thrust = 0.01
            mass -= motorCaseMass
            while(alt>0 and abs(Angle)<30.5):
                thrustcheck = tMax
                for r in D12:
                    if(abs(timeLBS - r[0])<abs(thrustcheck)):
                        thrustcheck = timeLBS - r[0]
                        thrust = r[1] * (thrustRand)
                mass += timestep*motorDecayRate
                torqueTarget = -kP * Angle - kD*angularVel
                if((abs(torqueTarget)>(thrust*Gimbald))):
                    torqueTarget = thrust*Gimbald
                print(time)
                if(time - tTimePID >= delayPID):
                    gTarget = math.degrees(math.asin(torqueTarget/(thrust*Gimbald)))
                    if(gTarget > 5):
                        gTarget = 5
                    if(gTarget < -5):
                        gTarget = -5
                    servoTarget[0] = servoTarget[1]
                    servoTarget[1] = gTarget
                    print(servoTarget)
                    tTimePID = time
                if(gAngle > servoTarget[0]):
                    gAngle -= gVel*timestep + 2*(random.random()-0.5)*gRand
                if(gAngle < servoTarget[0]):
                    gAngle += gVel*timestep + 2*(random.random()-0.5)*gRand
                Angle += angularVel*timestep
                angularVel += math.degrees(((math.sin(math.radians(gAngle))*thrust*Gimbald)/moi))*timestep
                if(Angle>180):
                    Angle = -180
                if(Angle<-180):
                    Angle = 180
                alt += yVel*timestep
                yVel += ((thrust*(math.cos(math.radians(gAngle+Angle))))/mass - G)*timestep
                anglep.append(Angle)
                timep.append(time)
                heightp.append(alt)
                yVelp.append(yVel)
                thrustp.append(thrust)
                massp.append(mass)
                time += timestep
                timeLBS += timestep
            counter +=1
print(maxAlt)
print(aIgnite)
print(yVel)
print(delayt)
thrustcheck = 0
fig, ax = plt.subplots()             
ax.plot(timep, heightp)  
fig, ay = plt.subplots()             
ay.plot(timep, anglep)   
fig, az = plt.subplots()             
az.plot(timep, thrustp)  
fig, aa = plt.subplots()             
aa.plot(timep, yVelp)  
fig, ab = plt.subplots()             
ab.plot(timep, massp)
plt.show()
