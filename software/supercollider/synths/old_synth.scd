//OLD SYNTH
(SynthDef(\old_synth,{|out= 0 freq = 440 amp = 1 gate=1 cutoff=8000 rq=0.8 lfowidth=0.001 lforate= 3.3 pan=(-0.1)|

	var pulse, filter, env, filterenv, lfo;

	lfo = LFTri.kr(lforate,Rand(0,2.0)!2);

	pulse = Mix(Pulse.ar((((freq.cpsmidi)+[0,0.14])+(lfo*lfowidth)).midicps,[0.5,0.51]+(lfowidth*lfo)))*0.5;

	filterenv = EnvGen.ar(Env([0.0,1.0,0.3,0.0],[0.005,0.57,0.1],-3));

	filter =  RLPF.ar(pulse,100+(filterenv*cutoff),rq);

	env = EnvGen.ar(Env.adsr(0.002,0.57,1.0,0.3),gate,doneAction:2);

	Out.ar(out,Pan2.ar(filter*env*amp*0.75,pan));

}).add;
)
