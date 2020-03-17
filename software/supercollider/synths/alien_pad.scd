//ALIEN PAD
(
SynthDef(\alienpad,{|out= 0 freq = 440 amp = 1 gate=1 lforate = 6 lfowidth= 0.5 cutoff= 4000 rq=0.25 lagTime=0.1 pan=0.0|

	var lfo, osc, filter, env;

	lfo = LFTri.kr(lforate+(LFNoise1.kr(5,0.3,0.3)),Rand(0,2.0));

	osc = Saw.ar((freq.lag(lagTime).cpsmidi+(lfo*lfowidth)).midicps,0.5);

	filter = BLowPass4.ar(osc,cutoff.lag(lagTime*4),rq);

	env = EnvGen.ar(Env.adsr(0.6,0.0,1.0,0.05),gate,doneAction:2);

	Out.ar(out,Pan2.ar(filter*env*amp.lag(lagTime*4)*0.75,pan));

}).add
)