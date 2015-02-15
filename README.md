# Matlab Emulator

A collection of different emulators for both MDPs and POMDPs interfaced to Matlab. Some of them might be pure Matlab implementations, while others are just interfaced to Matlab.

## Installation

To install the package just clone the repository and add it to your Matlab classpath by using the command
`addpath(genpath('<downloadPath>/MatlabEmulators'));`

Some of the emulators require additional steps to be installed properly as described in each individual section below. For any of the packages which work with external C++ libraries there is a *class_handle.hpp* header file which allows C++ objects to presist between Matlab mex calls and can be downloaded from the [Matlab FileExchange](http://www.mathworks.com/matlabcentral/fileexchange/38964-example-matlab-class-wrapper-for-a-c++-class). It is suggested to copy this file to your system path, as it might be required for the mex compilation of more than one of the emulators. On Linux machine the search paths are described [here](https://gcc.gnu.org/onlinedocs/cpp/Search-Path.html). If not you will need to edit each of the functions which compiles any mex files and add to the include path the location where you have stored the file. 

### ALE - Agent Learning Environment - tested for version 0.4.4

1. Download the most recent version of ALE from the [official ALE webpage](http://www.arcadelearningenvironment.org/downloads/)
2. Compile the library usinge make as described in the *manual.pdf*
3. Make sure the project is added to the Matlab path 
3. In Matlab change the working directory to *MatlabEmulators/ale* folder and run *aleMex.m*, by  editing accordingly the script to where you downloaded and compiled the ALE project. **[Requires *class_handle.hpp* to be on the include path]**
4. Copy the ALE library *libale.so* from the location where you compiled the project to `<Matlab Install Dir>/extern/lib/<platform>/`
5. Run the *aleTest.m* script to confim that the insallation was correct. All supported game's ROMs are included in the package. If you want at this point you can delete the downlaoded ALE project.
6. Done!

## Usage

TODO: Write usage instructions

## Contributing

If you want to help us by developing more emulators for Matlab, you can simply extend the **AbstractEmulator** class in Matlab and develop your own. This would make it consistent with the interface and easier to plug in.

## History

TODO: Write history

## Credits

TODO: Write credits

## License

TODO: Write license
