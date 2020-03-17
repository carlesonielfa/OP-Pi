//INITIALIZE MIDI
(
s.boot;
MIDIClient.init;
MIDIIn.connectAll;
~notes = Array.newClear(128);

MIDIdef.noteOn(\noteOn, {
	arg vel, note, chan ,src;
	[note, vel]++" on".postln;
	~notes[note] = Synth.new(
		\organdonor,
		[
			\freq, note.midicps,
			\gate, 1,
		]
	);
});

MIDIdef.noteOff(\noteOff, {
	arg vel, note;
	[vel, note].postln;
	~notes[note].set(\gate,0);
	~notes[note] = nil;
});
)

//----------------------------------------------
//                  SYNTHS
//----------------------------------------------

//ORGAN
(
SynthDef(\organdonor,{|out= 0 freq = 440 amp = 1 gate=1 lforate = 10 lfowidth= 0.0 cutoff= 100 rq=0.5 pan=0.0|

	var vibrato, pulse, filter, env;

	vibrato = SinOsc.ar(lforate,Rand(0,2.0));

	//up octave, detune by 4 cents
	//11.96.midiratio = 1.9953843530485
	//up octave and a half, detune up by 10 cents
	//19.10.midiratio = 3.0139733629359

	//Pulse version
	//pulse = Mix(Pulse.ar(([1,1.9953843530485,3.0139733629359]*freq)*(1.0+(lfowidth*vibrato)),Rand(0.4,0.6)!3,[1.0,0.7,0.3]))*0.5;

	//better alternative
	pulse = Mix(VarSaw.ar(([1,1.9953843530485,3.0139733629359]*freq)*(1.0+(lfowidth*vibrato)),Rand(0.0,1.0)!3,Rand(0.3,0.5)!3,[1.0,0.7,0.3]))*0.5;

	filter = RLPF.ar(pulse,cutoff,rq);

	env = EnvGen.ar(Env.adsr(0.01,0.5,1.0,0.5),gate,doneAction:2);

	Out.ar(out,Pan2.ar(filter*env*10*amp,pan));

}).add;
)
//SAW BELLS
(
SynthDef(\trianglewavebells,{|out= 0 freq = 440 amp = 1 gate=1 lforate = 10 lfowidth= 0.0 cutoff= 100 rq=0.5 pan=0.0|

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
//MOOG BASS 2
(SynthDef(\moogbasstone2,{|out= 0 freq = 440 amp = 1 gate=1 attackTime= 0.2 fenvamount=0.5 cutoff= 1000 gain=2.0 pan=0.0|

	var osc, filter, env, filterenv;

	//alternative: richer source
	osc = Mix(Pulse.ar(freq.lag(0.05)*[1.0,1.001,2.0],Rand(0.45,0.5)!3,0.33));

	filterenv = EnvGen.ar(Env.adsr(attackTime,0.0,1.0,0.2),gate,doneAction:2);
	filter =  MoogFF.ar(osc,cutoff*(1.0+(fenvamount*filterenv)),gain);

	env = EnvGen.ar(Env.adsr(0.001,0.3,0.9,0.2),gate,doneAction:2);

	Out.ar(out,Pan2.ar((0.7*filter+(0.3*filter.distort))*env*amp*5,pan));

}).add;
)


//PROPHET5
(
SynthDef(\prophet5pwmstrings,{
	arg out=0, freq =440, amp=0.5, gate=1, lforate=10, lfowidth=0.5, cutoff=12000, rq=0.5, pan=0.0;
	var lfo, pulse, filter, env;

	lfo = LFTri.kr(lforate*[1,1.01],Rand(0,2.0)!2);
	pulse = Pulse.ar(freq*[1,1.01],lfo*lfowidth+0.5);
	filter = RLPF.ar(pulse,cutoff,rq);
	env = EnvGen.ar(Env.adsr(0.01,0.0,1.0,0.5),gate,doneAction:2);
	Out.ar(out,Pan2.ar(Mix(filter)*env*amp*0.5,pan));

}).add;
)

//MOOG BASS
(SynthDef(\moogbasstone,{|out= 0 freq = 440 amp = 1 gate=1 cutoff= 1000 gain=2.0 lagamount = 0.01 pan=0.0|

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

//LEAD
(
SynthDef(\mrostinato,{|out= 0 freq = 440 amp = 1 gate=1 lforate = 10 lfowidth= 0.5 pan = 0.0|

	var lfo, pulse, filter, env;

	lfo = LFTri.kr(lforate,Rand(0,2.0)!3);

	pulse = Pulse.ar(freq*[1,1.01,0.5],lfo*lfowidth+0.5);

	env = EnvGen.ar(Env.adsr(0.01,0.05,0.5,0.1),gate,doneAction:2);

	Out.ar(out,Pan2.ar(Mix(pulse)*env*amp,pan));

}).add
)

//STRINGS
(
SynthDef(\plastickystrings,{|out= 0 freq = 440 amp = 1 gate=1 lforate = 5900 lfowidth= 0.01 cutoff= 12000 rq=0.5 pan=0.0|

	var lfo, saw, filter, env;

	lfo = LFTri.ar(lforate,Rand(0,2.0));

	saw = Saw.ar(freq*(1.0+(lfowidth*lfo)),0.5);

	//filter = BBandPass.ar(saw,freq,4);
	filter = BHiPass.ar(saw,freq,rq); 	//or using cutoff

	env = EnvGen.ar(Env.adsr(0.4,0.0,1.0,1.0),gate,doneAction:2);

	Out.ar(out,Pan2.ar(filter*env*amp,pan));

}).add;
)

//HEAVY BASS
(
SynthDef(\bassfoundation,{|out= 0 freq = 440 amp = 1 gate=1 cutoff= 1000 rq=0.5 pan=0.0|

	var osc, filter, env, filterenv;

	osc = Saw.ar(freq);

	filterenv = EnvGen.ar(Env.adsr(0.0,0.5,0.2,0.2),gate,doneAction:2);
	filter =  RLPF.ar(osc,cutoff*filterenv+100,rq);

	env = EnvGen.ar(Env.adsr(0.01,0.0,0.9,0.05),gate,doneAction:2);

	Out.ar(out,Pan2.ar(filter*env*amp*2,pan));

}).add;
)

//STRING LEAD
(
SynthDef(\winwoodlead,{|out= 0 freq = 440 amp = 1 gate=1 cutoff=8000 rq=0.8 lfowidth=0.01 lforate= 8 lagamount=0.01 pan=0.0|

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
//VOICE LEAD
(

SynthDef(\synchronicity,{|out= 0 freq = 440 amp = 0.1 gate=1 cutoff=8000 rq=0.2 pan=0.0|

	var pulse, filter, env, slavefreq;

	slavefreq = EnvGen.ar(Env([1,5,1],[0.04,0.9]))*freq;

	pulse = SyncSaw.ar(freq,slavefreq);

	filter = BLowPass.ar(pulse,cutoff,rq);

	env = EnvGen.ar(Env.adsr(0.01,0.0,1.0,0.1),gate,doneAction:2);

	Out.ar(out,Pan2.ar(filter*env*amp,pan));

}).add;

)

//90s SYNTH
(SynthDef(\situationsynth,{|out= 0 freq = 440 amp = 1 gate=1 cutoff=8000 rq=0.8 lfowidth=0.001 lforate= 3.3 pan=(-0.1)|

	var pulse, filter, env, filterenv, lfo;

	lfo = LFTri.kr(lforate,Rand(0,2.0)!2);

	pulse = Mix(Pulse.ar((((freq.cpsmidi)+[0,0.14])+(lfo*lfowidth)).midicps,[0.5,0.51]+(lfowidth*lfo)))*0.5;

	filterenv = EnvGen.ar(Env([0.0,1.0,0.3,0.0],[0.005,0.57,0.1],-3));

	filter =  RLPF.ar(pulse,100+(filterenv*cutoff),rq);

	env = EnvGen.ar(Env.adsr(0.002,0.57,1.0,0.3),gate,doneAction:2);

	Out.ar(out,Pan2.ar(filter*env*amp*0.75,pan));

}).add;
)

//SQUARE
(
SynthDef(\ressquares,{|out= 0 freq = 440 amp = 0.1 gate=1 cutoff=8000 rq=0.8 pan=(-0.1)|

	var pulse, filter, env;

	//2 cents detune for second oscillator
	pulse = Mix(Pulse.ar( ((freq.cpsmidi)+[0,0.02]).midicps, 0.5))*0.5;

	filter =  BLowPass.ar(pulse,100+cutoff,rq);

	env = EnvGen.ar(Env.adsr(0.002,0.1,1.0,0.2),gate,doneAction:2);

	Out.ar(out,Pan2.ar(filter*env*amp,pan));

}).add;
)

//SHY ORGAN
(
SynthDef(\whoorgan,{|out= 0 freq = 440 amp = 1 gate=1 cutoff=8000 rq=0.8 pan=(-0.1)|

	var osc, filter, env;
	var basefreq =  ((freq.cpsmidi)+[0,0.1]).midicps;

	//osc = Mix(Blip.ar(basefreq,16))*0.5;

  	osc = Mix.fill(10,{|i| SinOsc.ar(basefreq*(i+1),0.0,(0.25+(0.75*LFNoise0.kr(10.1+i,0.5,0.5)))/(1.0+(0.5*i)))})*0.2;

	filter =  BLowPass.ar(osc,2000+(amp*cutoff),rq);

	env = EnvGen.ar(Env.adsr(0.02,0.1,0.9,1.0),gate,doneAction:2);

	Out.ar(out,Pan2.ar(Mix(filter)*env*amp,pan));

}).add;
)

//ALIEN HIT
(
SynthDef(\pwmbling,{|out= 0 freq = 440 amp = 1 gate=1 lforate = 4.85 lfowidth= 0.5 cutoff= 12000 rq=0.25 pan = 0.0|

	var lfo, pulse, filter, env;
	var basefreq =  ((freq.cpsmidi)+[0,12.12]).midicps;

	lfo = LFTri.kr(lforate*[1,1.01],Rand(0,2.0)!2);

	pulse = Pulse.ar(basefreq,lfo*lfowidth+0.5);

	env = EnvGen.ar(Env.adsr(0.0,1.0,0.2,1.5),gate,doneAction:2);

	filter = RLPF.ar(pulse,(cutoff*(env.squared))+100,rq);

	Out.ar(out,Pan2.ar(Mix(filter)*env*amp*0.75,pan));

}).add;
)

//ALIEN PAD
(
SynthDef(\spacetheremin,{|out= 0 freq = 440 amp = 1 gate=1 lforate = 6 lfowidth= 0.5 cutoff= 4000 rq=0.25 lagTime=0.1 pan=0.0|

	var lfo, osc, filter, env;

	lfo = LFTri.kr(lforate+(LFNoise1.kr(5,0.3,0.3)),Rand(0,2.0));

	osc = Saw.ar((freq.lag(lagTime).cpsmidi+(lfo*lfowidth)).midicps,0.5);

	filter = BLowPass4.ar(osc,cutoff.lag(lagTime*4),rq);

	env = EnvGen.ar(Env.adsr(0.6,0.0,1.0,0.05),gate,doneAction:2);

	Out.ar(out,Pan2.ar(filter*env*amp.lag(lagTime*4)*0.75,pan));

}).add
)
//FAST BASS
(
SynthDef(\fatvelocitybass,{|out= 0 freq = 440 amp = 1 gate=1 cutoff= 12000 rq=0.25 lagTime=0.01 pan = 0.0|

	var lfo, osc, filter, env;

	var basefreq =  ((freq.lag(lagTime).cpsmidi)+[0,11.95,31.03]).midicps;

	osc = Saw.ar(basefreq,[0.5,0.4,0.1]); //+PinkNoise.ar(Line.kr(1.0,0,0.03));

	env = EnvGen.ar(Env.adsr(0.01,1.0,1.0,0.25),gate,doneAction:2);

	filter = BLowPass4.ar(osc,100+((amp.squared)*(freq+cutoff)),rq);

	Out.ar(out,Pan2.ar(Mix(filter)*env*amp*0.75,pan));

}).add
)
//WOBBLEBOI
(
SynthDef(\singleoscillatorwobble,{|out= 0 freq = 440 amp = 1.0 gate=1 lforate = 10 lfowidth= 0.5 cutoff= 12000 rq=0.5 pan=0.0|

	var lfo, pulse, filter, env;

	lfo = LFTri.kr(lforate,Rand(0,2.0)!2);

	pulse = Pulse.ar(freq*(1.0+(lfowidth*lfo)),0.5);

	filter = RLPF.ar(pulse,cutoff,rq);

	env = EnvGen.ar(Env.adsr(0.01,0.0,1.0,0.5),gate,doneAction:2);

	Out.ar(out,Pan2.ar(filter*env*amp*0.5,pan));

}).add;
)




//----------------------------------------------
//                  FX
//----------------------------------------------

SynthDef(\chorus, {|out =0 gate= 1|
	var source = In.ar(out,2);
	var chorus;
	var env = Linen.kr(gate, 0.1, 1, 0.1, 2);

	chorus= Mix.fill(7, {

		var maxdelaytime= rrand(0.005,0.02);

		DelayC.ar(source, maxdelaytime,LFNoise1.kr(Rand(4.5,10.5),0.25*maxdelaytime,0.75*maxdelaytime) )

	});

	XOut.ar(out,env, chorus);

}).add;

