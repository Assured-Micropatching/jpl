
Done by: Samuel Sarkisian | Mentor: Lini Mestar <br></br>
JPL | jpl.nasa.gov





<h1> <strong>1 -- Navigating Through Folders</strong></h1>
<h3>Example </h3>
<h4>challenge_problem_1-3</h4>
<h6> beaglebone_black & mpc5748g</h6>
<h6> before & after</h6>
<h6> C file & binary</h6>


<h1><strong> 2 -- Compilation & Running Process</strong></h1>

<h1>BeagleBone Black</h1>

<h3>Example </h3>

Compile command: gcc -o <u>binary_file_name</u> <u>file.c</u>

ex) gcc -o read_write_evaluate read_write_evaluate.c

Run command: sudo ./<u>binary_file_name</u>

ex) sudo ./read_write_evaluate


<h1>DEVKIT-MPC5748G </h1>

<h3>Example</h3>
<h6>Step 0</h6> Open S32 DESIGN STUDIO IDE
<h6>Step 1</h6> Go to File -> New -> S32DS Project from Example
<h6>Step 2 </h6> Go into S32DS Examples Projects folder -> MPC5748G
<h6>Step 3</h6> Open hello folder and choose hello then click finish
<h6>Step 4</h6>  Open project Explorer and you should see hello_Z4_1, hello_Z4_2, hello_Z4_3
<h6>Step 5</h6> Go into hello_Z4_1 then navigate to src and open hello_Z4_1.c
<h6>Step 6</h6> Go a head and copy the code provide to you by JPL and paste it in hello_Z4_1.c while highlighting the whole previous original content of hello_Z4_1.c. Save it
<h6>Step 7</h6> Go to debug -> debug Configuration and pick the project you want to compile/debug/run, which in this case the files's name should be hello_Z4_1_Debug
<h6>Step 8</h6>  During this process your board needs to be connected
<h6>Step 9</h6> As the build process is done you will need to press the resume button at the topleft, which will allow the program to run.
<h6>Step 10</h6> When finished make sure to press the terminate button

<h1><strong>3 -- Expected Operation & Output</strong></h1>
<h6>Note for MPC5748G* You will know that the program has started when the red led (DS4) turns on and you will know the program is done when the red led (DS4) turns off</h6>

<h2> Challenge Problem 1 -- CSC Patching</h2>
<h6>Before -> write in one physical address and read from it</h6>
<h6>After -> change the physical address from before to after</h6>
<h2> Challenge Problem 2 -- Removing Logic</h2>
<h6>Before -> check the time that it takes with the memory test</h6>
<h6>After ->check the time that it takes without the memory test by removing the logic </h6>
for the beaglebone it is imidiate whithout the memory test and with the memory test it is 3-4 seconds<br></br>
for the MPC5748G it is 00:00.30 seconds whithout the memorytest and with the memory test for the small chunk of RAM it is 00:00.57 seconds<br></br>
<h2> Challenge Problem 3 -- Modifying Logic</h2>
<h6> Before -> Create a memory test by writing the the exact name of the physical address in the physical address and reading from it</h6>
<h6>After -> Change the memory test from writing the the exact name of the physical address in the physical address and reading from it to checkerboard</h6>
