STEPS TO RUN THE TOURING SYSTEM

If you compile all the cpp files in provided.zip with those in Project 4 Submission with the main.cpp file, you can use it to test the program.
main.cpp in provided.zip file implements a command-line interface, meaning that if you open a
Windows/macOS command shell (e.g., by typing “cmd.exe” in the Windows start box in the
bottom-left corner of the screen, or by running the Terminal app in macOS), and switch to the
directory that holds your compiled executable file, you can run the system.

From the Windows command line, for example, you can run the system with:
C:\PATH\TO\YOUR\CODE> BruinTour.exe c:\path\to\your\mapdata.txt c:\path\to\your\stops.txt
You must specify a path to the map data file and a path to a text file that you create which
specifies the stops on the tour, and for each stop, a line of commentary to be delivered once
that stop is reached. 

The stops.txt file must have the following format:
Point Of Interest #1 Name|Description of point of interest #1
Point Of Interest #2 Name|Description of point of interest #2
…
Point Of Interest #N Name|Description of point of interest #N

For example, here’s an example stops.txt file:
Ackerman Union|This is Ackerman where you buy stuff.
John Wooden Center|This is where you go to get swole.
Diddy Riese|They sell yummy cheap cookies here.
Ackerman Union|We're back at Ackerman, and this is the end of your tour.

main.cpp will take the files you passed on the command line and pass them to the main
classes so they can load the appropriate map data, generate routes between the various stops,
and produce tour commands. The code in main.cpp will then take the output from your classes
and print them to the screen like this:

Starting tour...
Welcome to Ackerman Union!
This is Ackerman where you buy stuff.
Proceed 0.028 miles north on a path
Take a left turn on Bruin Walk
Proceed 0.098 miles west on Bruin Walk
Take a right turn on a path
12
Proceed 0.074 miles north on a path
Welcome to John Wooden Center!
This is where you go to get swole.
Proceed 0.074 miles south on a path
Take a left turn on Bruin Walk
Proceed 0.043 miles east on Bruin Walk
Take a right turn on Westwood Plaza
Proceed 0.514 miles south on Westwood Plaza
Take a right turn on Le Conte Avenue
Proceed 0.097 miles west on Le Conte Avenue
Take a left turn on Broxton Avenue
Proceed 0.053 miles south on Broxton Avenue
Take a left turn on a path
Proceed 0.015 miles northeast on a path
Welcome to Diddy Riese!
They sell yummy cheap cookies here.
Proceed 0.015 miles southwest on a path
Take a right turn on Broxton Avenue
Proceed 0.053 miles north on Broxton Avenue
Take a right turn on Le Conte Avenue
Proceed 0.097 miles east on Le Conte Avenue
Take a left turn on Westwood Plaza
Proceed 0.514 miles northeast on Westwood Plaza
Take a right turn on Bruin Walk
Proceed 0.055 miles east on Bruin Walk
Take a right turn on a path
Proceed 0.028 miles south on a path
Welcome to Ackerman Union!
We're back at Ackerman, and this is the end of your tour.
Your tour has finished!
Total tour distance: 1.758 miles

(P.S mapdata.txt's geospatial data scope is limited to Westwood, West Los Angeles, West Hollywood, Brentwood, and Santa Monica
areas)
