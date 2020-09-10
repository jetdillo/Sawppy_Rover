
module wheel() { 
rotate([0,90,0]) import("/home/armadilo/Documents/models/Sawppy_Rover/STL/Wheel.stl",convexity=10);

}

module snow_tread() { 
 difference() { 
    cylinder(r=63,h=80,center=true);
    cylinder(r=59,h=100,center=true);
}

    for(j=[-30:10:30]) { 
        echo(j);
        tread_start=rands(0,180,1);
        tread_start_i=floor(tread_start[0]);
        echo(tread_start_i);
        translate([0,0,j]) rotate([0,0,tread_start_i]) tread_gen();
    }
}

module tread_gen() { 
     for (i = [1:32]) {
     translate([sin(360*i/32)*65, cos(360*i/32)*65,0 ]) rotate([-90,0,(i*(360/32))*-1])cylinder(r1=5,r2=1,h=8,center=true);
    }
}
    snow_tread();
