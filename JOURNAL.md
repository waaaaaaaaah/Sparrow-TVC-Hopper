---
title: "Sparrow TVC Hopper"
author: "Lev Edelson"
description: "A TVC model rocket capable of launching and landing under thrust"
created_at: "2024-03-22"
---
# May 22nd: Started work on designing the landing legs
Today I started the design of the landing legs and airframe of the hopper. The landing legs are fixed in the deployment position, which enables the addition of large gas shocks for absorbing energy during landing. Based on previous research, I found that the randomness of ignition and thrust for these small black powder motors can create a relatively wide range of burnout altitudes, regardless of a consistent flight controller. Because of this, I decided that the addition of large shocks would allow me to absorb this randomness without needing to worry about more complex systems such as throttling. I also discovered that syringes can actually act as simple, and cheap (they cost a few bucks compared to the tens of dollars traditional shocks can cost), gas shocks at the trade off that they don't spring back after landing. The primary structure of the legs is designed to be built with carbon fibre rods connected by 3d printed linkages. While the carbon fibre rods inflate the overall costs of the landing legs compared to a material such as aluminum, they nearly third the overall weight of the legs, which allows me to fit the other hardware into the mass limit of the rocket (~900 grams). Moreover, the rods used are only $6, meaning that, apart from hardware and 3d printed parts, the overall cost of one leg is kept under $10 despite the swap to carbon. 

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
The detail in the CAD isn't full, fasteners and some parts are missing, so the next step will be to add them.

Time spent:
6 hours (My arse wasn't in school cause I was sick)

**Total time spent: 6h**
