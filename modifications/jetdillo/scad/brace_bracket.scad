module bracebracket() { 
import("/home/armadilo/projects/robots/sawppy/Sawppy_Rover/modifications/jetdillo/STL/BraceBracket.stl",convexity=10);
}

difference() { 
bracebracket();
    cube([60,60,15],center=true);
}