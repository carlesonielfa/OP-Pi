//SHY ORGAN
(
SynthDef(\shy_organ,{|out= 0 freq = 440 amp = 1 gate=1 cutoff=8000 rq=0.8 pan=(-0.1)|

	var osc, filter, env;
	var basefreq =  ((freq.cpsmidi)+[0,0.1]).midicps;

	//osc = Mix(Blip.ar(basefreq,16))*0.5;

  	osc = Mix.fill(10,{|i| SinOsc.ar(basefreq*(i+1),0.0,(0.25+(0.75*LFNoise0.kr(10.1+i,0.5,0.5)))/(1.0+(0.5*i)))})*0.2;

	filter =  BLowPass.ar(osc,2000+(amp*cutoff),rq);

	env = EnvGen.ar(Env.adsr(0.02,0.1,0.9,1.0),gate,doneAction:2);

	Out.ar(out,Pan2.ar(Mix(filter)*env*amp,pan));

}).add;
)