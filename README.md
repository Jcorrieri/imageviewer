# PPM Image Viewer
Reads a .ppm image and displays it. The bash script passes the filename argument to the C++ script, compiles, and runs the program. SFML is utilized to display the image, but the file contents, including pixel RGB values,
are read manually. 

*Note: The image must be in raw binary format (not ASCII) for the program to work properly. 

## Usage
```./run.sh image.ppm```
