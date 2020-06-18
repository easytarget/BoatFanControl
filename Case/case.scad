// Case for Boat fan Controller
$fn=90; // slowish, but otherwise can look fugly.

// XY Zero is the same as PCB axis zero

fitting = !true;

// Some dimensions: (mm)

pcbCorners = [[-0.2,-0.2],
              [-0.2,34.6],
              [33.8,34.6],
              [33.8,-0.2]];
pcbHoles = [[3,2.6],
            [31,2.4]];    // <-- MY PCB ERROR
            //[31,2.6]];
pcbHoleDia = 3.7;
pcbThick = 1.6; // thickness
pcbBaseClear = 5; // clearance under pcb
pcbTopClear = 18; // Total height (with DSpark clearance)
pcbSideClear = 5; // clearance around pcb
pcbCenter = pcbCorners[0]+(pcbCorners[2]-pcbCorners[0])/2;

terminalPoly = [[24.8,19.16], 
                [31,19.16],
                [31,34.4],
                [24.8,34.4]];
terminalCablePoly = [terminalPoly[0], // extended for case holes
                     terminalPoly[1]+[20,0],
                     terminalPoly[2]+[20,0],
                     terminalPoly[3]];
terminalCutoutMargin = [0,0.4];
terminalCutoutPoly = [terminalCablePoly[0]-terminalCutoutMargin,
                     terminalCablePoly[1]-terminalCutoutMargin,
                     terminalCablePoly[2]+terminalCutoutMargin,
                     terminalCablePoly[3]+terminalCutoutMargin];
terminalHigh = 10; 

dSparkExtra = 6; // extra Y axis clearance for DSpark usb pin
dSparkLift = 12;  // Clearance from main pcb
dSparkThick = 2.5;  // DigiSpark board thickness
dSparkPoly = [[0.45,16.85],
              [19.45,16.85],
              [19.45,34.35],
              [16.02,34.35],
              [16.02,43.35],
              [3.99,43.35],
              [3.99,34.35],
              [0.45,34.35]];
              
dht11Lift = 12.5; // Clearance from main pcb
dht11Thick = 1.6; // DHT11 pcb thickness
dht11Poly = [[2.5,4.5], // Really!!
             [18,4.5],
             [18,-28],
             [2.5,-28]];
dht11CutoutMargin = [0.4,0] ; // Make a case cutouts.
dht11CutoutPoly = [dht11Poly[0]-dht11CutoutMargin, 
                   dht11Poly[1]+dht11CutoutMargin, 
                   dht11Poly[2]+dht11CutoutMargin,
                   dht11Poly[3]-dht11CutoutMargin];

caseThick = 3; // case wall thickness
caseCorners = [pcbCorners[0],
               pcbCorners[1]+[0,dSparkExtra],
               pcbCorners[2]+[0,dSparkExtra],
               pcbCorners[3]];

buttonPos = [30.45,10.45]; // ??? position on pcb <- accurate???
buttonBase = 4; // height of the base
buttonPinDia = 3.2; // button pin+clearance
buttonPinHigh = 9.1; // b////utton pin top above pcb
buttonPoly = [buttonPos+[-3,-20],
              buttonPos+[-3,0],
              buttonPos+[10,0],
              buttonPos+[10,-20]];


module lid() 
difference () {
    union() {
        // A solid lid
        translate([0,0,caseThick/2+pcbBaseClear+pcbThick+pcbTopClear])
        linear_extrude(height=caseThick/2,convexity=10)
        minkowski() {
            polygon(caseCorners);
            circle(pcbSideClear+caseThick);
        }
        // Walls
        translate([0,0,caseThick/2])
        linear_extrude(height=pcbBaseClear+pcbThick+pcbTopClear,convexity=10)
        walls();
        // Button plate
        translate([0,0,caseThick+pcbBaseClear+pcbThick+buttonBase+0.5])
        linear_extrude(height=caseThick/2,convexity=10)
        intersection() {
            minkowski() {
                polygon(buttonPoly);
                circle(pcbSideClear+caseThick);         
            }
            minkowski() {
                polygon(caseCorners);
                circle(pcbSideClear);
            }
        }
        // Button Plate Walls
        translate([0,0,caseThick*1.5+pcbBaseClear+pcbThick+buttonBase+0.5])
        linear_extrude(height=pcbTopClear-caseThick-buttonBase+0.5,convexity=10)
        difference() {
            intersection() {
                minkowski() {
                    polygon(buttonPoly);
                    circle(pcbSideClear+caseThick);
                }
                minkowski() {
                    polygon(caseCorners);
                    circle(pcbSideClear+caseThick);
                }
            }
            minkowski() {
                polygon(buttonPoly);
                circle(pcbSideClear);         
            }
        }
    }
    // Slots for dht11 and cables
    linear_extrude(height=caseThick+pcbBaseClear+pcbThick+dht11Lift+dht11Thick+0.4, convexity=10)
    intersection() {
        walls();
        polygon(dht11CutoutPoly);
    }
    linear_extrude(height=caseThick+pcbBaseClear+pcbThick+terminalHigh, convexity=10)
    intersection() {
        walls();
        polygon(terminalCutoutPoly);
    }
    // Button Cutout.
    translate([0,0,1.5*caseThick+pcbBaseClear+pcbThick+buttonBase+0.5])
    linear_extrude(height=30,convexity=10) {
        minkowski() {
            polygon(buttonPoly);
            circle(pcbSideClear);         
        }
    }
    // Button pin
    translate(buttonPos)
    cylinder(d=buttonPinDia+0.1,h=2*pcbTopClear);
    // Cooling Holes
    translate(caseCorners[0]+[0,6])
    translate([0,0,caseThick*2+pcbTopClear])
    rotate([0,-90,0])
    hull() {
        translate([0,-5,0])
        cylinder(r=2,h=100,center=true);
        translate([0,5,0])
        cylinder(r=2,h=100,center=true);
    }
    translate(caseCorners[1]-[0,6])
    translate([0,0,caseThick*2+pcbTopClear])
    rotate([0,-90,0])
    hull() {
        translate([0,-5,0])
        cylinder(r=2,h=100,center=true);
        translate([0,5,0])
        cylinder(r=2,h=100,center=true);
    }
}

// Base
module base() {
    // Shell
    difference() {
        // Plate
        union() {
            linear_extrude(height=caseThick/2)
            difference() {
                minkowski() {
                    polygon(caseCorners);
                    circle(pcbSideClear+caseThick);
                }
                mountholes(4);
            }
            linear_extrude(height=caseThick*1.5)
            difference() {
                minkowski() {
                    polygon(caseCorners);
                    circle(pcbSideClear);
                }
                mountholes(9);
            }
        }
    }
    // PCB Screw Mounts
    for (a=[0,1]) {
        translate(pcbHoles[a]) 
        difference() {
            cylinder(d1=10,d2=6.5,h=caseThick+pcbBaseClear);
            cylinder(d=pcbHoleDia/1.2,h=caseThick+pcbBaseClear+1,$fn=6);
        }
    }
    // PCB Clip
    translate(pcbCorners[1]+[10,2])
    difference() {
        hull() {
            cylinder(d=10,h=1);
            translate([0,0,caseThick+2*pcbThick+pcbBaseClear])
            scale([1,1,0.5])
            sphere(d=10);
        }
        translate([-10,-11.8,caseThick+pcbBaseClear-0.1])
        hull() {
            cube([20,10,pcbThick+0.1]);
            translate([0,-10,10])
            cube([20,10,pcbThick]);
        }
    }
    // ScrewTerminal Support
    translate(pcbCorners[2])
    translate([-2,-15,caseThick])
    cube([2,15,pcbBaseClear]);
    // Fill Plates
    linear_extrude(height=caseThick+pcbBaseClear+pcbThick+dht11Lift, convexity=10)
    intersection() {
        walls();
        polygon(dht11Poly);
    }
    linear_extrude(height=caseThick+pcbBaseClear+pcbThick, convexity=10)
    intersection() {
        walls();
        polygon(terminalCablePoly);
    }
        
}

module walls() {
    // The walls of the case
    difference() {
        minkowski() {
            polygon(caseCorners);
            circle(pcbSideClear+caseThick);
        }
        minkowski() {
            polygon(caseCorners);
            circle(pcbSideClear);
        }
    }
}

module mountholes(slotdia=4) {
    // Mounting Holes
    translate(pcbHoles[0]) circle(d=pcbHoleDia);
    translate(pcbHoles[1]) circle(d=pcbHoleDia);
    hull() {
        translate(pcbCenter+[-4,10]) circle(d=slotdia);
        translate(pcbCenter+[4,10]) circle(d=slotdia);
    }
    hull() {
        translate(pcbCenter+[0,-14]) circle(d=slotdia);
        translate(pcbCenter+[0,-6]) circle(d=slotdia);
    }
}

// PCBs for fitting
module pcbs() if (fitting) color("lightgreen", 0.4) {
    // pcb
    translate([0,0,caseThick+pcbBaseClear])

    linear_extrude(height=pcbThick, convexity=10) 
    difference() {
        polygon(pcbCorners);
        translate(pcbHoles[0]) circle(d=pcbHoleDia);
        translate(pcbHoles[1]) circle(d=pcbHoleDia);
    }
    // DigiSpark
    translate([0,0,caseThick+pcbBaseClear+pcbThick+dSparkLift])
    linear_extrude(height=dSparkThick, convexity=10) 
    polygon(dSparkPoly);
    // DHT11
    translate([0,0,caseThick+pcbBaseClear+pcbThick+dht11Lift])
    linear_extrude(height=dht11Thick, convexity=10) 
    polygon(dht11Poly);
    // Button
    translate(buttonPos)
    translate([0,0,caseThick+pcbBaseClear+pcbThick]) {
        linear_extrude(height=buttonBase,convexity=10)
        square([buttonBase*1.6,buttonBase*1.6],center=true);
        cylinder(d=buttonPinDia,h=buttonPinHigh);
    }
    // Terminal
    translate([0,0,caseThick+pcbBaseClear+pcbThick])
    linear_extrude(height=terminalHigh, convexity=10) 
    polygon(terminalPoly);
}

base();
pcbs();
if (fitting) color("grey",0.8) lid();
else translate([-60,0,1.5*caseThick+pcbBaseClear+pcbThick+pcbTopClear]) rotate([180,0,0]) lid();
