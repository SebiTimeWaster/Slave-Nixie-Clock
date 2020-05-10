/**
  * This code is published under a
  * Creative Commons Attribution-NonCommercial-ShareAlike 3.0
  * licence, please respect it.
  */

module holder() {
    translate([36.41, 1.41, 0]) rotate([0, 0, 45]) {
                                   cube([29, 2, 15]);  // 45° beam
        translate([27,   2, 10.3]) cube([2,  9, 4.7]); // left upper finger
        translate([27,   2, 0])    cube([2,  9, 4.7]); // right upper finger
        translate([23.2, 2, 10.3]) cube([2,  9, 4.7]); // left lower finger
        translate([23.2, 2, 0])    cube([2,  9, 4.7]); // right lower finger
    }
    translate([54.91, 0, 0]) cube([2,     21.91, 15]); // vertical beam
                             cube([56.91, 3,     15]); // base
}

holder();
translate([56.91, 34, 0]) rotate([0, 0, 180]) holder();
