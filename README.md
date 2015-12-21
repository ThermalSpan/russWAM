# russWAM

This is my implementation of Warren's Abstract Machine (WAM.) This is a work in progress. My most important resource has been <a href="http://wambook.sourceforge.net">"Warren's Abstract Machine: A Tutorial Reconstruction"</a> by Hassan Aït-Kaci [1]. As the code base (read: documentation) grows, I will make it more explicit what segments drew heavily from his work.  

### How To:
You will need bison, flex, and GNU Prolog installed. At the moment I have only built this on OSX, and it will require a newer version of bison than the one that's included. I suggest using <a href="http://brew.sh">Homebrew</a> for package management on OSX. You can use Homebrew to install the dependencies for this project.
```
brew install bison flex gnu-prolog
```
The make file is setup to use the bison-3.0.4 keg, but if you have problems check the BISON variable in the makefile against the install location of bison on your computer. Assuming you don't run into problems, its as simple as cloning the repository and building it with make. 
```
git clone https://github.com/ThermalSpan/russWAM.git
cd russWAM
make
```
This will put an executable in the bin directory of the repository. The executable needs a prolog source file as an argument. It will run the predicate named "query," if it exists. Consider the following prolog program: 
```
fruit(apple).
fruit(orange).
fruit(banana).
fruit(tomato).

vegetable(cucumber).
vegetable(carrot).

query(X) :- fruit(X).
```
We can then pass this to russWAM and we will see:
```
$ ./russWAMex plants.pl
Input: plants.pl
pl2wam generated plants.wam
Parsed Succesfully
yes.
apple
orange
banana
tomato
```
Internally, it uses GNU Prolog's pl2wam utility to compile the prolog source into WAM code. This implementation is far from complete, but it should be robust enough to warn you if it can't handle something instead of crashing. 

### Online Resources

Notable links so far include:

<ul>
<li><a href="http://www.gamedev.net/page/resources/_/technical/general-programming/c-custom-memory-allocation-r3010"> C++ Custom Memory Allocation </a></li>
<li><a href="http://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/"> A Simple C++ Project Structure </a></li>
<li><a href="http://www.catb.org/esr/structure-packing/"> The Lost Art of Structure Packing </a></li>
<li><a href="https://isocpp.org/wiki/faq/dtors#overview-dtors"> Destructors FAQ </a></li>
<li><a href="http://stackoverflow.com/questions/18260876/in-a-warrens-abstract-machine-where-are-argument-variables-created"> SO: When are WAM Argument Variables created? </a></li>
<li><a href="http://www.gprolog.org/"> The GNU Prolog website </a></li>
<li><a href="http://stackoverflow.com/questions/19459516/unification-algorithm-example-in-wam-warrens-abstract-machine"> SO: Unification Algorithm Example </a></li>
<li><a href="http://lists.gnu.org/archive/html/users-prolog/2015-11/threads.html">GNU Prolog Mailing List 11/22/15</a></li>
<li><a href="http://www.sciencedirect.com/science/article/pii/0743106694900310"> The wonder years of sequential Prolog implementation </a></li>
</ul>

### License

This code is distributed under the MIT License. 
