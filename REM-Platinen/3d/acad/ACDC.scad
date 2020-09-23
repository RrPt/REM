
cube([23.5,15.1,1.6]);
translate([1,-3,0])cube([2,3,1.6]);
translate([4,-3,0])cube([2,3,1.6]);
translate([20.5 - 4,-3,0])cube([3,4,1.6]);
translate([20.5,-3,0])cube([3,4,1.6]);

translate([3,5,0])cylinder(h=10,d=5,$fn=20);
translate([20,11,5])rotate([90,0,0])cylinder(h=10,d=7,$fn=20);
translate([6,2,0])cube([10,10,9]);