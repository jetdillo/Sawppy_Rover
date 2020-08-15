use </home/armadilo/Documents/models/Sawppy_Rover/STL/baseplates.scad>;

module jetson_shell_blank() { 
scale([1,1,40]) fullplate();
}

module jetson_shell() { 
difference() { 
    camper_shell();
    translate([0,0,-5]) scale([0.97,0.97,0.97])  camper_shell();
}
}

module camper_shell() { 
difference() { 
difference() { 
jetson_shell_blank();
union() { 
translate([90,0,180]) rotate([0,45,0]) cube([400,500,50],center=true);
translate([-90,0,180]) rotate([0,-45,0]) cube([400,500,50],center=true);
}
}
union() { 
translate([0,290,45]) rotate([-45,0,0]) cube([400,500,50],center=true);
translate([0,-290,45]) rotate([45,0,0]) cube([400,500,50],center=true);
}
}
}

difference() { 
 jetson_shell();
 translate([0,320,0]) cube([500,500,250],center=true);
}
    
