module beam() {

include </home/armadilo/Documents/models/1515_model/files/microbeam.scad>
}


module clip() { 
    scale([1.1,1.1,1.1]);
include </home/armadilo/Documents/models/OpenBeamClip/clip.scad>
}


module clearplate() {
cube([64.5,89.2,2.54]);
    translate([5,5,4]) rotate([-90,0,90]) clip();
translate([59,5,4]) rotate([-90,0,90]) clip();
translate([59,84,4]) rotate([-90,0,90]) clip();
translate([5,84,4]) rotate([-90,0,90]) clip();
}

clearplate();

//rotate([90,0,0]) beam();