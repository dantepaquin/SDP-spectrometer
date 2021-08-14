# SDP-Spectrometer

This is the joint repository for the hardware and software for the UCSC EE SDP 2021 Spectrometer. 
The directory *kicad-libraries* contains all of the design files for the hardware, including the schematics, kicad projects, footprint & symbol libraries, and gerbers.
The directory *microcontroller-libraries* contains all of the software used by our spectrometer.

## Kicad Libraries
In our design, we used [KiCad v5.1.0](https://www.kicad.org/blog/2019/03/KiCad-5.1.0-Release/) to create libraries for footprints, symbols, schematics, and pcbs. Currently, the initial designs are in their first revision, and we have fabricated prototypes to be tested.

While our design uses five separate boards connected with wires, all designs are located within a single KiCad project, "main.pro."

### Overview of directories:
* Adafruit-PowerBoost-1000C-master/
> Our design uses an existing power delivery board, and this folder contains the physical design documents that we referenced and used in our own.

* Backup/
> An almost-empty folder used for managing local backups and versioining. Can be removed.

* RN4678dev/
> This contains a kicad project and its design files for a development board, opening the SMD footprint to machine headers. These are not necessary for the final design.

* Renders/
> This contains PDF views of the current PCBs, shown with a small selection of layers.

* SC70-Dev/
> This is a development board used for the SC70 footprint, allowing breadboard verification of our systems. This contains a kicad project with the scematic and PCB files.

* Separate/
> This directory contains subdirectories for each of the five PCBs of our design, which allowed us to manufacture individual boards rather than the full set. This also includes the gerbers used to manufacture the initial run of boards. 

* Wiring Diagram/
> This was a development project to identify and plan the necessary connections between the components of our design. It exists for reference, and has no physical form.

* spectrometer_core.pretty/
> This is the footprint library directory, implementing the physical dimensions and connections of each device used in our design.

* fp-lib-table
> This file tells KiCad how to associate the symbols in our schematic with the footprints in spectrometer_core.pretty.

* main-cache.lib
> This file keeps track of all of the symbols used in the schematic.

* main.kicad_pcb
> This is the main PCB file, which is used to design and lay out the footprints into their physical form.

* main.pro
> **This is the main project file of the spectrometer.** Opening this with kicad will give you access to design and change the footprints, symbols, schematics, and PCBs of the design.

* main.sch
> This is the main schematic file, used to establish connections between the components of the design.

* spectrometer_core.bck
> This is a local backup of the spectrometer_core.dcm file, and can be removed.

* spectrometer_core.dcm
> This keeps track of any documentation we added to the symbol library.

* spectrometer_core.lib
> This is our main symbol library, used to represent the components as used on our schematic.

* sym-lib-table
> This keeps track of the symbol libraries used in the main project.



## Microcontroller Libraries

Our project uses a [TeensyLC](https://www.pjrc.com/teensy/teensyLC.html) running [Arduino](https://www.arduino.cc/en/software), and was developed in the Arduino IDE. This directory contains the code we were able to complete, and verious sketches of test programs.

### Overview of directories:

* Bluetooth/
> This directory contains the currnent state of the bluetooth library implementation. The files include CircularBuffer.c/h, used for UART communication; RN4678.cpp/h, the main library file for the RN4678 bluetooth module; and RN4678_Command.h, a file containing all of the available bluetooth commands.

* Examples/
> This directory includes arduino sketches used to verify both the hardware and minor software usage in our design. These will allow basic back-and-forth, following PC -> USB -> Teesny -> UART -> RN4678 -> Bluetooth -> Phone

* TeesnyMain/
> This is the main directory of code running on the TeensyLC, TeensyMain.ino, and includes state machines and libraries used in our design.  

* Adafruit_SSD1306.cpp/h
> This is an open library by Adafruit designed for our OLED screen, based on the SSD1306 driver IC.

* FiniteStateMachine.cpp/h
> This is an old backup of the driving state machine of our microcontroller. The updated version is in TeensyMain/

* LED.cpp/h
> These files are basic LED drivers for arduino, and can be ignored.

* RN4678_Command.h
> This is a backup of the same file located in Bluetooth/. Both files include usage documentation inside

* TeensyMain.ino
> This is an old backup of the main arduino sketch within TeensyMain/, and can be ignored.
