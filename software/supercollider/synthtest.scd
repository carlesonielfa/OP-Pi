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

OSCdef.new(
		"\\noteOn0",
		{
		arg msg, time, addr, port;
		msg.postln;
		~notes[msg[1]] = Synth.new(
			\organdonor,
			[
				\freq, msg[1].midicps,
				\gate, 1,
			]
		);},
		'/0/noteOn'
);
OSCdef.new(
		"\\noteOff0",
		{
		arg msg, time, addr, port;
		msg.postln;
		~notes[msg[1]].set(\gate,0);
		~notes[msg[1]] = nil;
		},
		'/0/noteOff'
);
//----------------------------------------------
//                  SYNTHS
//----------------------------------------------

//ORGAN

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