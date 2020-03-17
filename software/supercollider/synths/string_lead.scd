//STRING LEAD
(
SynthDef(\string_lead,{|out= 0 freq = 440 amp = 1 gate=1 cutoff=8000 rq=0.8 lfowidth=0.01 lforate= 8 lagamount=0.01 pan=0.0|

	var pulse, filter, env, lfo;

	lfo = LFTri.kr(lforate,Rand(0,2.0)!2);

	pulse = Mix(Pulse.ar((freq.lag(lagamount))*[1,1.001]*(1.0+(lfowidth*lfo)),[0.2,0.19]))*0.5;

	filter =  RLPF.ar(pulse,cutoff,rq);

	//remove low end
	filter = BLowShelf.ar(filter,351,1.0,-9);

	env = EnvGen.ar(Env.adsr(0.01,0.0,0.9,0.05),gate,doneAction:2);

	Out.ar(out,Pan2.ar(filter*env*amp*0.75,pan));

}).add;

)