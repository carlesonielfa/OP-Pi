(
s.boot;
//LOAD ALL SYNTHS
//PathName.new("./supercollider/synths").filesDo{|sf| sf.asAbsolutePath.load};
//REBERB
SynthDef(\reverb, {|in, out, mix = 0.5, room = 0.15, damp = 0.5|
	var source = FreeVerb.ar(In.ar(in,2), mix, room, damp);
	Out.ar(out,source);
}).add;

SynthDef(\delay, {arg delaytime=0.5, in, out=0;
	var input, effect;
	input=In.ar(in,2); //get two channels of input starting (and ending) on bus 0
	effect= DelayN.ar(input, 1,delaytime); //max delay of one second
	Out.ar(out,effect); //adds to bus 0

}).add;

//CHANNEL ROUTER
SynthDef(\router, {
	arg in, out = 0;
	var source;
	source = In.ar(in,2);
	Out.ar(out, source);
}).add;

//ORGAN
SynthDef(\organ,{|out= 0 freq = 440 amp = 1 gate=1 lforate = 10 lfowidth= 0.0 cutoff= 100 rq=0.5 pan=0.0|

	var vibrato, pulse, filter, env;

	vibrato = SinOsc.ar(lforate,Rand(0,2.0));

	//better alternative
	pulse = Mix(VarSaw.ar(([1,1.9953843530485,3.0139733629359]*freq)*(1.0+(lfowidth*vibrato)),Rand(0.0,1.0)!3,Rand(0.3,0.5)!3,[1.0,0.7,0.3]))*0.5;

	filter = RLPF.ar(pulse,cutoff,rq);

	env = EnvGen.ar(Env.adsr(0.01,0.5,1.0,0.5),gate,doneAction:2);

	Out.ar(out,Pan2.ar(filter*env*10*amp,pan));

}).add;


//Wait for synthdefs to be loaded and server to initialize
Routine{
	10.wait;
	"Creating groups and OSCdefs".postln;
	~g_synth = Group.new(s);
	~g_fx = Group.after(~g_synth);
	~g_router = Group.after(~g_fx);


	~notes = Array.newClear(128);
	~bend = 0;
	~amp = 1;
	~preset = "organ";
	~max_synths = 2;
	~max_synths.do{arg synthn;
		var address = '/'++synthn.asString;

		var bus = Bus.audio(s, 2);
		var r = Synth.new(\router, [\in, bus], ~g_router);
		var reverb = Synth.new(\reverb, [\in, bus, \out, bus], ~g_fx);
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
}.play;
);
