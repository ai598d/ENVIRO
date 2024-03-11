
<h5><center> Freeway Wandarer </center></h5>

# Project Goal

* A wanderer bot that crosses a freeway of moving objects.

* Implement a state machine (see diagram) to acheive above objective.

* Implement multiple moving object(back and fourth) to create freeway.

* Implement a proportional controller to control wandarer direction.


![state](https://github.com/ai598d/ENVIRO/blob/main/states.png)

# Key Challenges

* Defining the requirement/architecture of state machine.
    * It's more managable to keep each state for one simple task.
* Trying to implement PID controller. 
    * Adding Integral and derivative terms makes thing more complicated. Out of scope for this project as it becomes for of a control theory problem. 

# Installation and Setup

* Installing Docker. [INSTRUCTION](https://github.com/sosper30/eep520-wi24/blob/main/week1/Lecture1_README.md) 

* Create working directory in your docker root

* Follow instruction here to initialize ENVIRO. [INSTRUCTION](https://github.com/sosper30/eep520-wi24/blob/main/week9/Lecture9-1_README.md)

* make sure [http://localhost](http://localhost ) is working and you can see the grey box.

* clone this repository into the working directory <code>git clone https://github.com/ai598d/ENVIRO.git </code>

# Run Project

* Change path part of <code> run_enviro.bat </code> to your current directory.

* run <code> run_enviro.bat </code> 

* execute command <code> make </code>

    * then execute <code>enviro </code>





