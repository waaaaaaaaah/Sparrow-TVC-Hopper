---
title: "Sparrow TVC Hopper"
author: "Lev Edelson"
description: "A TVC model rocket capable of launching and landing under thrust"
created_at: "2024-03-22"
---
# May 22nd: Started work on designing the landing legs
Today I started the design of the landing legs and airframe of the hopper. The landing legs need to be able to aborb a large amount of the energy of the rocket, and need to be wide to help prevent tipping after landing. The landing legs are fixed in the deployment position, which enables the addition of large gas shocks for absorbing energy during landing. Based on previous research, I found that the randomness of ignition and thrust for these small black powder motors can create a relatively wide range of burnout altitudes, regardless of a consistent flight controller; the second motor wont burn perfectly consistently, so the rocket needs to be able to absorb this random error. Because of this, I decided that the addition of large shocks would allow me to absorb this randomness without needing to worry about more complex systems such as throttling, which would dbe difficult as these are solid motors, so the burn rate cannot be easily changed. I also discovered that syringes can actually act as simple, and cheap (they cost a few bucks compared to the tens of dollars traditional shocks can cost), gas shocks at the trade off that they don't spring back after landing. The primary structure of the legs is designed to be built with carbon fibre rods connected by 3d printed linkages. While the carbon fibre rods inflate the overall costs of the landing legs compared to a material such as aluminum, they nearly third the overall weight of the legs, which allows me to fit the other hardware into the mass limit of the rocket (~900 grams). Moreover, the rods used are only $6, meaning that, apart from hardware and 3d printed parts, the overall cost of one leg is kept under $10 despite the swap to carbon. 

Picture 1:
![Screenshot 2025-05-22 10 35 39 PM](https://github.com/user-attachments/assets/ae3017de-8516-429c-a880-9c042546d303)

The "gas shocks" - 0.8in ID syringes that absorb the energy from landing by compressing and forcing air through a small vent hole.

Picture 2:
![Screenshot 2025-05-22 10 37 36 PM](https://github.com/user-attachments/assets/d7110e97-3d39-49a7-9bbb-9d743703be94)

Overall Landing leg assembly - The construction is built around the use of one 24 in carbon fibre rod and one syringe. This allows for a relatively small BOM for each leg, which allows for easy replacement after failed landing attempts. Based on suspension systems, I decided to orient the shock as close to vertical as possible to absorb a large portion of the impulse exerted by the ground onto the rocket to prevent bounce. This is contrary to a smaller angle between both struts which enables a deployment system, but would lower the effectiveness of the shocks, which would make landing far less consistent and harder. 

Picture 3:
![Screenshot 2025-05-22 10 44 39 PM](https://github.com/user-attachments/assets/40a0651f-04df-4ddf-a987-efab305e7326)

Mounting to the airframe: Each leg is mounted with two m5 bolts. This allows for the quick replacement of legs in the field, which will increase the tempo of test flights, as it is likely that the legs will commonly break. 

Future work:
The detail in the CAD isn't full, fasteners and some parts are missing, so the next step will be to add them. Moreover, some of the parts are crude and not ready for manufacturing; next steps for these will be to refine their design and strengthen weak points. 

**Total time spent: 6h**

# May 24th: Finished up the airframe and legs

This is a short journal entry; not much to talk about, but this morning I was able to squeeze in some work to finish the airframe and leg work I did on Thursday. I added the landing leg caps, mounting holes, strengthened some parts, assigned materials, added the nosecone, and cleaned up the appearance. 

Picture 1: 
![Screenshot 2025-05-24 1 38 59 PM](https://github.com/user-attachments/assets/ad3bb6d5-7a63-4975-8b29-9d933e38aa49)

Nosecone: Designed with 1.5mm thick walls to minimize mass  

Picture 2:
![Screenshot 2025-05-24 2 29 45 PM](https://github.com/user-attachments/assets/cc2f8575-c8b4-48f4-b0ad-d70e3422415a)

Landing leg feet: Round to allow for consistent contact patch as legs compress. Flat spot is to make printing easier. 


Picture 3: 
![Screenshot 2025-05-24 2 31 12 PM](https://github.com/user-attachments/assets/1fef28f8-ec1c-4526-a7c6-5394c1509e0b)

Mass Budget allocation: Currently I'm trying to stay within 800 grams for the airframe, and I'm cutting it close, but I'm hoping that the spare 70 grams will be enough for the flight computer and its power. This mass figure also includes an old version of the gimbal (from the last rocket) so mass should be able to be brought down. 

Picture 4: 
![image](https://github.com/user-attachments/assets/af06b746-efb4-4cd7-9f60-01dee7446c14)

Here's just a picture of the airframe as it stands right now. 

Next steps: The next thing on the agenda is to redesign the gimbal for smaller 24mm rocket motors, lower backlash by swapping the servo wire for some actual linkages, and shrinking the overall design so it doesn't need airframe cutouts. 


**Total time spent: 45min**

# May 25nd: Designed the new gimbal
Today I redesigned my older 29mm motor mount to fit the 24mm estes D motors. This swap was made as, while the D class motors limit the mass budget, they are slightly less than half the cost, enabling more and cheaper test flights. Before starting this redesign, I committed to two main design goals: one, the gimbal should be able to completely fit and gimbal (with a range of 5 degrees in all four directions) inside a three inch airframe without airframe cutouts as these look bad and can create torque on the vehicle causing roll; two, the servos should be directly connected to the motor mount and inner gimbal by flat linkage bars rather than linkage wires to minimize the issues, such as movement delay and backlash, made worse by the flexibility of the wires on the original mount and the shifting of the wire bends inside the servo horn holes. As the position of the gimbal needs to be accuratly and consistently controlled, as even a small error will create a large destabalizing torque, backlash needs to be minimized. As the motor was smaller, it allowed me to relatively easily compact the overall design to fit it within the 3in, while removing the cutouts. To limit the backlash, I replaced the wire with solid linkage bars mounted on the end with small shoulder bolts, thus removing the issue of wirebending and the issue of the wires shifting in the small, loosely toleranced, holes. Not only does the gimbal design fit my original specifications, it's further able to gimbal to 6 degrees, which is a small, but nice upgrade over the last system which could only gimbal 5 degrees. The linkage change also has a nice quality of life improvement; the old wires were a real pain to bend accurately, and it was pretty easy to injure myself bending them. Now, with the linkage bars it should be a far more simple procedure to connect the gimbal to the servos. 
New gimbal design (left) vs old gimbal (right):

![Gimbal Assembly](https://github.com/user-attachments/assets/814287c2-58a0-4e03-b8fb-fd12c96e8b4c) ![P O G G E R S  V4 Assembly](https://github.com/user-attachments/assets/48a426f8-626b-4f40-affc-cf48e103b18f)

As visible, these are two very similar designs apart from the previously mentioned changes: both have a flat bottom plane allowing for easy printing and zeroing, both use the same Hitech HS5055's for actuation. (while these are costly, they have low backlash and a high frequency update rate, moreover, I already have a few of them)

![Rocket Assembly](https://github.com/user-attachments/assets/566952a3-9654-4072-970b-119c8264d7d8)

Heres a picture of the gimbal in the airframe; this is starting to look pretty cool I'm not going to lie.

Future plans:
Time to start working on the flight computer! I have some plans, but it will be my first time designing and making a fully integrated board without any form of breakout. 

**Total time spent: 3hr**

# May 26th: Created a majority of the flight computer's schematic
Today I worked on the schematic for the flight computer. In order for the rocket to know its orientation so it can stabilize itself, it needs an IMU. I selected the BMI088 for its accuracy and shock resistance. Moreover, it has an existing arduino library so programming will be, hopefully, easy. Furthermore, the accelerometer on the IMU gives me the ability to integrate acceleration twice to find altitude, while a gyro on its own would only let me integrate to find orientation. To measure altitude I decided on the BMP390 barometer as it's incredibly low noise for a barometer (Just +/- 0.1m based on my tests!). Just like the IMU, it also already has an existing library. The reason to have two measurements of altitude is so I can fuse the two into a hopefully more accurate measurement (The barometer is noisy, while the acceleration integration drifts, so the hope is that the two can be fused together for a measurement that's less noisy than the barometer and less drifty than the integration). The rocket needs to know its altitude incredibly accurately so it can time the descent burn so the rocket doesn't land too hard or bounce. For the main processor I decided on the RP2040 as it is incredibly well documented and easy to design, while being very powerful, and cheap (each chip is only 80 cents). To power the servo motors, I'm using a buck converter that brings the battery voltage down to 5 volts, and to power the mcu and the sensors, I'm using a small linear regulator that will provide a low noise power source to the sensitive IC's. For data logging, I also added an sd card mount, and for the firing of e-matches to ignite the motor, I added two mosfets that will connect them to ground, allowing enough current to flow to start the match burning. 
Picture One: The overall schematic
![image](https://github.com/user-attachments/assets/52971367-9f40-4852-b5a1-a797861d56e4)

Picture Two: The sensor hookups. I decided to use I2C for the sensors as it requires less hookups, and the rp2040 doesn't have enough free SPI outputs for the sensors and the sd card thats used for data storage
![image](https://github.com/user-attachments/assets/d489ada2-9521-40d2-942f-4f383516b158)

Picture Three: The IO. I have added 6 pwm output headers. This would allow for the control of 6 servos, covering the 2 minimum servos the rocket needs, and allowing for the use of this flight computer in future projects. The two pyro (Pyrotechnic Electronic Matches) screw terminals are also future proofing; I only need one pyro channel, but two allows me to use this computer on more conventional high powered rockets with dual deploy. The usb allows me to program the RP2040. 
![image](https://github.com/user-attachments/assets/3b38c6a1-1820-45a8-a723-89f3f5c80816)

Future Plans: The schematic still needs a design review; there are more than likely a few pcb breaking errors. Moreover, the LED's still haven't been added. Tomorrow, I would like to get both done so I can start routing.

**Total time spent: 4hr**

# May 27th: Routed the dang thing (poorly) - I plan to redo
Today I did the first draft of the routing. Everything is connected, but I plan on doing it again; it's so garbage. This process started with the placement of the usb port and the RP2040 and the routing of the USB differential pair. This should come first as the USB differential pair should be precise to make sure the board can communicate through USB as fast as possible. Then I added the decoupling capacitors to the RP2040. The decoupling capacitors are very important to keep the power to the MCU smooth and denoised, and placing them as close to the chip as possible means that they work the most effectively. I did them second as placing them early helps ensure I have room to place them close. Then I added the SD card, Flash, clock crystal, and boot and reset buttons. These didn't need to be in any specific order, but I wanted to make sure the rp2040's peripherals were wired correctly and efficiently; I didn't want to route the connections for these around anything else. Then I wired up the sensors. I just made sure the I2C traces were roughly the same length and crossed at right angles. Finally I wired up the non-signal wires and the voltage regulators (I also did the PWM but it's not very sensitive). As these wires aren't very sensitive to routing and noise, they could be safely routed around everything else without major issue. 
Picture One:
![image](https://github.com/user-attachments/assets/5144ab34-31ef-4862-a4a8-53e140886581)

The entire board. As you can see it's two layers (to save money). I chose to make it bigger than it needed to be to save time routing, and as it remains under the Pcbway order minimum, it's still just 5 dollars. 

Picture Two:
![image](https://github.com/user-attachments/assets/f3ecc086-fccf-4aa2-8f50-c7be1fc01999)

The RP2040 and its close peripherals. This was not fun to route, and I can't imagine it will be fun to solder. No nice design decisions here; this just kinda sucked to do.

Picture three:
![image](https://github.com/user-attachments/assets/1b4a05a5-9f24-416c-9e5f-64e1f1bd4c89)

The io (servos, battery power, and pyro plugs). This was kinda chill to do because of all the surplus space. It's not pretty, but it was nice to do. 

Future Plans: I should redo at least part of this routing to make it prettier. Maybe now that I'm used to this board, I can make it smaller to cut down on the dead space. Regardless of whether or not I re-route, I need to double and triple check the design. 

**Total time spent: 5hr**

# May 30th: Redid the PCB routing
Today I redid the routing and prettied up the board. Not much in terms of design choices today, but I think the board looks really cool now. Mostly everything is the same for the actual routing order, but I utilized more area fills, especially for servo power, to clean up the design and increase current capacity and improve thermals. I also planned component placement more carefully, so it has less random/gross traces and vias. There was also some more pretty work done, but that will be saved for the pictures. 

Picture One:
![image](https://github.com/user-attachments/assets/e6817838-f6d0-410b-a59a-9b2ceb2b361e)

The new board layout. This one is functionally identical to the other routing, but it looks way cleaner. 

Picture Two:
![image](https://github.com/user-attachments/assets/1a34f824-6495-4dfc-982d-7db01329f602)

The major change: the use of power planes for the servos so I avoid using large and gross looking current carrying traces.

Picture 3:
![image](https://github.com/user-attachments/assets/5bc87c22-93f1-4920-8e68-fb7a888716bb)

Here's the silkscreen art I added to the back of the board; it adds nothing practical, but I think it looks super cool.

Picture 4:
![image](https://github.com/user-attachments/assets/f4ffd058-ddbe-4337-8a5f-b2563537d745)

Here's the front of the board; nothing special here but some cute lil pictures. 
Future Work: I plan on starting updating my old sim to work with a landing rocket so I can figure out the fine specs of the rocket. 

**Total time spent: 6hr**

# May 31st: Designed the Flight Computer Mount
Today I designed the avionics mounting for the rocket. It wasn't a lot, but it marks the completion of the mechanical design of the rocket; the cad contains all of the parts to be manufactured and assembled.
![Avbay Assembly](https://github.com/user-attachments/assets/2ef9d2c1-c48e-4dd6-8b53-e48ac4f3f551)

Future work: Remains the same as yesterday, I now need to update my flight sim so I can model the flight profile of the hopper. 

**Total time spent: 30mins**

