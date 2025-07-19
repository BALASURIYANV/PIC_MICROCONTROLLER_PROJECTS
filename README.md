# PIC_MICROCONTROLLER_PROJECTS
##  How to Run the Project
 1. Open in MPLAB X IDE
- Launch MPLAB X IDE
- Go to **File → Open Project**
- Navigate to the `MPLAB_Project.X` directory and open it
- Build and compile using the **XC8** compiler
2. Simulate in Proteus
- Launch Proteus
- Open the `.pdsprj` file from the `Proteus_Files` folder
- Make sure the compiled `.hex` file from MPLAB is linked to the PIC microcontroller in Proteus:
  - Double-click the PIC in the schematic
  - In the **Program File** section, browse and select the `.hex` file from the `dist/default/production/` directory inside your MPLAB X project
- Run the simulation
