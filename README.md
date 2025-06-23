# Sparrow-TVC-Hopper

Inspired by Joe Barnard’s Scout series of [rockets](https://www.youtube.com/watch?v=SH3lR2GLgT0), I decided to build a similar vehicle that can autonomously stabilize and land itself. I just think the concept looks really cool in flight, and I think that I can improve on his success rate with better shock absorption. I also think this is a logical continuation of my flights with a parachute-landing thrust vector controlled rocket last summer. The rocket is powered by a pair of solid rocket motors, specifically Estes D12's. The first motor is used to launch the rocket up to its apogee, or its highest altitude, while the second motor is ignited at a precise time to slow the rocket down for landing. As these motors cannot be throttled or shut down, the only way to control touchdown speed is by controlling ignition time. Moreover, there is a small window for ignition, too early and the motor burns out high above the ground and the rocket drops, too late and the rocket hits the ground too fast. This is where the flight controller comes in. It takes two measurements of altitude, one through a barometer, and another by integrating accelerometer data to dead reckon position. It then combines these measurements to produce an accurate estimate of altitude that it uses to time the ignition of the second motor. The flight controller also has to keep the rocket stable; as the rocket will be traveling in two directions through the air and needs to be stable in both, fins wont work as they would cause the rocket to flip on the way down. Therefore, to stabilize, there needs to be some form of active control. This rocket accomplishes this by vectoring the motor mount. The flight controller uses a gyroscope to estimate the current orientation and measure the angular rates of the rocket, and using these measurements, commands the servos that control the motor’s orientation to move. By controlling the motors orientation, the flight controller can control the torque acting on the rocket. The flight controller therefore can keep the rocket pointing straight up and down, despite destabilizing aerodynamic forces. While the flight controller is able to keep the rocket stable and time the ignition of the landing motor, it’s not perfect; the rocket will always touch down with some vertical velocity. To absorb this shock, the airframe is designed with large shock absorbing landing legs.

# Picture of Sparrow Cad:
![Rocket Assembly(3)](https://github.com/user-attachments/assets/9ecb744e-60da-4a3a-b72e-e62ddbc40ddb)

# Picture of Flight Controller CAD:
![Screenshot 2025-06-23 172332](https://github.com/user-attachments/assets/c51c4851-d507-4eb7-a8ab-db557e2a01fc)

# Electronics Hookups:
![Screenshot 2025-06-23 172515](https://github.com/user-attachments/assets/b4a82a53-39f3-4820-8c1c-c4e8c870b1e4)

# Accessing the Design Files:
PCB: Download and extract the zipped KiCad project and open the KiCad project file in the folder

CAD: Download and install the STEP file, opening it in a cad software of your choice, alternatively, open the Onshape link in your browser 

Subassembly ,Part,Link,Cost Per,QTY,Source,Preowned,Total Cost,Shipping (Per Supplier),Tax(6.5%),Total
Launch Hardware,Bulk Estes D12-0 (20 motors),https://www.acsupplyco.com/estes-model-rockets/model-rocket-engines/estes-c11-d-and-e-engines/estes-d12-0-model-rocket-engine,$107.90,1,ACSupplyCo,TRUE,0,0,15.45,310.07
Flight Computer,TS391AX,https://www.amazon.com/Chip-Quik-TS391AX-Thermally-No-Clean/dp/B096BM58D5,$15.95,1,Amazon,TRUE,0,0,,
Flight Computer,800mAh 2S 7.4V Lipo,https://www.amazon.com/Gens-ace-Battery-JST-SYP-Helicopter/dp/B077JLLN59?crid=FIYRQ7BBMEJN&dib=eyJ2IjoiMSJ9.XPhdKBeFB4QBjpRyyOQI02N_nRBheilCLb4P_ci9fWZiuvZw25Ag-S7MlEP2ZsDzgMi2g23l4WwZNWJnYlYbC_08HNFf5ThRYMYmVAAsCeeuNIpdLu45PfECLxzbA1E_wSbKIdOnVVWZVt4Znetx2T0uiDOzpuT5hwl_-7mbVgyrz2b9bGdeHTN_LImNnxe1ljrQYyL8fgx1VV4ucKVbrWfqcHhno6V422Zq7IhAjr6FxGkdweDQDEIpovqEDM9zc5Xj8ykJURav3sQmU7XJYwx8YfU-j0cGv8gNZ6XLLwc.zWpiSEN3poKOaBPrT4DtXBpACiAe7H_LUreWJkkNII8&dib_tag=se&keywords=2+cell+lipo+500+mah&qid=1750528198&sprefix=2+cell+lipo+500+mah%2Caps%2C82&sr=8-38,$7.60,1,Amazon,FALSE,$7.60,0,,
Flight Computer,RP2040,https://www.digikey.com/en/products/detail/raspberry-pi/SC0914-13/14306010?s=N4IgTCBcDaIE4AcwAYAsyQF0C%2BQ,$0.70,2,Digikey,FALSE,$1.40,$8.00,,
Flight Computer,BMP390,https://www.digikey.com/en/products/detail/bosch-sensortec/BMP390/16164575,$3.15,2,Digikey,FALSE,$6.30,,,
Flight Computer,BMI088,https://www.digikey.com/en/products/detail/bosch-sensortec/BMI088/8634936,$5.23,2,Digikey,FALSE,$10.46,,,
Flight Computer,10uF 25v Cap 0805 (GRM21BZ71E106KE15L),https://www.digikey.com/en/products/detail/murata-electronics/GRM21BZ71E106KE15L/13904911,$0.29,2,Digikey,FALSE,$0.58,,,
Flight Computer,3.3nF Cap 0603 (C0603C332K4REC7411),https://www.digikey.com/en/products/detail/kemet/C0603C332K4REC7411/8645095?s=N4IgjCBcpgbFoDGUBmBDANgZwKYBoQB7KAbRAGYBOAJgBZ4BdAgBwBcoQBlVgJwEsAdgHMQAXwJgA7AhDJI6bPiKkQtanTABWEExBsO3fsLEFqABlqUZchbgLFIZcuTNmABMwBiOlu0ggAVQE%2BVgB5FABZHDQsAFceHBMQAForaFkoXlilBycQCR1xFOprTJ5s%2BxVtBlEikscKADpyAU83RDRmNEQQwh5CoA,$0.10,2,Digikey,FALSE,$0.20,,,
Flight Computer,CAP CER 47UF 10V X5R 0805 (GRM21BR61A476ME15L),https://www.digikey.com/en/products/detail/murata-electronics/GRM21BR61A476ME15L/4905529,$0.38,6,Digikey,FALSE,$5.25,,,
Flight Computer,CAP CER 0.1UF 10V X7R 0603 (C0603C104J8RACTU),https://www.digikey.com/en/products/detail/kemet/C0603C104J8RACTU/2199774,$0.22,12,Digikey,FALSE,$2.65,,,
Flight Computer,CAP CER 10UF 10V X7R 0603 (GRM188Z71A106KA73D),https://www.digikey.com/en/products/detail/murata-electronics/GRM188Z71A106KA73D/13401725,$0.28,4,Digikey,FALSE,$1.12,,,
Flight Computer,CAP CER 1UF 10V X7R 0402 (GRM155Z71A105KE01J),https://www.digikey.com/en/products/detail/murata-electronics/GRM155Z71A105KE01J/16033607,$0.10,4,Digikey,FALSE,$0.40,,,
Flight Computer,CAP CER 0.1UF 10V X7R 0402 (C0402C104J8RACTU),https://www.digikey.com/en/products/detail/kemet/C0402C104J8RACTU/2196231,$0.10,20,Digikey,FALSE,$2.08,,,
Flight Computer,CAP CER 15PF 16V X8R 0402 (C0402C150F4HACTU),https://www.digikey.com/en/products/detail/kemet/C0402C150F4HACTU/7944820?s=N4IgjCBcoMxaBjKAzAhgGwM4FMA0IB7KAbXDBggF18AHAFyhAGU6AnASwDsBzEAX3xgAbPBBJIaLHkIkQMAJxgArAA4Q1EPUYsOPfoIDso8ZJz4ikUgBYATDdsiNWyMzZdeAkDYAMV%2BcZQMMxlLcCUAAhoAMXVaBhcAVU52OgB5ZABZbFRMAFdWbH0QAFp-aDEoNlzpC1I4QXVPYpsAyCqa2SVGzxbQ5RpkRqA,$0.15,4,Digikey,FALSE,$0.60,,,
Flight Computer,CONN RCPT USB2.0 MICRO B SMD R/A (1050170001),https://www.digikey.com/en/products/detail/molex/1050170001/2350832?s=N4IgTCBcDaIIwAYCsC4HYC0DtxAXQF8g,$0.92,2,Digikey,FALSE,$1.84,,,
Flight Computer, CONN MICRO SD CARD R/A SMD (0472192001),https://www.digikey.com/en/products/detail/molex/0472192001/3044807?s=N4IgTCBcDaICwHYwEYCcBaMAGLyQF0BfIA,$1.63,2,Digikey,FALSE,$3.26,,,
Flight Computer, TERM BLK 2POS SIDE ENT 3.5MM PCB (0393570002),https://www.digikey.com/en/products/detail/molex/0393570002/946543?s=N4IgTCBcDaIMwE44FYDsAGTEC6BfIA,$1.08,4,Digikey,FALSE,$4.32,,,
Flight Computer,SMD MOLDING POWER CHOKE (CSHB0421R-1R5M),https://www.digikey.com/en/products/detail/codaca/CSHB0421R-1R5M/16633473?s=N4IgTCBcDaIMIGUASAhADAFjARgEoFo8BWAWRAF0BfIA,$1.43,2,Digikey,FALSE,$2.86,,,
Flight Computer,MOSFET N-CH 30V 5.7A TO236AB (PMV20XNER),https://www.digikey.com/en/products/detail/nexperia-usa-inc/PMV20XNER/5395793?s=N4IgTCBcDaIAoFkBqYAMANAcgUQEogF0BfIA,$0.28,4,Digikey,FALSE,$1.12,,,
Flight Computer,RES 510K OHM 1% 1/10W 0603,https://www.digikey.com/en/products/detail/stackpole-electronics-inc/RMCF0603FT510K/1760917,$0.10,2,Digikey,FALSE,$0.20,,,
Flight Computer,RES 82K OHM 5% 1/10W 0603 (RC0603JR-0782KL),https://www.digikey.com/en/products/detail/yageo/RC0603JR-0782KL/726835,$0.10,2,Digikey,FALSE,$0.20,,,
Flight Computer,RES 4.7K OHM 1% 1/10W 0603 (RC0603FR-074K7L),https://www.digikey.com/en/products/detail/yageo/RC0603FR-074K7L/727212,$0.10,8,Digikey,FALSE,$0.80,,,
Flight Computer,RES 85.6K OHM 1% 1/10W 0603 (RN73R1JTTD8562F100),https://www.digikey.com/en/products/detail/koa-speer-electronics-inc/RN73R1JTTD8562F100/10022057,$0.10,4,Digikey,FALSE,$0.40,,,
Flight Computer,RES 40K OHM 0.1% 1/10W 0603 (AT0603BRD0740KL),https://www.digikey.com/en/products/detail/yageo/AT0603BRD0740KL/16990199,$0.33,4,Digikey,FALSE,$1.32,,,
Flight Computer,RES SMD 10K OHM 1% 1/10W 0603 (CRCW060310K0FKEA),https://www.digikey.com/en/products/detail/vishay-dale/CRCW060310K0FKEA/1174782,$0.10,8,Digikey,FALSE,$0.80,,,
Flight Computer,RES 300 OHM 5% 1/10W 0603 (RC0603JR-07300RL),https://www.digikey.com/en/products/detail/yageo/RC0603JR-07300RL/726765,$0.10,4,Digikey,FALSE,$0.40,,,
Flight Computer,RES 47K OHM 1% 1/10W 0603 (RC0603FR-0747KL),https://www.digikey.com/en/products/detail/yageo/RC0603FR-0747KL/727253,$0.10,8,Digikey,FALSE,$0.80,,,
Flight Computer,RES 27.4 OHM 0.1% 1/10W 0402 (RP73PF1E27R4BTD),https://www.digikey.com/en/products/detail/te-connectivity-passive-product/RP73PF1E27R4BTD/8260711,$0.18,4,Digikey,FALSE,$0.72,,,
Flight Computer,RES 1K OHM 1% 1/10W 0402 (RK73H1ERTTP1001F),https://www.digikey.com/en/products/detail/koa-speer-electronics-inc/RK73H1ERTTP1001F/12335224,$0.13,4,Digikey,FALSE,$0.52,,,
Flight Computer,SWITCH TACTILE SPST-NO 0.05A 24V (B3FS-1000P),https://www.digikey.com/en/products/detail/omron-electronics-inc-emc-div/B3FS-1000P/277812?s=N4IgTCBcDaIEIGYBiBlAtARgAw4AogF0BfIA,$0.64,4,Digikey,FALSE,$2.56,,,
Flight Computer,IC REG LINEAR 3.3V 1A SOT-223 (NCP1117ST33T3G),https://www.digikey.com/en/products/detail/onsemi/NCP1117ST33T3G/1749063,$0.58,2,Digikey,FALSE,$1.16,,,
Flight Computer,IC FLASH 128MBIT SPI/QUAD 8SOIC (W25Q128JVSIQ),https://www.digikey.com/en/products/detail/winbond-electronics/W25Q128JVSIQ/5803943,$1.54,2,Digikey,FALSE,$3.08,,,
Flight Computer,IC REG BUCK ADJ 4A 11VQFN (TPS621361RGXR),https://www.digikey.com/en/products/detail/texas-instruments/TPS621361RGXR/7653238?s=N4IgTCBcDaICoAUDKA2MBGAzC9AlA4gBq4gC6AvkA,$1.72,2,Digikey,FALSE,$3.44,,,
Flight Computer,TVS DIODE 5.25VWM 17VC SOT23-6 (USBLC6-2SC6),https://www.digikey.com/en/products/detail/stmicroelectronics/USBLC6-2SC6/1040559,$0.36,2,Digikey,FALSE,$0.72,,,
Flight Computer,CRYSTAL 12.0000MHZ 10PF SMD (ABM8-272-T3),https://www.digikey.com/en/products/detail/abracon-llc/ABM8-272-T3/22472366?s=N4IgTCBcDaIIICECyAOAtGA7GNAVAzCALoC%2BQA,$0.54,2,Digikey,FALSE,$1.08,,,
Flight Computer,LED BLUE 0805 SMD (5973605607F),https://www.digikey.com/en/products/detail/dialight/5973605607F/9385449,$0.34,6,Digikey,FALSE,$2.04,,,
Flight Computer,RES SMD 255 OHM 0.5% 1/5W 0603 (ERJ-PB3D2550V),https://www.digikey.com/en/products/detail/panasonic-electronic-components/ERJ-PB3D2550V/6212996,$0.12,6,Digikey,FALSE,$0.72,,,
Airframe and Legs,"DragonPlate Carbon Tube ~ .254""OD x .158""ID x 24""",https://dragonplate.com/dragonplate-carbon-tube-254od-x-158id-x-24,$5.52,8,Dragon Plate,FALSE,$44.16,$15,,
Airframe and Legs,LOC 3in Body Tube,https://locprecision.com/collections/rocket-components/products/cardboard-airframes?variant=39778656125119,$14.16,1,LOC Precision,FALSE,$14.16,$14,,
Gimbal,LOC 24mm Motor Mount Tube,https://locprecision.com/collections/rocket-components/products/motor-mount-tubing?variant=39778656878783,$1.75,3,LOC Precision,FALSE,$5.25,,,
Airframe and Legs,"Button Head Hex Drive Screw, Passivated 18-8 Stainless Steel, M3 x 0.50 mm Thread, 35mm Long",https://www.mcmaster.com/92095A201,$4.02,1,McMaster,FALSE,$4.02,$20,,
Airframe and Legs,"Button Head Hex Drive Screw, Passivated 18-8 Stainless Steel, M3 x 0.50 mm Thread, 10mm Long",https://www.mcmaster.com/92095A182,$7.19,1,McMaster,FALSE,$7.19,,,
Airframe and Legs,Medium-Strength Steel Nylon-Insert Locknut,https://www.mcmaster.com/90576A102/,$4.82,1,McMaster,FALSE,$4.82,,,
Airframe and Legs,"Clear Plastic Syringe with Luer Slip Connection, 10 ml Capacity",https://www.mcmaster.com/7181N23,$7.65,1,McMaster,FALSE,$7.65,,,
Gimbal,"Alloy Steel Shoulder Screws, 3 mm Shoulder Diameter, 3 mm Shoulder Length, M2 x 0.4 mm Thread",https://www.mcmaster.com/92981A767,$3.45,5,McMaster,FALSE,$17.25,,,
Launch Hardware,Fire Wire Initiators: 3ft box of 80,https://electricmatch.com/blasting-law-enforcement-military/see/6/7/mjg-firewire-initiator--standard,$66.40,1,MJG Technologies,TRUE,0,,,
Flight Computer,PCB and Stencil (4L Minimum) (Includes Shipping),,$60.12,1,PCBWay,FALSE,$60.12,,,
Airframe and Legs,"PolyLite™ PETG (1.75mm, 1kg)",https://us.polymaker.com/products/polylite-petg?srsltid=AfmBOooqUozcru0N6uNNisWVJbWWdUIMz94A-WZ4c6kXgjwwUONE-xj2,$22.99,1,PolyMaker,TRUE,0,,,
Flight Computer,Male to Female Servo Extensions (12in),https://www.servocity.com/hitec-super-duty-extensions/,$4.99,2,ServoCity ,TRUE,0,,,
Gimbal,Hitech HS-5055MG,https://www.servocity.com/hs-5055mg-servo/,$23.99,2,ServoCity ,TRUE,0,,,
