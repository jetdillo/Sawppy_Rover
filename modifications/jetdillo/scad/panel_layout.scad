cube([330,89.206,2.54],center=true);

module atmega() { 
import("/home/armadilo/Documents/models/ATMEGA_2560_bracket/files/Arduino_Mega_-_holder.stl");
}

module rocker_body_mount() { 
 import("/home/armadilo/Documents/models/Sawppy_Rover/STL/Rocker\ Body\ Mount.stl");
}
module motor_driver() { 
    import("/home/armadilo/Documents/models/L298N/files/motor_driver_scaled_and_centered.stl");
}

translate([110,0,0]) rotate([0,0,90]) atmega();
 translate([40,0,0]) rotate([0,90,90])  rocker_body_mount();
translate([-55,0,1]) rotate([0,0,180]) motor_driver();
translate([-100,0,1]) rotate([0,0,180]) motor_driver();
translate([-145,0,1]) rotate([0,0,180]) motor_driver();



translate([0,100,0]) cube([64.5,89.2,2.54]);
translate([30,150,5]) rotate([0,0,180]) motor_driver();
//translate([35,150,0]) rotate([0,0,90]) atmega();
translate([-208,200,0]) cube([208,89.2,2.54]);
/*
translate([-55,250,1]) rotate([0,0,180]) motor_driver();
translate([-100,250,1]) rotate([0,0,180]) motor_driver();
translate([-145,250,1]) rotate([0,0,180]) motor_driver();
*/
