declare name 		"pitchShifter";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";

 //--------------------------------------
 // very simple real time pitch shifter
 //--------------------------------------

import("stdfaust.lib");

pitchshifter1 = vgroup("Pitch Shifter", ef.transpose(
									hslider("window1", 1000, 50, 10000, 1),
									hslider("xfade1", 10, 1, 10000, 1),
									hslider("shift1", 0, -12, +12, 0.1)
								  )
				);

pitchshifter2 = vgroup("Pitch Shifter", ef.transpose(
									hslider("window2", 1000, 50, 10000, 1),
									hslider("xfade2", 10, 1, 10000, 1),
									hslider("shift2", 0, -12, +12, 0.1)
								  )
				);

process = pitchshifter1, pitchshifter2;
