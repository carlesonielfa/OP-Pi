//MOOG BASS
(SynthDef(\moog_bass,{|out= 0 freq = 440 amp = 1 gate=1 cutoff= 1000 gain=2.0 lagamount = 0.01 pan=0.0|

	var osc, filter, env, filterenv;

	osc = Mix(VarSaw.ar(freq.lag(lagamount)*[1.0,1.001,2.0],Rand(0.0,1.0)!3,Rand(0.5,0.75)!3,0.33));

	//alternative: richer source: see moogbasstone2 below
	//osc = Mix(Pulse.ar(freq.lag(lagamount)*[1.0,1.001,2.0],Rand(0.45,0.5)!3,0.33));

	filterenv = EnvGen.ar(Env.adsr(0.2,0.0,1.0,0.2),gate,doneAction:2);
	filter =  MoogFF.ar(osc,cutoff*(1.0+(0.5*filterenv)),gain);

	env = EnvGen.ar(Env.adsr(0.001,0.3,0.9,0.2),gate,doneAction:2);

	Out.ar(out,Pan2.ar((0.7*filter+(0.3*filter.distort))*env*amp*2,pan));

}).add;
)