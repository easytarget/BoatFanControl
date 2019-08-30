// Case for Boat fan Controller
$fn=90; // slowish, but otherwise can look fugly.

// XY Zero is the same as PCB axis zero

fitting = true;

// Some dimensions: (mm)
pcbCorners = [[-0.2,-0.2],
              [-0.2,34.6],
              [33.8,34.6],
              [33.8,-0.2]];
pcbHoles = [[3,2.6],
            [31,2.4]];    // <-- MY PCB ERROR
            //[31,2.6]];
pcbThick = 1.6; // thickness
pcbBaseClear = 5; // clearance under pcb
pcbTopClear = 20; // ??? height over DSpark top + clearance
pcbSideClear = 5; // clearance around pcb
pcbCenter = pcbCorners[0]+(pcbCorners[2]-pcbCorners[0])/2;

buttonPos = [30.45,10.45]; // ??? position on pcb <- accurate???
buttonBase = 4; // ??? height of the base
buttonPinDia = 4; // ??? button pin+clearance
buttonPinHigh = 9; // ?? button pin top above pcb

terminalPoly = [[24.8,19.16], // extended for case intersection
                [31,19.16],
                [31,34.4],
                [24.8,34.4]];
terminalCutoutPoly = [[24.8,18.96], // extended for case intersection
                      [51,18.96],
                      [51,34.6],
                      [24.8,34.6]];
terminalHigh = 8; // ?? 

dSparkExtra = 6; // extra for DSpark usb pin
dSparkLift = 8;  // ??? Clearance from main pcb
dSparkThick = 2;  // ??? DigiSpark board thickness
dSparkPoly = [[0.45,16.85],
              [19.45,16.85],
              [19.45,34.35],
              [16.02,34.35],
              [16.02,43.35],
              [3.99,43.35],
              [3.99,34.35],
              [0.45,34.35]];
              
dht11Lift = 8; // ??? Clearance from main pcb
dht11Thick = 1.6; // ???? DHT11 pcb thickness
dht11Poly = [[3,4.5], // ????????? Really!!
             [18,4.5],
             [18,-28],
             [3,-28]];
dht11CutoutPoly = [[3.2,4.5], // Used for case cutouts.
                   [17.8,4.5], // ???????????
                   [17.8,-28],
                   [3.2,-28]];

caseThick = 3; // case wall thickness
caseCorners = [pcbCorners[0],
               pcbCorners[1]+[0,dSparkExtra],
               pcbCorners[2]+[0,dSparkExtra],
               pcbCorners[3]];

base();


// PCBs for fitting
if (fitting) color("lightgreen", 0.4) {
    // pcb
    translate([0,0,caseThick+pcbBaseClear])

    linear_extrude(height=pcbThick, convexity=4) 
    difference() {
        polygon(pcbCorners);
        translate(pcbHoles[0]) circle(d=3.8);
        translate(pcbHoles[1]) circle(d=3.8);
    }
    // DigiSpark
    translate([0,0,caseThick+pcbBaseClear+pcbThick+dSparkLift])
    linear_extrude(height=dSparkThick, convexity=4) 
    polygon(dSparkPoly);
    // DHT11
    translate([0,0,caseThick+pcbBaseClear+pcbThick+dht11Lift])
    linear_extrude(height=dht11Thick, convexity=4) 
    polygon(dht11Poly);
    // Button
    translate(buttonPos)
    translate([0,0,caseThick+pcbBaseClear+pcbThick]) {
        linear_extrude(height=buttonBase,convexity=2)
        square([buttonBase*1.5,buttonBase*1.8],center=true);
        cylinder(d=buttonPinDia,h=buttonPinHigh);
    }
    // Terminal
    translate([0,0,caseThick+pcbBaseClear+pcbThick])
    linear_extrude(height=terminalHigh, convexity=4) 
    polygon(terminalPoly);
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
                mountholes();
            }
            linear_extrude(height=caseThick*1.5)
            difference() {
                minkowski() {
                    polygon(caseCorners);
                    circle(pcbSideClear);
                }
                mountholes();
            }
        }
    }
    // PCB Mounts
    for (a=[0,1]) {
        translate(pcbHoles[a]) 
        difference() {
            cylinder(d1=10,d2=6.5,h=caseThick+pcbBaseClear);
            cylinder(d=3,h=caseThick+pcbBaseClear+1,$fn=6);
        }
    }
    // PCB Clip
    translate(pcbCorners[1]+[0,2]+(pcbCorners[2]-pcbCorners[1])/2)
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
    // Fill Plates
    linear_extrude(height=caseThick+pcbBaseClear+pcbThick+dht11Lift, convexity=4)
    intersection() {
        walls();
        polygon(dht11CutoutPoly);
    }
    linear_extrude(height=caseThick+pcbBaseClear+pcbThick, convexity=4)
    intersection() {
        walls();
        polygon(terminalCutoutPoly);
    }
        
}

module lid() {
    // Walls
    #translate([0,0,caseThick])
    linear_extrude(height=pcbBaseClear+pcbThick+pcbTopClear)
    walls();
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

module mountholes() {
    // Mounting Holes
    translate(pcbHoles[0]) circle(d=4);
    translate(pcbHoles[1]) circle(d=4);
    hull() {
        translate(pcbCenter+[-4,10]) circle(d=4);
        translate(pcbCenter+[4,10]) circle(d=4);
    }
    hull() {
        translate(pcbCenter+[0,-14]) circle(d=4);
        translate(pcbCenter+[0,-6]) circle(d=4);
    }
}

