//VOICE LEAD
(
SynthDef(\voice_lead,{|out= 0 freq = 440 amp = 0.1 gate=1 cutoff=8000 rq=0.2 pan=0.0|

	var pulse, filter, env, slavefreq;

	slavefreq = EnvGen.ar(Env([1,5,1],[0.04,0.9]))*freq;

	pulse = SyncSaw.ar(freq,slavefreq);

	filter = BLowPass.ar(pulse,cutoff,rq);

	env = EnvGen.ar(Env.adsr(0.01,0.0,1.0,0.1),gate,doneAction:2);

	Out.ar(out,Pan2.ar(filter*env*amp,pan));

}).add;

)