module railclip() { 
include </home/armadilo/Documents/models/OpenBeam_1515/clip.scad>
}

module sensor_case() { 
   import("/home/armadilo/Documents/models/ultrasonic_1.stl");
}

module sensor_clip() { 
    import("/home/armadilo/Documents/models/ultrasonic_2b_V2-export.stl");
}

//translate([0,30,0]) holder1();
//translate([0,-12,5]) rotate([0,90,0]) railclip();
holder2();

