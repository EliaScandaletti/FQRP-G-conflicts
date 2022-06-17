#!/usr/bin/sh

(
    cd src;

    make;

    ./parser/converter_main data/exh_filt_gen.out data/exh_filt_gen_;

    ./parser/converter_main data/exh_gen.out data/exh_gen_;

    ./parser/converter_main data/int_filt_gen.out data/int_filt_gen_;

    ./parser/converter_main data/rand_filt_gen.out data/rand_filt_gen_;
);

mkdir documenti/data;
mv src/data/*.dat documenti/data/;