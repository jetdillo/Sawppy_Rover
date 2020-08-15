$fn=80;

module lidar_mount(){ 
import("/home/armadilo/Documents/models/XV11_mount/XV11_Lidar_Base_v4.stl");
}

module bracebracket() { 
import("/home/armadilo/projects/robots/sawppy/Sawppy_Rover/modifications/jetdillo/STL/BraceBracket.stl");
}

module angle_bracebracket(angle) { 

rotate([180,0,0]) bracebracket();

translate([0,0,-2]) minkowski() { 
difference() { 
    translate([0,0,10]) cube([28,50,20],center=true);
    translate([0,-15,30]) rotate([angle,0,0]) cube([100,100,40],center=true);
}
sphere(1);
}
}

module lidar_brace_bracket(angle) { 
angle_bracebracket(angle);
translate([0,0,45]) rotate([angle,0,0]) lidar_mount();
}

lidar_brace_bracket(10);