//
//	Gerause für REM-C  / Din rail
//
//  by Rainer Petzoldt
//  basiert auf REM-M-Geh.scad V0.3.7
//  Slicen ohne Stützstruktur ;  4 Wandlinien ;  3 Obere- und untere Schichten
//     generateStuetzstruktur = true setzen

/* width in TE (=18mm) */
AnzTE = 4;   // [1:0.5:12]
/* select which part to show */
part = "Deckel" ; // [Unterteil, Oberteil, Deckel, Oberteil_mit_Deckel, Schnapper, all, assembled]
showPlatinen = false;
generateStuetzstruktur = true;

// *******************************************************************

/* [Hidden] */
deckelLift = 1*5;   // zieht module auseinander (Explosionszeichnung)
h1debug =  0*19;   // 0 = no debug  erniedrigt aussenwand um h1debug mm
Vers =  "V1.1";
TE = 18;	// Teilungseinheit
d = 1.5;   				// Wanddicke

breite = AnzTE * TE-0.5+1;  // Gesamtbreite aussen
tiefe = 91;				// Tiefe unterste Ebene
tiefe2 = 62-12;			// Tiefe mittlere Ebene
tiefe3 = 45-10;			// Tiefe mittlere Ebene

deltaH = 0*12;
h1 = 26.5+deltaH;				// Hoehe Unterteil gesamt aussen
h2 = 5;           // Aussparung fuer Schiene 
h3 = 5;         // Hoehe unterste Deckelschicht
h4 = 17-deltaH;          // Hoehe mittlere Deckelschicht
h5 = 22-10;          // Hoehe obere Deckelschicht
b1 = 28-2.5;
b2 = 0.5;
b3 = 35;
b4 = 28;
spalt = 0.4;

mitteY = tiefe / 2;
mitteX = breite/2;

RemMMy = 42;
RemMMx = 33;
RemMMAbstandy = 0;

F5 = 0.001;


difference()
{
	union()
	{
if (part=="assembled")
{
		Unterteil(breite);
		translate([0,0,h1+deckelLift])	Oberteil(breite);
		translate([0,(tiefe+tiefe3)/2,h1+h3+h4+h5+2*deckelLift])rotate([180,0,0])Deckel(breite);
		color("red") translate([breite/2-14/2,b1+1.5,5]) rotate([-90,0,-90])Schienenhalter();
		if (showPlatinen==true)
		{	
			translate([d-31.5+1,d-100+0.5,9])	color("White") 	rotate([0,0,90])	import("REM-C-mit_Sockel_u_Stecker.stl",convexity=5);
		}
}
else
{
	if (part=="Unterteil")
	{
		Unterteil(breite);
		if (showPlatinen==true)
		{	
			translate([d-31.5+1,d-100+0.5,9])	color("White") 	rotate([0,0,90])	import("REM-C-mit_Sockel_u_Stecker.stl",convexity=5);
		}

	}
	if (part=="Oberteil")
	{
		Oberteil(breite);
		if (showPlatinen==true)
		{	
			translate([d-31.5+1,d-100+0.5,9-h1])	color("White") 	rotate([0,0,90])	import("REM-C-mit_Sockel_u_Stecker.stl",convexity=5);
		}
	}
	if (part=="Oberteil_mit_Deckel")
	{
		color("red")translate([0,(tiefe+tiefe3)/2+F5,h3+h4+h5+deckelLift])rotate([180,0,0])Deckel(breite);
		Oberteil(breite);
		if (showPlatinen==true)
		{	
			translate([d-31.5+1,d-100+0.5,9-h1])	color("White") 	rotate([0,0,90])	import("REM-C-mit_Sockel_u_Stecker.stl",convexity=5);
		}
	}
	if (part=="Deckel")
	{
			Deckel(breite);
	}
	if (part=="Schnapper")	rotate([-90,0,0])Schienenhalter();
	if (part=="all")
	{
		Unterteil(breite);
		translate([breite+10,0,5]) Oberteil(breite);
		translate([2*breite+20,0,0])Deckel(breite);
    translate([2*breite+20,50,3])rotate([-90,0,0])Schienenhalter();
		
		if (showPlatinen==true)
		{	
			translate([d-31.5+1,d-100+0.5,9])	color("White") 	rotate([0,0,90])	import("REM-C-mit_Sockel_u_Stecker.stl",convexity=5);
			translate([d-31.5+1+breite+10,d-100+0.5,9-h1+5])	color("White") 	rotate([0,0,90])	import("REM-C-mit_Sockel_u_Stecker.stl",convexity=5);
		}
	}
}
}
	//translate([33,-25,-17])cube([100,200,100]);
}


module Deckel(breite)
{
	da = d + 0.5;
	cube([breite,tiefe3,d]);	 // Deckel
	translate([d,0,0])cube([breite-2*d,d,d+2]);	 // Seitenwand
  // rechtes
	dx = 0.1;
	translate([2*d +dx/2  ,d,0])cube([d,tiefe3-2*da,d+2]);	  // rechts
  translate([2*d +dx/2  ,tiefe3-2*da,3])rotate([90,0,0])cylinder(h=tiefe3-2*da,d=1,$fn=20); // rechts 
	// links
	translate([breite-3*d-dx/2,d,0])cube([d,tiefe3-2*da,d+2]);	
  translate([breite -2*d-dx/2 ,tiefe3-2*da,3])rotate([90,0,0])cylinder(h=tiefe3-2*da,d=1,$fn=20);

  translate([mitteX,15,1])scale(0.5)linear_extrude(height=3)text(Vers,halign="center");

}  

module Deckelschienen()
{
	dy = 32.5;
	translate([0,29+dy,32.5])
	rotate([90,0,0])
	linear_extrude(height=dy,convexity=2)
	polygon(points = [ [0,0], [2*d,0],[2*d,-3],[0,-8] ], convexity = 2);
}

module Unterteil(breite)
{
	difference()
	{
		//translate([-d-0.001,0,118])  // debugging
		cube([breite,tiefe,h1-h1debug]);																				// Aussenwand
		translate([d,d,h2+d+F5])cube([breite-2*d,tiefe-2*d,h1-d-h2]);		// Innenwand
    // Kabelzufuehrungen
		translate([61,75,7+h2+d+F5])cube([3,15.599,5]);		//  3.3V   mit einer Schicht verschlossen da optional
		translate([61+2*2.54,75,7+h2+d+F5])cube([3,15.599,5]);		// 3.3V mit einer Schicht verschlossen da optional
		for (i=[2*5.08:5.08:7*5.08])
		{
			translate([40.7-2*5.08+i,-5,7+h2+d+F5])cube([3,20,5]);		//  Spannungsanschluss
		}
		for (i=[0:5.08:1*5.08])
		{
			translate([40.7-2*5.08+i,0.401,7+h2+d+F5])cube([3,20,5]);		//  Spannungsanschluss Optional
		}
		for (i=[0:5.08:1*5.08])
		{
			translate([6.5+i,-5,7+h2+d+F5])cube([3,20,5]);		//  Spannungsanschluss
		}
		
		
		translate([35.5,75,22.5])cube([17,20,14]);		// Ausschnitt für RJ45
		translate([9.5,85,20.5])uUSB();		// Ausschnitt für USB
		
		translate([0,b1,0])Railausschnitt(breite+1);										// Schienenausschnitt
		translate([breite/2-14/2-spalt,0-F5,2-2*spalt-F5])cube([14+2*spalt,b1+2*d+F5,3+2*spalt]);		// Schnapperausschnitt
  	translate([breite/2-3.5,10,0])		cylinder(h=8,d=3.0,$fn=20);   // Loch fuer Schnapperverankerung
		wa = 3;  // Wanddicke Aussparungen
		translate([breite/2-10/2,0-F5,d-4.9+2*F5])cube([10,13,h2]);		      // Wartungsoeffnung
		translate([wa,wa,-F5])cube([(breite-14)/2-2*wa,b1-2*wa,h2]);	    // Materialsparen unten1
		translate([(breite+14)/2+wa,wa,-F5])cube([(breite-14)/2-2*wa,b1-2*wa,h2]);	    // Materialsparen unten2
		translate([wa,tiefe-b4+wa,-F5])cube([breite-2*wa,b1-2*wa,h2]);		// Materialsparen unten3
		translate([(breite-14)/2+1.5,0,1.6+d])rotate([60,0,0])translate([0,0,-3])cube([4,3,7]);		// Rampe fuer Schnappernase
		translate([(breite-14)/2+5.5-F5,-1,1.6+d])rotate([20,0,0])translate([0,0,-0])cube([4,3,7]);		// Rampe fuer Schraubendreher
		// Schnapperaussparungen
		Schnapperaussparungen(10,h1-26.5+22);
		
	}
	  // Logo und Version
    translate([mitteX,tiefe-12,h2+d-0.4])scale(0.5)RPLogo();
 	  translate([mitteX,tiefe-27,h2+d-0.8])scale(0.5)linear_extrude(height=3)text(Vers,halign="center");

	// Platinenhalterungen
	phx = (RemMMx)/2 + 6;// breite/2 - d -2.25-0.5;	// Mittenabstand Platinenhalter x
	phy = tiefe/2-d-2-8;
	phy2 = RemMMAbstandy/2+2.6;


	echo("Unterteilloecher:", 2phx=2*phx, 2phy=2*phy, 2phy2=2*phy2, dpy=phy-phy2);
	// Abstandsbolzen
	//Bolzenpositionen festlegen
	translate([mitteX+phx,mitteY+phy,0]) Platinenhalter(2,0);
	translate([mitteX-phx,mitteY+phy,0]) Platinenhalter(2,0);
	translate([mitteX+phx,mitteY-phy,0]) Platinenhalter(2,0);
	translate([mitteX-phx,mitteY-phy,0]) Platinenhalter(2,0);
	// Schraublochbolzen
	translate([6.5,25,0]) Platinenhalter(5);
	translate([66.5,58,0]) Platinenhalter(5);
	// Haltekante nach oben
	hky = 3.75;
	
	if ( generateStuetzstruktur)
	{ 
		di = 0.41;
		color("blue")
		{	// Fuer Schnapperlement
			hull()
			{
				translate([29,0,4-0.21])cube([12,13,1]);	
				translate([33,1,0])cube([8,9,1]);	
			}
		// Fuer Bodenhohlräümen	
		translate([4,9,-0.10])cube([21,di,5-0.21]);		// z -0.1 wegen bug in Cura
		translate([4,15,0])cube([21,di,5-0.21]);		
		translate([14,4,0])cube([di,17,5-0.21]);		// quer

		translate([47,9,0])cube([21,di,5-0.21]);		
		translate([47,15,0])cube([21,di,5-0.21]);		
		translate([57,4,0])cube([di,17,5-0.21]);		// quer

		translate([28,26,0])cube([16,di,5-0.21]);		
		translate([0,36,0])cube([breite,di,5-0.21]);		
		translate([0,47,0])cube([breite,di,5-0.21]);		
		translate([breite/4,27,0])cube([di,29,5-0.21]);		// quer
		translate([2*breite/4,26,0])cube([di,29,5-0.21]);		// quer
		translate([3*breite/4,27,0])cube([di,29,5-0.21]);		// quer

		translate([4,70,0])cube([breite-8,di,5-0.21]);		
		translate([4,80,0])cube([breite-8,di,5-0.21]);		
		translate([breite/4,67,0])cube([di,18,5-0.21]);		// quer
		translate([2*breite/4,67,0])cube([di,18,5-0.21]);		// quer
		translate([3*breite/4,67,0])cube([di,18,5-0.21]);		// quer
		}
	}
}


module Schnapperaussparungen(schnapperbreite,h=22)
{
		at = 2;  	// tiefe Aussparung
		ah = 2;   	// Hoehe Aussparung
		ab = schnapperbreite;  		// Breite Aussparung
		//h = 22;	// Position Z
	  yd = 10;
	  y1 =  mitteY - yd;
    y2 =  mitteY + yd;

		translate([       0,y1  , h]) rotate([0,0,-90]) Schnapperaussparung(ab,at,ah);
		translate([  breite,y1, h]) rotate([0,0, 90]) Schnapperaussparung(ab,at,ah);
		translate([       0,y2  , h]) rotate([0,0,-90]) Schnapperaussparung(ab,at,ah);
		translate([  breite,y2, h]) rotate([0,0, 90]) Schnapperaussparung(ab,at,ah);
}

module Schnapperaussparung(ab,at,ah)
{
	translate([-ab/2,-F5,0])cube([ab,at,ah]);
	translate([-ab/2,1,1])cube([ab,at,5]);
}

module Railausschnitt(breite)
{
	difference()
	{
		
		translate([breite+0.5,0,h2-F5])		rotate([-90,0,90])
		linear_extrude(height=breite+1,convexity=2)
		{
			polygon(points=[[b2,0],[0,h2],[b2+b3,h2],[b2+b3,0]]);
		}
		
		translate([-0.5,b2+b3-2.5,3.5])rotate([0,90,0])
	
	  hull()
		{
        translate([1.8,0,0]) cylinder(h=breite+1, r=1, $fs=0.1, center=false);
        translate([0,1.8,0]) cube([2.8,1,breite+1], center=false);
        translate([3,0,0]) cube([1,3,breite+1], center=false);
    }
	}
}

module Schienenhalter()
{
	
	l1 = 30.4;
	l2 = 1.2;
	l3 = l1 + l2;
	h1 = 1.2;
	h2 = 1.8;
	h3 = h1 + h2;
	ba = 14;

	difference()
	{
		// Grundform
		linear_extrude(height=ba,convexity=2)
		{
			polygon(points=[[-0.5,h1],[l2,h3],[l3,h3],[l3,0],[l2,0],[l2,h1]]);
		}
		// Federelement
    translate([14,h3+F5,2])
		rotate([90,0,0])
		linear_extrude(height=h3+2*F5,convexity=2)
		{
			ha = 10.5;
			bx = 8;
			v = 1;
			polygon(points=[
			[0,0],[0,ha],[3-v,ha],[3,ha-v],[3,1.5],[5,1.5],[5,ha-v],[5+v,ha],
			[bx,ha],[bx,0]
			]);
		}
		translate([16,-2,3.5])cube([4,h3,9]);			        // Feder duenner machen
		translate([l3-3-2,0-F5,3])cube([3,h3+2*F5,8]);			// Aussparung zum oeffnen mit Schraubendreher
	}
	translate([18,h3,3.5])	rotate([90,0,0])	cylinder(h=h3+d,d=2,$fn=20);	// Arretierung
}

module Platinenhalter(durchmesser=4, loch=2)
{
	translate([0,0,h2+d])
	difference()
	{
		cylinder(h=2.5,d1=durchmesser+3,d2=durchmesser,$fn=20);
		translate([0,0,-F5])cylinder(h=2.6,d=loch,$fn=20);
	}
}




module uUSB()
{
	rad = 1;
	rad2 = 1.5;
	fn = 20;
	h = 8;
	dx = 1.;
	
	//translate([0,-1.5,0])cube([10,7,5]);
	hull()
	rotate([-90,0,0])
	{
		translate([dx+rad,-rad,0]) cylinder(h=h,r=rad,$fn=fn);
		translate([10-dx-rad,-rad,0]) cylinder(h=h,r=rad,$fn=fn);
		translate([rad2,rad2-5,0]) cylinder(h=h,r=rad2,$fn=fn);
		translate([10-rad2,-5+rad2,0]) cylinder(h=h,r=rad2,$fn=fn);
	
	}
	
}


module Oberteil(breite)
{
	difference()
	{
		union()
		{
			cube([breite,tiefe,h3]);																				// Aussenwand unten
			translate([0,(tiefe-tiefe2)/2,h3]) cube([breite,tiefe2,h4]);		// Aussenwand mitte
			translate([0,(tiefe-tiefe3)/2,h3+h4]) cube([breite,tiefe3,h5-d]);		// Aussenwand oben
			translate([30.5,70,h3]) cube([27,21,12]);		// RJ45 Auswoelbung
			// Beschriftungen
				translate([11,       11.5+F5,h3])	scale(0.5)linear_extrude(height=0.6/0.3,convexity=2)text(text="5V",halign="center",font="Arial:style=Bold");
				translate([10,       0.5+F5,h3])	scale(0.5)linear_extrude(height=0.6/0.3,convexity=2)text(text="+  -",halign="center",font="Arial:style=Bold");
				translate([32.95,       11.5+F5,h3])	scale(0.5)linear_extrude(height=0.6/0.3,convexity=2)text(text="U  L1 L2 L3",font="Arial:style=Bold");
				translate([65,       75+F5,h3])	scale(0.5)linear_extrude(height=0.6/0.3,convexity=2)text(text="3.3V",halign="center",font="Arial:style=Bold");
				translate([65,       86.5+F5,h3])	scale(0.5)linear_extrude(height=0.6/0.3,convexity=2)text(text="+  -",halign="center",font="Arial:style=Bold");
			
/*
			// Lochbeschriftung
			for(i=[0:AnzTE*3-0.1])
			{
				start = breite/2-(AnzTE*3-1)*5.08/2-0.75;
				num = i+1;
				translate([start+i*5.08,       11.5+F5,h3])	scale(0.5)linear_extrude(height=0.6/0.3,convexity=2)text(text=str(num),halign="center",font="Arial:style=Bold");
				translate([start+i*5.08, tiefe-16.2+F5,h3])	scale(0.5)linear_extrude(height=0.6/0.3,convexity=2)text(str(6-i),halign="center",font="Arial:style=Bold");
			}
			*/
			translate([mitteX,       64+F5,h3+h4])	scale(0.5)linear_extrude(height=0.6/0.3,convexity=2)text(text="REM-C",halign="center",font="Arial:style=Bold");
			translate([mitteX,       22+F5,h3+h4])	scale(0.5)linear_extrude(height=0.6/0.3,convexity=2)text(text=Vers,halign="center",font="Arial:style=Bold");
			
		}
		translate([d,d,0-F5])cube([breite-2*d,tiefe-2*d,h3-d]);		// Innenwand  unten
		translate([d,d+(tiefe-tiefe2)/2,h3-d-2*F5]) cube([breite-2*d,tiefe2-2*d,h4+F5]);		// Innenwand mitte
		translate([d,d+(tiefe-tiefe3)/2,h3+h4-d-2*F5]) cube([breite-2*d,tiefe3-2*d,h5+F5+3]);		// Innenwand oben
		translate([-10,14+d+(tiefe-tiefe3)/2,9+h3+h4-d-2*F5]) cube([100,13.5,10]);		// Kabelausschnitte
		translate([d,d+(tiefe-tiefe3)/2,h3+h4-d+9.8+F5]) cube([breite-2*d,tiefe3-d+F5,h5+F5+3]);		 // Wand weg
		translate([35.5,65,0-F5])cube([17,30,11]);		// Ausschnitt für RJ45
		
		// Schraubenloecher
		durchm = 4;
		for(i=[0:7])
		{
			start = 31.9;
			translate([start+i*5.08,           7.4+F5,h3-d-2*F5-15])	cylinder(h=20+d+3*F5,d=durchm,$fn=20);
		}
		for(i=[0:1])
		{
			start = 7.9;
			translate([start+i*5.08,           7.4+F5,h3-d-2*F5-15])	cylinder(h=20+d+3*F5,d=durchm,$fn=20);
			translate([start+i*5.08+54.5,           84.3+F5,h3-d-2*F5-15])	cylinder(h=20+d+3*F5,d=durchm,$fn=20);
		}

	}
  // RJ45 obere Wand
	translate([35.5,89.5,9.5])cube([17,d,1.5]);		// Ausschnitt für RJ45
	// Optionale  Schraubenloecher schliessen
	translate([29,5,4.5])cube([10,5,0.21]);
	translate([60,82,4.5])cube([10,5,0.21]);

	difference()
	{
		union()
		{
			Deckelschienen();
			translate([72.5,90.5,0])rotate([0,0,180])Deckelschienen();
		}
	  translate([breite -2*d,2*tiefe3-7+F5,31])rotate([90,0,0])cylinder(h=tiefe3-d,d=1.5,$fn=20);  // Schnapperrillen
	  translate([2*d        ,2*tiefe3-7+F5,31])rotate([90,0,0])cylinder(h=tiefe3-d,d=1.5,$fn=20);       // Schnapperrillen
		translate([-10,14+d+(tiefe-tiefe3)/2,9+h3+h4-d-2*F5]) cube([100,13.5,10]);		// Kabelausschnitte
	}
	  // Logo und Version
    translate([mitteX-20,mitteY+tiefe2/2-0.4,18])rotate([90,0,180])scale(0.5)RPLogo();
 	  translate([mitteX-20,mitteY+tiefe2/2-0.4,h2+d-0.4])rotate([90,0,180])scale(0.3)linear_extrude(height=3)text(Vers,halign="center",font="Arial:style=Bold");
	
	// Schnapper
  AlleSchnapper(10);
	
	h = h3+h4+5;
	phx = (RemMMx) - 2.5;// breite/2 - d -2.25-0.5;	// Mittenabstand Platinenhalter x
	phy = tiefe2/2-3.5-d;

	echo("Deckelloecher:", 2phx=2*phx, 2phy=2*phy);
	// Platinenhalterungen
	translate([mitteX+phx-0.5,mitteY+phy,h]) rotate([180,0,0])Platinenhalter(5);
	translate([mitteX-phx+0.5,mitteY+phy,h]) rotate([180,0,0])Platinenhalter(5);
	translate([mitteX+phx-0.5,mitteY-phy,h]) rotate([180,0,0])Platinenhalter(5);
	translate([mitteX-phx+0.5,mitteY-phy,h]) rotate([180,0,0])Platinenhalter(5);
	
	if ( generateStuetzstruktur)
	{ 
		di = d;
		color("blue")
		{	
			// Unterer Rand
			hu = 4.75;
			schnapperBreite = 11;
			stbre = .41;
  
			translate([0,0,-hu])cube([breite,di,hu-0.21]);		
  		translate([0,tiefe-d,-hu])cube([breite,di,hu-0.21]);
			translate([0,tiefe-d,-hu])cube([3,di,hu]);  // Ecke ohne Spalt
			translate([breite-3,tiefe-d,-hu])cube([3,di,hu]);  // Ecke ohne Spalt
			translate([0,0,-hu])cube([3,di,hu]);  // Ecke ohne Spalt
			translate([breite-3,0,-hu])cube([3,di,hu]);  // Ecke ohne Spalt
			
			difference()
			{
				translate([0,0,-hu])cube([di,tiefe,hu-0.21]);		
				translate([0,41,0])rotate([0,0,180])SchnapperStuetzAussaprung(schnapperBreite,di);
				translate([0,61,0])rotate([0,0,180])SchnapperStuetzAussaprung(schnapperBreite,di);
				
			}
  		difference()
			{
				translate([breite-d,0,-hu])cube([di,tiefe,hu-0.21]);	
				translate([breite,30,0])SchnapperStuetzAussaprung(schnapperBreite,di);
				translate([breite,50,0])SchnapperStuetzAussaprung(schnapperBreite,di);
			}
			
			// Schraubloecherstuetzen
			translate([6.2,25.5,-hu])cylinder(h=22.7-0.21,r=2.8);
			translate([breite-6.2,25.5,-hu])cylinder(h=22.7-0.21,r=2.8);
			translate([6.2,65.5,-hu])cylinder(h=22.7-0.21,r=2.8);
			translate([breite-6.2,65.5,-hu])cylinder(h=22.7-0.21,r=2.8);

			// Stuetzen für Flaechen
			translate([d+1,4,3.5-0.61-0.21])cube([breite-5,8.0,0.61]);	
		  translate([d+1,4,-hu-0.1])cube([breite-5,stbre,hu+3.5-0.21]);		// z um 0.1 kleiner wegen bug in cura
		  translate([d+1,12,-hu])cube([breite-5,stbre,hu+3.5-0.21]);		
		  translate([d+1,21.6,-hu])cube([breite-5,stbre,hu+3.5-0.21]);		
		  translate([d+8.5,22.3,-hu])cube([breite-22.5,stbre,hu+20.5-0.21]);		
		  translate([d+1,29.3,-hu])  cube([breite-5    ,stbre,hu+20.5-0.21]);		
			
			for (x=[2.5,10,20,30,40,50,60,70])  
			{
				translate([x,4,-hu])cube([stbre,25.7,hu+3.5-0.21]);		// quer
			}
			for (x=[10,20,30,40,50,60])  
			{
				translate([x,22.5,-hu])cube([stbre,7,hu+20.5-0.21]);		// quer
			}
			
      // 2. Haelfte
			// Stuetzen für Flaechen
			translate([59,80,3.5-0.61-0.21])cube([11,8.0,0.61]);	
		  translate([d+1,88,-hu])cube([breite-5,stbre,hu+3.5-0.21]);		
		  translate([d+1,80,-hu])cube([breite-5,stbre,hu+3.5-0.21]);		
		  translate([d+1,69,-hu])cube([breite-5,stbre,hu+3.5-0.21]);		
		  translate([d+8.5,68.3,-hu])cube([breite-22.5,stbre,hu+20.5-0.21]);		
		  translate([d+1,61.3,-hu])  cube([breite-5    ,stbre,hu+20.5-0.21]);		
			
			for (x=[2.5,10,20,30,40,50,60,70])  
			{
				translate([x,61.3,-hu])cube([stbre,27.1,hu+3.5-0.21]);		// quer
			}
			for (x=[10,20,30,40,50,60])  
			{
				translate([x,61.3,-hu])cube([stbre,7,hu+20.5-0.21]);		// quer
			}

			// RJ45 Stuetze
  		translate([36,tiefe-d,-1])cube([16,di,12-0.21-1.5]);
			translate([40,69,0])cube([stbre,20.5,11-0.21]);		// quer
			translate([47,69,0])cube([stbre,20.5,11-0.21]);		// quer
			
			
		}
	}

}

module SchnapperStuetzAussaprung(schnapperBreite,di)
{
			translate([-d-0.8,0,-7])cube([di,schnapperBreite,7]);		// z -0.01 wegen bug in Cura
			translate([-d+F5    ,0,-7])cube([di,schnapperBreite,5]);		// z -0.01 wegen bug in Cura
}

module AlleSchnapper(schnapperbreite)
{
		at = 2;  	// tiefe Aussparung
		ah = 2;   	// Hoehe Aussparung
		ab = schnapperbreite-1;  		// Breite Aussparung
		h = -4.75;	// Position Z
	  yd = 10;
	  y1 = mitteY - yd;
    y2 = mitteY + yd;

		translate([       0,y1  , h]) rotate([0,0,-90]) Schnapper(ab,at,ah);
		translate([  breite,y1, h]) rotate([0,0, 90]) Schnapper(ab,at,ah);
		translate([       0,y2  , h]) rotate([0,0,-90]) Schnapper(ab,at,ah);
		translate([  breite,y2, h]) rotate([0,0, 90]) Schnapper(ab,at,ah);
}

module Schnapper(ab,at,ah,ba=4)
{
	xa = 1;
	xb = d+1;
	ya = 2;
	yb = 8;
	//ba = 4;	// breite
	rotate([90,0,90]) translate([0,0,-ab/2])
	linear_extrude(height=ab,convexity=2)
	{
		polygon(points=[[xa,0],[0,ya],[xa,ya],[xa,yb],[xb-2,yb+2],[xb,yb-2],[xb,0]]);
	}
}

module RPLogo()
{
	h = 2;
  b = 10;		// Ellipsenbreite
  t = 6;		// Ellipsenhoehe
  l = 22;		// Strichlaenge
  fn = 40;
  d = 2;		// Liniendicke
	w = 40;
	l1 = (l - 2*t)/ cos(w) -d/2;
	difference()
	{
		scale([b,t,h])cylinder(r=1,h=1,$fn=fn);
		scale([b-d,t-d,h])cylinder(r=1,h=h,$fn=fn);
	}
	translate([0,t-l/2-0.1,h/2])cube([d,l,h],center=true);
	translate([d/2,-t,0])rotate([0,0,180-w])cube([d,l1,h]);

}