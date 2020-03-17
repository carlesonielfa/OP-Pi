//FAKE STRINGS
(
SynthDef(\fake_strings,{|out= 0 freq = 440 amp = 1 gate=1 lforate = 5900 lfowidth= 0.01 cutoff= 12000 rq=0.5 pan=0.0|

	var lfo, saw, filter, env;

	lfo = LFTri.ar(lforate,Rand(0,2.0));

	saw = Saw.ar(freq*(1.0+(lfowidth*lfo)),0.5);

	//filter = BBandPass.ar(saw,freq,4);
	filter = BHiPass.ar(saw,freq,rq); 	//or using cutoff

	env = EnvGen.ar(Env.adsr(0.4,0.0,1.0,1.0),gate,doneAction:2);

	Out.ar(out,Pan2.ar(filter*env*amp,pan));

}).add;
)
