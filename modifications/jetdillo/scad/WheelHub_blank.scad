 import("/home/armadilo/Documents/models/Sawppy_Rover/STL/Wheel Hub.stl",convexity=10);
 translate([3,0,0]) rotate([0,0,180]) cylinder(r=17,h=10,$fn=3);
 
 translate([11.5,0,5]) cube([5,10,8],center=true);