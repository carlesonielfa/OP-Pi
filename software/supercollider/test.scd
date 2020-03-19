(
    ~max_synths = 1;
    ~max_synths.do{arg synthn;
        (synthn.asString++'/bend').postln;
    };
)