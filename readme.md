- [Preamble](#org4ed5ceb)
  - [Doc struct <code>[8/8]</code>](#orgb1ed2bd)
- [Project](#orgea36d3d)
  - [Requirements](#orge00c2a7)
  - [Problem statement](#org1aff61c)
  - [Research](#orgbaff4ea)
    - [Topics <code>[0/3]</code>](#org67a81f4)
    - [Marketing Digital Outdoor](#org34efc2e)
  - [Report](#org14809c5)
    - [Outline <code>[0/7]</code>](#orgcc6235b)
- [Tools](#orgf2be94b)
  - [Project management](#orgf93afc9)
  - [Software](#orga797a6c)
- [Work Assignments](#orgdafa900)
  - [1](#org797dace)
    - [Problem statement](#org14760e4)
    - [Market research](#orgeeab8bc)
    - [Requirements & Constraints](#orga9e3ca6)
    - [Design](#org6d18248)



<a id="org4ed5ceb"></a>

# Preamble

This repository contains all the info related to ESRG Semester 1.


<a id="orgb1ed2bd"></a>

## Doc struct <code>[8/8]</code>

-   [X] Preamble: introduces the main aspects about the ESRG Semester 1.
-   [X] Project: contains the project requirements, notes, deadlines, etc.
-   [X] Tools: presents the required tools for this course.
-   [X] Work Assignments: contains the info related to the assignments given during this semester.


<a id="orgea36d3d"></a>

# Project


<a id="orge00c2a7"></a>

## Requirements

-   buildroot
-   c/c++ (both)
-   Device drivers
-   Linux/Raspberry Pi
-   CPS: Cyber-physical systems
-   Makefiles


<a id="org1aff61c"></a>

## Problem statement

Think about the project and deliver a document about it.


<a id="orgbaff4ea"></a>

## Research


<a id="org67a81f4"></a>

### Topics <code>[0/3]</code>

-   [ ] Cyber-physical systems characteristics: <span class="underline">identify the required features for the system</span>
-   [ ] Analyze previous projects to understand what is feasible in terms of Real-time systems using device drivers with Raspberry Pi: <span class="underline">gives an overall idea of what can be achieved</span>
-   [ ] Situate the project requirements, the project constraints


<a id="org34efc2e"></a>

### Marketing Digital Outdoor

1.  Topics

    1.  Motivation and context
        -   Scenting marketing is a great approach to draw people into stores.
        -   Scent sense is the fastest way to the brain, thus, providing an exceptional opportunity for marketing.
        -   Combining that with additional stimuli, like eye and earing, can significantly boost the marketing outcome.
            
            > -   Knowing your target audience it is critical for the success of stores.
            > -   Marketing can be used to collect, analyse, investigate and decide the best politics for addressing a specific target audience, understanding the its behavioral patterns.
            > -   To understand behavioral patterns <span class="underline">machine-learning models</span> can be used.
    2.  Concept
        -   Offer a marketing digital outdoor for brands to advertise and captivate customers
        -   Brands can buy advertisement space and time by sending the following data:
            
            |                         |               |           |          |              |      |
            |------------------------ |-------------- |---------- |--------- |------------- |----- |
            | Digital Outdoor location | Fragrance name | Start Time | Stop Time | Audio Message | Video |
            
            -   The brands can send the data to our company database through our website/application.
            -   The data will then be sent to the marketing digital outdoor using a wireless communication technology.
        -   The advertisement data will be exposed into a display, an audio message transmitted, as well as the indicate fragrance between the designated time interval.
        -   COVID pandemics changed the perspectives about user interaction with the surroundings, with non touch interfaces being preferred. Thus, a non touch user interface is a must have.
        -   When a user approaches the marketing digital outdoor, a proximity sensor will detect it and activate the <span class="underline">user interaction mode</span>.
            -   When activating this mode the camera is started mirroring the user into the display and providing additional options.
            -   In this mode, the user can:
                1.  apply image filters related to the brand
                2.  take pics
                3.  create GIFs
                4.  share them
            -   This mode requires:
                -   Facial recognition for image filter application
                -   Hand gesture recognition for navigating the menus and activating options
                -   A virtual keyboard (non-touch) will be provided for user input, by mapping the screen to the keys and waiting for a designated time before accepting it.
                -   A set of hand gestures to be used in user interaction
            -   Several sharing platforms shall be provided namely social media and email.
                -   Tracking the nr of shares provides feedback for the brands in respect of the brand awareness.
                -   Additionally, brands can also monitor this by checking their social media accounts.

2.  Technologies <code>[0/11]</code>

    1.  [ ] Computer vision for facial and gesture recognition (OpenCV)
    2.  [ ] Database for marketing digital outdoor management (SQL)
    3.  [ ] Website/Application for brands communication to our database
    4.  [ ] Wireless communication technology for remote communication with digital outdoors
    5.  [ ] Image filter application
    6.  [ ] Infrared detection
    7.  [ ] Camera recording
    8.  [ ] Audio output
    9.  [ ] Nebulizer technology for scenting
    10. [ ] Screen mapping to keys for virtual keyboard
    11. [ ] Social media and e-mail sharing APIs

3.  ✔ DONE Problem statement

4.  Market research <code>[0/3]</code>

    1.  [ ] Scenting marketing: trends, market value
    2.  [ ] Digital Outdoors: quantity, market value
    3.  [ ] Combined marketing: are they digital outdoor + scenting?

5.  Project planning

    1.  Required HW <code>[3/7]</code>
    
        -   [X] Raspberry Pi 4
        -   [ ] HDMI screen: <https://pt.aliexpress.com/item/33005274109.html?spm=a2g0o.detail.1000013.3.38072ea5MrfWq9&gps-id=pcDetailBottomMoreThisSeller&scm=1007.13339.169870.0&scm_id=1007.13339.169870.0&scm-url=1007.13339.169870.0&pvid=e1784609-f2f3-4547-9d9e-d5461fddc4c8&_t=gps-id:pcDetailBottomMoreThisSeller,scm-url:1007.13339.169870.0,pvid:e1784609-f2f3-4547-9d9e-d5461fddc4c8,tpp_buckets:668%232846%238110%231995&&pdp_ext_f=%7B%22sceneId%22:%223339%22,%22sku_id%22:%2212000023440173741%22%7D>
        -   [ ] Relay/Transistor + Ultrassonic actuator for nebulizing fragrance
        -   [ ] Audio output
        -   [X] Power supply
        -   [X] Mechanical structure
        -   [ ] Camera
        
        Research link: <https://www.one-tab.com/page/TZxmVAXJTO6nVyNO593ARA>


<a id="org14809c5"></a>

## Report


<a id="orgcc6235b"></a>

### Outline <code>[0/7]</code>

1.  [ ] Introduction
    1.  Problem statement
    2.  Motivation and context
    3.  Market research
    4.  Goals
    5.  Report outline
2.  [ ] Analysis
    1.  Background and state of the art
    2.  Requirements and constraints
    3.  System overview
    4.  System architecture
        1.  HW architecture
        2.  SW architecture
    5.  Subsystems decomposition
        1.  Events
        2.  Use cases
        3.  State machine diagram
        4.  Sequence diagram
    6.  Project planning and budget
3.  [ ] Design
    1.  HW specification
        1.  Block diagram with COTS components, if possible
        2.  List of constraints of functions to be implemented in HW or SW
    2.  HW interfaces definition
        1.  I/O ports
        2.  HW registers
        3.  Memory addresses for shared or I/O by memory mapping
        4.  HW interrupts
    3.  SW specification
        1.  Identify main subsystems
        2.  System tasks
    4.  SW interfaces definition
        -   Define the APIs in detail:
            -   header files with:
                -   functions prototypes
                -   data structure declarations
                -   class declarations
    5.  Start-up/shutdown process specification
    6.  Error Handling specification
4.  [ ] Implementation
5.  [ ] Testing
6.  [ ] Verification/Validation
7.  [ ] Conclusions


<a id="orgf2be94b"></a>

# Tools


<a id="orgf93afc9"></a>

## Project management

1.  Latex:
    -   Overleaf
    -   Linux
        
        ```bash
        sudo apt install texlive-latex-extra # basic
        sudo apt install texlive-xetex # compiler
        sudo apt install tex-lang-portuguese # lang
        sudo apt install texlive-science # 
        ```
2.  Git:
    1.  code
    2.  doc
    3.  readme
    4.  writing
        
        ```bash
        sudo apt install git
        ```
3.  Diagram Tool:
    1.  Draw.io
    2.  Block diagram
    3.  Flowcharts
    4.  Class Diagram
    5.  Sequence diagram
    6.  State-machine diagram
    7.  Deployment diagram
4.  Gantt diagram: project management
    1.  Define the project outline
    2.  Tool: Project Libre: <https://www.projectlibre.com/>
5.  Doxygen: source code documentation


<a id="orga797a6c"></a>

## Software

1.  Linux
2.  Buildroot
3.  Raspberry Pi 4B
4.  Ethernet cable
5.  SD card reader
6.  USB-to-serial converter: boot process
7.  Makefiles


<a id="orgdafa900"></a>

# Work Assignments


<a id="org797dace"></a>

## 1


<a id="org14760e4"></a>

### Problem statement

Design a remote control with three buttons that can remotely control the television (TV). It should be very light, powered by batteries and controls your TV via an infrared emitter. The TV has a built-in infrared receiver. A button on the remote control switches the TV on/off and will be labeled with the word "Power". The other two buttons are used to scroll up/down and select the available channels and they are labeled with the arrows up/down.


<a id="orgeeab8bc"></a>

### Market research

-   Brief description of a remote TV control
-   Bill of materials
-   Unit cost
-   Time to market
-   Sales/Quantity of sold items anually


<a id="orga9e3ca6"></a>

### Requirements & Constraints

1.  Requirements

    -   Remotely operated
    -   Low weight
    -   Powered by batteries
    -   3 buttons:
        1.  Power
        2.  Up
        3.  Down
    -   Infrared emitter response time (system output response time): 100 ms
    -   The TV remote may be upgraded in the future to use more buttons

2.  Constraints

    -   Contains an infrared emitter (the TV already has an infrared receiver)
    -   The TV remote control must supply the required data frames imposed by the TV manufacturer
    -   Data frames may not be provided by the client
    -   Security concerns are defined by the data frames and the specific communication frequency imposed by the TV manufacturer
    -   1 week deadline: 14 h
    -   2 people
    -   Budget:
        -   HW (parts acquisition and assembly): fixed costs &#x2014; 1 EUR/unit
            -   TV remote Shell
            -   TV remote membrane
            -   LED
            -   Data acquisition & Infrared emitter PCB
        -   Development: project
            -   20 EUR per hour per person: 20 \* 14 \* 2 = 560 EUR + IVA


<a id="org6d18248"></a>

### Design

1.  HW specification

    -   Block diagram with COTS components, if possible
    -   List of constraints of functions to be implemented in HW or SW
        -   Inclusion of a multiplexer may reduce SW burden
        -   CPU peripherals:
            -   PCA for wave generation

2.  HW interfaces definition

    -   I/O ports
    -   HW registers
    -   Memory addresses for shared or I/O by memory mapping
    -   HW interrupts

3.  SW specification: Top-down methodology

    1.  Identify main subsystems
        1.  Signal input detector
        2.  Event handler
        3.  Output generator

4.  SW interfaces definition

    -   Define the APIs in detail:
        -   header files with:
            -   functions prototypes
            -   data structure declarations
            -   class declarations

5.  Start-up/shutdown process specification

6.  Error handling specification

    -   Create error-handling routines
    -   Watchdog timer can be used for system recovery

7.  Design verification
