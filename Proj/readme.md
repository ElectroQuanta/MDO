- [Preamble](#orga82dd0d)
- [Versions <code>[1/1]</code>](#orgfdce8f7)
- [Diagrams](#org6768d04)
  - [PlantUML](#org35199da)
    - [Setup <code>[0/6]</code>](#orgd95e076)
    - [Workflow <code>[0/4]</code>](#orge682da0)
    - [Sequence diagrams](#org6946445)



<a id="orga82dd0d"></a>

# Preamble

-   This folder contains all the information about the project.
-   It is written incrementally, i.e., as the several project phases take place, the document versions pertaining to each phase are stored in the folder **submission**.


<a id="orgfdce8f7"></a>

# Versions <code>[1/1]</code>

1.  [X] Problem statement: deadline - <span class="timestamp-wrapper"><span class="timestamp">&lt;2021-10-28 qui&gt;</span></span>


<a id="org6768d04"></a>

# Diagrams

Diagrams can be drawn using <code>[2/2]</code>:

-   [X] draw.io
    -   User mockups
    -   State-machine
-   [X] [PlantUML](#org35199da) (stored in Proj/diags/plantuml)
    -   Sequence diagram
    -   Class diagram


<a id="org35199da"></a>

## PlantUML

[PlantUML](https://plantuml.com/) is a tool for quickly drawing diagrams from text based descriptions. It is specially adequate for sequence diagrams, as draw.io is not very fluid.


<a id="orgd95e076"></a>

### Setup <code>[0/6]</code>

1.  [ ] Download PlantUML from the [website](https://sourceforge.net/projects/plantuml/files/plantuml.jar/download): `plantuml.jar`
2.  [ ] Place the `plantuml.jar` file into a known directory and add it to the path
3.  [ ] Write a diagram text file in an extension `.pu` (example input/test.pu) - check the user manual for this
4.  [ ] Navigate to the `input` folder using cd
5.  [ ] Generate the diagram from the terminal using:
    
    ```bash
    java -jar plantuml.jar test.pu -o ../output/
    ```
6.  [ ] Check the generate png file: `output/test.png`


<a id="orge682da0"></a>

### Workflow <code>[0/4]</code>

1.  [ ] Write a diagram text file in an extension `.pu` (example input/test.pu) - check the user manual for this
2.  [ ] Navigate to the `input` folder using cd
3.  [ ] Generate the diagram from the terminal using:
    
    ```bash
    java -jar plantuml.jar test.pu -o ../output/
    ```
4.  [ ] Check the generate png file: `output/test.png`


<a id="org6946445"></a>

### Sequence diagrams

1.  Declaring participants

    If the keyword participant is used to declare a participant, more control on that participant is possible.
    
    The order of declaration will be the (default) order of display.
    
    Using these other keywords to declare participants will change the shape of the participant representation:
    
    1.  actor
    2.  boundary
    3.  control
    4.  entity
    5.  database
    6.  collections
    7.  queue
    
    ![img](diags/plantuml/seq-diag/examples/decl-partic.png)

2.  Change arrow style

    You can change arrow style by several ways:
    
    1.  add a final x to denote a lost message
    2.  use \\ or / instead of < or > to have only the bottom or top part of the arrow
    3.  repeat the arrow head (for example, >> or //) head to have a thin drawing
    4.  use &#x2013; instead of - to have a dotted arrow
    5.  add a final "o" at arrow head
    6.  use bidirectional arrow <->
    
    ![img](diags/plantuml/seq-diag/examples/arrow-style.png)

3.  Grouping messages

    ([src](https://plantuml.com/sequence-diagram#425ba4350c02142c))
    
    It is possible to group messages together using the following keywords:
    
    1.  alt/else
    2.  opt
    3.  loop
    4.  par
    5.  break
    6.  critical
    7.  group, followed by a text to be displayed
    
    It is possible to add a text that will be displayed into the header (for group, see next paragraph 'Secondary group label').
    
    The end keyword is used to close the group.
    
    Note that it is possible to nest groups.
    
    ![img](diags/plantuml/seq-diag/examples/group-msg.png)

4.  Notes on messages

    It is possible to put notes on message using the note left or note right keywords just after the message.
    
    You can have a multi-line note using the end note keywords.
    
    ![img](diags/plantuml/seq-diag/examples/notes-msgs.png)

5.  Divider or separator

    If you want, you can split a diagram using == separator to divide your diagram into logical steps.
    
    ![img](diags/plantuml/seq-diag/examples/divider.png)

6.  Lifeline activation and destruction

    The `activate` and `deactivate` are used to denote participant activation.
    
    Once a participant is activated, its lifeline appears.
    
    The activate and deactivate apply on the previous message.
    
    The `destroy` denote the end of the lifeline of a participant.
    
    ![img](diags/plantuml/seq-diag/examples/lifeline.png)

7.  Participant creation

    ![img](diags/plantuml/seq-diag/examples/partic-creation.png)

8.  Incoming and outgoing messages

    You can use incoming or outgoing arrows if you want to focus on a part of the diagram.
    
    Use square brackets to denote the left "[" or the right "]" side of the diagram.
    
    ![img](diags/plantuml/seq-diag/examples/in-out-msgs.png)

9.  Anchors and duration

    With `teoz` it is possible to add anchors to the diagram and use the anchors to specify duration time.
    
    ![img](diags/plantuml/seq-diag/examples/anchors-duration.png)
    
    You can use the -Pcommand-line option to specify the pragma:
    
    ```bash
    java -jar plantuml.jar -Pteoz=true
    ```

10. Participants encompass

    It is possible to draw a box around some participants, using box and end box commands.
    
    You can add an optional title or a optional background color, after the box keyword.
    
    ![img](diags/plantuml/seq-diag/examples/partic-encompass.png)

11. Remove foot boxes

    You can use the `hide footbox` keywords to remove the foot boxes of the diagram.
    
    ![img](diags/plantuml/seq-diag/examples/remove-foot-box.png)

12. Style `strictuml`

    To be conform to strict UML (for arrow style: emits triangle rather than sharp arrowheads), you can use:
    
    ![img](diags/plantuml/seq-diag/examples/strict-uml.png)

13. Color a group message

    It is possible to color a group message:
    
    ![img](diags/plantuml/seq-diag/examples/color-group-msg.png)

14. Colors

    You can use specify **fill** and **line** colors either:
    
    1.  with its standard name or CSS name
    2.  using HEX value (6 digits): #RRGGBB
    3.  using HEX value (8 digits) with alpha compositing or RGBA color model: \#RRGGBBaa
    4.  using short HEX value (3 digits): #RGB
    
    ![img](diags/plantuml/seq-diag/examples/colors.png)
