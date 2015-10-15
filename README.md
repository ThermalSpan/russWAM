# russWAM

This is my implementation of Warren's Abstract Machine (WAM.) This is a work in progress, expect it to be done in around two months time. My most important resource has been <a href="http://wambook.sourceforge.net">"Warren's Abstract Machine: A Tutorial Reconstruction"</a> by Hassan Aït-Kaci. As the code base (read: documentation) grows, I will make it more explicit what segments drew heavily from his work.  

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
This will but an executable in the bin directory of the repository. This executable will take in WAM code and evaluate it. For example, consider the following WAMcode:
```
iblahhhh
```
We can then pass this to the executable using.  
```
./russWAMex test.wam
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
