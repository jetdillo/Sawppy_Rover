module railclip() { 
include </home/armadilo/Documents/models/OpenBeam_1515/clip.scad>
}

module protoboard_mount() { 
import("/home/armadilo/Documents/models/PermaProto_BreadBoard_Mount/files/adafruit_half_size_permaproto_holder.stl",convexity=10);
}

module protoboard_rack_clip() { 
clip_trans=[[0,16,-2],[-30,16,-2],[30,16,-2],[0,76,-2],[-30,76,-2],[30,76,-2]];
clip_rot=[[0,90,0],[0,90,0],[0,90,0],[180,90,0],[180,90,0],[180,90,0]];
protoboard_mount();

for (i=[0:5]) {
     translate(clip_trans[i]) rotate(clip_rot[i]) scale([1.0,1.1,1.0])railclip();
}
}
/*
translate([0,17,-2]) rotate([0,90,0]) railclip();
translate([-30,17,-2]) rotate([0,90,0]) railclip();
translate([30,17,-2]) rotate([0,90,0]) railclip();

translate([0,75,-2]) rotate([180,90,0]) railclip();
*/

difference() { 
    protoboard_rack_clip();
translate([0,50,-10]) cube([120,80,10],center=true);
}