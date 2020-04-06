(
s.boot;
~g_synth = Group.new(s);
~g_fx = Group.after(~g_synth);
~g_router = Group.after(~g_fx);

//LOAD ALL SYNTHS
PathName.new("./supercollider/synths").filesDo{|sf| sf.asAbsolutePath.load};



~notes = Array.newClear(128);
~bend = 0;
~amp = 1;
~preset = "organ";
~max_synths = 2;
~max_synths.do{arg synthn;
	var address = '/'++synthn.asString;

	var bus = Bus.audio(s, 2);
	var r = Synth.new(\router, [\in, bus], ~g_router);
	OSCdef.new(
		"\\presetChange"++synthn.asString,
		{
			arg msg, time, addr, port;

			~preset = msg[1];
			~preset.postln;
		};,
		address++'/presetChange'
	);
	OSCdef.new(
		"\\pitchBend"++synthn.asString,
		{
			arg msg, time, addr, port;
			msg.postln;
			~bend = msg[1];
			~notes.do{arg synth; synth.set(\bend, ~bend)};
		};,
		address++'/pitchBend'
	);
	OSCdef.new(
		"\\ampChange"++synthn.asString,
		{
			arg msg, time, addr, port;
			msg.postln;
			~amp = msg[1];
			~notes.do{arg synth; synth.set(\amp, ~amp)};
		};,
		address++'/ampChange'
	);
	OSCdef.new(
		"\\noteOn"++synthn.asString,
		{
			arg msg, time, addr, port;
			msg.postln;
			~notes[msg[1]] = Synth.new(
			("\\"++~preset).interpret,
			[
				\out, bus,
				\freq, msg[1].midicps,
				\gate, 1,
				\bend, ~bend,
				\amp, ~amp
			], ~g_synth);
		},
		address++'/noteOn'
	);
	OSCdef.new(
		"\\noteOff"++synthn.asString,
		{
			arg msg, time, addr, port;
			msg.postln;
			~notes[msg[1]].set(\gate,0);
			~notes[msg[1]] = nil;
		},
		address++'/noteOff'
	);
};
)
(
//CHANNEL ROUTER
SynthDef(\router, {
	arg in, out = 0;
	var source;
	source = In.ar(in);
	Out.ar(out, source);
}).add;

//ORGAN

SynthDef(\organ,{|out= 0 freq = 440 amp = 1 gate=1 lforate = 10 lfowidth= 0.0 cutoff= 100 rq=0.5 pan=0.0|

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