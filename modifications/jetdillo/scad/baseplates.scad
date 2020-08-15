module halfplate() { 

import("/home/armadilo//projects/robots/sawppy/Sawppy_Rover/modifications/jetdillo/STL/half_baseplate.stl",convexity=10);
}
module jetson_plate() { 
import("/home/armadilo/Documents/models/Jetson_For_Donkey/files/plate.stl");
}

module legs_plate() { 
    import("/home/armadilo/Documents/models/Jetson_For_Donkey/files/fourLegsCamMount.stl");
}

module bracebracket() { 
import("/home/armadilo/projects/robots/sawppy/Sawppy_Rover/modifications/jetdillo/STL/BraceBracket.stl",convexity=10);
}

module fullplate() { 
union() { 
halfplate();
rotate([0,0,180]) halfplate();
}
}
module quarterplate(side) { 
difference() { 
halfplate();
if (side==0) {
cube([400,200,10],center=true);
}
if (side==1) { 
    cube([400,400,10]);
}
if (side==2) { 
   translate([-300,-180,0]) cube([300,400,10]);
}
}
/*
translate([-70,208,0]) rotate([0,0,180]) difference() { 
  bracebracket();
   translate([0,-22.5,0]) cube([60,60,60],center=true);
}
translate([70,208,0]) rotate([0,0,180]) difference() { 
  bracebracket();
   translate([0,-22.5,0]) cube([60,60,60],center=true);
}
*/
}

module notched_quarterplate() { 
difference() { 
quarterplate(0);
    translate([0,200,0])cube([32,52,10],center=true);
}
}


module notched_shorterplate() {
difference() {  
difference() { 
        halfplate();
        cube([400,75,10],center=true);
    }
    translate([0,200,0])cube([32,52,10],center=true);
}
}

module notched_halfplate() { 
    difference() { 
        halfplate();
        translate([0,200,0])cube([32,52,10],center=true);
    }
    
}

module plate_ribs()  {
difference() {
fullplate();
cube([260,400,10],center=true);
}
}

module hinged_shorterplate() {
difference() {
difference() {  
difference() { 
        halfplate();
        cube([400,75,10],center=true);
    }
    translate([0,200,0])cube([32,52,10],center=true);
}
%translate([0,175,0]) cube([400,78,10],center=true);
}
}

//notched_quarterplate();
//quarterplate(0);
//notched_shorterplate();
//notched_halfplate();
//translate([0,100,0]) rotate([0,0,90]) jetson_plate();

hinged_shorterplate();