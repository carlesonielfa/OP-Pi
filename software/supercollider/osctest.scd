(
s.boot;
~g_synth = Group.new(s);
~g_fx = Group.after(~g_synth);
~g_router = Group.after(~g_fx);

//LOAD ALL SYNTHS
PathName.new("./supercollider/synths").filesDo{|sf| sf.asAbsolutePath.load};

//CHANNEL ROUTER
SynthDef(\router, {
	arg in, out = 0;
	var source;
	source = In.ar(in);
	Out.ar(out, source);
}).add;

~notes = Array.newClear(128);
~bend = 0;
~amp = 1;
~preset = "organ";
~max_synths = 2;
~max_synths.do{arg synthn;
	var address = '/'++synthn.asString;

	var bus = Bus.audio(s);
	var r = Synth(\router, [\in, bus], ~g_router);
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
			]);
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