module axle() {
   difference() {  
    difference() { 
    import("/home/armadilo/Documents/models/Sawppy_Rover/STL/8mm_shafts_axle.stl");
        translate([-21.5,0,12]) cube([10,10,10],center=true);
}
translate([15,0,12]) cube([10,10,10],center=true);
}      
}


module steering() {
    difference() { 
    difference() { 
    import ("/home/armadilo/Documents/models/Sawppy_Rover/STL/8mm_shafts_steering.stl");
     translate([-27,0,12]) cube([10,10,10],center=true);
    }
     translate([21.5,0,12]) cube([10,10,10],center=true);
}
}
translate([0,50,0]) rotate([0,90,0]) axle(); 
difference() { 
translate([0,30,0]) rotate([0,90,0]) steering();
   translate([3.5,30,20.5]) cut_ring();
}

module cut_ring() { 
    rotate_extrude(angle=360,convexity=2,$fn=100) 
    translate([3.1,0,0])
    square([1.0,1.0]);
}

translate([3.5,50,-3.25]) cut_ring();