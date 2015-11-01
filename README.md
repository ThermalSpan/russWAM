# russWAM

This is my implementation of Warren's Abstract Machine (WAM.) This is a work in progress, expect it to be done in around a months time. My most important resource has been <a href="http://wambook.sourceforge.net">"Warren's Abstract Machine: A Tutorial Reconstruction"</a> by Hassan Aït-Kaci [1]. As the code base (read: documentation) grows, I will make it more explicit what segments drew heavily from his work.  

### How To:
You will need bison and flex installed. At the moment I have only built this on OSX, and it will require a newer version of bison than the one that's included. I suggest using <a href="http://brew.sh">Homebrew</a> for package management on OSX. You can use Homebrew to install the dependencies for this project.
```
brew install bison flex
```
The make file is setup to use the bison-3.0.4 keg, but if you have problems check the BISON variable in the makefile against the install location of bison on your computer. Assuming you don't run into problems, its as simple as cloning the repository and building it with make. 
```
git clone https://github.com/ThermalSpan/russWAM.git
cd russWAM
make
```
This will but an executable in the bin directory of the repository. Note that there is note a "make install" target at the moment so you will have to move the executable. Consider the following WAM code, based on figure 2.3 from [1]. It is saved in "rWAMfiles/fig23.rwam".
```
//  Based on Figure 2.3
label t/0:
write "Building Term"

put_structure h/2 3
set_variable 2
set_variable 5
put_structure f/1 4
set_value 5
put_structure p/3 1
set_value 2
set_value 3
set_value 4

write "Done building Term"
printHeap
terminate
```
We can then pass this to russWAM and we will see:
```
$ ./russWAMex < fig23.rwam
Input OK
"Building Term"
"Done building Term"
HEAP:
0	| STR: 1|
1	| h/2	|
2	| REF: 2|
3	| REF: 3|
4	| STR: 5|
5	| f/1	|
6	| REF: 3|
7	| STR: 8|
8	| p/3	|
9	| REF: 2|
10	| STR: 1|
11	| STR: 5|

```


### Online Resources

Notable links so far include:

<ul>
<li><a href="http://www.gamedev.net/page/resources/_/technical/general-programming/c-custom-memory-allocation-r3010"> C++ Custom Memory Allocation </a></li>
<li><a href="http://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/"> A Simple C++ Project Structure </a></li>
<li><a href="http://www.catb.org/esr/structure-packing/"> The Lost Art of Structure Packing </a></li>
<li><a href="https://isocpp.org/wiki/faq/dtors#overview-dtors"> Destructors FAQ </a></li>
<li><a href="http://stackoverflow.com/questions/18260876/in-a-warrens-abstract-machine-where-are-argument-variables-created"> SO: When are WAM Argument Variables created? </a></li>
<li><a href="http://www.gprolog.org/"> The GNU Prolog website </a></li>
</ul>

### License

This code is distributed under the MIT License. 
