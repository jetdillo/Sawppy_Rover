$fn=60;

use </home/armadilo/Documents/models/Sawppy_Rover/STL/baseplates.scad>;

module 2020_segment() { 
    import("/home/armadilo/Documents/models/2020_segment/2020_segment.stl",convexity=10);
}
module 2525_segment() {
    import("/home/armadilo/Documents/models/models/8020/Prototype_Smooth_Beams/files/General_Beam_smooth_6in-export.stl",convexity=10);
}

module brace_bracket() { 
import("/home/armadilo/projects/robots/sawppy/Sawppy_Rover/modifications/jetdillo/STL/BraceBracket.stl",convexity=10);
}

module fixed_knuckle() { 
    import("/home/armadilo/Documents/models/Sawppy_Rover/STL/Fixed\ Knuckle.stl",convexity=10);
}

module 2020_bracket() { 
difference() { 
import("/home/armadilo/Documents/models/20mm_8020_segment/files/2020_x_20mm-6in_export-onside.stl",convexity=10);

union() { 
translate([0,90,10]) rotate([45,0,0]) cube([40,40,100],center=true);
translate([0,-90,10]) rotate([-45,0,0]) cube([40,40,100],center=true);
}
}

}

module beam_anchor() { 
    difference() { 
    minkowski() { 
cube([30,30,90],center=true);
        sphere(2);
    }
cube([26,26,110],center=true);
}
}

module angled_beam_anchor(angles) { 
difference() { 
difference() { 
rotate([45,0,0]) { 
difference() { 
    minkowski() { 
cube([30,30,90],center=true);
        sphere(2);
    }
cube([27,27,110],center=true);
}
}


if (angles == 3) { 
union() { 
    translate([0,-20,40]) cube([40,60,40],center=true);
    translate([0,20,-40]) cube([40,60,40],center=true);
}
}
if (angles == 2) { 
     translate([0,-20,40]) cube([40,60,40],center=true);
}
if (angles == 1) { 
    translate([0,20,-40]) cube([40,60,40],center=true);
}
if (angles == 0) { 
    translate([0,20,-100]) cube([40,60,40],center=true);
}
}
{
for(i=[-9:9:9]) { 
    translate([0,0,i])  rotate([90,0,0]) cylinder(r=2.5,h=80,center=true,$fn=60);
    //cylinder(r=1.66,h=80,center=true,$fn=60);
}
}
}

}

module jetson_brace() { 

translate([0,-109,0]) rotate([180,0,0]) brace_bracket();
translate([0,-127,18]) angled_beam_anchor(3);


difference() { 
translate([0,-118,10]) rotate([45,0,0]) scale([1,1,1]) 2525_segment();
translate([0,-210,125]) cube([40,60,40],center=true);
}
    
translate([0,-205,100]) angled_beam_anchor(3);
}

//rotate([180,0,90]) brace_bracket();
//translate([0,-19,15]) angled_beam_anchor();


//jetson_brace();
//translate([0,-600,0]) rotate([0,0,180]) jetson_brace();

//translate([100,-300,118]) rotate([0,0,90]) halfplate();
/*
translate([0,-109,0]) rotate([180,0,0]) brace_bracket();
translate([0,-127,18]) angled_beam_anchor(3);
*/

translate([0,0,0]) rotate([180,0,0]) brace_bracket();
translate([0,-18,18]) angled_beam_anchor(3);


