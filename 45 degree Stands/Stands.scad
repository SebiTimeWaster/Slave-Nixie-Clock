/**
  *  The MIT License (MIT)
  *
  *  Slave Nixie Clock - Copyright (c) 2017 SebiTimeWaster
  *
  *  Permission is hereby granted, free of charge, to any person obtaining a copy
  *  of this software and associated documentation files (the "Software"), to deal
  *  in the Software without restriction, including without limitation the rights
  *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  *  copies of the Software, and to permit persons to whom the Software is
  *  furnished to do so, subject to the following conditions:
  *
  *  The above copyright notice and this permission notice shall be included in all
  *  copies or substantial portions of the Software.
  *
  *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  *  SOFTWARE.
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
