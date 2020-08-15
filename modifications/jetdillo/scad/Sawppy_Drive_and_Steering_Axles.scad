module new_cut_axle() { 
     import("/home/armadilo/projects/robots/sawppy/Sawppy_Rover/STL/new_cut_axle.stl");
}

module bogie_shaft_axle() { 
    import("/home/armadilo/Documents/models/Sawppy_Rover/STL/8mm_shafts_bogie_pivot_shaft.stl");
}
module rocker_shaft_axle() { 
    import("/home/armadilo/Documents/models/Sawppy_Rover/STL/8mm_shafts_rocker_pivot_shaft.stl");
}

//translate([10,0,0]) rotate([0,-90,0]) new_cut_axle();
//translate([10,0,0]) cylinder(r=4,h=50,$fn=100);

module axle(wheel_detent,motor_detent,wheel_ring_z,motor_ring_z,detent_size) {
 difference() { 
  difference() { 
   difference() {  
    difference() { 
    union() { 
    import("/home/armadilo/Documents/models/Sawppy_Rover/STL/8mm_shafts_axle.stl");
        translate([0,0,20]) cylinder(r=4,h=4,$fn=100);
        translate([0,0,38]) cylinder(r=4,h=4,$fn=100);
    }
       translate([-8,0,wheel_detent]) cube([10,10,detent_size],center=true);
}
translate([-8,0,motor_detent]) cube([10,10,detent_size],center=true);
}
translate([0,0,wheel_ring_z]) cut_ring();
}
translate([0,0,motor_ring_z]) cut_ring();
}
}

module steering_axle(steering_detent_z,servo_detent_z,servo_ring,wheel_ring,detent_size) { 
 difference() { 
  difference() { 
    difference() {  
    difference() { 
        cylinder(r=4,h=61,$fn=100);
       translate([-8,0,steering_detent_z]) cube([10,10,detent_size],center=true);
}
translate([-8,0,servo_detent_z]) cube([10,10,detent_size],center=true);
}      
 translate([0,0,servo_ring]) cut_ring();
}
  translate([0,0,wheel_ring]) cut_ring();
}
}

//translate([20,0,0]) cut_ring();

//translate([0,0,50]) rotate([0,180,0]) axle(40,2.5,9.25,28.5,10);

//translate([0,0,61]) rotate([0,180,0]) steering_axle(54,2.5,9.25,46,7);

module no_detent_shaft(shaft_ring1,shaft_ring2,shaft_ring3,shaft_length) { 
    
    difference() { 
             cylinder(r=4,h=shaft_length,$fn=100);
             union() { 
              translate([0,0,shaft_ring1]) cut_ring();
              translate([0,0,shaft_ring2]) cut_ring();
              translate([0,0,shaft_ring3]) cut_ring();
             }
    }
  //  translate([10,0,46]) cylinder(r=4,h=35,$fn=100);
   // translate([10,0,5]) cylinder(r=4,h=40,$fn=100);
}

//translate([10,0,0]) 
no_detent_shaft(2,43.5,79,84);
//no_detent_shaft(2,23.5,61.0,66.5);
//translate([20,0,32]) rotate ([0,-90,0]) bogie_shaft_axle();
%translate([10,0,3.5]) cylinder(r=4,h=20);
%translate([10,0,25]) cylinder(r=4,h=37.5);
%translate([-10,0,3.5]) cylinder(r=4,h=40);
%translate([-10,0,45]) cylinder(r=4,h=35);
//translate([20,0,40]) rotate ([0,-90,0]) rocker_shaft_axle();

module cut_ring() { 
    rotate_extrude(angle=360,convexity=2,$fn=100) 
    translate([3.1,0,0])
    square([1.0,1.5]);
}

//translate([3.5,50,-3.25]) cut_ring();

