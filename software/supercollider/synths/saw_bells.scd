//SAW BELLS
(
SynthDef(\saw_bells,{|out= 0 freq = 440 amp = 1 gate=1 lforate = 10 lfowidth= 0.0 cutoff= 100 rq=0.5 pan=0.0|

	var osc1, osc2, vibrato, filter, env;

	vibrato = SinOsc.ar(lforate,Rand(0,2.0));

	osc1 = Saw.ar(freq*(1.0+(lfowidth*vibrato)),0.75);

	//Saw a bit rough, possibly slighter smoother:
	//osc1 = DPW4Saw.ar(freq*(1.0+(lfowidth*vibrato)),0.5);

	osc2 = Mix(LFTri.ar((freq.cpsmidi+[11.9,12.1]).midicps));

	//filter = (osc1+(osc2*0.5))*0.5; //no filter version
	filter = RHPF.ar((osc1+(osc2*0.5))*0.5,cutoff,rq);

	env = EnvGen.ar(Env.adsr(0.01,0.1,1.0,0.5),gate,doneAction:2);

	Out.ar(out,Pan2.ar(filter*env*amp,pan));

}).add;
)